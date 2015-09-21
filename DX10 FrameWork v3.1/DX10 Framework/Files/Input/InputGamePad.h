//
// Bachelor of Software Engineering
// Media Design School 
// Auckland
// New Zealand 
// 
// (c) 2005 - 2015 Media Design School 
// 
// File Name : CInputGamePad.h
// Description : Input system to manage the Xbox 360 game pads using XInput api
// Author : Jc Fowles 
// Mail : Jc.Fowles@mediadesign.school.nz 
//
#pragma once

#ifndef __CINPUT_GAMEPAD_H__
#define __CINPUT_GAMEPAD_H__

// Library Link
//#pragma comment(lib, "Xinput.lib")
#pragma comment(lib, "XInput9_1_0.lib")

// Utility Include (for Windows.h)
#include "../Utility/Utilities.h"

// Library Include
#include <XInput.h>

// Local Includes


// TO DO JC: Move to a input utils

// Constants

// XInput Button values
static const WORD XINPUT_Buttons[] = 
{
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK
};

// Structs

/***********************
* XButtonIDs: Struct to hold the XInput Button IDs
* @author: Jc Fowles
********************/
struct XButtonIDs
{
	/***********************
	* XButtonIDs: Default Constructor for XButtonIDs struct
	* @author: Jc Fowles
	* @return:
	********************/
	XButtonIDs()
	{
		// These values are used to index the XINPUT_Buttons array,
		// accessing the matching XINPUT button value
		
		ActionButton_A = 0;
		ActionButton_B = 1;
		ActionButton_X = 2;
		ActionButton_Y = 3;

		DPad_Up = 4;
		DPad_Down = 5;
		DPad_Left = 6;
		DPad_Right = 7;

		Bumper_L = 8;
		Bumper_R = 9;

		Thumbstick_L = 10;
		Thumbstick_R = 11;

		Start = 12;
		Back = 13;

		/*LJoyStick_Up = 14;
		LJoyStick_Down = 15;
		LJoyStick_left = 16;
		LJoyStick_Right = 17;

		RJoyStick_Up = 18;
		RJoyStick_Down = 19;
		RJoyStick_left = 20;
		RJoyStick_Right = 21;

		Trigger_L = 22;
		Trigger_R = 23;*/

	};

	// Action Buttons
	int ActionButton_A;
	int ActionButton_B;
	int ActionButton_X;
	int ActionButton_Y;

	// Directional Pad (D-Pad)
	int DPad_Up;
	int DPad_Down;
	int DPad_Left;
	int DPad_Right;

	// Bumper buttons
	int Bumper_L;
	int Bumper_R;

	// Thumbstick buttons
	int Thumbstick_L;
	int Thumbstick_R;

	// 'START' button
	int Start; 

	// 'BACK' button
	int Back;  

};

/***********************
* XButtonIDs: Struct to hold the XInput Button IDs
* @author: Jc Fowles
********************/
struct XStickDirectionIDs
{
	XStickDirectionIDs()
	{
		LStick_Up = 0;
		LStick_Down = 1;
		LStick_Left = 2;
		LStick_Right = 3;
		
		RStick_Up = 4;
		RStick_Down = 5;
		RStick_Left = 6;
		RStick_Right = 7;
 	}

	// Joystick 
	int LStick_Up ;
	int LStick_Down ;
	int LStick_Left ;
	int LStick_Right ;

	int RStick_Up ;
	int RStick_Down ;
	int RStick_Left ;
	int RStick_Right ;
};

class InputGamePad
{
	// Member Functions
public:

	/***********************
	* CInputManager: Default Constructor for Game Pad Input Class
	* @author: Jc Fowles
	* @return:
	********************/
	InputGamePad();
	
	/***********************
	* ~CInputManager: Default Destructor for Game Pad Input Class
	* @author: Jc Fowles
	* @return:
	********************/
	~InputGamePad();

	/***********************
	* Initialise: Initialise the Game Pad Input
	* @author: Jc Fowles
	* @parameter: _gamepadIndex: Index to which of the four controllers you are wanting to read input from 
	* @return: succesfull Initialisation
	********************/
	bool Initialise(int _gamepadIndex);

	/***********************
	* Update: Update the the State of the Gamepad
	* @author: Jc Fowles
	* @return: void: 
	********************/
	void PreProcess();		
	
	/***********************
	* RefreshState: Update button states for next frame
	* @author: Jc Fowles
	* @return: void:
	********************/
	void PostProcess(); 
	
	// Thumbstick Functions 
	
	/***********************
	* LStick_InDeadZone: Return whether the Left stick is in a dead zone
	* @author: Jc Fowles
	* @return: bool: Whether the Left stick is in a dead zone (True is one or both Axes are in the DeadZone)
	********************/
	bool LStick_InDeadZone();

