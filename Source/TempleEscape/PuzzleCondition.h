// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#pragma once

#include "CoreMinimal.h"
#include "PuzzleCondition.generated.h"


/**
 * Abstract class for a puzzle condition.
 */
UCLASS( Abstract, EditInlineNew, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UPuzzleCondition : public UObject
{
	GENERATED_BODY()

public:
	UPuzzleCondition();
	~UPuzzleCondition();

	virtual bool Evaluate() PURE_VIRTUAL(UPuzzleCondition::Evaluate, return true;);
};
