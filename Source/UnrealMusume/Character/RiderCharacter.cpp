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

	//���� ���������� RidingTarget�� �����Ϳ��� ���� ������������ ���⼭ ����
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
	//���� ���Ŀ����� BP���� RidingTarget�� ������������ ���⼭ ����
	if (IsValid(RidingTarget))
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		AttachToActor(RidingTarget, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SetOwner(RidingTarget);

		GetCapsuleComponent()->IgnoreActorWhenMoving(RidingTarget, true);
	}
}