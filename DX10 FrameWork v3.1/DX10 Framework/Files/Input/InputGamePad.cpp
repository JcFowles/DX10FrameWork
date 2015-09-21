//
// Bachelor of Software Engineering
// Media Design School 
// Auckland
// New Zealand 
// 
// (c) 2005 - 2015 Media Design School 
// 
// File Name : CInputGamePad.h
// Description : Input system to manage the Xbox 360 game oads using XInput api
// Author : Jc Fowles 
// Mail : Jc.Fowles@mediadesign.school.nz 
//

// This include
#include "InputGamePad.h"


// Define the 'XButtonIDs' struct as 'XButtons'
XButtonIDs XButtons;
XStickDirectionIDs XStickDirections;

InputGamePad::InputGamePad()
{
}

InputGamePad::~InputGamePad()
{
}

bool InputGamePad::Initialise(int _gamepadIndex)
{
	if ((_gamepadIndex >= 0) &&
		(_gamepadIndex <= 4))
	{
		m_gamepadIndex = _gamepadIndex - 1;
	}
	else
	{
		return false;
	}

	// Initialise the Button Arrays
	for (int i = 0; i < ButtonCount; i++)
	{
		Prev_ButtonStates[i] = false;
		ButtonStates[i] = false;
		Gamepad_ButtonsDown[i] = false;
	}

	// Initialise the Button Arrays
	for (int i = 0; i < StickCount; i++)
	{
		Prev_StickStates[i] = false;
		StickStates[i] = false;
		Gamepad_StickDown[i] = false;
	}

	// return succesful initialization
	return true;
}

void InputGamePad::PreProcess()
{
	// Get the Current GamepadState
	m_gamepadState = GetState();

	// Iterate through all gamepad buttons
	for (int i = 0; i < ButtonCount; i++)
	{
		// Set button state for current frame
		ButtonStates[i] = ((m_gamepadState.Gamepad.wButtons & XINPUT_Buttons[i]) == XINPUT_Buttons[i]);

		// Set 'DOWN' state for current frame
		Gamepad_ButtonsDown[i] = ((!Prev_ButtonStates[i]) && (ButtonStates[i]));
	}

	// Iterate through all gamepad Stick
	for (int i = 0; i < StickCount; i++)
	{
		if (!LStick_InDeadZone())
		{
			v2float LeftAxis = GetLStickAxis();
			v2float RightAxis = GetRStickAxis();
			
			switch (i)
			{
				case 0:		// LJoyStick_Up
				{
					if (LeftAxis.y > 0.8f)
					{
						// Left Stick is Up
						StickStates[i] = true;
					}
					else
					{
						StickStates[i] = false;
					}
				}
					break;
				case 1:		// LJoyStick_Down
				{
					if (LeftAxis.y < -0.8f)
					{
						// Left Stick is Down
						StickStates[i] = true;
					}
					else
					{
						StickStates[i] = false;
					}
				}
					break;
				case 2:		// LJoyStick_left
				{
					if (LeftAxis.x < -0.8f)
					{
						// Left Stick is Left
						StickStates[i] = true;
					}
					else
					{
						StickStates[i] = false;
					}
				}
					break;
				case 3:		// LJoyStick_right
				{
					if (LeftAxis.x > 0.8f)
					{
						// Left Stick is Right
						StickStates[i] = true;
					}
					else
					{
						StickStates[i] = false;
					}
				}
					break;
				case 4:		// RJoyStick_Up
				{
					if (RightAxis.y > 0.8f)
					{
						// Right Stick is Up
						StickStates[i] = true;
					}
					else
					{
						StickStates[i] = false;
					}
				}
					break;
				case 5:		// RJoyStick_Down
				{
					if (RightAxis.y < -0.8f)
					{
						// Right Stick is Down
						StickStates[i] = true;
					}
					else
					{
						StickStates[i] = false;
					}
				}
					break;
				case 6:		// RJoyStick_Left
				{
					if (RightAxis.x < -0.8f)
					{
						// Right Stick is Left
						StickStates[i] = true;
					}
					else
					{
						StickStates[i] = false;
					}
				}
					break;
				case 7:		// RJoyStick_Right
				{
					if (RightAxis.x > 0.8f)
					{
						// Right Stick is Right
						StickStates[i] = true;
					}
					else
					{
						StickStates[i] = false;
					}
				}
					break;
				default: break;
			}
			
		}
		else
		{
			StickStates[i] = false;
		}
		
		// Set 'DOWN' state for current frame
		Gamepad_StickDown[i] = ((!Prev_StickStates[i]) && (StickStates[i]));
	}
}

void InputGamePad::PostProcess()
{
	// Store the current frames button values in previous button states
	memcpy(Prev_ButtonStates, ButtonStates,	sizeof(Prev_ButtonStates));

	// Store the current frames Stick Direction values in previous button states
	memcpy(Prev_StickStates, StickStates, sizeof(Prev_StickStates));
}

// Thumbstick Functions

