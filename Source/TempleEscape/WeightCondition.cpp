// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#include "WeightCondition.h"


UWeightCondition::UWeightCondition()
{
}


UWeightCondition::~UWeightCondition()
{
}


bool UWeightCondition::Evaluate()
{
    TArray<AActor*> OverlappingActors;
    this->Trigger->GetOverlappingActors(OverlappingActors);

    for (auto &&OverlappingActor : OverlappingActors)
    {
        UE_LOG(LogTemp, Warning, TEXT("UWeightCondition : %s overlapping."), *OverlappingActor->GetName());
    }

    return true;
}
