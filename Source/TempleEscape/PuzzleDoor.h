// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "PuzzleInterface.h"
#include "PuzzleDoor.generated.h"

/**
 * 
 */
UCLASS()
class TEMPLEESCAPE_API APuzzleDoor : public ADoor, public IPuzzleInterface
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual bool Interact_Implementation() override;
	virtual bool ConditionsMet_Implementation() override;
	virtual void OnConditionsMet_Implementation() override;
	virtual void OnConditionsUnmet_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Conditions;

private:
	TArray<AActor*> ValidConditions;

	UPROPERTY(VisibleAnywhere)
	bool bIsUnlocked = false;
};
