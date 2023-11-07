// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterGame.h"
#include "Player/ShooterCharacterWithGui.h"

#include "ShooterWeapon.h"

void AShooterCharacterWithGui::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FString NameSafe = GetNameSafe(this);
	WindowId = TCHAR_TO_ANSI(*NameSafe);
	ImGui::Begin(WindowId,nullptr,ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Checkbox("Can Debug",&CanDebug);
	if(!CanDebug) {
		ImGui::End();
		return;
	}

	ImGui::BulletText("Status");
	ImGui::Text("Max Health: %d",GetMaxHealth());
	ImGui::SliderFloat("current health",&Health,0.f,1000.f);
	ImGui::SliderFloat("Max Targeting Movement Speed",&TargetingSpeedModifier,0.f,1000.f);
	ImGui::SliderFloat("Max Running Movement Speed",&RunningSpeedModifier,0.f,1000.f);
	ImGui::SliderFloat("Low Health Percentage",&LowHealthPercentage,0.f,1.f);
	if(CurrentWeapon)
	{
		ImGui::BulletText("Weapon Properties");
		FString NameSafe2 = GetNameSafe(CurrentWeapon);
		const char* weaponName= TCHAR_TO_ANSI(*NameSafe2);
		ImGui::Text("Current Weapon: %s",weaponName);
		CurrentWeapon->ImGuiDebug();
	}
	//如果要修改其他属性（如PlayerState），则同理
	//ImGui::BulletText("Player State");
	//AShooterPlayerController* ShooterPlayerController = Cast<AShooterPlayerController>(GetController());
	ImGui::End();
}
