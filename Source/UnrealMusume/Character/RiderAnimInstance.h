#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RiderAnimInstance.generated.h"

UCLASS()
class UNREALMUSUME_API URiderAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	APawn* RidingTarget;

protected:
	UPROPERTY(BlueprintReadOnly)
	float Speed;

	UPROPERTY(BlueprintReadOnly)
	float Direction;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
