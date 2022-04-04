// Copyright (c) 2021 Artyom "Tricky Fat Cat" Volkov (tricky.fat.cat@gmail.com)


#include "UserInterface/Session/GameOverScreenWidget.h"

#include "HttpModule.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Core/TrickyGameInstance.h"
#include "Core/Session/SessionGameMode.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "UserInterface/Session/PlayerStatWidget.h"

DECLARE_LOG_CATEGORY_CLASS(LogGameOverScreen, All, All);

void UGameOverScreenWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Button_NextLevel)
	{
		Button_NextLevel->OnClicked.AddDynamic(this, &UGameOverScreenWidget::OnNextLevelPressed);
	}
}

void UGameOverScreenWidget::OnTransitionScreenShowed()
{
	Super::OnTransitionScreenShowed();

	if (TransitionCommand == ETransitionCommand::NextLevel)
	{
		OpenNextLevel();
	}
}

void UGameOverScreenWidget::OnNextLevelPressed()
{
	TransitionCommand = ETransitionCommand::NextLevel;
	StartTransition();
}

void UGameOverScreenWidget::OpenNextLevel() const
{
	if (!GetWorld()) return;

	UTrickyGameInstance* GameInstance = GetWorld()->GetGameInstance<UTrickyGameInstance>();

	if (!GameInstance) return;

	const FName NextLevelName = GameInstance->GetNextLevelName();

	if (NextLevelName.IsNone()) return;

	UGameplayStatics::OpenLevel(this, NextLevelName);
}

float UGameOverScreenWidget::GetFinalTime()
{
	
	if (!GetWorld()) return -1.f;

	ASessionGameMode* SessionGameMode = Cast<ASessionGameMode>(GetWorld()->GetAuthGameMode());

	if (!SessionGameMode) return -1.f;

	Time = SessionGameMode->GetFinalTime();
	return Time;
}

void UGameOverScreenWidget::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
	if (bSuccess == false) return;
	
	UE_LOG(LogGameOverScreen, Display, TEXT("username: %s"), *Response->GetContentAsString());
	TSharedPtr<FJsonValue> ResponseObj;
	auto Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(Reader, ResponseObj);

	Stats->ClearChildren();
	for (auto Player: ResponseObj->AsArray())
	{
		UPlayerStatWidget* PlayerStat = CreateWidget<UPlayerStatWidget>(this, PlayerStatRowWidgetClass);
		PlayerStat->SetUsername(Player->AsObject()->GetStringField("username"), MyShinyNewInt == Player->AsObject()->GetNumberField("id"));
		PlayerStat->SetScore(FString::FromInt(Player->AsObject()->GetNumberField("score")), MyShinyNewInt == Player->AsObject()->GetNumberField("id"));
		Stats->AddChildToVerticalBox(PlayerStat);
	}
	StatHeader->SetVisibility(ESlateVisibility::Visible);
}

void UGameOverScreenWidget::OnResponseReceived1(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
	if (bSuccess == false) return;
	FString Level = GetWorld()->GetMapName();
	
	MyShinyNewInt = FCString::Atoi(*Response->GetContentAsString());
	
	FHttpRequestRef Request2 = FHttpModule::Get().CreateRequest();
	Request2->OnProcessRequestComplete().BindUObject(this, &UGameOverScreenWidget::OnResponseReceived);
	Request2->SetURL("http://188.68.208.161:8000/score/" + Level);
	Request2->SetVerb("GET");
	Request2->ProcessRequest();
}

void UGameOverScreenWidget::ShowStat()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	auto RequestObj = MakeShared<FJsonObject>();
	FString Level = GetWorld()->GetMapName();

	RequestObj->SetStringField("level", GetWorld()->GetMapName());
	RequestObj->SetNumberField("score",  FMath::FloorToInt(Time * 10.0));

	FString RequestBody;
	auto Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->SetURL("http://188.68.208.161:8000/score");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->OnProcessRequestComplete().BindUObject(this, &UGameOverScreenWidget::OnResponseReceived1);
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();

}
