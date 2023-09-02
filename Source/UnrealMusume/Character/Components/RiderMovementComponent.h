#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RiderMovementComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMUSUME_API URiderMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URiderMovementComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
