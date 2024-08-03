// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/EeecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/AuraCharacter.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"


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
	RelevantAttributesToCapture.Add(Damagestatics().CriticalHitDamageDef);
	
	RelevantAttributesToCapture.Add(Damagestatics().Resistance_FireDef);
	RelevantAttributesToCapture.Add(Damagestatics().Resistance_LightningDef);
	RelevantAttributesToCapture.Add(Damagestatics().Resistance_ArcaneDef);
	RelevantAttributesToCapture.Add(Damagestatics().Resistance_PhysicalDef);
}

void UEeecCalc_Damage::DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams, const FGameplayEffectSpec& Spec, FAggregatorEvaluateParameters EvaluateParameters,
	  TMap<FGameplayTag,FGameplayEffectAttributeCaptureDefinition> InTagsToDefs) const
{
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();

	for (TTuple<FGameplayTag, FGameplayTag> Pair : GameplayTags.DamageTypesToDebuff)
	{
		const FGameplayTag& DamageType = Pair.Key;
		const FGameplayTag& DebuffType = Pair.Value;
		const float TypeDamage = Spec.GetSetByCallerMagnitude(DamageType, false, -1.f);
		if (TypeDamage > -.5f) // .5 padding for floating point [im]precision
		{
			// Determine if there was a successful debuff
			const float SourceDebuffChance = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Chance, false, -1.f);

			float TargetDebuffResistance = 0.f;
			const FGameplayTag& ResistanceTag = GameplayTags.DamageTypesToResistance[DamageType];
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(InTagsToDefs[ResistanceTag], EvaluateParameters, TargetDebuffResistance);
			TargetDebuffResistance = FMath::Max<float>(TargetDebuffResistance, 0.f);
			const float EffectiveDebuffChance = SourceDebuffChance * ( 100 - TargetDebuffResistance ) / 100.f;
			const bool bDebuff = FMath::RandRange(1, 100) < EffectiveDebuffChance;
			if (bDebuff)
			{
				FGameplayEffectContextHandle ContextHandle = Spec.GetContext();

				UAuraAbilitySystemLibrary::SetIsSuccessfulDebuff(ContextHandle, true);
				UAuraAbilitySystemLibrary::SetDamageType(ContextHandle, DamageType);

				const float DebuffDamage = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Damage, false, -1.f);
				const float DebuffDuration = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Duration, false, -1.f);
				const float DebuffFrequency = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Frequency, false, -1.f);

				UAuraAbilitySystemLibrary::SetDebuffDamage(ContextHandle, DebuffDamage);
				UAuraAbilitySystemLibrary::SetDebuffDuration(ContextHandle, DebuffDuration);
				UAuraAbilitySystemLibrary::SetDebuffFrequency(ContextHandle, DebuffFrequency);
			}
		}
	}
}

void UEeecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput
                                            ) const
{
	TMap<FGameplayTag,FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	const FAuraGameplayTags& Tags=FAuraGameplayTags::Get();
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Armor,Damagestatics().ArmorDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_ArmorPenetration,Damagestatics().ArmorPenetrationDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_BlockChance,Damagestatics().BlockChanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitChance,Damagestatics().CriticalHitChanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitResistance,Damagestatics().CriticalHitResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitDamage,Damagestatics().CriticalHitDamageDef);

	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Fire,Damagestatics().Resistance_FireDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Lightning,Damagestatics().Resistance_LightningDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Arcane,Damagestatics().Resistance_ArcaneDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Physical,Damagestatics().Resistance_PhysicalDef);
	
	const UAbilitySystemComponent* SourceASC=ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC=ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar=SourceASC?SourceASC->GetAvatarActor():nullptr;
	AActor* TargetAvatar=TargetASC?TargetASC->GetAvatarActor():nullptr;

	int32 SourcePlayerLevel=1;
	if(SourceAvatar->Implements<UCombatInterface>())
	{
		SourcePlayerLevel=ICombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}
	int32 TargetPlayerLevel=1;
	if(SourceAvatar->Implements<UCombatInterface>())
	{
		TargetPlayerLevel=ICombatInterface::Execute_GetPlayerLevel(TargetAvatar);
	}

	
	const FGameplayEffectSpec& Spec =ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle EffectContextHandle =Spec.GetContext();
	
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags=SourceTags;
	EvaluateParameters.TargetTags=TargetTags;

	//Debuff

	DetermineDebuff(ExecutionParams, Spec, EvaluateParameters,TagsToCaptureDefs);
	
	//Get Damage Set by Caller Magnitude

	float Damage =0.f;
	for(auto& Pair:FAuraGameplayTags::Get().DamageTypesToResistance)
	{
		const FGameplayTag DamageTypeTag=Pair.Key;
		const FGameplayTag ResistanceTag=Pair.Value;
		checkf(TagsToCaptureDefs.Contains(ResistanceTag),TEXT("TagsToCaptureDefs doesnot contain Tag: [%s] in EeeCalc_Damage"),*ResistanceTag.ToString())
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = TagsToCaptureDefs[ResistanceTag];
		
		 float DamageTypeValue=Spec.GetSetByCallerMagnitude(Pair.Key,false);
		
        float Resistance=0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef,EvaluateParameters,Resistance);
		Resistance=FMath::Clamp(Resistance,0.f,100.f);

		DamageTypeValue*=(100-Resistance)/100;


         if(UAuraAbilitySystemLibrary::IsRadialDamage(EffectContextHandle))
         {
	         if(ICombatInterface* CombatInterface =Cast<ICombatInterface>(TargetAvatar))
	         {
		         CombatInterface->GetOnDamageSignature().AddLambda([&](float DamageAmount)
		         {
			         DamageTypeValue=DamageAmount;
		         });
	         }

         	UGameplayStatics::ApplyRadialDamageWithFalloff(TargetAvatar,DamageTypeValue,0.f,
         		UAuraAbilitySystemLibrary::GetRadialOrigin(EffectContextHandle),
                 UAuraAbilitySystemLibrary::GetRadialInnerDamage(EffectContextHandle),
                 UAuraAbilitySystemLibrary::GetRadialOuterDamage(EffectContextHandle),
                 1.f,
                 UDamageType::StaticClass(),
                 TArray<AActor*>(),
                 SourceAvatar,
                 nullptr
         		);
         }


		
		Damage+=DamageTypeValue;

		
	}

	
	//Capture BlockChance from Target
	float TargetBlockChance=0.0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Damagestatics().BlockChanceDef,EvaluateParameters,TargetBlockChance);
	TargetBlockChance=FMath::Max<float>(TargetBlockChance,0.f);
 
	const bool bBlocked=FMath::RandRange(1,100)<TargetBlockChance;



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
	const float ArmorPenetrationCoefficient=ArmorPenetrationCurve->Eval(SourcePlayerLevel);
	
	const float EffectiveArmor=TargetArmor*=(100-SourceArmorPenetration*ArmorPenetrationCoefficient)/100;
	
	const FRealCurve* EffectiveArmorCurve= CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"),FString());
	const float EffectiveArmorCoefficient=EffectiveArmorCurve->Eval(TargetPlayerLevel);
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
	const float CriticalHitResistanceCoefficent=CriticalHitResistanceCurve->Eval(SourcePlayerLevel);
	
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
