#include "FlyingHorseMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

UFlyingHorseMovementComponent::UFlyingHorseMovementComponent()
	: FlyingTargetZ(300.f)
	, ZInterpSpeed(5.f)
{

}

void UFlyingHorseMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	OwingCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
}

void UFlyingHorseMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector start = OwingCharacter->GetActorLocation();
	FVector end = start + FVector(0.f, 0.f, -1000.f);

	FCollisionQueryParams params;
	params.AddIgnoredActor(OwingCharacter);

	FHitResult hitResult;
	bool isHit = GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_WorldStatic, params);
	if (isHit)
	{
		FVector target = UKismetMathLibrary::VInterpTo(OwingCharacter->GetActorLocation(), hitResult.ImpactPoint + FVector(0.f, 0.f, FlyingTargetZ), DeltaTime, ZInterpSpeed);
		OwingCharacter->SetActorLocation(target);
	}
}