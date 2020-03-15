// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle.h"
#include "PuzzleCondition.h"
#include "PuzzleReward.h"
#include "PuzzleImplementation.generated.h"

UCLASS()
class TEMPLEESCAPE_API APuzzleImplementation : public AActor, public IPuzzle
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleImplementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Puzzle")
	TArray<AActor*> Conditions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Puzzle")
	TArray<AActor*> Rewards;
	// TODO: Implement triggers
	// UPROPERTY(EdotAnywhere, BlueprintReadWrite, Category="Puzzle")
	// AActor* Trigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Puzzle")
	bool bConditionsAlreadyMet = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Puzzle", AdvancedDisplay)
	bool bDebug = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Puzzle", AdvancedDisplay)
	bool bConditionsOK = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Puzzle", AdvancedDisplay)
	bool bRewardsOK = false;

	UFUNCTION(BlueprintCallable, Category="Puzzle")
	bool CheckConditionsImplementation();
	UFUNCTION(BlueprintCallable, Category="Puzzle")
	bool CheckRewardsImplementation();

	UFUNCTION(BlueprintCallable, Category="Puzzle")
	void UnlockAllRewards();
	UFUNCTION(BlueprintCallable, Category="Puzzle")
	void LockAllRewards();

	bool ConditionsMet_Implementation() override;
	void OnConditionsMet_Implementation() override;
	void OnConditionsUnmet_Implementation() override;
};
