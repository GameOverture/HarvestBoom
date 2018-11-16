#pragma once
#include "pch.h"
#include "InfoPanel.h"

class EquipButton : public InfoPanel
{
public:
	EquipButton(HyEntity2d *pParent);

	bool IsUsed();

private:
	virtual void OnMouseDown(void *pUserParam) override;
	virtual void OnMouseUp(void *pUserParam) override;
	virtual void OnMouseLeave(void *pUserParam) override;
	virtual void OnMouseClicked(void *pUserParam) override;
};
