#include "RiderAnimInstance.h"

#include "RiderCharacter.h"
#include "HorseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

URiderAnimInstance::URiderAnimInstance()
	: Speed(0.f)
	, Direction(0.f)
	, IsFalling(false)
	, IsRiding(true)
{

}

void URiderAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	GetWorld()->GetTimerManager().SetTimerForNextTick([&]
		{
			RiderCharacter = Cast<ARiderCharacter>(TryGetPawnOwner());
			HorseCharacter = RiderCharacter ? RiderCharacter->GetOwner<AHorseCharacter>() : nullptr;
		});
}

void URiderAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(RiderCharacter) == false || IsValid(HorseCharacter) == false)
	{
		return;
	}

	Speed = HorseCharacter->GetVelocity().Length();

	FRotator deltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(HorseCharacter->GetVelocity().ToOrientationRotator(), HorseCharacter->GetControlRotation());
	Direction = deltaRotator.Yaw;

	if (UCharacterMovementComponent* movmenetComponent = RiderCharacter->GetCharacterMovement())
	{
		IsFalling = movmenetComponent->MovementMode == MOVE_Falling;
	}
}

void URiderAnimInstance::SetIsRiding(bool _IsRiding)
{
	IsRiding = _IsRiding;
}
