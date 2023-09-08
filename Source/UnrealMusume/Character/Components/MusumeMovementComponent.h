#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MusumeMovementComponent.generated.h"

class ACharacter;
class USplineComponent;
class UCharacterMovementComponent;

UCLASS(Abstract)
class UNREALMUSUME_API UMusumeMovementComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USplineComponent* TrackSplineComponent;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ACharacter* OwingCharacter;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCharacterMovementComponent* CharacterMovementComponent;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Speed")
	FVector2D SpeedRandomValueRange;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Speed")
	float SpeedRandomValueChangeTime;

	FTimerHandle SpeedRandomValueTimerHandle;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rotation")
	FVector2D RotationRandomValueRange;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rotation")
	float RotationRandomValueChangeTime;

	UPROPERTY(BlueprintReadWrite)
	float RotationRandomValue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rotation")
	float RotationLerpSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rotation")
	float RotationCorrectionMinYawValue;

	FRotator TargetRotation;

	FTimerHandle RotationRandomValueTimerHandle;

public:
	UMusumeMovementComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void Init();

	virtual void Init_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void Movement(float DeltaTime);

	virtual void Movement_Implementation(float DeltaTime);

	void StartRandomTimer();
	void ClearRandomTimer();

private:
	void RotateToSpline(float _DeltaTime);
	float CalcRotationLerpSpeed(const FRotator& _LookAtRotation);
};
