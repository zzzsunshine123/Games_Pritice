// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */

struct FAuraGameplayTags
{
public:
 static const FAuraGameplayTags& Get(){return GameplayTags;}

 static void InitializeNativeGameplayTags();
 //Secondart Attributes
 FGameplayTag Attributes_Secondary_Armor;
 FGameplayTag Attributes_Secondary_ArmorPenetration;
 FGameplayTag Attributes_Secondary_BlockChance;
 FGameplayTag Attributes_Secondary_CriticalHitChance;
 FGameplayTag Attributes_Secondary_CriticalHitDamage;
 FGameplayTag Attributes_Secondary_CriticalHitResistance;
 FGameplayTag Attributes_Secondary_HealthRegeneration;
 FGameplayTag Attributes_Secondary_ManaRegeneration;
 FGameplayTag Attributes_Secondary_MaxHealth;
 FGameplayTag Attributes_Secondary_MaxMana;

 FGameplayTag Attributes_Resistance_Fire;
 FGameplayTag Attributes_Resistance_Lightning;
 FGameplayTag Attributes_Resistance_Arcane;
 FGameplayTag Attributes_Resistance_Physical;

 //Vital Attributes
 FGameplayTag Attributes_Vital_Health;
 FGameplayTag Attributes_Vital_Mana;
 
 //Primary Attributes

 FGameplayTag Attributes_Primary_Strength;
 FGameplayTag Attributes_Primary_Intelligence;
 FGameplayTag Attributes_Primary_Resistance;
 FGameplayTag Attributes_Primary_Vigor;


 //Input Tags

 FGameplayTag InputTag_LMB;
 FGameplayTag InputTag_RMB;
 FGameplayTag InputTag_1;
 FGameplayTag InputTag_2;
 FGameplayTag InputTag_3;
 FGameplayTag InputTag_4;
 FGameplayTag InputTag_Passive_1;
 FGameplayTag InputTag_Passive_2;

 FGameplayTag Damage;

 FGameplayTag Damage_Fire;
 FGameplayTag Damage_Lightning;
 FGameplayTag Damage_Arcane;
 FGameplayTag Damage_Physical;

 FGameplayTag Abilities_None;
 
 FGameplayTag Abilities_Attack;
 FGameplayTag Abilities_Summon;

 	
 FGameplayTag Abilities_HitReact;

 FGameplayTag Abilities_Status_Locked;
 FGameplayTag Abilities_Status_Eligible;
 FGameplayTag Abilities_Status_Unlocked;
 FGameplayTag Abilities_Status_Equipped;

 FGameplayTag Abilities_Type_Offensive;
 FGameplayTag Abilities_Type_Passive;
 FGameplayTag Abilities_Type_None;
 
 FGameplayTag Abilities_Fire_FireBolt;
 FGameplayTag Abilities_Fire_FireBlast;
 FGameplayTag Abilities_Lightning_Electrocute;
 FGameplayTag Abilities_Arcane_ArcaneShards;

 FGameplayTag Ability_Passive_HaloOfProtection;
 FGameplayTag Ability_Passive_LifeSiphon;
 FGameplayTag Ability_Passive_ManaSiphon;

 
 FGameplayTag Cooldown_Fire_FireBolt;

 FGameplayTag Debuff_Burn;
 FGameplayTag Debuff_Stun;
 FGameplayTag Debuff_Physical;
 FGameplayTag Debuff_Arcane;
 FGameplayTag Debuff_Chance;
 FGameplayTag Debuff_Frequency;
 FGameplayTag Debuff_Damage;
 FGameplayTag Debuff_Duration;

 
 
 FGameplayTag CombatSocket_Weapon;
 FGameplayTag CombatSocket_RightHand;
 FGameplayTag CombatSocket_LeftHand;
 FGameplayTag CombatSocket_Tail;

 FGameplayTag Montage_Attack_1;
 FGameplayTag Montage_Attack_2;
 FGameplayTag Montage_Attack_3;
 FGameplayTag Montage_Attack_4;

 FGameplayTag Attributes_Meta_IncomingXP;
 
 TMap<FGameplayTag,FGameplayTag>DamageTypesToResistance;
 TMap<FGameplayTag,FGameplayTag>DamageTypesToDebuff;

 FGameplayTag Effects_HitReact;

 FGameplayTag Player_Block_InputPressed;
 FGameplayTag Player_Block_InputHeld;
 FGameplayTag Player_Block_InputReleased;
 FGameplayTag Player_Block_CursorTrace;

 FGameplayTag GameplayCue_FireBlast;
protected:
 static FAuraGameplayTags GameplayTags;
};
