
#include "SIGCViewport.h"
#include "IGCViewportClient.h"
#include "AdvancedPreviewScene.h"

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
}
