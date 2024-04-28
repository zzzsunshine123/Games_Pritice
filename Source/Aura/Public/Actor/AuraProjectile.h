// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AuraProjectile.generated.h"

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraProjectile();
	UPROPERTY(VisibleAnywhere)
    TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
};
