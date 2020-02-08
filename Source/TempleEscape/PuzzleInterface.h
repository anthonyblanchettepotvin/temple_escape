// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PuzzleInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPuzzleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class TEMPLEESCAPE_API IPuzzleInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
		bool ConditionsMet();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
		void OnConditionsMet();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
		void OnConditionsUnmet();
};
