/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DirectInput.h
* Description : Handles mouse input
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "DirectInput.h"

DirectInput::DirectInput()
{
	
}

DirectInput::~DirectInput()
{
	m_DIMouse->Unacquire();
	m_pDirectInput->Release();
}

bool DirectInput::Initialise(HINSTANCE hInstance, HWND _hWnd)
{
	DirectInput8Create(hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pDirectInput,
		NULL);

	m_pDirectInput->CreateDevice(GUID_SysMouse,
		&m_DIMouse,
		NULL);

	m_DIMouse->SetDataFormat(&c_dfDIMouse);
	m_DIMouse->SetCooperativeLevel(_hWnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
	m_DIMouse->Acquire();

	return true;
}

void DirectInput::DetectMouseInput(float* _yawChange, float* _pitchChange)
{
	HRESULT hr = m_DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseCurrState);
	if (FAILED(hr))
	{
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
		{
			m_DIMouse->Acquire();
		}
	}
	else
	{
		// Detect the change in mouse state (if any)
		if ((m_mouseCurrState.lX != m_mousePrevState.lX) || (m_mouseCurrState.lY != m_mousePrevState.lY))
		{
			*_yawChange += m_mouseCurrState.lX;
			*_pitchChange += m_mouseCurrState.lY;
	
			m_mousePrevState = m_mouseCurrState;
		}
	}
	//m_mousePrevState = m_mouseCurrState;
}