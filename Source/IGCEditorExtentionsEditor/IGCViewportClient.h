
#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

class UIGC;

class FIGCViewportClient : public FEditorViewportClient, public TSharedFromThis<FIGCViewportClient>
{
public:
	// 생성자에서 모든 필요한 기본 변수를 설정.
	FIGCViewportClient(TWeakPtr<class FIGCEditor> ParentIGCEditor, const TSharedRef<class FAdvancedPreviewScene>& AdvPreviewScene, const TSharedRef<class SIGCViewport>& IGCViewport, UIGC* ObjectToEdit);
	~FIGCViewportClient();

	// 에디터에서 사용하는 입력
	virtual void Tick(float DeltaSeconds) override;
	virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;


private:
	TWeakPtr<class FIGCEditor> IGCEditorPtr;
	TWeakPtr<class SIGCViewport> IGCEditorViewportPtr;
	UIGC* IGCObject;
	class FAdvancedPreviewScene* AdvancedPreviewScene;

};