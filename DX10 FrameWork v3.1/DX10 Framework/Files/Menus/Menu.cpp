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
#include "Menu.h"

Menu::Menu()
{
	m_space = 20.0f;
	m_position.x = 0;
	m_position.y = 0;
	m_state = MENU_STATE_DEFAULT;
	m_elaspedTime = 0.0f;
	m_imageIndex = 0;
}

Menu::~Menu()
{
	// Release all sprite related resources
	ReleasePtr(m_pShader_Sprite);
	ReleasePtr(m_title);

	while (!m_sprites.empty())
	{
		ReleasePtr(m_sprites.back());
		m_sprites.pop_back();
	}

	while (!m_toggleButtons.empty())
	{
		ReleasePtr(m_toggleButtons.back());
		m_toggleButtons.pop_back();
	}

	while (!m_buttons.empty())
	{
		ReleasePtr(m_buttons.back());
		m_buttons.pop_back();
	}
}

bool Menu::Initialize(DX10_Renderer*_pDX10_Renderer, HWND* _pHWnd, InputGamePad* _pGamepad, MENU_LAYOUT _layout)
{
	m_pDX10_Renderer = _pDX10_Renderer;
	m_pHWnd = _pHWnd;
	m_pGamepad = _pGamepad;
	m_layout = _layout;

	m_menuItem = 0;

	m_pShader_Sprite = new DX10_Shader_Sprite();
	VALIDATE(m_pShader_Sprite->Initialize(m_pDX10_Renderer, m_pHWnd));

	return true;
}

void Menu::Process(float _deltaTime)
{
	if (m_state == MENU_STATE_DEFAULT)
	{
		// Update the shader
		if (m_pShader_Sprite != 0)
		{
			m_pShader_Sprite->Update(_deltaTime);
		}

		// Draw Title
		if (m_title)
		{
			//m_title->Process(_deltaTime);
			if (m_elaspedTime > 60.0f)
			{
				m_title->SetState((BUTTON_STATE)++m_imageIndex);
				if (m_imageIndex == 3)
				{
					m_imageIndex = 0;
				}

				m_elaspedTime = 0.0f;
			}
			else
			{
				m_elaspedTime += _deltaTime * 100.0f;
			}
		}

		// Process all the buttons
		/*for (auto button = m_buttons.begin(); button != m_buttons.end(); button++)
		{
			(*button)->m_pButton->Process(_deltaTime);
		}

		for (auto button = m_toggleButtons.begin(); button != m_toggleButtons.end(); button++)
		{
			(*button)->Process(_deltaTime);
		}*/

		// Handle Controller Input
		m_pGamepad->PreProcess();

		// Menu Item Navigation
		if (m_pGamepad->GetButtonDown(m_XButtons.DPad_Down) || m_pGamepad->GetStickDirectionDown(m_XStickDirections.LStick_Down))
		{
			if (m_menuItem < m_buttons.size() - 1)
			{
				if (m_menuItem >= 0)
				{
					m_buttons[m_menuItem]->m_pButton->SetState(BUTTON_STATE_DEFAULT);
				}

				m_menuItem++;
				if (m_menuItem >= 0)
				{
					m_buttons[m_menuItem]->m_pButton->SetState(BUTTON_STATE_HOVER);
				}
			}
		}
		else if (m_pGamepad->GetButtonDown(m_XButtons.DPad_Up) || m_pGamepad->GetStickDirectionDown(m_XStickDirections.LStick_Up))
		{
			if (m_menuItem > 0)
			{
				if (m_menuItem >= 0)
				{
					m_buttons[m_menuItem]->m_pButton->SetState(BUTTON_STATE_DEFAULT);
				}

				m_menuItem--;
				if (m_menuItem >= 0)
				{
					m_buttons[m_menuItem]->m_pButton->SetState(BUTTON_STATE_HOVER);
				}
			}
		}

		// Menu Item Selected
		if (m_pGamepad->GetButtonDown(m_XButtons.ActionButton_A)) // Confirm Selection
		{
			m_state = m_buttons[m_menuItem]->m_option;
		}
		else if (m_pGamepad->GetButtonDown(m_XButtons.ActionButton_B))
		{
			m_state = MENU_STATE_EXIT;
		}

		m_pGamepad->PostProcess();
	}
}

