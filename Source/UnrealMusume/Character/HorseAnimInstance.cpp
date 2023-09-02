#include "HorseAnimInstance.h"

#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"

void UHorseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Owner = TryGetPawnOwner();
}

void UHorseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
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