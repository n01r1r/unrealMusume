#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HorseCharacter.generated.h"

UCLASS()
class UNREALMUSUME_API AHorseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AHorseCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
