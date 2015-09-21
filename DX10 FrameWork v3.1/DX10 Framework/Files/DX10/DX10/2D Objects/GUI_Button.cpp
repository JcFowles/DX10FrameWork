// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	:	GUI_Button.cpp
// Description	:	The implementation file.
// Author(s)	:	Juran Griffith.
// Mail			:	juran.griffith@mediadesignschool.com
//

// Library Includes

// Local Includes
#include "GUI_Button.h"

GUI_Button::GUI_Button()
{
	m_horizontal = false;
	m_boundsOffset = 0;
	m_col = 0;
	m_row = 0; 
}

GUI_Button::~GUI_Button()
{
	//ReleasePtr(m_pSprite);
}

bool GUI_Button::Initialize(DX10_Renderer* _pDX10_Renderer, DXSprite* _pSprite, float _x, float _y, float _width, float _height)
{
	if (!_pDX10_Renderer && !_pSprite)
		return false;

	m_pDX10_Renderer = _pDX10_Renderer;
	m_pSprite = _pSprite;

	m_position.x = _x;
	m_position.y = _y;

	m_width = _width;
	m_height = _height;

	m_bounds.m_x = _x;
	m_bounds.m_y = _y;
	m_bounds.m_w = _width;
	m_bounds.m_h = _height;

	// Intialize the bounds
	m_bounds.m_w = m_position.x + m_width - m_boundsOffset;
	m_bounds.m_h = m_position.y + m_height - m_boundsOffset;

	return true;
}

v2float GUI_Button::GetPosition()
{
	return m_position;
}

BUTTON_STATE GUI_Button::GetState()
{
	return m_state;
}

DXSprite* GUI_Button::GetSprite()
{
	return m_pSprite;
}

float GUI_Button::GetWidth()
{
	return m_width;
}

float GUI_Button::GetHeight()
{
	return m_height;
}

void GUI_Button::SetPosition(v2float _position)
{
	m_position = _position;

	m_bounds.m_x = m_position.x + m_boundsOffset;
	m_bounds.m_y = m_position.y + m_boundsOffset;

	// Intialize the bounds
	m_bounds.m_w = m_position.x + m_width - m_boundsOffset;
	m_bounds.m_h = m_position.y + m_height - m_boundsOffset;
}

void GUI_Button::SetState(BUTTON_STATE _state)
{
	m_state = _state;
}

void GUI_Button::SetBoundsOffset(float _offset)
{
	m_boundsOffset = _offset;
}

void GUI_Button::SetColumnIndex(UINT _index)
{
	m_col = _index;
}

void GUI_Button::SetRowIndex(UINT _index)
{
	m_row = _index;
}

void GUI_Button::Draw()
{
	switch (m_state)
	{
	case BUTTON_STATE::BUTTON_STATE_DEFAULT:
		m_pSprite->SetImageIndex(m_col + 0);
		break;
	case BUTTON_STATE::BUTTON_STATE_HOVER:
		m_pSprite->SetImageIndex(m_col + 1 * m_pSprite->GetSliceWidth());
		break;
	case BUTTON_STATE::BUTTON_STATE_SELECTED:
		m_pSprite->SetImageIndex(m_col + 2 * m_pSprite->GetSliceWidth());
		break;
	case BUTTON_STATE::BUTTON_STATE_DEACTIVATED:
		m_pSprite->SetImageIndex(m_col + 3 * m_pSprite->GetSliceWidth());
		break;
	}

	m_pSprite->SetSize(m_width, m_height);
	m_pSprite->SetPosition(m_position.x, m_position.y);
	m_pSprite->Render();
}

/*void GUI_Button::Process(float _deltaTime)
{
	if (m_state == BUTTON_STATE::BUTTON_STATE_DEACTIVATED)
		return;

	DIMOUSESTATE mouseCurrState = m_pInput->GetMouseState();

	D3DXVECTOR2 mousePosition;
	m_pInput->GetMousePosition(mousePosition);

	if (mousePosition.x >= m_bounds.m_x && mousePosition.x <= m_bounds.m_w &&
		mousePosition.y >= m_bounds.m_y && mousePosition.y <= m_bounds.m_h)
	{
		if (mouseCurrState.rgbButtons[0] && !m_pInput->IsMouseBtnLocked(0))
		{
			m_pInput->LockMouseBtn(0);
			m_state = eState::ES_SELECTED;
		}
		else
			m_state = eState::ES_HOVER;
	}
	else
		m_state = eState::ES_DEFAULT;
}*/

bool GUI_Button::IsInBounds(v2float _point)
{
	return (_point.x >= m_bounds.m_x && _point.x <= m_bounds.m_w &&
		_point.y >= m_bounds.m_y && _point.y <= m_bounds.m_h);
}