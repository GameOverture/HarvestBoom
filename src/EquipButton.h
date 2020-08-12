#pragma once
#include "pch.h"

class EquipButton : public HyInfoPanel
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
