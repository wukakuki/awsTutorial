//
// Created by Siqi Wu on 1/17/25.
//

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "Net/Core/Connection/NetResult.h"

#include "awsTutorial_PlayerController.generated.h"

UENUM(BlueprintType)
enum class EKickResult : uint8 {
	/** Base result types */

	/** Default state (do not move the position of this in enum) */
	Unknown,

	/** Close was successful, happening under normal conditions */
	Success,

	/** Extended/custom ErrorContext state. To be interpreted by code */
	Extended,

	/** not allow to join this server */
	Unauthorized,

	/** kicked by game owner */
	GameOwner,
};

DECLARE_NETRESULT_ENUM(EKickResult);

AWSTUTORIAL_API const TCHAR* LexToString(EKickResult Enum);

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
	void Kick(EKickResult InResult = EKickResult::Unknown, const FString& InErrorContext = "");

	UFUNCTION(BlueprintNativeEvent, Category="awsTutorial")
	void GotDisconnected();

	virtual void GotDisconnected_Implementation();
};
