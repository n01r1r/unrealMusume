#pragma once

#include "CoreMinimal.h"
#include "MusumeMovementComponent.h"
#include "HorseMovementComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMUSUME_API UHorseMovementComponent : public UMusumeMovementComponent
{
	GENERATED_BODY()

public:
	UHorseMovementComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
