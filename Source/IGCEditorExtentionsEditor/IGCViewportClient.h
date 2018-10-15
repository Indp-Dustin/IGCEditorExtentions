
#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

class UIGC;

class FIGCViewportClient : public FEditorViewportClient, public TSharedFromThis<FIGCViewportClient>
{
public:
	// �����ڿ��� ��� �ʿ��� �⺻ ������ ����.
	FIGCViewportClient(TWeakPtr<class FIGCEditor> ParentIGCEditor, const TSharedRef<class FAdvancedPreviewScene>& AdvPreviewScene, const TSharedRef<class SIGCViewport>& IGCViewport, UIGC* ObjectToEdit);
	~FIGCViewportClient();

private:
	TWeakPtr<class FIGCEditor> IGCEditorPtr;
	TWeakPtr<class SIGCViewport> IGCEditorViewportPtr;
	UIGC* IGCObject;
	class FAdvancedPreviewScene* AdvancedPreviewScene;
};