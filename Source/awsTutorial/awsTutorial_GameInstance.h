//
// Created by Siqi Wu on 7/25/25.
//

#pragma once

#include "CoreMinimal.h"

#include "Engine/GameInstance.h"

#include "awsTutorial_GameInstance.generated.h"

UCLASS(Blueprintable)
class AWSTUTORIAL_API UAwsTutorial_GameInstance : public UGameInstance {
	GENERATED_BODY()

public:
	virtual TSubclassOf<UOnlineSession> GetOnlineSessionClass() override;
};
