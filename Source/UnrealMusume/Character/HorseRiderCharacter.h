#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HorseRiderCharacter.generated.h"

UCLASS()
class UNREALMUSUME_API AHorseRiderCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AHorseRiderCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
