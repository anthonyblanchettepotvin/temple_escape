// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorComponent.h"
#include "GameFramework/Actor.h"
#include "PuzzleCondition.h"
#include "PuzzleInterface.h"
#include "PuzzleDoorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UPuzzleDoorComponent : public UDoorComponent, public IPuzzleInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzleDoorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Interact() override;

	virtual bool ConditionsMet_Implementation() override;

	virtual void OnConditionsMet_Implementation() override;

	virtual void OnConditionsUnmet_Implementation() override;

private:
	UPROPERTY(Instanced, EditAnywhere)
	TArray<UPuzzleCondition*> Conditions;

	UPROPERTY(VisibleAnywhere)
	bool bUnlocked = false;
	
	UPROPERTY(VisibleAnywhere)
	bool bConditionsMet = false;
};
