#pragma once
#include "pch.h"
#include "InfoPanel.h"

class CheckBox : public InfoPanel
{
	bool			m_bIS_FOR_FOOD;

	HyPrimitive2d	m_Check;
	HyPrimitive2d	m_Box;
	HyPrimitive2d	m_BoxHighlight;

public:
	CheckBox(bool bIsForFood, HyEntity2d *pParent);

	void Sync();

protected:
	virtual void OnMouseEnter(void *pUserParam) override;
	virtual void OnMouseLeave(void *pUserParam) override;
	virtual void OnMouseDown(void *pUserParam) override;
	virtual void OnMouseUp(void *pUserParam) override;
	virtual void OnMouseClicked(void *pUserParam) override;
};
