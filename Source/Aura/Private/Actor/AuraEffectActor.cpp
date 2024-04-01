// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
    Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
	
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
		if(IAbilitySystemInterface * ASCIterface = Cast<IAbilitySystemInterface>(OtherActor))
		{
			//Change tihs to apply a Gameplay Effect
			const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(ASCIterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
			UAuraAttributeSet* MutableAttributeSet= const_cast<UAuraAttributeSet*>(AuraAttributeSet);
			MutableAttributeSet->SetHealth(AuraAttributeSet->GetHealth()+25.f);
			Destroy();
		}
	
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	 Sphere ->OnComponentBeginOverlap.AddDynamic(this,&AAuraEffectActor::OnOverlap);
	 Sphere -> OnComponentEndOverlap.AddDynamic(this,&AAuraEffectActor::EndOverlap);
}



