
#include "IGCExtensionStyle.h"

#include "Slate/SlateGameResources.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr< FSlateStyleSet > FIGCExtensionStyle::StyleInstance = nullptr;

void FIGCExtensionStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FIGCExtensionStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FIGCExtensionStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("IGCExtensionStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef< FSlateStyleSet > FIGCExtensionStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("IGCExtensionStyle"));
	Style->SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate"));

	// Menu Icons
	Style->Set("IGCExtensions.Command1", new IMAGE_BRUSH("Icons/icon_file_switch_16px", Icon16x16));
	Style->Set("IGCExtensions.Command2", new IMAGE_BRUSH("Icons/icon_file_savelevels_16px", Icon16x16));
	Style->Set("IGCExtensions.Command3", new IMAGE_BRUSH("Icons/icon_file_ProjectOpen_16x", Icon16x16));
	Style->Set("IGCExtensions.Command4", new IMAGE_BRUSH("Icons/icon_file_ProjectsRecent_16px", Icon16x16));

	// Toolbar Icons
	Style->Set("IGCToolbarIcon.Command1", new IMAGE_BRUSH("Icons/icon_Landscape_Tool_Erosion_40x", Icon40x40));
	Style->Set("IGCToolbarIcon.Command1.Small", new IMAGE_BRUSH("Icons/icon_Landscape_Tool_Erosion_20x", Icon20x20));
	Style->Set("IGCToolbarIcon.Command2", new IMAGE_BRUSH("Icons/icon_Landscape_Tool_Flatten_40x", Icon40x40));
	Style->Set("IGCToolbarIcon.Command3", new IMAGE_BRUSH("Icons/icon_Landscape_Tool_Noise_40x", Icon40x40));
	Style->Set("IGCToolbarIcon.Command4", new IMAGE_BRUSH("Icons/icon_Landscape_Tool_Smooth_40x", Icon40x40));

	return Style;
}

#undef IMAGE_BRUSH

void FIGCExtensionStyle::ReloadTextures()
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

const ISlateStyle& FIGCExtensionStyle::Get()
{
	return *StyleInstance;
}
