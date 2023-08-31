#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HorseRiderMovementComponent.generated.h"

class ACharacter;
class USplineComponent;
class UCharacterMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMUSUME_API UHorseRiderMovementComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USplineComponent* TrackSplineComponent;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ACharacter* OwingCharacter;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCharacterMovementComponent* CharacterMovementComponent;

protected:
	UPROPERTY(EditAnywhere, Category = "Speed")
	FVector2D SpeedRandomValueRange;

	UPROPERTY(EditAnywhere, Category = "Speed")
	float SpeedRandomValueChangeTime;

	FTimerHandle SpeedRandomValueTimerHandle;

protected:
	UPROPERTY(EditAnywhere, Category = "Rotation")
	FVector2D RotationRandomValueRange;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	float RotationRandomValueChangeTime;

	float RotationRandomValue;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	float RotationLerpSpeed;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	float RotationCorrectionMinYawValue;

	FRotator TargetRotation;

	FTimerHandle RotationRandomValueTimerHandle;

public:
	UHorseRiderMovementComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void RotateToSpline(float _DeltaTime);
	float CalcRotationLerpSpeed(const FRotator& _LookAtRotation);
};
