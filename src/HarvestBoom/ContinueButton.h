#pragma once
#include "pch.h"
#include "InfoPanel.h"

class ContinueButton : public InfoPanel
{
public:
	ContinueButton(const InfoPanelInit &infoPanelInitRef, HyEntity2d *pParent);

	bool IsUsed();

private:
	virtual void OnMouseDown(void *pUserParam) override;
	virtual void OnMouseUp(void *pUserParam) override;
	virtual void OnMouseLeave(void *pUserParam) override;
	virtual void OnMouseClicked(void *pUserParam) override;
};
