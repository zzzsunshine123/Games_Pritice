// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayTags.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSpellGlobeSelectedSignature,bool,bSpellPointsButtonEnabled,bool,bEquipButtonEnabled,FString,DecsriptionString,FString,NextLevelDescription);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitForEquipSelectionSignature,const FGameplayTag& ,AbilityType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FspellGlobeReassignedSignature,const FGameplayTag& ,AbilityTag);
struct FSelectedAbility
{
	FGameplayTag Ability=FGameplayTag();
	FGameplayTag Status=FGameplayTag();
};
/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)

class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|SpellPoints")
	FOnPlayerStatChangedSignature SpellPointsDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FSpellGlobeSelectedSignature SpellGlobeSelectedDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FWaitForEquipSelectionSignature WaitForEquipDelegate;

	UPROPERTY(BlueprintAssignable)
	FWaitForEquipSelectionSignature StopWaitingForEquipDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FspellGlobeReassignedSignature  SpellGlobeReassignedDelegate;
	
	UFUNCTION(BlueprintCallable)
	void SpellGlobeSelected(const FGameplayTag& AbilityTag);
	
	UFUNCTION(BlueprintCallable)
	void SpellPointButtonPressed();
	
	UFUNCTION(BlueprintCallable)
    void GlobeDeselect();
	
	UFUNCTION(BlueprintCallable)
	void EquipButtonPressed();
	
	UFUNCTION(BlueprintCallable)
	void SpellRowGlobePressed(const FGameplayTag& SlotTag,const FGameplayTag& AbilityType);

	void OnAbilityEquipped(const FGameplayTag& AbilityTag,const FGameplayTag& Status,const FGameplayTag& Slot,const FGameplayTag& PreviousSlot);
private:
	static void ShouldEnableButton(const FGameplayTag& AbilityStatus,int32 SpellPoints,bool& bShouldEnableSpellPointsButton,bool& bShouldEnableEquipButton);

	FSelectedAbility SelectedAbility={FAuraGameplayTags::Get().Abilities_None,FAuraGameplayTags::Get().Abilities_Status_Locked};
	int32 CurrentSpellPoints=0;

	bool bWaitingForEquipSelection = true;

	FGameplayTag SelectedSlot;
};
