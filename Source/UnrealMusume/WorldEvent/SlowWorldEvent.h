#pragma once

#include "CoreMinimal.h"
#include "WorldEventBase.h"
#include "SlowWorldEvent.generated.h"

class USkeletalMeshComponent;

UCLASS()
class UNREALMUSUME_API USlowWorldEvent : public UWorldEventBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	FVector2D RandomTimeRange;	// X ~ Y 사이의 랜덤 시간마다 슬로우 이벤트 발생

	UPROPERTY(EditAnywhere)
	float ApplyTime;	// 슬로우의 지속 시간

	UPROPERTY(EditAnywhere)
	float SlowSpeedRate;	// 느려질 속도 비율 (0.4일 경우 40%만큼 느려진다.)

	UPROPERTY(EditAnywhere)
	int32 CountToExclude;	// 몇명을 제외하고 적용할 것인지. (1일 경우 1명을 제외하고 모두 슬로우 적용)

	TArray<FMovementComponentData> AllMovementComponents;

	TArray<FMovementComponentData> ActiveMovementComponents;
	TArray<USkeletalMeshComponent*> ActiveSkeletalMeshComponents;

	FTimerHandle SlowTimerHandle;
	FTimerHandle SlowEndTimerHandle;

public:
	USlowWorldEvent();

protected:
	virtual void Start_Implementation(const TArray<FMovementComponentData>& _MovementComponentData) override;

	void Slow();
	void SlowEnd();
};
