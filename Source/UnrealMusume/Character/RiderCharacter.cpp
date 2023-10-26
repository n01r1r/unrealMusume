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

	//기존 버젼에서는 RidingTarget을 에디터에서 직접 설정해줌으로 여기서 실행
	if (IsValid(RidingTarget))
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);

		AttachToActor(RidingTarget, FAttachmentTransformRules::SnapToTargetIncludingScale);
		SetOwner(RidingTarget);

		GetCapsuleComponent()->IgnoreActorWhenMoving(RidingTarget, true);
	}
}

void ARiderCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARiderCharacter::AttachRiderToHorse()
{	
	//스폰 형식에서는 BP에서 RidingTarget을 설정해줌으로 여기서 실행
	if (IsValid(RidingTarget))
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		AttachToActor(RidingTarget, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SetOwner(RidingTarget);

		GetCapsuleComponent()->IgnoreActorWhenMoving(RidingTarget, true);
	}
}