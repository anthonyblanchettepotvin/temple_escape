// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle.h"
#include "PuzzleCondition.h"
#include "PuzzleReward.h"
#include "PuzzleTrigger.h"
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
	/** The puzzle conditions associated with the puzzle.
	 * @note All puzzle conditions must evaluate to true for the puzzle rewards to be unlocked.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Puzzle)
	TArray<AActor*> Conditions;

	/** The puzzle rewards associated with the puzzle.
	 * @note All puzzle conditions must evaluate to true for the puzzle rewards to be unlocked.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Puzzle)
	TArray<AActor*> Rewards;

	/** The puzzle trigger associated with the puzzle.
	 * @note If a puzzle trigger is specified, the puzzle conditions will be evaluated only when the trigger is triggered.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Puzzle)
	AActor* Trigger = nullptr;

	/** Whether or not the puzzle rewards should be unlocked permanently. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Puzzle)
	bool bUnlockRewardsPermanently = false;

	/** Whether or not the puzzle conditions are all met. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Puzzle)
	bool bConditionsMet = false;

	/** Whether or not debug messages should appear in the output log. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Puzzle, AdvancedDisplay)
	bool bDebug = false;

	/** Whether or not all the puzzle conditions' actor implements IPuzzleCondition. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Puzzle, AdvancedDisplay)
	bool bConditionsOK = false;

	/** Whether or not all the puzzle rewards' actor implements IPuzzleReward. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Puzzle, AdvancedDisplay)
	bool bRewardsOK = false;

	// Functions
	/** Check if all the puzzle conditions' actor implements IPuzzleCondition.
	 * @return True if all the puzzle conditions' actor implements IPuzzleCondition, false otherwise
	 * @note Also set bConditionsOK
	 */
	UFUNCTION(BlueprintCallable, Category=Puzzle)
	bool CheckConditionsImplementation();

	/** Check if all the puzzle rewards' actor implements IPuzzleReward.
	 * @return True if all the puzzle rewards' actor implements IPuzzleReward, false otherwise
	 * @note Also set bRewardsOK
	 */
	UFUNCTION(BlueprintCallable, Category=Puzzle)
	bool CheckRewardsImplementation();

	/** Unlock all the puzzle rewards. */
	UFUNCTION(BlueprintCallable, Category=Puzzle)
	void UnlockAllRewards();

	/** Lock all the puzzle rewards. */
	UFUNCTION(BlueprintCallable, Category=Puzzle)
	void LockAllRewards();

	/** Check the result of AreConditionsMet() and act based on its return value.
	 * 
	 * If AreConditionsMet() returns true, unlocks all the rewards and invoke OnConditionsMet().
	 * If AreConditionsMet() returns false, locks all the rewards and invoke OnConditionsUnmet().
	 */
	void ActOnConditionsMet();

	// IPuzzle implementation
	virtual bool AreConditionsMet_Implementation() override;

	virtual bool ConditionStateChanged_Implementation(AActor* Condition, bool State) override;

	virtual void OnConditionsMet_Implementation() override;

	virtual void OnConditionsUnmet_Implementation() override;

	virtual bool ReactToTrigger_Implementation() override;

	virtual bool SubscribeToTrigger_Implementation(UObject* Trigger) override;

	virtual bool UnsubscribeFromTrigger_Implementation(UObject* Trigger) override;
};
