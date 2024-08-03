// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "NiagaraSystem.h"
#include "AbilitySystem/Debuff/DebuffNiagaraComponent.h"
#include "AbilitySystem/Passive/PassiveNiagaraComponent.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"



class UAnimMontage;
UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()

public:
    virtual void Tick(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	// Sets default values for this character's properties
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const  override;

	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
	
	UFUNCTION(NetMulticast,Reliable)
	virtual void MulticastHandDeath(FVector DeathImpulse);

	
	//Combat Interface
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;

	virtual void Die(FVector DeathImpulse) override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation()  override;
	virtual  TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
    virtual  UNiagaraSystem* GetBloodEffect_Implementation() override;

	virtual FTaggedMontage GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag) override;

	virtual int32 GetMinionCount_Implementation() override;

	virtual void IncreaseMinionCount_Implementation(int32 Amount) override;
	virtual ECharacterClass GetCharacterClass_Implementation() override;

	virtual FOnASCRegistered& GetOnAscRegisteredDelegate() override;
	virtual  FOnDeath GetOnDeathDelegate() override;
    virtual  USkeletalMeshComponent* GetWeapon_Implementation() override;

	virtual FOnDamageSignature& GetOnDamageSignature() override;
	//End Combat Interface

	FOnASCRegistered OnAscRegistered;

	FOnDamageSignature DamageSignature;
	FOnDeath OnDeath;
	
    UPROPERTY(EditAnywhere,Category="Combat")
	TArray<FTaggedMontage>AttackMontages;

    UPROPERTY(Replicated,BlueprintReadOnly)
	bool bIsStunned=false;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

     UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Combat")
	 TObjectPtr<USkeletalMeshComponent>Weapon;
	
	UPROPERTY(EditAnywhere,Category="Combat")
	FName WeaponTipSocketName;

	UPROPERTY(EditAnywhere,Category="Combat")
	FName LeftHandTipSocketName;

	UPROPERTY(EditAnywhere,Category="Combat")
	FName RightHandTipSocketName;
	
	UPROPERTY(EditAnywhere,Category="Combat")
	FName TailSocketName;
     
	bool bDead = false;
     UPROPERTY()
	 TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
     UPROPERTY()
	 TObjectPtr<UAttributeSet> AttributeSet;

	virtual  void InitAbilityActorInfo();
    UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attribute")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;


	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attribute")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attribute")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass,float Level) const;

	virtual  void InitializeDefaultAttributes() const;
     void AddCharacterAbilities();
	
	virtual  void StunTagChanged(const FGameplayTag CallbackTag,int32 NewCount) ;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="combat")
	float BaseWalkSpeed =600.f;

	/*  Dissolve Effects*/

	virtual void Dissolve();
	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void WeaponStartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UMaterialInstance>DissolveMaterialInstance;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UMaterialInstance>WeaponDissolveMaterialInstance;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Combat")
	UNiagaraSystem* BloodEffect;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Combat")
	USoundBase* DeathSound;


	/*Minions*/
	
	int32 MinionCount=0;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDebuffNiagaraComponent>BurnDebuffNiagaraComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDebuffNiagaraComponent>StunDebuffNiagaraComponent;
	 
private:

	UPROPERTY(EditAnywhere,Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere,Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupPassiveAbilities;
	
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<UAnimMontage>HitReactMontage;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPassiveNiagaraComponent> HaloOfProtectionNiagaraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPassiveNiagaraComponent> LifeSiphonNiagaraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPassiveNiagaraComponent> ManaSiphonNiagaraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>EffectAttachComponent;
};
