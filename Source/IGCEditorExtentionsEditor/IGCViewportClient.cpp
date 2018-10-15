
#include "IGCViewportClient.h"
#include "SIGCViewport.h"
#include "IGCEditor.h"
#include "AdvancedPreviewScene.h"

FIGCViewportClient::FIGCViewportClient(TWeakPtr<class FIGCEditor> ParentIGCEditor, const TSharedRef<class FAdvancedPreviewScene>& AdvPreviewScene, const TSharedRef<class SIGCViewport>& IGCViewport, UIGC * ObjectToEdit)
	: FEditorViewportClient(nullptr, &AdvPreviewScene.Get(), StaticCastSharedRef<SEditorViewport>(IGCViewport))
	, IGCEditorPtr(ParentIGCEditor)
	, IGCEditorViewportPtr(IGCViewport)
	, IGCObject(ObjectToEdit)
{
	SetViewMode(VMI_Lit);

	AdvancedPreviewScene = static_cast<FAdvancedPreviewScene*>(PreviewScene);
}

FIGCViewportClient::~FIGCViewportClient()
{
}
