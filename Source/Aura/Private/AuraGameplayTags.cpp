// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGameplayTags.h"
#include"GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;
void FAuraGameplayTags::InitializeNativeGameplayTags()
{
    //Secondary Attributes	
	GameplayTags.Attributes_Secondary_Armor=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),FString("Reduces damage taken, improves Block Chance"));

	GameplayTags.Attributes_Secondary_ArmorPenetration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"),FString("ArmorPenetration"));

	GameplayTags.Attributes_Secondary_BlockChance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"),FString("BlockChance"));
	GameplayTags.Attributes_Secondary_CriticalHitChance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"),FString("CriticalHitChance"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"),FString("CriticalHitDamage"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"),FString("CriticalHitResistance"));
	GameplayTags.Attributes_Secondary_HealthRegeneration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"),FString("HealthRegeneration"));
	GameplayTags.Attributes_Secondary_ManaRegeneration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"),FString("ManaRegeneration"));
	GameplayTags.Attributes_Secondary_MaxHealth=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),FString("MaxHealth"));
	GameplayTags.Attributes_Secondary_MaxMana=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"),FString("MaxMana"));

	//Vital Attributes
	GameplayTags.Attributes_Vital_Health=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"),FString("Health"));
	GameplayTags.Attributes_Vital_Mana=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"),FString("Mana"));

	//Primary Attributes

	GameplayTags.Attributes_Primary_Strength=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"),FString("Strength"));
	GameplayTags.Attributes_Primary_Intelligence=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"),FString("Intelligence"));
	GameplayTags.Attributes_Primary_Resistance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resistance"),FString("Resistance"));
	GameplayTags.Attributes_Primary_Vigor=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"),FString("Vigor"));
}

