// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterGame.h"
#include "Bots/ShooterBot.h"
#include "imgui.h"
#include "ShooterWeapon.h"
#include "Bots/ShooterAIController.h"

AShooterBot::AShooterBot(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	AIControllerClass = AShooterAIController::StaticClass();

	UpdatePawnMeshes();

	bUseControllerRotationYaw = true;
}

bool AShooterBot::IsFirstPerson() const
{
	return false;
}

void AShooterBot::FaceRotation(FRotator NewRotation, float DeltaTime)
{
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);

	Super::FaceRotation(CurrentRotation, DeltaTime);
}

void AShooterBot::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FString NameSafe = GetNameSafe(this);
	WindowId = TCHAR_TO_ANSI(*NameSafe);
	ImGui::Begin(WindowId,nullptr,ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Enemy bot:%s",WindowId);
	ImGui::Checkbox("Can Debug",&CanDebug);
	if(!CanDebug)
	{
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
	ImGui::End();
}
