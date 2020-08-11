#pragma once
#include "pch.h"
#include "InfoPanel.h"

class EquipButton : public InfoPanel
{
public:
	EquipButton(HyEntity2d *pParent);

	bool IsUsed();

private:
	virtual void OnMouseDown() override;
	virtual void OnMouseUp() override;
	virtual void OnMouseLeave() override;
	virtual void OnMouseClicked() override;
};
