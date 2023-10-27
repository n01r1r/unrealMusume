#include "MusumeMovementComponent.h"

#include "Components/SplineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UMusumeMovementComponent::UMusumeMovementComponent()
	: SpeedRandomValueChangeTime(1.f)
	, SpeedRate(1.f)
	, RotationRandomValueChangeTime(3.f)
	, RotationRandomValue(0.f)
	, RotationLerpSpeed(5.f)
	, RotationCorrectionMinYawValue(10.f)
	, IsHorseMovement(true)
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> horseMoveCurveFloat_Banana(TEXT("/Script/Engine.CurveFloat'/Game/Musume/FloatCurve/HorseMoveCurveFloat_Banana.HorseMoveCurveFloat_Banana'"));
	if (horseMoveCurveFloat_Banana.Succeeded())
	{
		HorseMoveCurveFloat_Banana = horseMoveCurveFloat_Banana.Object;
	}
}

void UMusumeMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Init();


	check(HorseMoveCurveFloat_Banana != nullptr);
	FOnTimelineFloat HorseMoveCallback;
	FOnTimelineEventStatic HorseMoveFinishedCallback;

	HorseMoveCallback.BindUFunction(this, FName("HorseMove_Banana"));
	HorseMoveFinishedCallback.BindUFunction(this, FName("HorseMoveFinished_Banana"));

	HorseMoveCurveFTimeline_Banana.AddInterpFloat(HorseMoveCurveFloat_Banana, HorseMoveCallback);
	HorseMoveCurveFTimeline_Banana.SetTimelineFinishedFunc(HorseMoveFinishedCallback);
	HorseMoveCurveFTimeline_Banana.SetTimelineLength(2.0f);
}

void UMusumeMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HorseMoveCurveFTimeline_Banana.TickTimeline(DeltaTime);
	Movement(DeltaTime);
}

void UMusumeMovementComponent::Init_Implementation()
{
	TArray<AActor*> splineActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Spline"), splineActors);

	if (splineActors.IsEmpty() == false)
	{
		TrackSplineComponent = splineActors[0]->FindComponentByClass<USplineComponent>();
	}

	OwingCharacter = GetOwner<ACharacter>();
	CharacterMovementComponent = OwingCharacter ? OwingCharacter->GetCharacterMovement() : nullptr;

	check(OwingCharacter);
	check(CharacterMovementComponent);

	StartRandomTimer();
}

void UMusumeMovementComponent::Movement_Implementation(float DeltaTime)
{
	if (IsValid(TrackSplineComponent) == false || IsValid(OwingCharacter) == false)
	{
		return;
	}

	if (IsHorseMovement)
	{
		RotateToSpline(DeltaTime);
		OwingCharacter->AddMovementInput(OwingCharacter->GetActorForwardVector(), 1.f);
	}	
}

void UMusumeMovementComponent::StartRandomTimer()
{
	// 회전 랜덤 타이머 설정
	GetWorld()->GetTimerManager().SetTimer(RotationRandomValueTimerHandle, [&]
		{
			RotationRandomValue = FMath::FRandRange(RotationRandomValueRange.X, RotationRandomValueRange.Y);
		},
		RotationRandomValueChangeTime,
		true,
		0.f);

	// 이동속도 랜덤 타이머 설정
	GetWorld()->GetTimerManager().SetTimer(SpeedRandomValueTimerHandle, [&]
		{
			float randomSpeed = FMath::FRandRange(SpeedRandomValueRange.X, SpeedRandomValueRange.Y);
			CharacterMovementComponent->MaxWalkSpeed = randomSpeed * SpeedRate;
			CharacterMovementComponent->MaxFlySpeed = randomSpeed * SpeedRate;
		},
		SpeedRandomValueChangeTime,
		true,
		0.f);
}

void UMusumeMovementComponent::ClearRandomTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(RotationRandomValueTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(SpeedRandomValueTimerHandle);
}

void UMusumeMovementComponent::RotateToSpline(float _DeltaTime)
{
	FVector owingPawnLocation = OwingCharacter->GetActorLocation();

	FVector tangent = TrackSplineComponent->FindTangentClosestToWorldLocation(owingPawnLocation, ESplineCoordinateSpace::World);
	tangent.Normalize();
	tangent *= 2000.f;
	tangent += owingPawnLocation;

	FVector targetSplineLocation = TrackSplineComponent->FindLocationClosestToWorldLocation(tangent, ESplineCoordinateSpace::World);

	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(owingPawnLocation, targetSplineLocation);
	lookAtRotation.Yaw += RotationRandomValue;

	FRotator targetRotation = FMath::RInterpTo(OwingCharacter->GetActorRotation(), lookAtRotation, _DeltaTime, CalcRotationLerpSpeed(lookAtRotation));
	targetRotation.Pitch = 0.f;

	OwingCharacter->SetActorRotation(targetRotation, ETeleportType::TeleportPhysics);
}

float UMusumeMovementComponent::CalcRotationLerpSpeed(const FRotator& _LookAtRotation)
{
	// 스플라인에서 많이 벗어날수록 회전각에 가중치를 추가해 더 빠르게 회전하도록 처리

	FRotator deltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(_LookAtRotation, OwingCharacter->GetActorRotation());
	float deltaYaw = FMath::Abs(deltaRotation.Yaw);

	float lerpSpeed = RotationLerpSpeed;
	if (RotationCorrectionMinYawValue <= deltaYaw)
	{
		float correctionValue = deltaYaw - RotationCorrectionMinYawValue;
		correctionValue *= 0.1f;

		lerpSpeed = RotationLerpSpeed + (RotationLerpSpeed * correctionValue);
	}

	return lerpSpeed;
}

void UMusumeMovementComponent::SetSpeedRate(float _SpeedRate)
{
	SpeedRate = _SpeedRate;

	if (CharacterMovementComponent)
	{
		CharacterMovementComponent->MaxWalkSpeed *= _SpeedRate;
		CharacterMovementComponent->MaxFlySpeed *= _SpeedRate;
	}
}

void UMusumeMovementComponent::BananaEvent()
{
	if (IsValid(GetOwner()) == false)
	{
		return;
	}

	FirstHorseForwardVec = GetOwner()->GetActorForwardVector();

	//바나나에 미끄러지는 중엔 Movement 일시중지
	IsHorseMovement = false;

	// 회전 랜덤 타이머 설정
	GetWorld()->GetTimerManager().SetTimer(HorseRotatorTimerHandle_Banana, [&]
		{
			FRotator newRotator = FRotator(
				GetOwner()->GetActorRotation().Pitch,
				GetOwner()->GetActorRotation().Yaw + 30.0f,
				GetOwner()->GetActorRotation().Roll);

			GetOwner()->SetActorRotation(newRotator);
		},
		0.02f,
		true,
		0.f);

	HorseMoveCurveFTimeline_Banana.PlayFromStart();
}

void UMusumeMovementComponent::HorseMove_Banana(float _val)
{
	FVector newVector = FVector(
		GetOwner()->GetActorLocation() +
		FirstHorseForwardVec * _val * 10.0f);
	
	GetOwner()->SetActorLocation(newVector);
}

void UMusumeMovementComponent::HorseMoveFinished_Banana()
{
	HorseMoveCurveFTimeline_Banana.SetNewTime(0.0f);
	GetWorld()->GetTimerManager().ClearTimer(HorseRotatorTimerHandle_Banana);
	IsHorseMovement = true;
}
