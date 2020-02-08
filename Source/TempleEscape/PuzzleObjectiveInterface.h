// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PuzzleObjectiveInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPuzzleObjectiveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TEMPLEESCAPE_API IPuzzleObjectiveInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
		bool Unlock();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
		bool Lock();
};
