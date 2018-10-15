// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "IGCEditor.h"
#include "IGC.h"
#include "IGCExtensionStyle.h"

const FName FIGCEditor::IGCEditorAppIdentifier = FName(TEXT("IGCEditorApp"));
const FName FIGCEditor::ViewportTabId = FName(TEXT("IGC Viewport"));
const FName FIGCEditor::DetailTabId = FName(TEXT("IGC Detail"));

#define LOCTEXT_NAMESPACE "IGCEditor"

void FIGCEditor::InitIGCEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UIGC * InIGC)
{
	// 툴바가 들어갈 기본 레이아웃 설계.

	const TSharedRef<FTabManager::FLayout> EditorDefaultLayout = FTabManager::NewLayout("IGCEditor_Layout_v2")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)->SetHideTabWell(true)
			)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.6)
					->AddTab(ViewportTabId, ETabState::OpenedTab)->SetHideTabWell(true)
				)
				->Split
				(
					FTabManager::NewStack()
					->AddTab(DetailTabId, ETabState::OpenedTab)
				)
			)
		);

	// 에디터 초기화.
	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, IGCEditorAppIdentifier, EditorDefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, InIGC);

}

FIGCEditor::~FIGCEditor()
{
}

TSharedRef<SDockTab> FIGCEditor::SpawnTab_Viewport(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == ViewportTabId);
	return SNew(SDockTab);
}

TSharedRef<SDockTab> FIGCEditor::SpawnTab_Detail(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == DetailTabId);
	return SNew(SDockTab);
}

void FIGCEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager)
{
	WorkspaceMenuCategory = TabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_IGCAssetEditor", "IGC Asset Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(TabManager);

	TabManager->RegisterTabSpawner(ViewportTabId, FOnSpawnTab::CreateSP(this, &FIGCEditor::SpawnTab_Viewport))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FIGCExtensionStyle::GetStyleSetName(), "IGCExtensions.Command1"));

	TabManager->RegisterTabSpawner(DetailTabId, FOnSpawnTab::CreateSP(this, &FIGCEditor::SpawnTab_Detail))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FIGCExtensionStyle::GetStyleSetName(), "IGCExtensions.Command2"));
}

void FIGCEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(TabManager);

	TabManager->UnregisterTabSpawner(ViewportTabId);
	TabManager->UnregisterTabSpawner(DetailTabId);
}

FName FIGCEditor::GetToolkitFName() const
{
	return FName("IGC Editor");
}

FText FIGCEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "IGC Editor");
}

FString FIGCEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "IGC ").ToString();
}

FLinearColor FIGCEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.0f, 0.0f, 0.2f, 0.5f);
}

#undef LOCTEXT_NAMESPACE 