#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RiderCharacter.generated.h"

class AHorseCharacter;

UCLASS()
class UNREALMUSUME_API ARiderCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
	AHorseCharacter* RidingTarget;

public:
	ARiderCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void AttachRiderToHorse();
};
