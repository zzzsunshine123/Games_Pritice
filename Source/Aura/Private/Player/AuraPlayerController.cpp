// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates=true;
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	
}
void AAuraPlayerController::CursorTrace()
{
	  FHitResult CursorHit;
	  GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	  if(!CursorHit.bBlockingHit) return;
      LastActor=ThisActor;
	  
	  ThisActor=Cast<IEnemyInterface>(CursorHit.GetActor());

	  if(LastActor== nullptr)
	  {
		  if(ThisActor!= nullptr)
		  {
			  ThisActor->HighlightActor();
		  }
		  else
		  {
			  //both are null, do nothing
		  }
	  }
	  else
	  {
	  	if(ThisActor==nullptr)
	  	{
	  		LastActor->UnHighlightActor();
	  	}
	    else
	    {
		    if(LastActor!=ThisActor)
		    {
		    	LastActor->UnHighlightActor();
			    ThisActor->HighlightActor();
		    }
		    else
		    {
			    // same object do nothing
		    }
	    }
	  }
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext,0);

	bShowMouseCursor=true;

	DefaultMouseCursor=EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;

	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);

	SetInputMode(InputModeData);
	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent =CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
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


