#pragma once
#include "pch.h"

class CheckBox : public HyEntity2d
{
	bool			m_bIsChecked;

	HyPrimitive2d	m_Check;
	HyPrimitive2d	m_Box;
	HyPrimitive2d	m_BoxHighlight;

public:
	CheckBox(bool bIsForFood, HyEntity2d *pParent);

	void Sync();

	bool IsChecked();

protected:
	virtual void OnMouseEnter() override;
	virtual void OnMouseLeave() override;
	virtual void OnMouseDown() override;
	virtual void OnMouseUp() override;
	virtual void OnMouseClicked() override;
};
