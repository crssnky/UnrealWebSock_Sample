// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WebsocketSampleSubsystem.generated.h"

class IWebSocket;

DECLARE_LOG_CATEGORY_EXTERN(LogMyWebSocket, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSockMsg, FString, msg);

/**
 *
 */
UCLASS()
class WEBSOCK_SAMPLE_API UWebsocketSampleSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection)override;
	virtual void Deinitialize()override;

	UFUNCTION(BlueprintPure)
		FString CurrentMessage()const;


	UPROPERTY(BlueprintAssignable)
		FSockMsg OnReceiveSockMsg;

private:
	void OnSocketConnected()const;
	void OnSocketConnectioinError(const FString& err)const;
	void OnSocketClosed(const int statusCode, const FString& reason, const bool wasClean)const;
	void OnSocketMessageReceived(const FString& msg);

	TSharedPtr<IWebSocket> Socket = nullptr;
	FString currentMsg;
};
