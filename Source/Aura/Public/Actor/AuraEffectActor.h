// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"

#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class USphereComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemovel
};
UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect>GameplayEffectClass);
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	bool bDestroyOnEffectRemoval =false;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
    
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy= EEffectApplicationPolicy::DoNotApply;
    
   
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy= EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy= EEffectRemovalPolicy::RemoveOnEndOverlap;

	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	float ActorLevel =1.f;
    
};
