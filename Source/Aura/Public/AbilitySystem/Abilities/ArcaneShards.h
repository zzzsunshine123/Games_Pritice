// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "ArcaneShards.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UArcaneShards : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()
public:
	virtual FString GetDescription(int32 Level) override;

	virtual FString GetNextLevelDescription(int32 Level) override;

	UPROPERTY(EditDefaultsOnly, Category = "ArcaneShards")
	int32 MaxNumShards = 11;

};
