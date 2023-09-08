#include "RiderCharacter.h"

#include "HorseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ARiderCharacter::ARiderCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARiderCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);

	if (IsValid(RidingTarget))
	{
		AttachToActor(RidingTarget, FAttachmentTransformRules::SnapToTargetIncludingScale);
		SetOwner(RidingTarget);

		GetCapsuleComponent()->IgnoreActorWhenMoving(RidingTarget, true);
	}
}

void ARiderCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}