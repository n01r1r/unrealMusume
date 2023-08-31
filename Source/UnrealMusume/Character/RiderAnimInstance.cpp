#include "RiderAnimInstance.h"

#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"

void URiderAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = TryGetPawnOwner();
}

void URiderAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Owner) == false)
	{
		return;
	}

	Speed = Owner->GetVelocity().Length();

	FRotator deltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(Owner->GetVelocity().ToOrientationRotator(), Owner->GetControlRotation());
	Direction = deltaRotator.Yaw;
}