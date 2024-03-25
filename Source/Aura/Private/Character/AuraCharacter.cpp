// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	//角色在移动时自动调整其朝向以匹配移动方向。
	GetCharacterMovement()->bOrientRotationToMovement=true;
	//置了角色旋转的速度
	GetCharacterMovement()->RotationRate=FRotator(0.f,400.f,0.f);
	//将角色的移动限制在一个平面内
	GetCharacterMovement()->bConstrainToPlane=true;
	GetCharacterMovement()->bSnapToPlaneAtStart=true;
    //关闭了角色对控制器输入的旋转响应
	bUseControllerRotationPitch=false;
	bUseControllerRotationRoll=false;
	bUseControllerRotationYaw=false;
}
