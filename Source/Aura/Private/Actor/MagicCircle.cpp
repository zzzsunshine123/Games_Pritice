// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MagicCircle.h"
#include "Components/DecalComponent.h"
// Sets default values
AMagicCircle::AMagicCircle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    MagicCircleDecal=CreateDefaultSubobject<UDecalComponent>("MagicCircleDecal");\
    MagicCircleDecal->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AMagicCircle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagicCircle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

