#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HorseMovementComponent.generated.h"

class ACharacter;
class USplineComponent;
class UCharacterMovementComponent;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMUSUME_API UHorseMovementComponent : public UActorComponent
{
	GENERATED_BODY()

private:
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
	UHorseMovementComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void Init();

	virtual void Init_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void Movement(float DeltaTime);

	virtual void Movement_Implementation(float DeltaTime);

private:
	void RotateToSpline(float _DeltaTime);
	float CalcRotationLerpSpeed(const FRotator& _LookAtRotation);
};
