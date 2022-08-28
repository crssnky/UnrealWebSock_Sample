// Fill out your copyright notice in the Description page of Project Settings.


#include "WebsocketSampleSubsystem.h"

#include "WebSocketsModule.h"
#include "IWebSocket.h"

DEFINE_LOG_CATEGORY(LogMyWebSocket);

void UWebsocketSampleSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	const FString ServerURI = TEXT("ws://localhost:8080/ws");
	const FString ServerProtocol = TEXT("ws");

	Socket = FWebSocketsModule::Get().CreateWebSocket(ServerURI, ServerProtocol);

	Socket->OnConnected().AddUObject(this, &UWebsocketSampleSubsystem::OnSocketConnected);
	Socket->OnConnectionError().AddUObject(this, &UWebsocketSampleSubsystem::OnSocketConnectioinError);
	Socket->OnClosed().AddUObject(this, &UWebsocketSampleSubsystem::OnSocketClosed);
	Socket->OnMessage().AddUObject(this, &UWebsocketSampleSubsystem::OnSocketMessageReceived);

	Socket->Connect();
}

void UWebsocketSampleSubsystem::Deinitialize()
{
	Socket->Close();
	Socket = nullptr;
}

FString UWebsocketSampleSubsystem::CurrentMessage() const
{
	return currentMsg;
}

void UWebsocketSampleSubsystem::OnSocketConnected() const
{
	UE_LOG(LogMyWebSocket, Log, TEXT("OnSocketConnected"));
}

void UWebsocketSampleSubsystem::OnSocketConnectioinError(const FString& err) const
{
	UE_LOG(LogMyWebSocket, Warning, TEXT("OnSocketConnectioinError: %s"), *err);
}

void UWebsocketSampleSubsystem::OnSocketClosed(const int statusCode, const FString& reason, const bool wasClean) const
{
	UE_LOG(LogMyWebSocket, Log, TEXT("OnSocketClosed: statuscode %d, reason %s, wasClean %s"), statusCode, *reason, (wasClean ? TEXT("true") : TEXT("false")));
}

void UWebsocketSampleSubsystem::OnSocketMessageReceived(const FString& msg)
{
	UE_LOG(LogMyWebSocket, Log, TEXT("OnSocketMessageReceived: %s"), *msg);
	currentMsg = msg;
	OnReceiveSockMsg.Broadcast(currentMsg);
}
