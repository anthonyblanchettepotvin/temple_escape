// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#include "PuzzleComponent.h"


// Sets default values for this component's properties
UPuzzleComponent::UPuzzleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPuzzleComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	if (!Objective)
	{
		UE_LOG(LogTemp, Error, TEXT("PuzzleComponent on %s : Objective property is null."), *GetOwner()->GetName());
	}

	if (Conditions.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("PuzzleComponent on %s : Conditions property is empty."), *GetOwner()->GetName());
	}
}


// Called every frame
void UPuzzleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Objective || Conditions.Num() == 0) { return; }

	if (ConditionMet())
	{
		UnlockObjective();
	}
	else
	{
		LockObjective();
	}
}


bool UPuzzleComponent::ConditionMet()
{	
	if (Conditions.Num() == 0) { return true; }

	for (int32 i = 0; i < Conditions.Num(); i++)
	{
		if (!Conditions[i]->Evaluate()) { return false; }
	}
	
	return true;
}

void UPuzzleComponent::UnlockObjective()
{
	if (!Objective) { return; }
	
	Objective->Unlock();
}

void UPuzzleComponent::LockObjective()
{
	if (!Objective) { return; }
	
	Objective->Lock();
}
