// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const  override;

	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

     UPROPERTY(EditAnywhere,Category="Combat")
	 TObjectPtr<USkeletalMeshComponent>Weapon;
     UPROPERTY()
	 TObjectPtr<UAbilitySystemComponent> AbilitySystemCompoent;
     UPROPERTY()
	 TObjectPtr<UAttributeSet> AttributeSet;

	virtual  void InitAbilityActorInfo();
    UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attribute")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	void InitializePrimaryAttributes() const;
};
