
#pragma once

#include "EngineMinimal.h"
#include "SlateFwd.h"
#include "UObject/GCObject.h"
#include "SEditorViewport.h"
#include "SCommonEditorViewportToolbarBase.h"

class FIGCEditor;
class UIGC;

class SIGCViewport : public SEditorViewport, public FGCObject
{
public:
	SLATE_BEGIN_ARGS(SIGCViewport) {}
		SLATE_ARGUMENT(TWeakPtr<FIGCEditor>, ParentIGCEditor)
		SLATE_ARGUMENT(UIGC*, ObjectToEdit)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	SIGCViewport();
	~SIGCViewport();

	// FGCObject 인터페이스. U오브젝트가 아니라도 가비지컬렉션 회수 가능.
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	TSharedRef<class FAdvancedPreviewScene> GetPreviewScene();

protected:
	// 아래 함수를 구현해 뷰포트 클라이언트를 생성해주어야 한다.
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:
	// 부모 에디터, 프리뷰 씬, 뷰포트 클라이언트, 넘겨받은 IGC 객체. 
	TWeakPtr<FIGCEditor> IGCEditorPtr;
	TSharedPtr<class FAdvancedPreviewScene> PreviewScene;
	TSharedPtr<class FIGCViewportClient> IGCViewportClient;
	UIGC* IGCObject;

	// 오버레이에 사용할 버티컬 박스 위젯.
	TSharedPtr<SVerticalBox> OverlayTextVerticalBox;

	// 프리뷰를 위한 스태틱 메시 컴포넌트.
	class UStaticMeshComponent* PreviewMeshComponent;
};