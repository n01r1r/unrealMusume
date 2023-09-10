#pragma once

#include "Library/StructLibrary.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorldEventBase.generated.h"

UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class UNREALMUSUME_API UWorldEventBase : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void Start(const TArray<FMovementComponentData>& _MovementComponentData);

protected:
	virtual void Start_Implementation(const TArray<FMovementComponentData>& _MovementComponentData) { };
};
