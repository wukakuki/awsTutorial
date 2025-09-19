//
// Created by Siqi Wu on 1/17/25.
//

#include "awsTutorial_PlayerController.h"

#include <Net/Core/Connection/NetCloseResult.h>
#include <Engine/NetConnection.h>

FString AAwsTutorial_PlayerController::GetRequestURL() const {
	UNetConnection* netConnection = GetNetConnection();
	if (netConnection == NULL) return FString();
	return netConnection->RequestURL;
}

TArray<FString> AAwsTutorial_PlayerController::GetRequestOptions() const {
	UNetConnection* netConnection = GetNetConnection();
	if (netConnection == NULL) return TArray<FString>();
	FURL InURL( NULL, *netConnection->RequestURL, TRAVEL_Absolute );
	return InURL.Op;
}

bool AAwsTutorial_PlayerController::HasRequestOption(const FString& key) const {
	UNetConnection* netConnection = GetNetConnection();
	if (netConnection == NULL) return false;
	FURL InURL( NULL, *netConnection->RequestURL, TRAVEL_Absolute );
	return InURL.HasOption(*key);
}

FString AAwsTutorial_PlayerController::GetRequestOption(const FString& key) const {
	UNetConnection* netConnection = GetNetConnection();
	if (netConnection == NULL) return FString("");
	FURL InURL( NULL, *netConnection->RequestURL, TRAVEL_Absolute );
	const TCHAR* o = InURL.GetOption(*key, NULL);
	if (o == NULL) return FString("");
	if (o[0] == '=') return FString(o + 1);
	return FString(o);
}

using FKickResult = UE::Net::TNetResult<EKickResult>;

const TCHAR* LexToString(EKickResult Enum) {
	switch (Enum) {
		case EKickResult::Unknown: return TEXT("Unknown");
		case EKickResult::Success: return TEXT("Success");
		case EKickResult::Extended: return TEXT("Extended");
		case EKickResult::Unauthorized: return TEXT("Unauthorized");
	}
	return TEXT("Unknown");
}

void AAwsTutorial_PlayerController::Kick_Implementation(EKickResult InResult, const FString& InErrorContext) {
	UNetConnection* netConnection = GetNetConnection();
	if (netConnection == NULL) return;

	netConnection->Close(FKickResult(InResult, InErrorContext));
}

void AAwsTutorial_PlayerController::GotDisconnected_Implementation() {

}