bool InputGamePad::LStick_InDeadZone()
{
	// Get the X and Y axis of the left stick
	short x = m_gamepadState.Gamepad.sThumbLX;
	short y = m_gamepadState.Gamepad.sThumbLY;

	// Check the X Axis 
	if ((x > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ||
		(x < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		// The X Axis is Outside of the Deadzone 
		return false;
	}

	// Check the Y Axis
	if ((y > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ||
		(y < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		// The Y Axis is Outside of the Deadzone 
		return false;
	}

	// One or Both Axes are inside of the Deadzone
	return true;

}

bool InputGamePad::RStick_InDeadZone()
{
	// Get the X and Y axis of the left stick
	short X = m_gamepadState.Gamepad.sThumbLX;
	short Y = m_gamepadState.Gamepad.sThumbLY;

	// Check the X Axis 
	if ((X > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ||
		(X < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		// The X Axis is Outside of the Deadzone 
		return false;
	}

	// Check the Y Axis
	if ((Y > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ||
		(Y < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		// The Y Axis is Outside of the Deadzone 
		return false;
	}

	// One or Both Axes are inside of the Deadzone
	return true;
}

v2float	InputGamePad::GetLStickAxis()
{
	// Get the X and Y axis of the left stick
	short X = m_gamepadState.Gamepad.sThumbLX;
	short Y = m_gamepadState.Gamepad.sThumbLY;

	v2float leftStickAxisXY;
	// convert to a float between 0.0f and 1.0f
	leftStickAxisXY.x = (static_cast<float>(X) / 32768.0f);
	leftStickAxisXY.y = (static_cast<float>(Y) / 32768.0f);

	// Return the Left stick X and Y Axes
	return leftStickAxisXY;
}

v2float	InputGamePad::GetRStickAxis()
{
	// Get the X and Y axis of the left stick
	short X = m_gamepadState.Gamepad.sThumbRX;
	short Y = m_gamepadState.Gamepad.sThumbRY;

	v2float rightStickAxisXY;
	// convert to a float value between 0.0f and 1.0f
	rightStickAxisXY.x = (static_cast<float>(X) / sizeof(short));
	rightStickAxisXY.y = (static_cast<float>(Y) / sizeof(short));

	// Return the Right stick X and Y Axes
	return rightStickAxisXY;
}

bool InputGamePad::GetStickDirectionPressed(int _Direction)
{
	return StickStates[_Direction];
}

bool InputGamePad::GetStickDirectionDown(int _Direction)
{
	return Gamepad_StickDown[_Direction];
}

// Trigger Functions

float InputGamePad::GetLTrigger()
{
	// Get the Value of the Left Trigger
	BYTE leftTrigger = m_gamepadState.Gamepad.bLeftTrigger;

	if (leftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		// XInput trigger values range from 0 to 255. 
		// Therefore Divide by 255 to convert the value
		// to the range between 0.0f and 1.0f
		return (leftTrigger / 255.0f);
	}
	else
	{
		// Left Trigger was not Pressed
		return 0.0f;
	}
}

float InputGamePad::GetRTrigger()
{
	// Get the Value of the Left Trigger
	BYTE rightTrigger = m_gamepadState.Gamepad.bLeftTrigger;

	if (rightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		// XInput trigger values range from 0 to 255. 
		// Therefore Divide by 255 to convert the value
		// to the range between 0.0f and 1.0f
		return (rightTrigger / 255.0f);
	}
	else
	{
		// Right Trigger was not Pressed
		return 0.0f;
	}
}

// Button Functions

bool InputGamePad::GetButtonPressed(int _button)
{

	// To check if a Button is pressed, Get the ‘wButtons‘ Value from the Gamepad State
	// Then use the bitwise AND operator (‘&’), to check it against the	specified buttons

	if (m_gamepadState.Gamepad.wButtons & XINPUT_Buttons[_button])
	{
		// The button is pressed
		return true;
	}
	else
	{
		// The button is not pressed
		return false;
	}
}

bool InputGamePad::GetButtonDown(int _button)
{
	return Gamepad_ButtonsDown[_button];
}

// Vibrate Functions

void InputGamePad::Vibrate(float _LMotorSpeed, float _RMotorSpeed)
{
	// Vibration State
	XINPUT_VIBRATION VibrationState;

	// Clear the memory of the vibration state
	ZeroMemory(&VibrationState, sizeof(XINPUT_VIBRATION));

	// Calculate the vibration values 
	// XInput’s default vibration values range from 0 to 65535
	// So convert the passed in 0.0f to 1.0f values to that
	int LMotorSpeed = int(_LMotorSpeed * 65535.0f);
	int RMotorSpeed = int(_RMotorSpeed * 65535.0f);

	// Set the vibrations
	VibrationState.wLeftMotorSpeed = LMotorSpeed;
	VibrationState.wRightMotorSpeed = RMotorSpeed;

	// Set the Vibration state
	XInputSetState(m_gamepadIndex, &VibrationState);
}

void InputGamePad::StopVibrate()
{
	// Call the vibrate function with no vibrations on each motor
	Vibrate(0.0f, 0.0f);
}

// Utility Functions

XINPUT_STATE InputGamePad::GetState()
{
	// Temporary XINPUT_STATE to return
	XINPUT_STATE tempGamepadState;

	// Clear the memory
	ZeroMemory(&tempGamepadState, sizeof(XINPUT_STATE));

	// Get the state of the gamepad
	XInputGetState(m_gamepadIndex, &tempGamepadState);

	// Return the gamepad state
	return tempGamepadState;
};

bool InputGamePad::Connected()
{
	// Clear the memory 
	ZeroMemory(&m_gamepadState, sizeof(XINPUT_STATE));

	// Get the State of the Gamepad
	// and store it in the member variable
	DWORD result = XInputGetState(m_gamepadIndex, &m_gamepadState);

	// Check the result of getting the input state
	if (result == ERROR_SUCCESS)
	{
		// The Gamepad state was recieved therefor 
		// the Gamepad is connected
		return true;
	}
	else
	{
		// The Gamepad state was not recieved therefor 
		// the Gamepad is not connected
		return false;
	}
}