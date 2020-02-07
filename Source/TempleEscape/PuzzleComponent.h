// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzleCondition.h"
#include "PuzzleObjective.h"
#include "PuzzleComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UPuzzleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzleComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual bool ConditionMet();
	virtual void UnlockObjective();
	virtual void LockObjective();

private:
	UPROPERTY(Instanced, EditAnywhere) // TODO : This should not be Instanced, it should be the objective it self, from the scene.
	UPuzzleObjective* Objective;
	UPROPERTY(Instanced, EditAnywhere)
	TArray<UPuzzleCondition*> Conditions;
};
