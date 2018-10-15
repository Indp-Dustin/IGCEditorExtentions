
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
	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Detail(const FSpawnTabArgs& Args);

private:
	// IGC �����Ͱ� ����� ������ ���� ��Ī.
	static const FName IGCEditorAppIdentifier;

	// �� Tab�� ����� ���� ��Ī.
	static const FName ViewportTabId;
	static const FName DetailTabId;

	// ������ ��.
	TSharedPtr< class IDetailsView > DetailsView;

	// ������ IGC ������Ʈ
	class UIGC* IGCObject;
};

