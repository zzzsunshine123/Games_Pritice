// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	/** Enemy Interface*/
	virtual  void HighlightActor() override;
	virtual  void UnHighlightActor() override;
    /** end Enemy Interface*/


	/** Combat Interface*/

	virtual int32 GetPlayerLevel() override;
	/**end Combat Interface*/
    UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

protected:
	virtual  void BeginPlay() override;
	void InitAbilityActorInfo()override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Character Class Defaults")
	int32 Level = 1;


	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
     TObjectPtr<UWidgetComponent>HealthBar;


};
