// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamegeTextComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UDamegeTextComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void setDamageText(float Damage,bool bBlockedHit,bool bCriticalHit);
};
