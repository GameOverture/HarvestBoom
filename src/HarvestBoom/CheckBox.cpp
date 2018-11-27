#include "pch.h"
#include "CheckBox.h"
#include "HousePanel.h"
#include "HarvestBoom.h"

#define CHECKBOX_SIZE 18.0f

CheckBox::CheckBox(bool bIsForFood, HyEntity2d *pParent) :
	HyEntity2d(pParent),
	m_bIsChecked(true),
	m_Check(this),
	m_Box(this),
	m_BoxHighlight(this)
{
	m_Check.GetShape().SetAsCircle(CHECKBOX_SIZE * 0.5f);
	m_Check.pos.Set(CHECKBOX_SIZE * 0.5f, CHECKBOX_SIZE * 0.5f);
	m_Check.SetTint(1.0f, 0.0f, 0.0f);
	m_Box.GetShape().SetAsBox(CHECKBOX_SIZE, CHECKBOX_SIZE);
	m_Box.SetWireframe(true);
	m_Box.SetLineThickness(4.0f);
	m_Box.SetTint(0.0f, 0.0f, 0.0f);

	std::vector<glm::vec2> ptVecList;
	ptVecList.push_back(glm::vec2(0.0f, 0.0f));
	ptVecList.push_back(glm::vec2(0.0f, CHECKBOX_SIZE));
	ptVecList.push_back(glm::vec2(CHECKBOX_SIZE, CHECKBOX_SIZE));
	ptVecList.push_back(glm::vec2(CHECKBOX_SIZE, 0.0f));
	m_BoxHighlight.GetShape().SetAsLineLoop(&ptVecList[0], ptVecList.size());
	m_BoxHighlight.SetTint(0.0f, 0.0f, 0.0f);
	m_BoxHighlight.SetLineThickness(2.0f);

	Sync();
}

void CheckBox::Sync()
{
	if(m_bIsChecked)
		m_Check.GetShape().SetAsCircle(CHECKBOX_SIZE * 0.5f);
	else
		m_Check.GetShape().SetAsNothing();
}

bool CheckBox::IsChecked()
{
	return m_bIsChecked;
}

/*virtual*/ void CheckBox::OnMouseEnter(void *pUserParam) /*override*/
{
	m_BoxHighlight.SetTint(1.0f, 0.0f, 0.0f);
}

/*virtual*/ void CheckBox::OnMouseLeave(void *pUserParam) /*override*/
{
	m_BoxHighlight.SetTint(0.0f, 0.0f, 0.0f);
}

/*virtual*/ void CheckBox::OnMouseDown(void *pUserParam) /*override*/
{
	m_BoxHighlight.SetTint(1.0f, 1.0f, 1.0f);
}

/*virtual*/ void CheckBox::OnMouseUp(void *pUserParam) /*override*/
{
	m_BoxHighlight.SetTint(1.0f, 0.0f, 0.0f);
}

/*virtual*/ void CheckBox::OnMouseClicked(void *pUserParam) /*override*/
{
	HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_BUYSTUFF);
	m_bIsChecked = !m_bIsChecked;
	
	Values::Get()->Sync();
}
