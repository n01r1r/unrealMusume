#include "RiderCharacter.h"

#include "HorseCharacter.h"
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
		AttachToActor(RidingTarget, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SetOwner(RidingTarget);
	}
}

void ARiderCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}