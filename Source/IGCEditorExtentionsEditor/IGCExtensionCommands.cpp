// Fill out your copyright notice in the Description page of Project Settings.

#include "IGCExtensionCommands.h"
#include "IGCEditor.h"
#include "IGC.h"

#define LOCTEXT_NAMESPACE "IGCCommand"

void FIGCExtensionCommands::RegisterCommands()
{
	UI_COMMAND(Command1, "IGCCommand1", "IGC Command1 Tooltip", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(Command2, "IGCCommand2", "IGC Command2 Tooltip", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(Command3, "IGCCommand3", "IGC Command3 Tooltip", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(Command4, "IGCCommand4", "IGC Command4 Tooltip", EUserInterfaceActionType::Button, FInputGesture());
}

void FIGCExtensionActions::Action1()
{
	FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("IGCCommand", "IGC Editor Extension Action 1 Message"));
}

void FIGCExtensionActions::Action2()
{
	FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("IGCCommand", "IGC Editor Extension Action 2 Message"));
}

void FIGCExtensionActions::Action3()
{
	TSharedRef< FIGCEditor > NewIGCEditor(new FIGCEditor());
	NewIGCEditor->InitIGCEditor(EToolkitMode::Standalone, TSharedPtr<IToolkitHost>(), NewObject<UIGC>());
}

#undef LOCTEXT_NAMESPACE