//
// Created by Siqi Wu on 1/17/25.
//

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"

#include "awsTutorial_PlayerController.generated.h"

UCLASS(Blueprintable)
class AWSTUTORIAL_API AAwsTutorial_PlayerController : public APlayerController {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="awsTutorial")
	FString GetRequestURL() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="awsTutorial")
	TArray<FString> GetRequestOptions() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="awsTutorial")
	bool HasRequestOption(const FString& key) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="awsTutorial")
	FString GetRequestOption(const FString& key) const;

	UFUNCTION(BlueprintCallable, Server, Reliable, Category="awsTutorial")
	void Kick();
};
