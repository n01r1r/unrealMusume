#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RiderAnimInstance.generated.h"

class AHorseCharacter;
class ARiderCharacter;

UCLASS()
class UNREALMUSUME_API URiderAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	AHorseCharacter* HorseCharacter;

	UPROPERTY()
	ARiderCharacter* RiderCharacter;

protected:
	UPROPERTY(BlueprintReadOnly)
	float Speed;

	UPROPERTY(BlueprintReadOnly)
	float Direction;

	UPROPERTY(BlueprintReadOnly)
	bool IsFalling;

	UPROPERTY(BlueprintReadOnly)
	bool IsRiding;

public:
	URiderAnimInstance();

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	void SetIsRiding(bool _IsRiding);
};
