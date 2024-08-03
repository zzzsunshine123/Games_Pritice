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

	//Input Tag

	GameplayTags.InputTag_LMB=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"),FString("Input Tag for Left Mouse Button"));
	GameplayTags.InputTag_RMB=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"),FString("Input Tag for Right Mouse Button"));
	GameplayTags.InputTag_1=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"),FString("Input Tag for key 1"));
	GameplayTags.InputTag_2=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"),FString("Input Tag for key 2"));
	GameplayTags.InputTag_3=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"),FString("Input Tag for key 3"));
	GameplayTags.InputTag_4=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"),FString("Input Tag for key 4"));
	GameplayTags.InputTag_Passive_1=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Passive.1"),FString("Input Tag for Passive 1"));
	GameplayTags.InputTag_Passive_2=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Passive.2"),FString("Input Tag for Passive 2"));
	
	GameplayTags.Damage=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"),FString("Damage"));

	//Damage Types
	GameplayTags.Damage_Fire=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Fire"),FString("Fire Damage type"));
	GameplayTags.Damage_Lightning=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Lightning"),FString("Lightning Damage type"));
	GameplayTags.Damage_Arcane=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Arcane"),FString("Arcane Damage type"));
	GameplayTags.Damage_Physical=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Physical"),FString("Physical Damage type"));


	//Damage Resistance
	GameplayTags.Attributes_Resistance_Fire=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Fire"),FString("Resistance to Fire Damage"));
	GameplayTags.Attributes_Resistance_Lightning=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Lightning"),FString("Resistance to Lightning Damage"));
	GameplayTags.Attributes_Resistance_Arcane=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Arcane"),FString("Resistance to Arcane Damage"));
	GameplayTags.Attributes_Resistance_Physical=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Physical"),FString("Resistance to Physical Damage"));


	//Debuff

	GameplayTags.Debuff_Burn=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Burn"),FString("Debuff for Fire Damage"));
	GameplayTags.Debuff_Arcane=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Arcane"),FString("Debuff for Arcane Damage"));
	GameplayTags.Debuff_Stun=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Stun"),FString("Debuff for Lightning Damage"));
	GameplayTags.Debuff_Physical=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Physical"),FString("Debuff for Physical Damage"));
	GameplayTags.Debuff_Chance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Chance"),FString("Debuff Chance"));
	GameplayTags.Debuff_Damage=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Damage"),FString("Debuff  Damage"));
	GameplayTags.Debuff_Frequency=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Frequency"),FString("Debuff Frequency"));
	GameplayTags.Debuff_Duration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Duration"),FString("Debuff Duration"));

	// Map of Damage Types to Debuff
	
	GameplayTags.DamageTypesToDebuff.Add(GameplayTags.Damage_Fire,GameplayTags.Debuff_Burn);
	GameplayTags.DamageTypesToDebuff.Add(GameplayTags.Damage_Lightning,GameplayTags.Debuff_Stun);
	GameplayTags.DamageTypesToDebuff.Add(GameplayTags.Damage_Physical,GameplayTags.Debuff_Physical);
	GameplayTags.DamageTypesToDebuff.Add(GameplayTags.Damage_Arcane,GameplayTags.Debuff_Arcane);

	// Map of Damage Types to Resistances
	
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Fire,GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Lightning,GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Arcane,GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Physical,GameplayTags.Attributes_Resistance_Physical);

	//Effects
	
	GameplayTags.Effects_HitReact=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"),FString("Effects_HitReact"));


    //Ability
	GameplayTags.Abilities_None=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.None"),FString("None Ability -like the nullptr for Ability Tag"));
	GameplayTags.Abilities_Attack=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack"),FString("Attack Ability Tag"));
	GameplayTags.Abilities_Summon=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Summon"),FString("Summon Ability Tag"));

	//Offensive ability
	GameplayTags.Abilities_Fire_FireBolt=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.FireBolt"),FString("FireBolt Ability Tag"));
	GameplayTags.Abilities_Fire_FireBlast=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.FireBlast"),FString("FireBlast Ability Tag"));
	GameplayTags.Abilities_Lightning_Electrocute=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Lightning.Electrocute"),FString("Electrocute Ability Tag"));
	GameplayTags.Abilities_Arcane_ArcaneShards=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Arcane.ArcaneShards"),FString("Arcane  Ability Tag"));

	//Passive ability
	GameplayTags.Ability_Passive_LifeSiphon=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Passive.LifeSiphon"),FString("Abilities Passive LifeSiphon"));
	GameplayTags.Ability_Passive_ManaSiphon=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Passive.ManaSiphon"),FString("Abilities Passive ManaSiphon"));
	GameplayTags.Ability_Passive_HaloOfProtection=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Passive.HaloOfProtection"),FString("Abilities Passive HaloOfProtection"));
	
	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.HitReact"),FString("Hit React Ability"));
	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Eligible"),FString("Eligible Status"));
	GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Equipped"),FString("Equipped Status"));
	GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Locked"),FString("Locked Status"));
	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Unlocked"),FString("Unlocked Status"));
	GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.None"),FString("Type None"));
	GameplayTags.Abilities_Type_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Offensive"),FString("Type Offensive"));
	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Passive"),FString("Type Passive"));

	//CoolDown
	GameplayTags.Cooldown_Fire_FireBolt=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"),FString("Fire Cooldown Tag"));	
	//CombatSocket
	GameplayTags.CombatSocket_Weapon=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Weapon"),FString("Weapon"));
	GameplayTags.CombatSocket_RightHand=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.RightHand"),FString("RightHand"));
	GameplayTags.CombatSocket_LeftHand=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.LeftHand"),FString("LeftHand"));
	GameplayTags.CombatSocket_Tail=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Tail"),FString("Tail"));


	//Montage

	GameplayTags.Montage_Attack_1=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.1"),FString("Attack 1"));
	GameplayTags.Montage_Attack_2=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.2"),FString("Attack 2"));
	GameplayTags.Montage_Attack_3=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.3"),FString("Attack 3"));
	GameplayTags.Montage_Attack_4=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.4"),FString("Attack 4"));

	//Meta Attribute

	GameplayTags.Attributes_Meta_IncomingXP=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Meta.IncomingXP"),FString("Incoming XP Attribute"));


	//Player Block Tags
	GameplayTags.Player_Block_InputPressed=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputPressed"),FString("Block Input Pressed callback for input"));
	GameplayTags.Player_Block_InputHeld=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputHeld"),FString("Block Input Held callback for input"));
	GameplayTags.Player_Block_InputReleased=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputReleased"),FString("Block Input Released callback for input"));
	GameplayTags.Player_Block_CursorTrace=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.CursorTrace"),FString("Block Tracing under the cursor"));


	//GameplayCue

	GameplayTags.GameplayCue_FireBlast=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayCue.FireBlast"),FString("FireBlast GameplayCue"));
	
}

