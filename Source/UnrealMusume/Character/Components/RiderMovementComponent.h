#pragma once

#include "CoreMinimal.h"
#include "MusumeMovementComponent.h"
#include "RiderMovementComponent.generated.h"

class AHorseCharacter;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMUSUME_API URiderMovementComponent : public UMusumeMovementComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	AHorseCharacter* HorseCharacter;

public:	
	URiderMovementComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE AHorseCharacter* GetHorseCharacter() const { return HorseCharacter; }
};
