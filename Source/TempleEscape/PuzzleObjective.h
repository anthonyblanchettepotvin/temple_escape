// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#pragma once

#include "CoreMinimal.h"
#include "PuzzleObjective.generated.h"


/**
 * Abstract class for a puzzle objective.
 */
UCLASS( Abstract, EditInlineNew, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UPuzzleObjective : public UObject
{
	GENERATED_BODY()

public:
	UPuzzleObjective();
	~UPuzzleObjective();

	virtual void Unlock() PURE_VIRTUAL(UPuzzleObjective::Unlock,);
	virtual void Lock() PURE_VIRTUAL(UPuzzleObjective::Lock,);
};
