// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuraCharacter.generated.h"
class USpringArmComponent;
class UCameraComponent;
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public  AAuraCharacterBase , public IPlayerInterface
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;


	/**Player Interface*/

	virtual void AddToXP_Implementation(int32 InXP) override;
    virtual  void LevelUp_Implementation() override;
	virtual int32 GetXP_Implementation() override;
	virtual int32 FindLevelForXP_Implementation(int32 InXP) override;
    virtual int32 GetAttributePointsReward_Implementation(int32 level) const override;
	virtual int32 GetSpellPointsReward_Implementation(int32 level) const override;
	virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevel) override;
	virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;
	virtual void AddToSpellPoints_Implementation(int32 InSpellPoints) override;

	virtual  int32 GetAttributePoints_Implementation() const override;
	virtual  int32 GetSpellPoints_Implementation() const override;
	
	/** end Player Interface*/

	
	/**Combat Interface*/

	virtual int32 GetPlayerLevel_Implementation() override;

	/** end Combat Interface*/

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent>LevelUpNiagaraComponent;
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> TopDownCameraComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	void InitAbilityActorInfo()override;

	UFUNCTION(NetMulticast,Reliable)
	void MulticastLevelUpParticles()const;
};
