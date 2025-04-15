//
// Created by Siqi Wu on 1/17/25.
//

#include "awsTutorial_PlayerController.h"

#include <Net/Core/Connection/NetCloseResult.h>

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

void AAwsTutorial_PlayerController::Kick_Implementation() {
	UNetConnection* netConnection = GetNetConnection();
	if (netConnection == NULL) return;

	netConnection->Close(UE::Net::FNetCloseResult());
}