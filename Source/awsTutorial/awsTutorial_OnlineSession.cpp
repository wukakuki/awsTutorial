//
// Created by Siqi Wu on 7/25/25.
//

#include "awsTutorial_OnlineSession.h"
#include "awsTutorial_PlayerController.h"

#include <Misc/AssertionMacros.h>
#include <Engine/Engine.h>
#include <Containers/Ticker.h>

UAwsTutorial_GameInstance* UAwsTutorial_OnlineSession::GetGameInstance() const
{
	return CastChecked<UAwsTutorial_GameInstance>(GetOuter());
}

void UAwsTutorial_OnlineSession::RegisterOnlineDelegates() {
}

void UAwsTutorial_OnlineSession::ClearOnlineDelegates() {
}

void UAwsTutorial_OnlineSession::HandleDisconnect(UWorld *World, class UNetDriver *NetDriver) {
	// player controller Got disconnected
	AAwsTutorial_PlayerController *PC = Cast<AAwsTutorial_PlayerController>(GetGameInstance()->GetFirstLocalPlayerController(GetWorld()));
	if (PC) PC->GotDisconnected();

	// GEngine->HandleDisconnect(World, NetDriver);

	// There must be some context for this disconnect
	check(World || NetDriver);

	// World might be null. It might also not map to any valid world context (for example, a pending net game disconnect)
	// If there is a context for this world, setup client travel.
	if (FWorldContext* WorldContext = GEngine->GetWorldContextFromWorld(World))
	{
		// Remove ?Listen parameter, if it exists
		WorldContext->LastURL.RemoveOption( TEXT("Listen") );
		WorldContext->LastURL.RemoveOption( TEXT("LAN") );

		FName NetDriverName = NetDriver->NetDriverName;

		FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([World, NetDriverName](float DeltaTime)
		{
			if (GEngine)
			{
				GEngine->DestroyNamedNetDriver(World, NetDriverName);
			}
			return false; // one-shot
		}));
	} else if (NetDriver)
	{
		// If the NetDriver that failed was a pending netgame driver, cancel the PendingNetGame
		const TIndirectArray<FWorldContext> WorldList = GEngine->GetWorldContexts();
		// Find WorldContext whose pendingNetGame's NetDriver is the passed in net driver
		for( int32 idx=0; idx < WorldList.Num(); ++idx)
		{
			const FWorldContext &Context = WorldList[idx];
			if (Context.PendingNetGame && Context.PendingNetGame->NetDriver == NetDriver)
			{
				// Kill this PendingNetGame
				GEngine->CancelPending(Context.World(), nullptr);
				check(Context.PendingNetGame == NULL);	// Verify PendingNetGame was cleared in CancelPending
			}
		}

		// Shut down any existing game connections
		if (World)
		{
			// Call this to remove the NetDriver from the world context's ActiveNetDriver list
			GEngine->DestroyNamedNetDriver(World, NetDriver->NetDriverName);
		}
		else
		{
			NetDriver->Shutdown();
			NetDriver->LowLevelDestroy();
		}
	}
}