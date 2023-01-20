// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* actor = GetAcceptableActor();
    if(actor != nullptr)
    {
        UPrimitiveComponent* component = Cast<UPrimitiveComponent>(actor->GetRootComponent());
        if(component != nullptr)
        {
            component->SetSimulatePhysics(false);
        }
        actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
        mover->SetShouldMove(true);
    }
    else
        mover->SetShouldMove(false);
}

void UTriggerComponent::SetMover(UMover* _newMover)
{
    mover = _newMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
    TArray<AActor *> actors;
    GetOverlappingActors(actors);

    for (AActor *_actor : actors)
    {
        if (_actor->ActorHasTag(acceptableActorTag) && !_actor->ActorHasTag("Grabbed"))
        {
            return _actor;
        }
    }
    return nullptr;
}
