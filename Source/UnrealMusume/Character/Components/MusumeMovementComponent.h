#pragma once

#include "GameFramework/Character.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimeLineComponent.h"
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

	float SpeedRate;

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

	//말 기능 온오프
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ExecuteFunction(bool _IsFunctionOn);

	virtual void ExecuteFunction_Implementation(bool _IsFunctionOn){}

	void StartRandomTimer();
	void ClearRandomTimer();

private:
	void RotateToSpline(float _DeltaTime);
	float CalcRotationLerpSpeed(const FRotator& _LookAtRotation);

public:
	void SetSpeedRate(float _SpeedRate);

//바나나 밟았을때 관련 이벤트
private:
	FTimerHandle HorseRotatorTimerHandle_Banana;

	FTimeline HorseMoveCurveFTimeline_Banana;

	UCurveFloat* HorseMoveCurveFloat_Banana;

	FVector FirstHorseForwardVec;

	bool IsHorseMovement;

public:
	UFUNCTION(BlueprintCallable)
	void BananaEvent();

	UFUNCTION()
	void HorseMove_Banana(float _val);

	UFUNCTION()
	void HorseMoveFinished_Banana();
};
