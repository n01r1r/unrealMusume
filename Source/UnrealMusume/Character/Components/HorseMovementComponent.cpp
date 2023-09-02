#include "HorseMovementComponent.h"

#include "GameFramework/Character.h"

#include "Components/SplineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UHorseMovementComponent::UHorseMovementComponent()
	: SpeedRandomValueChangeTime(1.f)
	, RotationRandomValueChangeTime(3.f)
	, RotationRandomValue(0.f)
	, RotationLerpSpeed(5.f)
	, RotationCorrectionMinYawValue(10.f)
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UHorseMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Init();
}

void UHorseMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Movement(DeltaTime);
}

void UHorseMovementComponent::Init_Implementation()
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

	// ȸ�� ���� Ÿ�̸� ����
	GetWorld()->GetTimerManager().SetTimer(RotationRandomValueTimerHandle, [&]
		{
			RotationRandomValue = FMath::FRandRange(RotationRandomValueRange.X, RotationRandomValueRange.Y);
		},
		RotationRandomValueChangeTime,
		true,
		0.f);

	// �̵��ӵ� ���� Ÿ�̸� ����
	GetWorld()->GetTimerManager().SetTimer(SpeedRandomValueTimerHandle, [&]
		{
			float randomSpeed = FMath::FRandRange(SpeedRandomValueRange.X, SpeedRandomValueRange.Y);
			CharacterMovementComponent->MaxWalkSpeed = randomSpeed;
		},
		SpeedRandomValueChangeTime,
		true,
		0.f);
}

void UHorseMovementComponent::Movement_Implementation(float DeltaTime)
{
	if (IsValid(TrackSplineComponent) == false || IsValid(OwingCharacter) == false)
	{
		return;
	}

	RotateToSpline(DeltaTime);

	OwingCharacter->AddMovementInput(OwingCharacter->GetActorForwardVector(), 1.f);
}

void UHorseMovementComponent::RotateToSpline(float _DeltaTime)
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

float UHorseMovementComponent::CalcRotationLerpSpeed(const FRotator& _LookAtRotation)
{
	// ���ö��ο��� ���� ������� ȸ������ ����ġ�� �߰��� �� ������ ȸ���ϵ��� ó��

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