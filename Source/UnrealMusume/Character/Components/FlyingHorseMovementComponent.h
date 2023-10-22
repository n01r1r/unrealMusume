#pragma once

#include "CoreMinimal.h"
#include "HorseMovementComponent.h"
#include "FlyingHorseMovementComponent.generated.h"

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALMUSUME_API UFlyingHorseMovementComponent : public UHorseMovementComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Flying")
	float FlyingTargetZ;

	UPROPERTY(EditAnywhere, Category = "Flying")
	float ZInterpSpeed;

public:
	UFlyingHorseMovementComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
