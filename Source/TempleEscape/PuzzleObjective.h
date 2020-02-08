// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#pragma once

#include "CoreMinimal.h"
#include "PuzzleObjectiveInterface.h"
#include "PuzzleObjective.generated.h"


/**
 * Abstract class for a puzzle objective.
 */
UCLASS( Abstract, EditInlineNew, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UPuzzleObjective : public UObject, public IPuzzleObjectiveInterface
{
	GENERATED_BODY()

public:
	UPuzzleObjective();
	~UPuzzleObjective();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
		bool Unlock();
	virtual bool Unlock_Implementation() override PURE_VIRTUAL(UPuzzleObjective::Unlock_Implementation, return true;);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
		bool Lock();
	virtual bool Lock_Implementation() override PURE_VIRTUAL(UPuzzleObjective::Lock_Implementation, return true;);
};
