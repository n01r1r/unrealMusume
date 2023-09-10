#include "SlowWorldEvent.h"

#include "Character/Components/HorseMovementComponent.h"
#include "Character/Components/RiderMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Library/StaticFunctionLibrary.h"

USlowWorldEvent::USlowWorldEvent()
	: ApplyTime(0.f)
	, SlowSpeedRate(1.f)
	, CountToExclude(1)
{

}

void USlowWorldEvent::Slow()
{
	// AllMovementComponents를 랜덤으로 섞은 뒤 이동속도를 감소시키고 SkeletalMeshComponent의 GlobalAnimRateScale을 줄여 애니메이션 속도 감소
	ActiveMovementComponents.Empty(AllMovementComponents.Num() - CountToExclude);

	UStaticFunctionLibrary::ShuffleArray(AllMovementComponents);
	for (int i = 0; i < AllMovementComponents.Num() - CountToExclude; ++i)
	{
		ActiveMovementComponents.Add(AllMovementComponents[i]);

		float slowSpeed = 1.f - SlowSpeedRate;

		if (AllMovementComponents[i].HorseMovementComponent)
		{
			AllMovementComponents[i].HorseMovementComponent->SetSpeedRate(slowSpeed);

			if (USkeletalMeshComponent* skelComp = AllMovementComponents[i].HorseMovementComponent->GetOwner()->FindComponentByClass<USkeletalMeshComponent>())
			{
				skelComp->GlobalAnimRateScale = slowSpeed;
				ActiveSkeletalMeshComponents.Add(skelComp);
			}
		}

		if (AllMovementComponents[i].RiderMovementComponent)
		{
			AllMovementComponents[i].RiderMovementComponent->SetSpeedRate(slowSpeed);

			if (USkeletalMeshComponent* skelComp = AllMovementComponents[i].RiderMovementComponent->GetOwner()->FindComponentByClass<USkeletalMeshComponent>())
			{
				skelComp->GlobalAnimRateScale = slowSpeed;
				ActiveSkeletalMeshComponents.Add(skelComp);
			}
		}
	}

	GetWorld()->GetTimerManager().SetTimer(SlowEndTimerHandle, this, &USlowWorldEvent::SlowEnd, ApplyTime, false);
}

void USlowWorldEvent::SlowEnd()
{
	for (const FMovementComponentData& data : ActiveMovementComponents)
	{
		if (data.HorseMovementComponent)
		{
			data.HorseMovementComponent->SetSpeedRate(1.f);
		}

		if (data.RiderMovementComponent)
		{
			data.RiderMovementComponent->SetSpeedRate(1.f);
		}
	}

	for (USkeletalMeshComponent* skelComp : ActiveSkeletalMeshComponents)
	{
		skelComp->GlobalAnimRateScale = 1.f;
	}

	ActiveMovementComponents.Empty();
	ActiveSkeletalMeshComponents.Empty();

	float randTime = FMath::RandRange(RandomTimeRange.X, RandomTimeRange.Y);
	GetWorld()->GetTimerManager().SetTimer(SlowTimerHandle, this, &USlowWorldEvent::Slow, randTime, false);
}

void USlowWorldEvent::Start_Implementation(const TArray<FMovementComponentData>& _MovementComponentData)
{
	AllMovementComponents = _MovementComponentData;

	float randTime = FMath::RandRange(RandomTimeRange.X, RandomTimeRange.Y);
	GetWorld()->GetTimerManager().SetTimer(SlowTimerHandle, this, &USlowWorldEvent::Slow, randTime, false);
}