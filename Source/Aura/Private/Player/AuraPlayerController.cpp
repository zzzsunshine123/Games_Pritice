// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/DecalComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "GameFramework/Character.h"
#include "UI/Widget/DamegeTextComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates=true;
	Spline=CreateDefaultSubobject<USplineComponent>("Spline");
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();

	AutoRun();
	UpdateMagicCircleLocation();
}

void AAuraPlayerController::ShowMagicCircle(UMaterialInterface* DecalMaterial)
{
	if(!IsValid(MagicCircle))
	{
		MagicCircle=GetWorld()->SpawnActor<AMagicCircle>(MagicCircleClass);
		if(DecalMaterial!=nullptr)
		{
			MagicCircle->MagicCircleDecal->SetMaterial(0,DecalMaterial);
		}
	}
}

void AAuraPlayerController::HideMagicCircle()
{
	if(IsValid(MagicCircle))
	{
		MagicCircle->Destroy();
	}
}
 void AAuraPlayerController::UpdateMagicCircleLocation()
{
	if(IsValid(MagicCircle))
	{
		MagicCircle->SetActorLocation(CursorHit.ImpactPoint);
	}
}

void AAuraPlayerController::ShowDamageNumber_Implementation(float DamageAmount,ACharacter* TargetCharacter,bool bBlockedHit,bool bCriticalHit)
{
	if(IsValid(TargetCharacter)&&DamageTextComponentClass&&IsLocalController())
	{
		UDamegeTextComponent* DamageText=NewObject<UDamegeTextComponent>(TargetCharacter,DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->setDamageText(DamageAmount, bBlockedHit, bCriticalHit);
	}
}

void AAuraPlayerController::AutoRun()
{
	if(!bAutoRunning) return;
	if(APawn* ControlledPawn =GetPawn())
	{
		  const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(),ESplineCoordinateSpace::World);
		  const FVector Direction =Spline->FindDirectionClosestToWorldLocation(LocationOnSpline,ESplineCoordinateSpace::World);
		  ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination =(LocationOnSpline - CacheDestination).Length();
		if(DistanceToDestination<=AutoRunAcceptanceRadius)
		{
			bAutoRunning=false;
		}
	}
}
void AAuraPlayerController::CursorTrace()
{
	 if(GetASC()&&GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_CursorTrace))
	 {
	 	if(LastActor) LastActor->UnHighlightActor();
	 	if(ThisActor)ThisActor->UnHighlightActor();
	 	LastActor=nullptr;
	 	ThisActor=nullptr;
		 return;
	 }
	  GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	  if(!CursorHit.bBlockingHit) return;
      LastActor=ThisActor;
	  
	  ThisActor=Cast<IEnemyInterface>(CursorHit.GetActor());

	 if(LastActor!=ThisActor)
	 {
		 if(LastActor) LastActor->UnHighlightActor();
	 	 if(ThisActor)ThisActor->HighlightActor();
	 }
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if(GetASC()&&GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputPressed))
	{
		 return;
	}
	if(InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bTargeting =ThisActor ? true:false;
		bAutoRunning =false;
	}
	if(GetASC()) GetASC()->AbilityInputTagPressed(InputTag);
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if(GetASC()&&GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputReleased))
	{
		return;
	}
	
	if(!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if(GetASC()) 
			GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}
	if(GetASC())
		GetASC()->AbilityInputTagReleased(InputTag);
	if(!bTargeting&&!bShiftKeyDown)
	{
		const APawn* ControlledPawn = GetPawn();
		if(FollowTime<=ShortPressThreshold&&ControlledPawn)
		{
			if(UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this,ControlledPawn->GetActorLocation(),CacheDestination))
			{
				Spline->ClearSplinePoints();
				for(auto& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc,ESplineCoordinateSpace::World);
					
					
				}
			   if(NavPath->PathPoints.Num()>0)
			   {
			   	CacheDestination=NavPath->PathPoints[NavPath->PathPoints.Num()-1];
			   	bAutoRunning=true;
			   }
			}
			if(GetASC()&&!GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputPressed))
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ClickNiagaraSystem,CacheDestination);
			}
			
		}
		FollowTime=0.f;
		bTargeting=false;
	}
	
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{

	if(GetASC()&&GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputHeld))
	{
		return;
	}
	if(!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if(GetASC()) 
			GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}
	if(bTargeting||bShiftKeyDown)
	{
		if(GetASC())
			GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime+=GetWorld()->GetDeltaSeconds();

		
		if(CursorHit.bBlockingHit)
		{
			CacheDestination=CursorHit.ImpactPoint;
		}
		if(APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CacheDestination-ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if(AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent =Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return AuraAbilitySystemComponent;
}



void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraInputComponent* AuraInputComponent =CastChecked<UAuraInputComponent>(InputComponent);

	AuraInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
    AuraInputComponent->BindAction(ShiftAction,ETriggerEvent::Started,this,&AAuraPlayerController::ShiftPressed);
	AuraInputComponent->BindAction(ShiftAction,ETriggerEvent::Completed,this,&AAuraPlayerController::ShiftReleased);
	AuraInputComponent->BindAbilityActions(InputConfig,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputTagHeld);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{

	if(GetASC()&&GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputPressed))
	{
		return;
	}
    const FVector2D InputAxisVector= InputActionValue.Get<FVector2D>();
	const FRotator Rotation =GetControlRotation();

	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	const FVector ForwardDirection =FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection =FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn=GetPawn())
	{

		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y); 

		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
	
	
	 
}


