#pragma once

#include "CoreMinimal.h"
#include "MusumeMovementComponent.h"
#include "RiderMovementComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMUSUME_API URiderMovementComponent : public UMusumeMovementComponent
{
	GENERATED_BODY()

public:	
	URiderMovementComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