	/***********************
	* RStick_InDeadZone: Return whether the Right stick is in a dead zone
	* @author: Jc Fowles
	* @return: bool: Whether the Right stick is in a dead zone (True is one or both Axes are in the DeadZone)
	********************/
	bool RStick_InDeadZone();

	/***********************
	* GetLStickAxis: Get the Value of the X and Y axes of the Left stick
	* @author: Jc Fowles
	* @return: v2float: The Value of the X and Y axes of the Left stick
	********************/
	v2float	GetLStickAxis();

	/***********************
	* GetRStickAxis: Get the Value of the X and Y axes of the Right stick
	* @author: Jc Fowles
	* @return: v2float: The Value of the X and Y axes of the Right stick
	********************/
	v2float	GetRStickAxis();

	/***********************
	* GetStickDirectionPressed: Get whether a stick has been pressed in a certian direction based on the passed in Stick Direction ID
	* @author: Jc Fowles
	* @parameter: _direction: The Stick Direction ID of which stick in what direction you are checking
	* @return: bool: Whether the Stick Direction is pressed (True if the Stick Direction is pressed)
	********************/
	bool GetStickDirectionPressed(int _direction);

	/***********************
	* GetButtonDown: Get whether a stick has been pressed in a certian direction was pressed (gone down) in this frame based on the passed in Stick Direction ID
	* @author: Jc Fowles
	* @parameter: _direction:  The Stick Direction ID of which stick in what direction you are checking
	* @return: bool: Whether the Stick Direction was pressed (gone down) in this frame (True if the Stick Direction is down)
	********************/
	bool GetStickDirectionDown(int _direction);

	// Trigger Functions 

	/***********************
	* GetLTrigger: Get the Value of the Left Trigger
	* @author: Jc Fowles
	* @return: float: The Value of the Left Trigger
	********************/
	float GetLTrigger(); 
	
	/***********************
	* GetRTrigger: Get the Value of the Right Trigger
	* @author: Jc Fowles
	* @return: float: The Value of the Right Trigger
	********************/
	float GetRTrigger(); 

	// Button Functions

	/***********************
	* GetButtonPressed: Get whether the button is pressed based on the passed in button ID 
	* @author: Jc Fowles
	* @parameter: _button: The Button ID of the button you are checking
	* @return: bool: Whether the button is pressed (True if the button is pressed)
	********************/
	bool GetButtonPressed(int _button);

	/***********************
	* GetButtonDown: Get whether the button was pressed (gone down) in this frame based on the passed in button ID
	* @author: Jc Fowles
	* @parameter: _button: The Button ID of the button you are checking
	* @return: bool: Whether the button was pressed (gone down) in this frame (True if the button is down)
	********************/
	bool GetButtonDown(int _button); 
	
	// Vibrate Functions

	/***********************
	* Vibrate: Vibrate the gamepad
	* @author: Jc Fowles
	* @parameter: _LMotorSpeed: The Speed of the Left Motors Vibrations (0.0f No Vibration, 1.0f Max Vibration)
	* @parameter: _RMotorSpeed: The Speed of the Right Motors Vibrations (0.0f No Vibration, 1.0f Max Vibration)
	* @return: void: 
	********************/
	void Vibrate(float _LMotorSpeed, float _RMotorSpeed);

	/***********************
	* StopVibrate: Stop Vibrating the gamepad 
	* @author: Jc Fowles
	* @return: void:
	********************/
	void StopVibrate();

	// Utility Functions 
	/***********************
	* GetIndex: Return the Gamepad Index (which of the four connected contollers)
	* @author: Jc Fowles
	* @return: int: The Gamepad Index
	********************/
	int GetIndex(){ return m_gamepadIndex; };

	/***********************
	* Connected: Return the Connected State of the Gamepad 
	* @author: Jc Fowles
	* @return: bool: The Conected State of the Gamepad (True if the Gamepad is Connected)
	********************/
	bool Connected();   

protected:
private:
	/***********************
	* GetState: Return the Current Gamepad State
	* @author: Jc Fowles
	* @return: XINPUT_STATE: The Current Gamepad State
	********************/
	XINPUT_STATE GetState();

	  // Member Variables
public:
protected:
private:

	// Current gamepad state
	XINPUT_STATE m_gamepadState; 
	
	// Gamepad index (Which one of the 4 game pads)
	int m_gamepadIndex;  
	  
	// Total gamepad buttons
	static const int ButtonCount = 14;   
	
	// Previous frame button states
	bool Prev_ButtonStates[ButtonCount];
	// Current frame button states
	bool ButtonStates[ButtonCount];      
  	// Buttons pressed on current frame
	bool Gamepad_ButtonsDown[ButtonCount];

	// Total gamepad buttons
	static const int StickCount = 8;

	// Previous frame Stick states
	bool Prev_StickStates[StickCount];
	// Current frame Stick states
	bool StickStates[ButtonCount];
	// Stick pressed on current frame
	bool Gamepad_StickDown[ButtonCount];

};

#endif; //__CINPUT_GAMEPAD_H__