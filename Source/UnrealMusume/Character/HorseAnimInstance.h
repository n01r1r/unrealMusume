#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HorseAnimInstance.generated.h"

class APawn;

UCLASS()
class UNREALMUSUME_API UHorseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	APawn* Owner;

protected:
	UPROPERTY(BlueprintReadOnly)
	float Speed;

	UPROPERTY(BlueprintReadOnly)
	float Direction;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
