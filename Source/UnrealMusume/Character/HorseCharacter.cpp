#include "HorseCharacter.h"

AHorseCharacter::AHorseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHorseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHorseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}