// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "IGCEditor.h"
#include "IGC.h"
#include "IGCExtensionStyle.h"
#include "SIGCViewport.h"

#include "PropertyEditorModule.h"
#include "AdvancedPreviewSceneModule.h"

const FName FIGCEditor::IGCEditorAppIdentifier = FName(TEXT("IGCEditorApp"));
const FName FIGCEditor::ViewportTabId = FName(TEXT("IGC Viewport"));
const FName FIGCEditor::DetailTabId = FName(TEXT("IGC Detail"));
const FName FIGCEditor::PreviewSceneSettingsTabId = FName(TEXT("IGC PreviewScene Setting"));

#define LOCTEXT_NAMESPACE "IGCEditor"

void FIGCEditor::InitIGCEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UIGC * InIGC)
{
	// �����ϱ� ���� ���� IGC ��ü�� ����.
	InIGC->SetFlags(RF_Transactional); // Undo, Redo�� ����.
	IGCObject = InIGC;

	// ������Ƽ������ ����� �����ͼ� ������ �並 ����.
	const bool bIsUpdatable = false;
	const bool bAllowFavorites = true;
	const bool bIsLockable = false;

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs(bIsUpdatable, bIsLockable, true, FDetailsViewArgs::ObjectsUseNameArea, false);
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

	// ����Ʈ ����.
	Viewport = SNew(SIGCViewport)
		.ParentIGCEditor(SharedThis(this))
		.ObjectToEdit(IGCObject);

	// ������ �� ���� ����.
	FAdvancedPreviewSceneModule& AdvancedPreviewSceneModule = FModuleManager::LoadModuleChecked<FAdvancedPreviewSceneModule>("AdvancedPreviewScene");
	AdvancedPreviewSettingsWidget = AdvancedPreviewSceneModule.CreateAdvancedPreviewSceneSettingsWidget(Viewport->GetPreviewScene());

	// ���ٰ� �� �⺻ ���̾ƿ� ����.
	const TSharedRef<FTabManager::FLayout> EditorDefaultLayout = FTabManager::NewLayout("IGCEditor_Layout_v2")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.6)
					->AddTab(ViewportTabId, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.4f)
						->AddTab(DetailTabId, ETabState::OpenedTab)
					)
					->Split
					(
						FTabManager::NewStack()
						->AddTab(PreviewSceneSettingsTabId, ETabState::OpenedTab)
					)
				)
			)
		);

	// ������ �ʱ�ȭ.
	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, IGCEditorAppIdentifier, EditorDefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, InIGC);

	// ������ �信 IGC ��ü�� ����.
	if (DetailsView.IsValid())
	{
		DetailsView->SetObject(IGCObject);
	}

}

FIGCEditor::~FIGCEditor()
{
	DetailsView.Reset();
	AdvancedPreviewSettingsWidget.Reset();
}

TSharedRef<SDockTab> FIGCEditor::SpawnTab_Viewport(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == ViewportTabId);
	return SNew(SDockTab)
		[
			Viewport.ToSharedRef()
		];
}

TSharedRef<SDockTab> FIGCEditor::SpawnTab_Detail(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == DetailTabId);
	return SNew(SDockTab)
		[
			DetailsView.ToSharedRef() 
		];
}

TSharedRef<SDockTab> FIGCEditor::SpawnTab_PreviewSceneSettings(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == PreviewSceneSettingsTabId);
	return SNew(SDockTab)
		[
			AdvancedPreviewSettingsWidget.ToSharedRef()
		];
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

	TabManager->RegisterTabSpawner(PreviewSceneSettingsTabId, FOnSpawnTab::CreateSP(this, &FIGCEditor::SpawnTab_PreviewSceneSettings))
		.SetDisplayName(LOCTEXT("PreviewSceneTab", "Preview Scene Settings"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FIGCExtensionStyle::GetStyleSetName(), "IGCExtensions.Command3"));
}

void FIGCEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(TabManager);

	TabManager->UnregisterTabSpawner(ViewportTabId);
	TabManager->UnregisterTabSpawner(DetailTabId);
	TabManager->UnregisterTabSpawner(PreviewSceneSettingsTabId);
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