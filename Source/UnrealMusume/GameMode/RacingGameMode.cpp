#include "RacingGameMode.h"

#include "WorldEvent/WorldEventBase.h"
#include "Character/HorseCharacter.h"
#include "Character/RiderCharacter.h"
#include "Character/Components/HorseMovementComponent.h"
#include "Character/Components/RiderMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ARacingGameMode::ARacingGameMode()
{

}

void ARacingGameMode::BeginPlay()
{
	Super::BeginPlay();

	ProcessSetMovementComponents();
	
	for (UWorldEventBase* worldEvent : WorldEvents)
	{
		worldEvent->Start(MusumeMovementComponents);
	}
}

void ARacingGameMode::ProcessSetMovementComponents()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHorseCharacter::StaticClass(), actors);

	for (AActor* actor : actors)
	{
		UHorseMovementComponent* horseMovementComponent = actor->FindComponentByClass<UHorseMovementComponent>();

		URiderMovementComponent* riderMovementComponent = nullptr;
		if (horseMovementComponent)
		{
			if (ARiderCharacter* riderCharacter = horseMovementComponent->GetRiderCharacter())
			{
				riderMovementComponent = riderCharacter->FindComponentByClass<URiderMovementComponent>();
			}
		}

		FMovementComponentData movementData;
		movementData.HorseMovementComponent = horseMovementComponent;
		movementData.RiderMovementComponent = riderMovementComponent;

		MusumeMovementComponents.Add(movementData);
	}
}
