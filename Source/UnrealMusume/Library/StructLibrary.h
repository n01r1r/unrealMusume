#pragma once

#include "StructLibrary.generated.h"

class UHorseMovementComponent;
class URiderMovementComponent;

USTRUCT(BlueprintType)
struct FMovementComponentData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	UHorseMovementComponent* HorseMovementComponent;

	UPROPERTY(BlueprintReadOnly)
	URiderMovementComponent* RiderMovementComponent;
};