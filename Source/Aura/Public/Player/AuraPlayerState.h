// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChanged,int32 /*StateValue*/)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLevelChanged,int32 /*StateValue*/,bool /*bLevelUp*/)
class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const  override;

	UAttributeSet* GetAttributeSet() const {return AttributeSet;}

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo>LevelUpInfo;
	
    FOnPlayerStateChanged OnXPChangedDelegate;
	FOnLevelChanged OnLevelChangedDelegate;
	FOnPlayerStateChanged OnAttributePointsChangedDelegate;
	FOnPlayerStateChanged OnSpellPointsChangedDelegate;
	
	int32 GetPlayerLevel()const;
	void SetLevel(int inLevel);

	void AddToLevel(int inLevel);
	
	void SetXP(int inXP);
	void AddToXP(int inXP);
	int32 GetXP();

	void SetAttributePoints(int inAttributesPoints);
	void AddToAttributePoints(int inAttributePoints);
	int32 GetAttributePoints();

	void SetSpellPoints(int inSpellPoints);
	void AddToSpellPoints(int inSpellPoints);
	int32 GetSpellPoints();
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:

	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_Level)
	int32 Level =1;
	
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_XP)
	int32 XP=0;

	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_AttributePoints)
	int32 AttributePoints=0;

	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_SpellPoints)
	int32 SpellPoints=1;
	
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_XP(int32 OldXP);

	UFUNCTION()
	void OnRep_AttributePoints(int32 OldAttributePoints);

	UFUNCTION()
	void OnRep_SpellPoints(int32 OldSpell);
	
};



