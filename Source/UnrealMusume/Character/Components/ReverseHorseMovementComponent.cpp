#include "ReverseHorseMovementComponent.h"

#include "Components/SplineComponent.h"

#include "Character/RiderCharacter.h"
#include "Components/CapsuleComponent.h"
#include "ReverseRiderMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UReverseHorseMovementComponent::UReverseHorseMovementComponent()
	: ThrowTime(0.f)
	, ThrowForwardImpulse(0.f)
	, ThrowUpImpulse(0.f)
	, ChangeMoveSpeed(1500.f)
	, IsChangeStart(false)
{

}

void UReverseHorseMovementComponent::Movement_Implementation(float DeltaTime)
{
	if (IsChangeStart == false)
	{
		Super::Movement_Implementation(DeltaTime);
	}
	else
	{
		RotateToRider(DeltaTime);

		OwingCharacter->AddMovementInput(OwingCharacter->GetActorForwardVector(), 1.f);
	}
}

void UReverseHorseMovementComponent::RotateToRider(float _DeltaTime)
{
	FVector owingPawnLocation = OwingCharacter->GetActorLocation();

	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(owingPawnLocation, RiderCharacter->GetActorLocation());
	FRotator targetRotation = FMath::RInterpTo(OwingCharacter->GetActorRotation(), lookAtRotation, _DeltaTime, 10.f);
	targetRotation.Pitch = 0.f;

	OwingCharacter->SetActorRotation(targetRotation, ETeleportType::TeleportPhysics);
}

void UReverseHorseMovementComponent::ThrowRider()
{
	if (IsValid(RiderCharacter) && IsValid(ReverseRiderMovementComponent))
	{
		FVector tangentDirection = TrackSplineComponent->FindTangentClosestToWorldLocation(OwingCharacter->GetActorLocation(), ESplineCoordinateSpace::World);
		tangentDirection.Normalize();

		FVector impulse = tangentDirection * ThrowForwardImpulse;
		impulse.Z = ThrowUpImpulse;
		ReverseRiderMovementComponent->BeThrown(impulse);

		IsChangeStart = true;
		ClearRandomTimer();

		CharacterMovementComponent->MaxWalkSpeed = ChangeMoveSpeed;
	}
}

void UReverseHorseMovementComponent::OnLanded(const FHitResult& _HitResult)
{
	SetComponentTickEnabled(true);
	StartRandomTimer();

	if (ReverseRiderMovementComponent)
	{
		ReverseRiderMovementComponent->RidingHorse();
	}

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &UReverseHorseMovementComponent::ThrowRider, ThrowTime, false);

	OwingCharacter->LandedDelegate.RemoveDynamic(this, &UReverseHorseMovementComponent::OnLanded);
}

void UReverseHorseMovementComponent::BeThrown(FVector _Impulse)
{
	if (IsValid(OwingCharacter))
	{
		OwingCharacter->GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, OwingCharacter->GetMesh()->GetRelativeLocation().Z - 100.f));

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

		OwingCharacter->LandedDelegate.AddDynamic(this, &UReverseHorseMovementComponent::OnLanded);
	}
}

void UReverseHorseMovementComponent::RidingRider()
{
	ClearRandomTimer();
	SetComponentTickEnabled(false);

	IsChangeStart = false;

	OwingCharacter->AttachToActor(RiderCharacter, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("head"));
	OwingCharacter->GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, OwingCharacter->GetMesh()->GetRelativeLocation().Z + 100.f));
	OwingCharacter->GetCharacterMovement()->StopMovementImmediately();
	OwingCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Flying);

	OwingCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UReverseHorseMovementComponent::Init_Implementation()
{
	Super::Init_Implementation();

	ReverseRiderMovementComponent = RiderCharacter ? RiderCharacter->FindComponentByClass<UReverseRiderMovementComponent>() : nullptr;

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &UReverseHorseMovementComponent::ThrowRider, ThrowTime, false);
}
