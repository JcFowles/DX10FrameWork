//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	:	Menu.h
// Description	:	This wraps all the menu objects, handles the menu item interactions and its current state.
// Author		:	Juran Griffith
// Mail			:	juran.griffith@mediadesignschool.com
//

// Inclusion Guards
#pragma once
#ifndef __MENU_H__
#define __MENU_H__

// Local Includes
#include "..\DX10\DX10\2D Objects\GUI_Button.h"
#include "..\Input\InputGamePad.h"

enum MENU_STATE
{
	// Main menu states
	MENU_STATE_DEFAULT,
	MENU_STATE_START,
	MENU_STATE_INSTRUCTIONS,
	MENU_STATE_OPTIONS,
	MENU_STATE_EXIT,

	// Options menu states
	MENU_STATE_FULL_SCREEN,
	MENU_STATE_SOUND,
	MENU_STATE_RUMBLE,

	// Match menu states
	MENU_STATE_PLAYERS_2,
	MENU_STATE_PLAYERS_3,
	MENU_STATE_PLAYERS_4,

	// Pause menu states (reuses the main menu states)
	MENU_STATE_RESUME
};

enum MENU_LAYOUT
{
	MENU_LAYOUT_CENTRE,
	MENU_LAYOUT_CUSTOM
};

struct TButton
{
	~TButton()
	{
		ReleasePtr(m_pButton);
	}

	void SetButton(GUI_Button* _pButton, MENU_STATE _option, UINT _index, float _scale, UINT _col, UINT _row)
	{
		m_pButton = _pButton;
		m_option = _option;
		m_index = _index;
		m_scale = _scale;
		m_pButton->SetColumnIndex(_col);
		m_pButton->SetRowIndex(_row);
	}

	GUI_Button* m_pButton = 0;
	MENU_STATE m_option = MENU_STATE_DEFAULT;
	UINT m_index = 0;
	float m_scale = 1.0f;
};

class Menu
{
	// Functions
	public:
		/*******************
		-> Default constructor.
		@author:	Juran Griffith.
		@parameter:	None.
		@return:	...
		********************/
		Menu();

		/*******************
		-> Default destructor.
		@author:	Juran Griffith.
		@parameter:	None.
		@return:	...
		********************/
		~Menu();

		/***********************
		-> Initialize the object
		@author:	Juran Griffith.
		@parameter: _pDX10_Renderer	- The graphics device.
		@parameter: _pHWnd			- The handler to the window.
		@parameter: _gamePad		- The gamepad controller to listen to.
		@parameter: _layout			- How to layout the menu items.
		@return:	bool			- Successful or not
		********************/
		bool Initialize(DX10_Renderer* _pDX10_Renderer, HWND* _pHWnd, InputGamePad* _pGamepad, MENU_LAYOUT _layout = MENU_LAYOUT_CENTRE);

		/*******************
		-> Draws the object
		@author:	Juran Griffith.
		@parameter:	None.
		@return:	void
		********************/
		void Draw();

		/*******************
		-> Process the object
		@author:	Juran Griffith.
		@parameter:	_deltaTime	- The application change in time.
		@return:	void
		********************/
		void Process(float _deltaTime);

		/***********************
		-> Adds a new sprite to the menus list of sprites (may need to improve this). This also loads the sprite aswell.
		@author:	Juran Griffith.
		@parameter: _filename		- The filename/path of the image
		@parameter: _imageWidth		- The image width.
		@parameter: _imageHeight	- The image height.
		@parameter: _sliceWidth		- How many slices along the width of the image to do to split the image up into sections. (For sprite sheets etc...)
		@parameter: _sliceHeight	- How many slices along the height of the image to do to split the image up into sections. (For sprite sheets etc...)
		@return:	bool			- True if added otherwise false.
		********************/
		bool AddSprite(std::string _filename, UINT _imageWidth, UINT _imageHeight, UINT _sliceWidth = 1, UINT _sliceHeight = 1);

