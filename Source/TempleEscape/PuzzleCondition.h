// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#pragma once

#include "CoreMinimal.h"
#include "PuzzleConditionInterface.h"
#include "PuzzleCondition.generated.h"


/**
 * Abstract class for a puzzle condition.
 */
UCLASS( Abstract, EditInlineNew, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UPuzzleCondition : public UObject, public IPuzzleConditionInterface
{
	GENERATED_BODY()

public:
	UPuzzleCondition();
	~UPuzzleCondition();

	virtual bool Evaluate_Implementation() PURE_VIRTUAL(UPuzzleCondition::Evaluate_Implementation, return true;);
};
