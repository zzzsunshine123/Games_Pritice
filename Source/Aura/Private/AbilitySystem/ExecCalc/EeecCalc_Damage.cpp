// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/EeecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/AuraCharacter.h"
#include "Interaction/CombatInterface.h"


struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Fire);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Lightning);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Arcane);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Physical);


	TMap<FGameplayTag,FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,BlockChance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,ArmorPenetration,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitChance,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitDamage,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Resistance_Fire,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Resistance_Lightning,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Resistance_Arcane,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Resistance_Physical,Target,false);

		const auto& Tags=FAuraGameplayTags::Get();
		
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Armor,ArmorDef);\
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_ArmorPenetration,ArmorPenetrationDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_BlockChance,BlockChanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitChance,CriticalHitChanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitResistance,CriticalHitResistanceDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitDamage,CriticalHitDamageDef);

		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Fire,Resistance_FireDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Lightning,Resistance_LightningDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Arcane,Resistance_ArcaneDef);
		TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Physical,Resistance_PhysicalDef);
		
	}
	
};

static const AuraDamageStatics& Damagestatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}
UEeecCalc_Damage::UEeecCalc_Damage()
{
	RelevantAttributesToCapture.Add(Damagestatics().ArmorDef);
	RelevantAttributesToCapture.Add(Damagestatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(Damagestatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(Damagestatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(Damagestatics().CriticalHitResistanceDef);
	
	RelevantAttributesToCapture.Add(Damagestatics().Resistance_FireDef);
	RelevantAttributesToCapture.Add(Damagestatics().Resistance_LightningDef);
	RelevantAttributesToCapture.Add(Damagestatics().Resistance_ArcaneDef);
	RelevantAttributesToCapture.Add(Damagestatics().Resistance_PhysicalDef);
}

void UEeecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC=ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC=ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar=SourceASC?SourceASC->GetAvatarActor():nullptr;
	AActor* TargetAvatar=TargetASC?TargetASC->GetAvatarActor():nullptr;
	
	ICombatInterface* SourceCombatInterface=Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface=Cast<ICombatInterface>(TargetAvatar);
	
	const FGameplayEffectSpec& Spec =ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags=SourceTags;
	EvaluateParameters.TargetTags=TargetTags;

	//Get Damage Set by Caller Magnitude

	float Damage =0.f;
	for(auto& Pair:FAuraGameplayTags::Get().DamageTypesToResistance)
	{
		const FGameplayTag DamageTypeTag=Pair.Key;
		const FGameplayTag ResistanceTag=Pair.Value;
		checkf(AuraDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag),TEXT("TagsToCaptureDefs doesnot contain Tag: [%s] in EeeCalc_Damage"),*ResistanceTag.ToString())
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = AuraDamageStatics().TagsToCaptureDefs[ResistanceTag];
		
		 float DamageTypeValue=Spec.GetSetByCallerMagnitude(Pair.Key);
		
        float Resistance=0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef,EvaluateParameters,Resistance);
		Resistance=FMath::Clamp(Resistance,0.f,100.f);

		DamageTypeValue*=(100-Resistance)/100;
		Damage+=DamageTypeValue;
	}
	//Capture BlockChande from Target
	float TargetBlockChance=0.0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Damagestatics().BlockChanceDef,EvaluateParameters,TargetBlockChance);
	TargetBlockChance=FMath::Max<float>(TargetBlockChance,0.f);
 
	const bool bBlocked=FMath::RandRange(1,100)<TargetBlockChance;

	FGameplayEffectContextHandle EffectContextHandle =Spec.GetContext();

	UAuraAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle,bBlocked);
	bool test =UAuraAbilitySystemLibrary::IsBlockedHit(EffectContextHandle);
	//if block  halve the damage
	Damage=bBlocked?Damage/2.0f:Damage;

	//ArmorPenetration ignores a percentage of the target'Armor
	float TargetArmor=0.0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Damagestatics().ArmorDef,EvaluateParameters,TargetArmor);
	TargetArmor=FMath::Max<float>(TargetArmor,0.f);

	float SourceArmorPenetration=0.0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Damagestatics().ArmorPenetrationDef,EvaluateParameters,SourceArmorPenetration);
	SourceArmorPenetration=FMath::Max<float>(SourceArmorPenetration,0.f); 

	const UCharacterClassInfo* CharacterClassInfo=UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	const FRealCurve* ArmorPenetrationCurve= CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"),FString());
	const float ArmorPenetrationCoefficient=ArmorPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	
	const float EffectiveArmor=TargetArmor*=(100-SourceArmorPenetration*ArmorPenetrationCoefficient)/100;
	
	const FRealCurve* EffectiveArmorCurve= CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"),FString());
	const float EffectiveArmorCoefficient=EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	Damage*=(100-EffectiveArmor*EffectiveArmorCoefficient)/100.f;


	//暴击 和暴击概率减免
	float SourceCriticalHitChance=0.0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Damagestatics().CriticalHitChanceDef,EvaluateParameters,SourceCriticalHitChance);
	SourceCriticalHitChance=FMath::Max<float>(SourceCriticalHitChance,0.f);

	float TargetCriticalHitResistance=0.0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Damagestatics().CriticalHitResistanceDef,EvaluateParameters,TargetCriticalHitResistance);
	TargetCriticalHitResistance=FMath::Max<float>(TargetCriticalHitResistance,0.f);

	float SourceCriticalHitDamage=0.0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Damagestatics().CriticalHitDamageDef,EvaluateParameters,SourceCriticalHitDamage);
	SourceCriticalHitDamage=FMath::Max<float>(SourceCriticalHitDamage,0.f); 

	const FRealCurve* CriticalHitResistanceCurve= CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("CriticalHitResistance"),FString());
	const float CriticalHitResistanceCoefficent=CriticalHitResistanceCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	
	//暴击概率减免
	const float EffectiveCriticalHitChance=SourceCriticalHitChance-TargetCriticalHitResistance*CriticalHitResistanceCoefficent;
    //是否暴击
	const bool IsCriticalHit=FMath::RandRange(1,100)<EffectiveCriticalHitChance;
	UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle,IsCriticalHit);
	if(IsCriticalHit)
	{
		//暴击
		Damage=Damage*2.0+SourceCriticalHitDamage;
	}
	 

	
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive,Damage);

	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
