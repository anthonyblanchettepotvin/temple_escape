// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "PuzzleImplementation.h"

APuzzleImplementation::APuzzleImplementation()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APuzzleImplementation::BeginPlay()
{
	Super::BeginPlay();

	bConditionsOK = CheckConditionsImplementation();
	bRewardsOK = CheckRewardsImplementation();

	if (!bConditionsOK)
	{
		UE_LOG(LogTemp, Error, TEXT("APuzzleImplementation %s: Not all conditions implement IPuzzleCondition."), *GetName())
	}

	if (!bRewardsOK)
	{
		UE_LOG(LogTemp, Error, TEXT("APuzzleImplementation %s: Not all rewards implement IPuzzleReward."), *GetName())
	}
}

void APuzzleImplementation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bConditionsOK || !bRewardsOK) { return; }
	
	bool bConditionsMet = Execute_ConditionsMet(this);

	if (bConditionsMet && !bConditionsAlreadyMet)
	{
		// The conditions turned from met to unmet
		bConditionsAlreadyMet = true;
		Execute_OnConditionsMet(this);
		return;
	}

	if (!bConditionsMet && bConditionsAlreadyMet)
	{
		// The conditions turned from unmet to met
		bConditionsAlreadyMet = false;
		Execute_OnConditionsUnmet(this);
		return;
	}
}

bool APuzzleImplementation::CheckConditionsImplementation()
{
	for (AActor* Condition : Conditions)
	{
		if (!Condition->GetClass()->ImplementsInterface(UPuzzleCondition::StaticClass()))
		{
			return false;
		}
	}

	return true;	
}

bool APuzzleImplementation::CheckRewardsImplementation()
{
	for (AActor* Reward : Rewards)
	{
		if (!Reward->GetClass()->ImplementsInterface(UPuzzleReward::StaticClass()))
		{
			return false;
		}
	}

	return true;
}

void APuzzleImplementation::UnlockAllRewards()
{
	for (AActor* Reward : Rewards)
	{
		// We already know all the actors implement the necessary interface(s)
		IPuzzleReward::Execute_UnlockReward(Reward);
	}
}

void APuzzleImplementation::LockAllRewards()
{
	for (AActor* Reward : Rewards)
	{
		// We already know all the actors implement the necessary interface(s)
		IPuzzleReward::Execute_LockReward(Reward);
	}
}

bool APuzzleImplementation::ConditionsMet_Implementation()
{
	if (!bConditionsOK || !bRewardsOK) { return false; }

	for (AActor* Condition : Conditions)
	{
		// We already know all the actors implement the necessary interface(s)
		if (!IPuzzleCondition::Execute_Evaluate(Condition))
		{
			return false;
		}
	}

	return true;
}

void APuzzleImplementation::OnConditionsMet_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("APuzzleImplementation %s: OnConditionsMet event invoked."), *GetName())
	}

	UnlockAllRewards();
}

void APuzzleImplementation::OnConditionsUnmet_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("APuzzleImplementation %s: OnConditionsUnmet event invoked."), *GetName())
	}

	LockAllRewards();
}
