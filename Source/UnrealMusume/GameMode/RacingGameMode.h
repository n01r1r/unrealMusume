#pragma once

#include "Library/StructLibrary.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RacingGameMode.generated.h"

class UWorldEventBase;

UCLASS()
class UNREALMUSUME_API ARacingGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Instanced, Category = "Event")
	TArray<UWorldEventBase*> WorldEvents;

private:
	TArray<FMovementComponentData> MusumeMovementComponents;

public:
	ARacingGameMode();

	virtual void BeginPlay() override;

private:
	void ProcessSetMovementComponents();
};
