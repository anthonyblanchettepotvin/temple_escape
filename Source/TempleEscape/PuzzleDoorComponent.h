// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "OpenDoor.h"
#include "PuzzleObjectiveInterface.h"
#include "PuzzleDoorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UPuzzleDoorComponent : public UOpenDoor, public IPuzzleObjectiveInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzleDoorComponent();

public:
	virtual void Interact() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
		bool Unlock();
	virtual bool Unlock_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
		bool Lock();
	virtual bool Lock_Implementation() override;

private:
	bool Unlocked = false;
};
