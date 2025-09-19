//
// Created by Siqi Wu on 7/25/25.
//

#include "awsTutorial_OnlineSession.h"
#include "awsTutorial_PlayerController.h"

#include <Misc/AssertionMacros.h>

UAwsTutorial_GameInstance* UAwsTutorial_OnlineSession::GetGameInstance() const
{
	return CastChecked<UAwsTutorial_GameInstance>(GetOuter());
}

void UAwsTutorial_OnlineSession::RegisterOnlineDelegates() {
}

void UAwsTutorial_OnlineSession::ClearOnlineDelegates() {
}

void UAwsTutorial_OnlineSession::HandleDisconnect(UWorld *World, class UNetDriver *NetDriver) {
	FDebug::DumpStackTraceToLog(ELogVerbosity::Type::Warning);

	// player controller Got disconnected
	AAwsTutorial_PlayerController *PC = Cast<AAwsTutorial_PlayerController>(GetGameInstance()->GetFirstLocalPlayerController(GetWorld()));
	if (PC) PC->GotDisconnected();

	// GEngine->HandleDisconnect(World, NetDriver);
}