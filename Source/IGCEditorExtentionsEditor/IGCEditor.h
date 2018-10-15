
#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Toolkits/IToolkitHost.h"


class FIGCEditor : public FAssetEditorToolkit
{
public:
	// �Ҹ���. 
	virtual ~FIGCEditor();

	// �ʱ�ȭ �Լ�. 
	void InitIGCEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UIGC* InIGC);

	// IToolkit���� ��ӹ޾� �����ؾ� �� �����Լ���.
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetDocumentationLink() const override
	{
		return TEXT("NotAvailable");
	}

private:
	// �����Ͱ� ����� ���� �� �̸�.
	static const FName IGCEditorAppIdentifier;
};

