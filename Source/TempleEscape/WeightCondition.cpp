// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#include "WeightCondition.h"


UWeightCondition::UWeightCondition()
{
}


UWeightCondition::~UWeightCondition()
{
}


bool UWeightCondition::Evaluate_Implementation()
{
    float TotalMass = 0.0f;

    TArray<AActor*> OverlappingActors;
    this->Trigger->GetOverlappingActors(OverlappingActors);
    

    for (int32 i = 0; i < OverlappingActors.Num(); i++)
    {
        UE_LOG(LogTemp, Warning, TEXT("UWeightCondition : %s overlapping."), *OverlappingActors[i]->GetName());

        TotalMass += OverlappingActors[i]->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }

    return TotalMass >= GoalMass ? true : false;
}
