// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "AuraAttributeSet.generated.h"
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

template<class T>
using TAttributeFunPtr = typename TBaseStaticDelegateInstance<T,FDefaultDelegateUserPolicy>::FFuncPtr;
/**
 * 
 */
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties(){}
	
	FGameplayEffectContextHandle EffectContextHandle;
	UPROPERTY()
	AActor* SourceAvatarActor=nullptr;
	UPROPERTY()
	AController* SourceController=nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter =nullptr;
	UPROPERTY()
	UAbilitySystemComponent* SourceASC=nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor=nullptr;
	UPROPERTY()
	AController* TargetController=nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter =nullptr;
	UPROPERTY()
	UAbilitySystemComponent* TargetASC=nullptr;
};
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();
	virtual  void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual  void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual  void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	TMap<FGameplayTag,TAttributeFunPtr<FGameplayAttribute()> > TagsToAttributes;

	

	//Secondary Attributes
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Armor,Category="Secondary Atttibutes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Armor);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_ArmorPenetration,Category="Secondary Atttibutes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ArmorPenetration);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_BlockChance,Category="Secondary Atttibutes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,BlockChance);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_CriticalHitChance,Category="Secondary Atttibutes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitChance);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_CriticalHitDamage,Category="Secondary Atttibutes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitDamage);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_CriticalHitResistance,Category="Secondary Atttibutes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitResistance);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_HealthRegeneration,Category="Secondary Atttibutes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,HealthRegeneration);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_ManaRegeneration,Category="Secondary Atttibutes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ManaRegeneration);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxMana,Category="Secondary Atttibutes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxMana);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxHealth,Category="Secondray Atttibutes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth);

	//Resistance
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Resistance_Fire,Category="Resistance Atttibutes")
	FGameplayAttributeData Resistance_Fire;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Resistance_Fire);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Resistance_Lightning,Category="Resistance Atttibutes")
	FGameplayAttributeData Resistance_Lightning;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Resistance_Lightning);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Resistance_Arcane,Category="Resistance Atttibutes")
	FGameplayAttributeData Resistance_Arcane;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Resistance_Arcane);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Resistance_Physical,Category="Resistance Atttibutes")
	FGameplayAttributeData Resistance_Physical;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Resistance_Physical);
	
	
    //Strength Intelligence Resilience  Vigor
	//primary attributes
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Strength,Category="Primary Atttibutes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Strength);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Intelligence,Category="Primary Atttibutes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Intelligence);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Resilience ,Category="Primary Atttibutes")
	FGameplayAttributeData Resilience ;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Resilience );
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Vigor,Category="Primary Atttibutes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Vigor);

	 

	//vital attributes
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health,Category="Vital Atttibutes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Health);
	
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Mana,Category="Vital Atttibutes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Mana);

	//Meta Attributes

	UPROPERTY(BlueprintReadOnly,Category="Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,IncomingDamage);

	UPROPERTY(BlueprintReadOnly,Category="Meta Attributes")
	FGameplayAttributeData IncomingXP;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,IncomingXP);
	
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	UFUNCTION()
	void OnRep_Resistance_Fire(const FGameplayAttributeData& OldResistanceFire) const;

	UFUNCTION()
	void OnRep_Resistance_Lightning(const FGameplayAttributeData& OldResistanceLightning) const;

	UFUNCTION()
	void OnRep_Resistance_Arcane(const FGameplayAttributeData& OldResistanceArcane) const;
	
	UFUNCTION()
	void OnRep_Resistance_Physical(const FGameplayAttributeData& OldResistancePhysical) const;
	
private:
    void HandleIncomingDamage(const FEffectProperties& Props);
	void HandleIncomingXP(const FEffectProperties& Props);
	void Debuff(const FEffectProperties& Props);
	
	void SetEffectProperties(const FGameplayEffectModCallbackData&Data,FEffectProperties& Props)const;
	void ShowFloatingText(const FEffectProperties& Props,float Damage,bool bBlockedHit,bool bCriticalHit)const ;

	void SendXPEvent(const FEffectProperties& Props);

	bool bTopOffHealth=false;
	bool bTopOffMana=false;
};
