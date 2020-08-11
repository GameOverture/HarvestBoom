#pragma once
#include "pch.h"
#include "InfoPanel.h"

class BuyButton : public InfoPanel
{
public:
	BuyButton(HyEntity2d *pParent);

	bool IsUsed();

private:
	virtual void OnMouseDown() override;
	virtual void OnMouseUp() override;
	virtual void OnMouseLeave() override;
	virtual void OnMouseClicked() override;
};
