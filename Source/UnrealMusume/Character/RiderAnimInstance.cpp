#include "RiderAnimInstance.h"

#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"

void URiderAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	GetWorld()->GetTimerManager().SetTimerForNextTick([&] { RidingTarget = TryGetPawnOwner()->GetOwner<APawn>(); });
}

void URiderAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(RidingTarget) == false)
	{
		return;
	}

	Speed = RidingTarget->GetVelocity().Length();

	FRotator deltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(RidingTarget->GetVelocity().ToOrientationRotator(), RidingTarget->GetControlRotation());
	Direction = deltaRotator.Yaw;
}