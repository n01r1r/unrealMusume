#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StaticFunctionLibrary.generated.h"

UCLASS()
class UNREALMUSUME_API UStaticFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	template <class T>
	static void ShuffleArray(T& _Array)
	{
		const int32 lastIndex = _Array.Num() - 1;
		for (int32 i = 0; i < lastIndex; ++i)
		{
			int32 Index = FMath::RandRange(0, lastIndex);
			if (i != Index)
			{
				_Array.Swap(i, Index);
			}
		}
	}
};