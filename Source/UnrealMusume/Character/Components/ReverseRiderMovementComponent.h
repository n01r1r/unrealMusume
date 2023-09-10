#pragma once

#include "CoreMinimal.h"
#include "RiderMovementComponent.h"
#include "ReverseRiderMovementComponent.generated.h"

class UReverseHorseMovementComponent;

UCLASS()
class UNREALMUSUME_API UReverseRiderMovementComponent : public URiderMovementComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	UReverseHorseMovementComponent* ReverseHorseMovementComponent;

protected:
	UPROPERTY(EditAnywhere, Category = "Reverse")
	float ThrowTime;

	UPROPERTY(EditAnywhere, Category = "Reverse")
	float ThrowForwardImpulse;

	UPROPERTY(EditAnywhere, Category = "Reverse")
	float ThrowUpImpulse;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Speed")
	float ChangeMoveSpeed;

	bool IsChangeStart;

public:
	UReverseRiderMovementComponent();

protected:
	virtual void Init_Implementation() override;
	virtual void Movement_Implementation(float DeltaTime) override;

public:
	void BeThrown(FVector _Impulse);
	void RidingHorse();

private:
	void RotateToHorse(float _DeltaTime);
	void ThrowHorse();

	UFUNCTION()
	void OnLanded(const FHitResult& _HitResult);
};
