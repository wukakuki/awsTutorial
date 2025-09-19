//
// Created by Siqi Wu on 7/25/25.
//

#include "awsTutorial_GameInstance.h"

#include "awsTutorial_OnlineSession.h"

TSubclassOf<UOnlineSession> UAwsTutorial_GameInstance::GetOnlineSessionClass() {
	return UAwsTutorial_OnlineSession::StaticClass();
}