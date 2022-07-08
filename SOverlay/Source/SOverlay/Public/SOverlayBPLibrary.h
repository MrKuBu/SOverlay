// Copyright 2022 Awesomium team LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine.h"
#include "Containers/UnrealString.h"
#pragma push_macro("ARRAY_COUNT")
#undef ARRAY_COUNT
#include "ThirdParty/Steamworks/Steamv151/sdk/public/steam/steam_api.h"
#include "ThirdParty/Steamworks/Steamv151/sdk/public/steam/steamtypes.h"
#include "ThirdParty/Steamworks/Steamv151/sdk/public/steam/isteamutils.h"
#include "ThirdParty/Steamworks/Steamv151/sdk/public/steam/isteamfriends.h"
#pragma pop_macro("ARRAY_COUNT")
#include "SOverlayBPLibrary.generated.h"

#pragma warning(push)
#pragma warning(disable:4996)
#pragma warning(disable:4265)
#pragma warning(pop)

UCLASS()
class USOverlayBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//  Проверка, работает ли Steam

	// Check if steam is working
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Steam worked?", Keywords = "Steam worked"), Category = "AWTeam|Steam|Overlays")
		static bool SteamWorked();


	// Проверка, работает ли оверлей Steam

	// Check if steam overlay is working
	// * Make a check and make an overlay or launch URL or warning widget
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Steam overlay worked?", Keywords = "Steam overlay worked"), Category = "AWTeam|Steam|Overlays")
		static bool SOverlayWorked();


	// Таблица страниц которые могут быть открыты автоматически(введи одну из них)

	// Table of pages that can be opened automatically (Please enter one of the following)
	//    friends
	//    community
	//    players
	//    settings
	//    officialgamegroup
	//    stats
	//    achievements
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Steam overlay", Keywords = "Steam overlay"), Category = "AWTeam|Steam|Overlays")
		static void GameOverlay(const FString Window);


	// Открытие списка друзей и приглашение в игру

	// Opened friend list and can invite player from game
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Steam overlay invite", Keywords = "Steam overlay invite"), Category = "AWTeam|Steam|Overlays")
		static void GameOverlayInvite();
	

	// Открыте магазина Steam

	// Open steam marketplace
	// * Enter you App id (this method is better to use if you have DLC)
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Steam overlay to store", Keywords = "Steam overlay to store"), Category = "AWTeam|Steam|Overlays")
		static void GameOverlayToStore(const int32 AppID);
	

	// Таблица страниц которые могут быть открыты автоматически у игрока(введи одну из них)

	// Table of pages that can be opened automatically to user (Please enter one of the following) 
	//    steamid
	//    chat
	//    jointrade
	//    stats
	//    achievements
	//    friendadd
	//    friendremove
	//    friendrequestaccept
	//    friendrequestignore
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Steam overlay to user", Keywords = "Steam overlay to user"), Category = "AWTeam|Steam|Overlays")
		static void GameOverlayToUser(const FString Window);


	// Открытие Steam браузера

	// Open steam browser
	// * If automatic closing is on, then when you close the steam browser, the overlay will also close
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Steam overlay browser", Keywords = "Steam overlay browser"), Category = "AWTeam|Steam|Overlays")
		static void GameOverlayWEB(const FString URL, bool auto_closer);
};
