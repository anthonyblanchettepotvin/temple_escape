// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#pragma once

#include "CoreMinimal.h"
#include "PuzzleCondition.h"
#include "Engine/TriggerVolume.h"
#include "WeightCondition.generated.h"


/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UWeightCondition : public UPuzzleCondition
{
	GENERATED_BODY()
	
public:
	UWeightCondition();
	~UWeightCondition();
	
	virtual bool Evaluate_Implementation() override;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* Trigger;
	
	UPROPERTY(EditAnywhere)
	float GoalMass = 0.0f;
};
