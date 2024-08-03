// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "EeecCalc_Damage.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UEeecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UEeecCalc_Damage();
	void DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                     const FGameplayEffectSpec& Spec,
	                     FAggregatorEvaluateParameters EvaluateParameters,
	                     TMap<FGameplayTag,FGameplayEffectAttributeCaptureDefinition> InTagsToDefs) const;
	virtual  void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
