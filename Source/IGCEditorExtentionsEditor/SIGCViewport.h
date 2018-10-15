
#pragma once

#include "CoreMinimal.h"
#include "SlateFwd.h"
#include "UObject/GCObject.h"
#include "SEditorViewport.h"

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

	// FGCObject �������̽�. U������Ʈ�� �ƴ϶� �������÷��� ȸ�� ����.
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

protected:
	// �Ʒ� �Լ��� ������ ����Ʈ Ŭ���̾�Ʈ�� �������־�� �Ѵ�.
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:
	// �θ� ������, ������ ��, ����Ʈ Ŭ���̾�Ʈ, �Ѱܹ��� IGC ��ü. 
	TWeakPtr<FIGCEditor> IGCEditorPtr;
	TSharedPtr<class FAdvancedPreviewScene> PreviewScene;
	TSharedPtr<class FIGCViewportClient> IGCViewportClient;
	UIGC* IGCObject;
};