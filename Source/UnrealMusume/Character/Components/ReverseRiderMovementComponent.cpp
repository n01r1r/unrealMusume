#include "ReverseRiderMovementComponent.h"

#include "Components/SplineComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Character/RiderAnimInstance.h"
#include "Character/HorseCharacter.h"
#include "ReverseHorseMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UReverseRiderMovementComponent::UReverseRiderMovementComponent()
	: ThrowTime(0.f)
	, ThrowForwardImpulse(0.f)
	, ThrowUpImpulse(0.f)
	, ChangeMoveSpeed(1500.f)
	, IsChangeStart(false)
{

}

void UReverseRiderMovementComponent::Movement_Implementation(float DeltaTime)
{
	if (IsChangeStart == false)
	{
		Super::Movement_Implementation(DeltaTime);
	}
	else
	{
		RotateToHorse(DeltaTime);

		OwingCharacter->AddMovementInput(OwingCharacter->GetActorForwardVector(), 1.f);
	}
}

void UReverseRiderMovementComponent::BeThrown(FVector _Impulse)
{
	if (IsValid(OwingCharacter))
	{
		if (URiderAnimInstance* animInstance = Cast<URiderAnimInstance>(OwingCharacter->GetMesh()->GetAnimInstance()))
		{
			animInstance->SetIsRiding(false);
		}

		OwingCharacter->GetCharacterMovement()->AddImpulse(_Impulse, true);

		OwingCharacter->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		OwingCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Falling);

		FTimerHandle timerHandle;
		GetWorld()->GetTimerManager().SetTimer(timerHandle, [&]
			{
				OwingCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			},
			1.f,
			false);

		// Riding 애니메이션들이 기본적으로 Roll이 90도 회전되어 있어 다른 마네킹 애니메이션 사용할떄는 0도로 변경
		FRotator rot = OwingCharacter->GetMesh()->GetRelativeRotation();
		OwingCharacter->GetMesh()->SetRelativeRotation(FRotator(rot.Pitch, rot.Yaw, 0.f));

		OwingCharacter->LandedDelegate.AddDynamic(this, &UReverseRiderMovementComponent::OnLanded);
	}
}

void UReverseRiderMovementComponent::RidingHorse()
{
	ClearRandomTimer();
	SetComponentTickEnabled(false);

	if (URiderAnimInstance* animInstance = Cast<URiderAnimInstance>(OwingCharacter->GetMesh()->GetAnimInstance()))
	{
		animInstance->SetIsRiding(true);
	}

	IsChangeStart = false;

	OwingCharacter->AttachToActor(HorseCharacter, FAttachmentTransformRules::SnapToTargetIncludingScale);
	OwingCharacter->GetCharacterMovement()->StopMovementImmediately();
	OwingCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Flying);

	OwingCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FRotator rot = OwingCharacter->GetMesh()->GetRelativeRotation();
	OwingCharacter->GetMesh()->SetRelativeRotation(FRotator(rot.Pitch, rot.Yaw, 90.f));
}

void UReverseRiderMovementComponent::RotateToHorse(float _DeltaTime)
{
	FVector owingPawnLocation = OwingCharacter->GetActorLocation();

	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(owingPawnLocation, HorseCharacter->GetActorLocation());
	FRotator targetRotation = FMath::RInterpTo(OwingCharacter->GetActorRotation(), lookAtRotation, _DeltaTime, 10.f);
	targetRotation.Pitch = 0.f;

	OwingCharacter->SetActorRotation(targetRotation, ETeleportType::TeleportPhysics);
}

void UReverseRiderMovementComponent::ThrowHorse()
{
	if (IsValid(HorseCharacter) && IsValid(ReverseHorseMovementComponent))
	{
		FVector tangentDirection = TrackSplineComponent->FindTangentClosestToWorldLocation(OwingCharacter->GetActorLocation(), ESplineCoordinateSpace::World);
		tangentDirection.Normalize();

		FVector impulse = tangentDirection * ThrowForwardImpulse;
		impulse.Z = ThrowUpImpulse;
		ReverseHorseMovementComponent->BeThrown(impulse * SpeedRate);

		IsChangeStart = true;
		ClearRandomTimer();

		CharacterMovementComponent->MaxWalkSpeed = ChangeMoveSpeed * SpeedRate;
	}
}

void UReverseRiderMovementComponent::OnLanded(const FHitResult& _HitResult)
{
	SetComponentTickEnabled(true);
	StartRandomTimer();

	if (ReverseHorseMovementComponent)
	{
		ReverseHorseMovementComponent->RidingRider();
	}

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &UReverseRiderMovementComponent::ThrowHorse, ThrowTime, false);

	OwingCharacter->LandedDelegate.RemoveDynamic(this, &UReverseRiderMovementComponent::OnLanded);
}

void UReverseRiderMovementComponent::Init_Implementation()
{
	Super::Init_Implementation();

	ReverseHorseMovementComponent = HorseCharacter ? HorseCharacter->FindComponentByClass<UReverseHorseMovementComponent>() : nullptr;
}