		/***********************
		-> Adds a new button to the menu. By default it is placed after the last button added.
		@author:	Juran Griffith.
		@parameter: _option			- The menu state option this button refers to
		@parameter: _spriteIndex	- The sprite index to set as the buttons image. (make sure to load a sprite to the menu object using the add sprite function)
		@parameter: _scale			- How big to make the object.
		@parameter: _position		- The position to put the button.
		@parameter: _col			- The col image index
		@parameter: _row			- The row image index
		@return:	bool			- True if added otherwise false.
		********************/
		bool AddButton(MENU_STATE _option, UINT _spriteIndex, float _scale = 1.0f, UINT _col = 0, UINT _row = 0);

		/***********************
		-> Adds a new button to the menu. By default it is placed after the last button added.
		@author:	Juran Griffith.
		@parameter: _button			- The button struct to attach this toggle to.
		@parameter: _spriteIndex	- The sprite index to set as the buttons image. (make sure to load a sprite to the menu object using the add sprite function)
		@parameter: _toggled		- Sets the toggled buttons intial state.
		@parameter: _scale			- How big to make the object.
		@return:	bool			- True if added otherwise false.
		********************/
		bool AddToggleButton(TButton* _button, UINT _spriteIndex, bool _toggled = true, float _scale = 1.0f);

		/***********************
		-> Adds a title to the menu.
		@author:	Juran Griffith.
		@parameter: _spriteIndex	- The sprite index to set as the buttons image. (make sure to load a sprite to the menu object using the add sprite function)
		@parameter: _scale			- How big to make the object.
		@parameter: _position		- Where to place the item. (make sure to set the menu layout to custom to use this)
		@return:	bool			- True if added otherwise false.
		********************/
		bool AddTitle(UINT _spriteIndex, float _scale = 1.0f, v2float _position = v2float(0.0f, 0.0f));

		/***********************
		-> Gets the current button state based on the menu index provided.
		@author:	Juran Griffith.
		@parameter: _index			- The button index to check.
		@return:	BUTTON_STATE	- The current buttons state.
		********************/
		BUTTON_STATE GetButtonState(UINT _index);

		/***********************
		-> Gets the button at the current index.
		@author:	Juran Griffith.
		@parameter: _index		- The button index.
		@return:	TButton		- The pointer to the button struct in this menu
		********************/
		TButton* GetButton(UINT _index);

		/***********************
		-> Gets the current menu item the menu is hovering over(for mouse) or at(xbox)
		@author:	Juran Griffith.
		@parameter: None.
		@return:	UINT	- The current menu item
		********************/
		UINT GetCurrentMenuItem();

		/***********************
		-> Gets the menus current state
		@author:	Juran Griffith.
		@parameter: None.
		@return:	MENU_STATE	- The current menu state
		********************/
		MENU_STATE GetMenuState();

		/***********************
		-> Sets the menus position
		@author:	Juran Griffith.
		@parameter: _position		- The new position to set the menu
		@return:	void
		********************/
		void SetPosition(v2float _position);

		/***********************
		-> Sets the current index buttons position.
		@author:	Juran Griffith.
		@parameter: _index		- The button index.
		@parameter: _position	- The new position for the button.
		@return:	void
		********************/
		void SetButtonPosition(UINT _index, v2float _position);

		/***********************
		-> Resets the menu states
		@author:	Juran Griffith.
		@parameter: None.
		@return:	void
		********************/
		void Reset();

		/***********************
		-> Toggles the button at the given index
		@author:	Juran Griffith.
		@parameter: _index		- The toggle button index.
		@return:	void
		********************/
		void ToggleButton(UINT _index);
	protected:
	private:

	// Variables
	public:
	protected:
	private:
		HWND*						m_pHWnd;
		DX10_Renderer*				m_pDX10_Renderer;

		float						m_space;

		// Sprite
		UINT						m_menuItem;
		std::vector<DXSprite*>		m_sprites;
		std::vector<TButton*>		m_buttons;
		std::vector<GUI_Button*>	m_toggleButtons;

		DX10_Shader_Sprite*			m_pShader_Sprite;
		v2float						m_position;
		GUI_Button*					m_title;

		// Input
		XButtonIDs					m_XButtons;	//TO DO Jc - Maybe use enums
		XStickDirectionIDs			m_XStickDirections; //TO DO Jc - Maybe use enums
		InputGamePad*				m_pGamepad;

		// State
		MENU_STATE					m_state;
		MENU_LAYOUT					m_layout;

		float						m_elaspedTime;
		UINT						m_imageIndex;
};

#endif