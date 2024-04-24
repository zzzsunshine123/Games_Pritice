// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{

	for(auto& InputAction:AbilityInputActions)
	{
		if(InputAction.InputTag==InputTag&& InputAction.InputAction)
			return InputAction.InputAction;
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("Can't find AbilityInputAction for InputTag [%s],on InputConfig [%s]"), *InputTag.ToString(),*GetNameSafe(this));
	}

	return nullptr;
	
	
}
