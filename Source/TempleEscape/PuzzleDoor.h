// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "Puzzle.h"
#include "PuzzleCondition.h"
#include "PuzzleDoor.generated.h"

/**
 * 
 */
UCLASS()
class TEMPLEESCAPE_API APuzzleDoor : public ADoor, public IPuzzle
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual bool Interact_Implementation() override;
	virtual bool ConditionsMet_Implementation() override;
	virtual void OnConditionsMet_Implementation() override;
	virtual void OnConditionsUnmet_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Conditions;
	TArray<AActor*> ValidConditions;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsUnlocked = false;
};
