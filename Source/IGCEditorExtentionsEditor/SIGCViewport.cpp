
#include "SIGCViewport.h"
#include "IGCViewportClient.h"
#include "AdvancedPreviewScene.h"

#define LOCTEXT_NAMESPACE "IGCViewport"

SIGCViewport::SIGCViewport()
	: PreviewScene(MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues())))
{

}

SIGCViewport::~SIGCViewport()
{
	if (IGCViewportClient.IsValid())
	{
		IGCViewportClient->Viewport = NULL;
	}
}

void SIGCViewport::AddReferencedObjects(FReferenceCollector & Collector)
{
	Collector.AddReferencedObject(IGCObject);
	Collector.AddReferencedObject(PreviewMeshComponent);
}

TSharedRef<class FAdvancedPreviewScene> SIGCViewport::GetPreviewScene()
{
	return PreviewScene.ToSharedRef();
}

TSharedRef<FEditorViewportClient> SIGCViewport::MakeEditorViewportClient()
{
	IGCViewportClient = MakeShareable(new FIGCViewportClient(IGCEditorPtr, PreviewScene.ToSharedRef(), SharedThis(this), IGCObject));

	return IGCViewportClient.ToSharedRef();
}


void SIGCViewport::Construct(const FArguments& InArgs)
{
	IGCEditorPtr = InArgs._ParentIGCEditor;
	IGCObject = InArgs._ObjectToEdit;

	SEditorViewport::Construct(SEditorViewport::FArguments());

	ViewportOverlay->AddSlot()
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Left)
		.Padding(FMargin(10.0f, 10.0f, 10.0f, 10.0f))
		[
			SAssignNew(OverlayTextVerticalBox, SVerticalBox)
		];

	OverlayTextVerticalBox->ClearChildren();
	OverlayTextVerticalBox->AddSlot()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("IGCWelcomeText", "Welcome To IGC 2018"))
			.TextStyle(FEditorStyle::Get(), TEXT("TextBlock.ShadowedText"))
			.ColorAndOpacity(FLinearColor::Red)
		];


	UStaticMesh* StaticMesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/EngineMeshes/SM_MatPreviewMesh_01.SM_MatPreviewMesh_01"), NULL, LOAD_None, NULL);
	UMaterialInterface* BaseMaterial = LoadObject<UMaterialInterface>(NULL, TEXT("/Engine/EditorMeshes/ColorCalibrator/M_ChromeBall.M_ChromeBall"), NULL, LOAD_None, NULL);

	PreviewMeshComponent = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, RF_Transient);
	PreviewMeshComponent->SetStaticMesh(StaticMesh);
	PreviewMeshComponent->SetMaterial(0, BaseMaterial);

	FTransform Transform = FTransform::Identity;
	PreviewScene->AddComponent(PreviewMeshComponent, Transform);

	PreviewMeshComponent->SetSimulatePhysics(true);
}

#undef LOCTEXT_NAMESPACE

