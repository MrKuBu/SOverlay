// Copyright 2024 Awesomium team LLC. All Rights Reserved.

#include "SOverlayBPLibrary.h"
#include "SOverlay.h"

#pragma warning(push)
#pragma warning(disable:4996)
#pragma warning(disable:4265)
#pragma warning(pop)

// Callback
USOverlayBPLibrary* USOverlayBPLibrary::GetFriends()
{
	return SteamFriends() ? USOverlayBPLibrary::StaticClass()->GetDefaultObject<USOverlayBPLibrary>() : nullptr;
}

static TArray<void*> CallbacksFriends;

USOverlayBPLibrary::USOverlayBPLibrary()
{
	CallbacksFriends.Add(new CCallback<USOverlayBPLibrary, GameOverlayActivated_t>(this, (void(USOverlayBPLibrary::*)(GameOverlayActivated_t*))&USOverlayBPLibrary::OnGameOverlayActivated));
}

void USOverlayBPLibrary::OnGameOverlayActivated(void* Data)
{
	GameOverlayActivated_t* Converted = (GameOverlayActivated_t*)Data;
	GameOverlayActivated.Broadcast(Converted->m_bActive != 0);
}

// Functions
bool USOverlayBPLibrary::SteamWorked()
{
	if (SteamAPI_Init())
	{
		if (SteamUser())
		{
			return SteamUser()->BLoggedOn();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[AWTeam SOverlay] Problem getting Steam user information."));
			return false;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[AWTeam SOverlay] Steam not running or game not see steam."));
		return false;
	}
}

bool USOverlayBPLibrary::SOverlayWorked()
{
	if (SteamAPI_Init())
	{
		if (SteamUtils())
		{
			return SteamUtils()->IsOverlayEnabled();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[AWTeam SOverlay] Problem getting Steam user information."));
			return false;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[AWTeam SOverlay] Steam not worked overlay or overlay disabled."));
		return false;
	}
}

void USOverlayBPLibrary::GameOverlay(const FString Window)
{
	if (SteamAPI_Init())
	{
		if (SteamFriends())
		{
			SteamFriends()->ActivateGameOverlay(TCHAR_TO_UTF8(*Window));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[AWTeam SOverlay] Can't open overlay, maybe overlay is disabled on steam."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[AWTeam SOverlay] Steam not running or game not see steam."));
	}
}

void USOverlayBPLibrary::GameOverlayInvite()
{
	if (SteamAPI_Init())
	{
		if (SteamFriends())
		{
			CSteamID playerID = SteamUser()->GetSteamID();

			SteamFriends()->ActivateGameOverlayInviteDialog(playerID);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[AWTeam SOverlay] Can't open overlay, maybe overlay is disabled on steam."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[AWTeam SOverlay] Steam not running or game not see steam."));
	}
}

void USOverlayBPLibrary::GameOverlayToStore(const int32 AppID)
{
	if (SteamAPI_Init())
	{
		if (SteamFriends())
		{
			SteamFriends()->ActivateGameOverlayToStore(AppID, k_EOverlayToStoreFlag_None);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[AWTeam SOverlay] Can't open overlay, maybe overlay is disabled on steam."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[AWTeam SOverlay] Steam not running or game not see steam."));
	}
}

void USOverlayBPLibrary::GameOverlayToUser(const FString Window)
{
	if (SteamAPI_Init())
	{
		if (SteamFriends())
		{
			CSteamID playerID = SteamUser()->GetSteamID();

#if PLATFORM_WINDOWS || PLATFORM_LINUX
			// For normal OS (Windows and Linux)
			char* result = TCHAR_TO_ANSI(*Window);

			SteamFriends()->ActivateGameOverlayToUser(result, playerID);
#elif PLATFORM_MAC
			// For GayOS (Mac)
			TArray<TCHAR> WindowCharArray;
            		Window.GetCharArray(WindowCharArray);
            		FString WindowString = FString::Printf(TEXT("%s"), WindowCharArray.GetData());
			
            		const char* Result = TCHAR_TO_UTF8(*WindowString);
#endif
            		SteamFriends()->ActivateGameOverlayToUser(Result, playerID);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[AWTeam SOverlay] Can't open overlay, maybe overlay is disabled on steam."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[AWTeam SOverlay] Steam not running or game not see steam."));
	}
}

void USOverlayBPLibrary::GameOverlayWEB(const FString URL, bool auto_closer)
{
	if (SteamAPI_Init())
	{
		if (SteamFriends())
		{
			if (auto_closer == true) {
				SteamFriends()->ActivateGameOverlayToWebPage(TCHAR_TO_UTF8(*URL), k_EActivateGameOverlayToWebPageMode_Modal);
			}
			else {
				SteamFriends()->ActivateGameOverlayToWebPage(TCHAR_TO_UTF8(*URL), k_EActivateGameOverlayToWebPageMode_Default);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[AWTeam SOverlay] Can't open overlay, maybe overlay is disabled on steam."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[AWTeam SOverlay] Steam not running or game not see steam."));
	}
}
