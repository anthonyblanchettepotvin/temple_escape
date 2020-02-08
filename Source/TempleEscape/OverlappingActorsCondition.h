// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#pragma once

#include "CoreMinimal.h"
#include "PuzzleCondition.h"
#include "Engine/TriggerVolume.h"
#include "OverlappingActorsCondition.generated.h"


/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UOverlappingActorsCondition : public UPuzzleCondition
{
	GENERATED_BODY()

	virtual bool Evaluate_Implementation() override;
	
private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* Trigger;
	
	UPROPERTY(EditAnywhere)
	int32 GoalCount = 0;
};
