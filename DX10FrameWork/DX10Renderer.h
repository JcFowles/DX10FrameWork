/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Application.h
* Description : The core of the Application is run here. The link between all components. //TO DO
* Author :	Jc Fowles
* Mail :	Jc.Fowles@mediadesign.school.nz
*/
#pragma once

// Library Includes

// Local Includes
#include "DX10Utilities.h"

class CDX10Renderer
{
	// Memeber Functions
public:

	// Creation and Deletion

	/***********************
	* CDX10Renderer: Default Constructor for the DX10Renderer 
	* @author: Jc Fowles
	* @return: 
	********************/
	CDX10Renderer();

	/***********************
	* ~CDX10Renderer: Default Destructor for the DX10Renderer
	* @author: Jc Fowles
	* @return:
	********************/
	~CDX10Renderer();

	/***********************
	* Initialise: Initialise the DX10Renderer
	* @author: Jc Fowles
	* @Parameter: _windowWidth: Width of the application window
	* @Parameter: _windowHeight: Height of the application window
	* @Parameter: _hWND: Handle to the Application window
	* @return: bool: Successful Initialisation
	********************/
	bool Initialise(int _windowWidth, int _windowHeight, HWND _hWND);

	/***********************
	* ShutDown: Shuts down the DX10Renderer and releases all memory Created by it.
	* @author: Jc Fowles
	* @return: void
	********************/
	void ShutDown();

	// Renderer Functionality

	/***********************
	* InitialiseDeviceAndSwapChain: Initialise the DX10 Device and Swap Chain
	* @author: Jc Fowles
	* @return: bool: Successful Initialisation
	********************/
	bool InitialiseDeviceAndSwapChain();

	/***********************
	* onResize: Recreate Depth and Render Views when resizing the application
	* @author: Jc Fowles
	* @return: void
	********************/
	void onResize();

	/***********************
	* RenderFrame: Render a single frame
	* @author: Jc Fowles
	* @return: void
	********************/
	void RenderFrame();

	// Extra Functionality

	/***********************
	* ToggleFullscreen: Toggle Full screen mode
	* @author: Jc Fowles
	* @return: void
	********************/
	void ToggleFullscreen();

	// TO DO: Add Set Rasterizer stage function

protected:
private:

	// Memeber Variables
public:
protected:
private:

	// Window Variables
	HWND m_hWnd;
	int m_windowWidth;
	int m_windowHeight;
	bool m_fullScreen;

	// DX10 Variables
	ID3D10Device*    m_pDX10Device;
	IDXGISwapChain*  m_pDX10SwapChain;
	ID3D10RenderTargetView* m_pRenderTargetView;

	D3D10_DRIVER_TYPE m_DX10DriverType;
	D3DXCOLOR m_clearColor;

};