void Menu::Draw()
{
	if (m_state == MENU_STATE_DEFAULT)
	{
		// Turn the z buffer off
		m_pDX10_Renderer->TurnZBufferOff();

		// Draw Title
		if (m_title)
		{
			m_title->Draw();
		}

		// Draw all the buttons
		for (auto button = m_buttons.begin(); button != m_buttons.end(); button++)
		{
			(*button)->m_pButton->Draw();
		}

		for (auto button = m_toggleButtons.begin(); button != m_toggleButtons.end(); button++)
		{
			(*button)->Draw();
		}

		// Turn the z buffer on
		m_pDX10_Renderer->TurnZBufferOn();
	}
}

bool Menu::AddSprite(std::string _filename, UINT _imageWidth, UINT _imageHeight, UINT _sliceWidth, UINT _sliceHeight)
{
	//	TO IMPROVE Juran
	//  - Dynamically find the width and height of image files (may need to check which type of image it is too)
	//	- Check for duplicate sprites
	m_sprites.push_back(new DXSprite());
	VALIDATE(m_sprites.back()->Initialize(m_pHWnd, m_pDX10_Renderer, m_pShader_Sprite, _filename, _imageWidth, _imageHeight, _sliceWidth, _sliceHeight));

	return true;
}

bool Menu::AddButton(MENU_STATE _option, UINT _spriteIndex, float _scale, UINT _col, UINT _row)
{
	if (_spriteIndex < m_sprites.size())
	{
		float offsety = 0.0f;
		if (m_buttons.size() > 0)
		{
			offsety = m_buttons[m_buttons.size() - 1]->m_pButton->GetHeight();
		}

		m_buttons.push_back(new TButton());
		GUI_Button* temp = new GUI_Button();
		switch (m_layout)
		{
		case MENU_LAYOUT_CENTRE:
		{
			float m_screenWidth = 0.0f;
			float m_screenHeight = 0.0f;

			RECT rect;
			if (GetClientRect(*m_pHWnd, &rect))
			{
				m_screenWidth = static_cast<float>(rect.right - rect.left);
				m_screenHeight = static_cast<float>(rect.bottom - rect.top);
			}

			m_screenWidth = m_screenWidth * 0.5f - (m_sprites[_spriteIndex]->GetWidth() * 0.25f);
			m_screenHeight = m_screenHeight * 0.5f;

			VALIDATE(temp->Initialize(m_pDX10_Renderer, m_sprites[_spriteIndex],
				m_position.x + m_screenWidth,
				m_position.y + m_screenHeight + (m_space + offsety) * (m_buttons.size() - 1),
				m_sprites[_spriteIndex]->GetWidth() * _scale,
				m_sprites[_spriteIndex]->GetHeight() * _scale));
		}
			
			break;
		case MENU_LAYOUT_CUSTOM:
			VALIDATE(temp->Initialize(m_pDX10_Renderer, m_sprites[_spriteIndex],
				m_position.x,
				m_position.y,
				m_sprites[_spriteIndex]->GetWidth() * _scale,
				m_sprites[_spriteIndex]->GetHeight() * _scale));
			break;
		}
		
		m_buttons.back()->SetButton(temp, _option, _spriteIndex, _scale, _col, _row);

		if (m_buttons.size() == 1)
		{
			m_buttons.back()->m_pButton->SetState(BUTTON_STATE_HOVER);
		}
	}
	
	return true;
}

