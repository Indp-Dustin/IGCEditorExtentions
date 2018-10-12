// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "IGCExtensionStyle.h"

class FIGCExtensionCommands : public TCommands<FIGCExtensionCommands>
{
public:
	FIGCExtensionCommands()
		: TCommands<FIGCExtensionCommands>(TEXT("IGCExtensions"), 
			NSLOCTEXT("IGCExtensions", "IGCExtensions", "IGCExtensions"), 
			NAME_None, 
			FIGCExtensionStyle::GetStyleSetName())
	{
	}

	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > Command1;
	TSharedPtr< FUICommandInfo > Command2;
	TSharedPtr< FUICommandInfo > Command3;
	TSharedPtr< FUICommandInfo > Command4;
};



class FIGCExtensionActions
{
public:
	static void Action1();
	static void Action2();
	static void Action3();
};