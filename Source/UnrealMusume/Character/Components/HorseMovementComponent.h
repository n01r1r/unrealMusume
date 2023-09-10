#pragma once

#include "CoreMinimal.h"
#include "MusumeMovementComponent.h"
#include "HorseMovementComponent.generated.h"

class ARiderCharacter;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMUSUME_API UHorseMovementComponent : public UMusumeMovementComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Reverse")
	ARiderCharacter* RiderCharacter;

public:
	UHorseMovementComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE ARiderCharacter* GetRiderCharacter() const { return RiderCharacter; }
};
