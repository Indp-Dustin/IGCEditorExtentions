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
	// Ŀ�ǵ� ���.
	FIGCExtensionCommands::Register();

	// Ŀ�ǵ�� �׼��� ���� �����ֱ�.
	IGCCommandList = MakeShareable(new FUICommandList());
	IGCCommandList->MapAction(FIGCExtensionCommands::Get().Command1, FExecuteAction::CreateStatic(&FIGCExtensionActions::Action1), FCanExecuteAction());
	IGCCommandList->MapAction(FIGCExtensionCommands::Get().Command2, FExecuteAction::CreateStatic(&FIGCExtensionActions::Action2), FCanExecuteAction());
	IGCCommandList->MapAction(FIGCExtensionCommands::Get().Command3, FExecuteAction::CreateStatic(&FIGCExtensionActions::Action3), FCanExecuteAction());
	IGCCommandList->MapAction(FIGCExtensionCommands::Get().Command4, FExecuteAction::CreateStatic(&FIGCExtensionActions::Action3), FCanExecuteAction());

	// �޴� ������ ���� ��������Ʈ �Լ� ����.
	struct IGCMenu
	{
		static void CreateIGCMenu(FMenuBuilder& MenuBuilder)
		{
			// ù ��° ����.
			MenuBuilder.BeginSection("IGCSection1", LOCTEXT("IGCMenu", "IGC Menu Section1"));

				MenuBuilder.AddMenuEntry(FIGCExtensionCommands::Get().Command1);
				MenuBuilder.AddMenuEntry(FIGCExtensionCommands::Get().Command2);

			MenuBuilder.EndSection();

			// �� ��° ����.
			MenuBuilder.BeginSection("IGCSection2", LOCTEXT("IGCMenu", "IGC Menu Section2"));

			{
				// ���� �޴� ������ ���� ��������Ʈ �Լ� ����.
				struct IGCSubMenu
				{
					static void CreateIGCSubMenu(FMenuBuilder& SubMenuBuilder)
					{
						SubMenuBuilder.AddMenuEntry(FIGCExtensionCommands::Get().Command3);
						SubMenuBuilder.AddMenuEntry(FIGCExtensionCommands::Get().Command4);
					}
				};

				// ���� �޴� ���.
				MenuBuilder.AddSubMenu(
					LOCTEXT("IGCMenu", "IGC SubMenu"),
					LOCTEXT("IGCMenu", "IGC SubMenu Tooltip"),
					FNewMenuDelegate::CreateStatic(&IGCSubMenu::CreateIGCSubMenu), false, FSlateIcon());
			}

			MenuBuilder.EndSection();
		}
	};

	// ���� ������ ������. 
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	// �޴� ����.
	TSharedPtr<FExtender> IGCMenuExtender = MakeShareable(new FExtender());
	IGCMenuExtender->AddMenuExtension("WindowLayout" /*�޴�����������ġ*/, EExtensionHook::After, IGCCommandList,
		FMenuExtensionDelegate::CreateStatic(&IGCMenu::CreateIGCMenu));

	// �޴� �߰�.
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(IGCMenuExtender);


	// ���� ������ ���� ��������Ʈ �Լ� ����.
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

	// ���� ����.
	TSharedPtr<FExtender> IGCToolbarExtender = MakeShareable(new FExtender());
	IGCToolbarExtender->AddToolBarExtension("Settings" /*���ٸ���������ġ*/, EExtensionHook::After, IGCCommandList,
		FToolBarExtensionDelegate::CreateStatic(&IGCToolbar::CreateIGCToolbar));

	// ���� �߰�.
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(IGCToolbarExtender);
}

void FIGCEditorExtensionsEditor::ShutdownModule()
{
	// Ŀ�ǵ� ��� ����.
	FIGCExtensionCommands::Unregister();

}

#undef LOCTEXT_NAMESPACE