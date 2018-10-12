// Fill out your copyright notice in the Description page of Project Settings.

#include "IGCEditorExtensionsEditor.h"
#include "IGCExtensionCommands.h"

#include "Framework/MultiBox/MultiBoxExtender.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "LevelEditor.h"

IMPLEMENT_MODULE( FIGCEditorExtensionsEditor, "IGCEditorExtensionsEditor" );

#define LOCTEXT_NAMESPACE "IGCMenu"

void FIGCEditorExtensionsEditor::StartupModule()
{
	// 커맨드 등록.
	FIGCExtensionCommands::Register();

	// 커맨드와 액션을 서로 묶어주기.
	IGCCommandList = MakeShareable(new FUICommandList());
	IGCCommandList->MapAction(FIGCExtensionCommands::Get().Command1, FExecuteAction::CreateStatic(&FIGCExtensionActions::Action1), FCanExecuteAction());
	IGCCommandList->MapAction(FIGCExtensionCommands::Get().Command2, FExecuteAction::CreateStatic(&FIGCExtensionActions::Action2), FCanExecuteAction());
	IGCCommandList->MapAction(FIGCExtensionCommands::Get().Command3, FExecuteAction::CreateStatic(&FIGCExtensionActions::Action3), FCanExecuteAction());
	IGCCommandList->MapAction(FIGCExtensionCommands::Get().Command4, FExecuteAction::CreateStatic(&FIGCExtensionActions::Action3), FCanExecuteAction());

	// 메뉴 생성을 위한 델리게이트 함수 선언.
	struct IGCMenu
	{
		static void CreateIGCMenu(FMenuBuilder& MenuBuilder)
		{
			// 첫 번째 섹션.
			MenuBuilder.BeginSection("IGCSection1", LOCTEXT("IGCMenu", "IGC Menu Section1"));

				MenuBuilder.AddMenuEntry(FIGCExtensionCommands::Get().Command1);
				MenuBuilder.AddMenuEntry(FIGCExtensionCommands::Get().Command2);

			MenuBuilder.EndSection();

			// 두 번째 섹션.
			MenuBuilder.BeginSection("IGCSection2", LOCTEXT("IGCMenu", "IGC Menu Section2"));

			{
				// 서브 메뉴 생성을 위한 델리게이트 함수 선언.
				struct IGCSubMenu
				{
					static void CreateIGCSubMenu(FMenuBuilder& SubMenuBuilder)
					{
						SubMenuBuilder.AddMenuEntry(FIGCExtensionCommands::Get().Command3);
						SubMenuBuilder.AddMenuEntry(FIGCExtensionCommands::Get().Command4);
					}
				};

				// 서브 메뉴 등록.
				MenuBuilder.AddSubMenu(
					LOCTEXT("IGCMenu", "IGC SubMenu"),
					LOCTEXT("IGCMenu", "IGC SubMenu Tooltip"),
					FNewMenuDelegate::CreateStatic(&IGCSubMenu::CreateIGCSubMenu), false, FSlateIcon());
			}

			MenuBuilder.EndSection();
		}
	};

	// 레벨 에디터 얻어오기. 
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	// 메뉴 생성.
	TSharedPtr<FExtender> IGCMenuExtender = MakeShareable(new FExtender());
	IGCMenuExtender->AddMenuExtension("WindowLayout" /*메뉴를삽입할위치*/, EExtensionHook::After, IGCCommandList,
		FMenuExtensionDelegate::CreateStatic(&IGCMenu::CreateIGCMenu));

	// 메뉴 추가.
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(IGCMenuExtender);


	// 툴바 생성을 위한 델리게이트 함수 선언.
	struct IGCToolbar
	{
		static void CreateIGCToolbar(FToolBarBuilder& ToolbarBuilder)
		{
			ToolbarBuilder.BeginSection("IGCToolbar");
			{
				ToolbarBuilder.AddToolBarButton(FIGCExtensionCommands::Get().Command1);
				ToolbarBuilder.AddToolBarButton(FIGCExtensionCommands::Get().Command2);
				ToolbarBuilder.AddToolBarButton(FIGCExtensionCommands::Get().Command3);
				ToolbarBuilder.AddToolBarButton(FIGCExtensionCommands::Get().Command4);
			}
			ToolbarBuilder.EndSection();
		}
	};

	// 툴바 생성.
	TSharedPtr<FExtender> IGCToolbarExtender = MakeShareable(new FExtender());
	IGCToolbarExtender->AddToolBarExtension("Settings" /*툴바를삽입할위치*/, EExtensionHook::After, IGCCommandList,
		FToolBarExtensionDelegate::CreateStatic(&IGCToolbar::CreateIGCToolbar));

	// 툴바 추가.
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(IGCToolbarExtender);
}

void FIGCEditorExtensionsEditor::ShutdownModule()
{
	// 커맨드 등록 해제.
	FIGCExtensionCommands::Unregister();

}

#undef LOCTEXT_NAMESPACE