bool Menu::AddToggleButton(TButton* _button, UINT _spriteIndex, bool _toggled, float _scale)
{
	if (_spriteIndex < m_sprites.size())
	{
		m_toggleButtons.push_back(new GUI_Button());

		VALIDATE(m_toggleButtons.back()->Initialize(m_pDX10_Renderer, m_sprites[_spriteIndex],
			_button->m_pButton->GetPosition().x + _button->m_pButton->GetWidth() + m_space,
			_button->m_pButton->GetPosition().y,
			m_sprites[_spriteIndex]->GetWidth() * _scale,
			m_sprites[_spriteIndex]->GetHeight() * _scale));
	}
	return true;
}

bool Menu::AddTitle(UINT _spriteIndex, float _scale, v2float _position)
{
	if (!m_title)
	{
		m_title = new GUI_Button();
		switch (m_layout)
		{
		case MENU_LAYOUT_CENTRE:
		{
			float m_screenWidth = 0.0f;
			float m_screenHeight = 0.0f;

			RECT rect;
			if (GetClientRect(*m_pHWnd, &rect))
			{
				m_screenWidth = static_cast<float>(rect.right - rect.left);
				m_screenHeight = static_cast<float>(rect.bottom - rect.top);
			}

			m_screenWidth = m_screenWidth * 0.5f - (m_sprites[_spriteIndex]->GetWidth() * 0.25f);
			m_screenHeight = m_screenHeight * 0.25f;

			if (m_position.x + m_screenWidth + m_sprites[_spriteIndex]->GetWidth() * _scale > static_cast<float>(rect.right - rect.left))
			{
				m_screenWidth = static_cast<float>(rect.right - rect.left) * 0.125f * 0.125f;
			}

			VALIDATE(m_title->Initialize(m_pDX10_Renderer, m_sprites[_spriteIndex],
				m_position.x + m_screenWidth,
				m_position.y + m_screenHeight,
				m_sprites[_spriteIndex]->GetWidth() * _scale,
				m_sprites[_spriteIndex]->GetHeight() * _scale));
		}
			
			break;
		case MENU_LAYOUT_CUSTOM:
			VALIDATE(m_title->Initialize(m_pDX10_Renderer, m_sprites[_spriteIndex],
				m_position.x + _position.x,
				m_position.y + _position.y,
				m_sprites[_spriteIndex]->GetWidth() * _scale,
				m_sprites[_spriteIndex]->GetHeight() * _scale));
			break;
		}
		
	}

	return true;
}

BUTTON_STATE Menu::GetButtonState(UINT _index)
{
	if (_index < m_buttons.size())
	{
		return m_buttons[_index]->m_pButton->GetState();
	}
	return BUTTON_STATE_DEACTIVATED;
}

UINT Menu::GetCurrentMenuItem()
{
	return m_menuItem;
}

MENU_STATE Menu::GetMenuState()
{
	return m_state;
}

TButton* Menu::GetButton(UINT _index)
{
	if (_index < m_buttons.size())
	{
		return m_buttons[_index];
	}
	return NULL;
}

void Menu::SetPosition(v2float _position)
{
	m_position = _position;
}

void Menu::SetButtonPosition(UINT _index, v2float _position)
{
	m_buttons[_index]->m_pButton->SetPosition(_position);
}

void Menu::ToggleButton(UINT _index)
{
	if (m_toggleButtons[_index]->GetState() == BUTTON_STATE_DEFAULT)
		m_toggleButtons[_index]->SetState(BUTTON_STATE_HOVER);
	else
		m_toggleButtons[_index]->SetState(BUTTON_STATE_DEFAULT);
}

void Menu::Reset()
{
	m_state = MENU_STATE_DEFAULT;
	
	// Reset all buttons
	/*m_menuItem = 0;
	for (auto button = m_buttons.begin(); button != m_buttons.end(); button++)
	{
		(*button)->m_pButton->SetState(BUTTON_STATE_DEFAULT);
	}

	m_buttons[0]->m_pButton->SetState(BUTTON_STATE_HOVER);*/
}