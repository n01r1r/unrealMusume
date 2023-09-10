#pragma once

#include "CoreMinimal.h"
#include "HorseMovementComponent.h"
#include "ReverseHorseMovementComponent.generated.h"

class UReverseRiderMovementComponent;

UCLASS()
class UNREALMUSUME_API UReverseHorseMovementComponent : public UHorseMovementComponent
{
	GENERATED_BODY()
	
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

private:
	UPROPERTY()
	UReverseRiderMovementComponent* ReverseRiderMovementComponent;

public:
	UReverseHorseMovementComponent();

protected:
	virtual void Init_Implementation() override;
	virtual void Movement_Implementation(float DeltaTime) override;

public:
	void BeThrown(FVector _Impulse);
	void RidingRider();

private:
	void RotateToRider(float _DeltaTime);
	void ThrowRider();

	UFUNCTION()
	void OnLanded(const FHitResult& _HitResult);
};
