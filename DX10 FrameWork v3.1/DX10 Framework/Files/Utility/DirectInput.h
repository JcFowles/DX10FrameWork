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

// Inclusion Guards
#pragma once
#ifndef __DIRECTINPUT_H__
#define __DIRECTINPUT_H__

// Linker Includes
#pragma comment (lib, "dinput8.lib")

#ifndef DIRECTINPUT_VERSION
	#define DIRECTINPUT_VERSION 0x0800
#endif

// Library Includes
#include <windows.h>
#include <dinput.h>


class DirectInput
{
public:

	/***********************
	* CDirectInput: Default Constructor for Direct Input class
	* @author: Callan Moore
	********************/
	DirectInput();

	/***********************
	* ~CDirectInput: Default Destructor for Direct Input class
	* @author: Callan Moore
	********************/
	~DirectInput();

	/***********************
	* Initialise: Initialise the Direct Input
	* @author: Callan Moore
	* @Parameter: hInstance: Handle to the current instance
	* @Parameter: _hWnd: Handle to the Window of the application
	* @return: bool: Successful or not
	********************/
	bool Initialise(HINSTANCE hInstance, HWND _hWnd);

	/***********************
	* DetectMouseInput: Detect Mouse Input 
	* @author: Callan Moore
	* @Parameter: _pMouseX: Storage Variable for the mouse movement on the X axis
	* @Parameter: _pMouseY: Storage Variable for the mouse movement on the Y axis
	* @return: void
	********************/
	void DetectMouseInput(float* _pMouseX, float* _pMouseY);

private:
	IDirectInputDevice8* m_DIMouse;
	DIMOUSESTATE m_mousePrevState;
	DIMOUSESTATE m_mouseCurrState;
	IDirectInput8* m_pDirectInput;
};
#endif	// __DIRECTINPUT_H__