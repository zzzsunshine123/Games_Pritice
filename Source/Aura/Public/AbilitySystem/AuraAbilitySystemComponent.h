// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags,const FGameplayTagContainer& /*AssetTags*/)
DECLARE_MULTICAST_DELEGATE(FAbilitiesGiven)
DECLARE_DELEGATE_OneParam(FForEachAbility,const FGameplayAbilitySpec&)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FAbilityStatusChanged,const FGameplayTag& /*AbilityTag*/,const FGameplayTag& /*StatusTag*/,const int32&/*AbilityLevel*/)
DECLARE_MULTICAST_DELEGATE_FourParams(FAbilityEquipped,const FGameplayTag&/*AbilityTag*/,const FGameplayTag&/*Status*/,const FGameplayTag&/*Slot*/,const FGameplayTag&/*previousSlot*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FDeactivatePassiveAbility,const FGameplayTag& /*AbilityTag*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FActivePassiveEffect,const FGameplayTag& /*AbilityTag*/,bool/*bActivate*/);

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;
	FAbilitiesGiven AbilitiesGivenDelegate;
	FAbilityStatusChanged AbilityStatusChanged;
	FAbilityEquipped AbilityEquipped;
	FDeactivatePassiveAbility DeactivatePassiveAbility;
	FActivePassiveEffect ActivePassiveEffect;
	
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities);
	bool bStartupAbilitiesGiven = false;

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagHeld(const FGameplayTag& InputTag);

	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ForEachAbility(const FForEachAbility& Delegate);

	 FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	 FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	 FGameplayTag GetStatusTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
     FGameplayTag GetstatusFromAbilityTag(const FGameplayTag& AbilityTag);
	 FGameplayTag GetInputTagFromAbilityTag(const FGameplayTag& AbilityTag);
     bool SoltIsEmpty(const FGameplayTag& Slot);
	 bool AbilityHasSlot (const FGameplayAbilitySpec& Spec,const FGameplayTag& Slot);
	 bool AbilityHasAnySlot(const FGameplayAbilitySpec& Spec);
	FGameplayAbilitySpec* GetSpecWithSlot(const FGameplayTag& Slot);
	bool IsPassiveAbility(const FGameplayAbilitySpec& Spec);

	void AssignSlotToAbility(FGameplayAbilitySpec& Spec,const FGameplayTag& Slot);

    UFUNCTION(NetMulticast,Unreliable)
	void MulticastActivatePassiveEffect(const FGameplayTag& AbilityTag,bool bActivate);
	
	FGameplayAbilitySpec* GetSpecFromAbilityTag(const FGameplayTag& AbilityTag);
;	void UpGradeAttribute(const FGameplayTag& AttributeTag);

	UFUNCTION(Server,Reliable)
	void ServerUpGradeAttribute(const FGameplayTag& AttributeTag);

	void UpdateAbilityStatus(int32 Level);

	UFUNCTION(Server,Reliable)
	void ServerSpendSpellPoint(const FGameplayTag& AbilityTag);
	
	UFUNCTION(Server,Reliable)
	void ServerEquipAbility(const FGameplayTag& AbilityTag,const FGameplayTag& slot);
	UFUNCTION(Client,Reliable)
	void ClientEquipAbility(const FGameplayTag& AbilityTag,const FGameplayTag& Status,const FGameplayTag& Slot,const FGameplayTag& PreviousSlot);
	bool GetDescriptionsByAbilityTag(const FGameplayTag& AbilityTag,FString& OutDescription,FString& OutNextLevelDescription);

	  void ClearSlot(FGameplayAbilitySpec* Spec);
	void ClearAbilitiesOfSlot(const FGameplayTag& Slot);
	 bool AbilityHasSlot(FGameplayAbilitySpec* Spec, const FGameplayTag& Slot);
protected:
	virtual void OnRep_ActivateAbilities() override;
	UFUNCTION(Client,Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent,const FGameplayEffectSpec& EffectSpec,FActiveGameplayEffectHandle ActiveEffectHandle);

	UFUNCTION(Client,Reliable)
	void ClientUpdateAbilityStatus(const FGameplayTag& AbilityTag,const FGameplayTag& StatusTag,int32 AbilityLevel);
};
