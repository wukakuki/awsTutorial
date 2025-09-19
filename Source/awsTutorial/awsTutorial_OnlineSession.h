//
// Created by Siqi Wu on 7/25/25.
//

#pragma once

#include "CoreMinimal.h"

#include "awsTutorial_GameInstance.h"

#include <GameFramework/OnlineSession.h>

#include "awsTutorial_OnlineSession.generated.h"

UCLASS(Blueprintable)
class AWSTUTORIAL_API UAwsTutorial_OnlineSession : public UOnlineSession {
	GENERATED_BODY()

private:
	/** @return the current game instance */
	virtual UAwsTutorial_GameInstance* GetGameInstance() const;

public:
	virtual void RegisterOnlineDelegates() override;
	virtual void ClearOnlineDelegates() override;
	virtual void HandleDisconnect(UWorld *World, class UNetDriver *NetDriver) override;
};
