#include "pch.h"
#include "InfoPanel.h"

InfoPanel::InfoPanel(const InfoPanelInit &infoPanelInitRef, HyEntity2d *pParent) :	HyEntity2d(pParent),
																						m_pPanel(infoPanelInitRef.panel_LoadPath.IsUsed() ? HY_NEW HySprite2d(infoPanelInitRef.panel_LoadPath.szPrefix, infoPanelInitRef.panel_LoadPath.szName, this) : nullptr),
																						m_pText(infoPanelInitRef.text_LoadPath.IsUsed() ? HY_NEW HyText2d(infoPanelInitRef.text_LoadPath.szPrefix, infoPanelInitRef.text_LoadPath.szName, this) : nullptr)
#ifdef LG_DEBUG_BOXES
																						, m_pDebugTextBox(infoPanelInitRef.text_LoadPath.IsUsed() ? HY_NEW HyPrimitive2d(this) : nullptr)
#endif
{
	if(m_pText)
	{
		m_pText->TextSetAlignment(HYALIGN_Center);
		SetTextLocation(infoPanelInitRef.text_LocalOffSet.x, infoPanelInitRef.text_LocalOffSet.y, infoPanelInitRef.text_ScaleBox.x, infoPanelInitRef.text_ScaleBox.y);

#ifdef LG_DEBUG_BOXES
		m_pDebugTextBox->SetTint(1.0f, 0.0f, 0.0f);
#endif
	}

	UseWindowCoordinates();
	
	pos.Set(infoPanelInitRef.panel_Pos);
}

InfoPanel::~InfoPanel()
{
	delete m_pPanel;
	delete m_pText;
#ifdef LG_DEBUG_BOXES
	delete m_pDebugTextBox;
#endif
}

HySprite2d *InfoPanel::GetPanelPtr()
{
	return m_pPanel;
}

HyText2d *InfoPanel::GetTextPtr()
{
	return m_pText;
}

/*virtual*/ void InfoPanel::SetPanelState(uint32 uiAnimIndex, bool bResetAnim)
{
	if(m_pPanel)
	{
		m_pPanel->AnimSetState(uiAnimIndex);

		if(bResetAnim)
			m_pPanel->AnimSetFrame(0);

		if(m_pText)
			SetTextLocation(m_vTextOffset.x, m_vTextOffset.y, static_cast<int32>(m_pText->TextGetBox().x), static_cast<int32>(m_pText->TextGetBox().y));
	}
}

float InfoPanel::GetPanelWidth()
{
	if(m_pPanel)
		return m_pPanel->AnimGetCurFrameWidth(true);
	
	return 0.0f;
}

float InfoPanel::GetPanelHeight()
{
	if(m_pPanel)
		return m_pPanel->AnimGetCurFrameHeight(true);

	return 0.0f;
}

/*virtual*/ std::string InfoPanel::GetStr()
{
	if(m_pText)
		return m_pText->TextGet();

	return std::string();
}

/*virtual*/ void InfoPanel::SetStr(std::string sText)
{
	if(m_pText)
		m_pText->TextSet(sText);
}

/*virtual*/ void InfoPanel::SetTextLocation(int32 iOffsetX, int32 iOffsetY, int32 iWidth, int32 iHeight)
{
	if(m_pText == nullptr)
		return;

	m_vTextOffset.x = iOffsetX;
	m_vTextOffset.y = iOffsetY;

	glm::ivec2 vPanelOffset(0);
	//if(m_pPanel)
	//{
	//	const HySprite2dData *pPanelData = static_cast<const HySprite2dData *>(m_pPanel->AcquireData());
	//	const HySprite2dFrame &frameRef = pPanelData->GetFrame(m_pPanel->AnimGetState(), m_pPanel->AnimGetFrame());
	//	vPanelOffset = frameRef.vOFFSET;
	//}
	
	m_pText->pos.Set(m_vTextOffset.x + vPanelOffset.x, m_vTextOffset.y + vPanelOffset.y);
	m_pText->SetAsScaleBox(static_cast<float>(iWidth), static_cast<float>(iHeight), true);

#ifdef LG_DEBUG_BOXES
	if(m_pDebugTextBox)
	{
		m_pDebugTextBox->pos.Set(m_pText->pos);
		m_pDebugTextBox->SetWireframe(true);
		m_pDebugTextBox->GetShape().SetAsBox(m_pText->TextGetBox().x, m_pText->TextGetBox().y);
	}
#endif
}

/*virtual*/ void InfoPanel::SetTextAlignment(HyAlign eAlignment)
{
	if(m_pText)
		m_pText->TextSetAlignment(eAlignment);
}

/*virtual*/ glm::vec2 InfoPanel::GetTextScaleBox()
{
	if(m_pText)
		return m_pText->TextGetBox();

	return glm::vec2(0.0f);
}
