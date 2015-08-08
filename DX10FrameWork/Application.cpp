/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Application.cpp
* Description : The core of the Application is run here. The link between all components. //TO DO
* Author :	Jc Fowles
* Mail :	Jc.Fowles@mediadesign.school.nz
*/

// This Include
#include "Application.h"

// *** Windows Functions ***

// Static Variables
CApplication* CApplication::s_pApp = 0;

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _CmdShow)
{
	// Create the Application 
	CApplication* pApp = CApplication::GetInstance();
	
	// Create a window for the application based on the width/hieght and Title given
	// Check if Created succesfully 
	if (pApp->CreateAndRegisterWindow(_hInstance, 1000, 1000, L"Basic Window" ) )
	{
		VALIDATE(pApp->Initialise());
		pApp->RunApp();
	}

	// Delete all contents of the Application
	pApp->DestroyInstance();
	return 0;
}

LRESULT CALLBACK CApplication::WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	// Retrieve the Instance of the Application
	CApplication* pApp = CApplication::GetInstance();

	// Switch case dependent on the message sent
	switch (_uiMsg)
	{
	case WM_DESTROY:	
	// Fall Through
	case WM_CLOSE:
	{
		// Kill the application, this sends a WM_QUIT message.
		PostQuitMessage(0);
	}
		break;
	case WM_KEYDOWN:
	{
		// Only accepts the input once per key press
		if (((_lParam >> 30) & 1) != 1)
		{
			//Set key press to for this key to true
			pApp->SetKeyPress(_wParam, true);
		}
	}
		break;
	case WM_KEYUP:
	{
		//Set key press to for this key to false
		pApp->SetKeyPress(_wParam, false);
	}
		break;
	default: break;
	} 
	// End switch

	// Process any messages left to process
	return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

bool CApplication::CreateAndRegisterWindow(HINSTANCE _hInstance, int _width, int _height, LPCWSTR _lpTitle)
{
	WNDCLASSEX winClass;

	// Save the Windows dimentions
	m_windowWidth = _width;
	m_windowHeight = _height;
	
	// Clear out the window class for use
	ZeroMemory(&winClass, sizeof(WNDCLASSEX));

	//Fill in the struct with the needed information
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc = WindowProc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = _hInstance;
	winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)BLACK_BRUSH;
	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = WINDOWS_CLASS_NAME;
	winClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Register the window class and check if succesful
	VALIDATE(RegisterClassEx(&winClass));
	
	// Create the window and return the result as the handle
	m_hWnd = CreateWindowEx(NULL,												// Extend style.
							WINDOWS_CLASS_NAME,									// Class.		
							_lpTitle,											// Title.
							WS_OVERLAPPEDWINDOW | WS_BORDER |
							WS_CAPTION | WS_SYSMENU | WS_VISIBLE,				// Window stlye(Windowed)
							CW_USEDEFAULT, CW_USEDEFAULT,						// Initial x,y.
							m_windowWidth, m_windowHeight,						// Initial width, height.
							NULL,												// Handle to parent.
							NULL,												// Handle to menu.
							_hInstance,											// Instance of this application.
							NULL);												// Extra creation parameters.

	// Check if window was created succesfully
	VALIDATE(m_hWnd);

	// Return the Succesful Creation
	return true;
}

int CApplication::RunApp()
{
	//This holds Windows event messages
	MSG uiMsg;

	//Clear out the event message for use
	ZeroMemory(&uiMsg, sizeof(MSG));

	// Enter main event loop.
	while (uiMsg.message != WM_QUIT)
	{
		while (PeekMessage(&uiMsg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&uiMsg);
			DispatchMessage(&uiMsg);
		}

		// Execute one frame of application
		ExecuteOneFrame(); //remember VIRTUAL
	}

	// Return this part of the WM_QUIT message to Windows
	return (static_cast<int>(uiMsg.wParam));
}

// *** Application Functions ***

// Creation and Deletion

CApplication::CApplication()
{
}

CApplication::~CApplication()
{
}

CApplication* CApplication::GetInstance()
{
	// If the application doesnt excist create it
	if (s_pApp == 0)
	{
		s_pApp = new CApplication();
	}
	// Return a pointer to the Application
	return s_pApp;
}

bool CApplication::Initialise()
{
	// Create a Renderer for graphics
	m_pRenderManager = new CDX10Renderer();
	VALIDATE(m_pRenderManager->Initialise(m_windowWidth, m_windowHeight, m_hWnd));

	// Initialise boolean array for KeyDown to false
	m_pKeyPress = new bool[255];
	memset(m_pKeyPress, false, 255);

	// Return the Succesful Initialization 
	return true;
}

void CApplication::ShutDown()
{
	ReleasePointer(m_pKeyPress);

	m_pRenderManager->ShutDown();
	ReleasePointer(m_pRenderManager);
}

void CApplication::DestroyInstance()
{
	s_pApp->ShutDown();
	ReleasePointer(s_pApp);
}

// Application Functionality

void CApplication::ExecuteOneFrame()
{

	// TO DO: remove comment
	//CalculateFPS();
	//PreProcess();
	//Process();
	//LogDebug();
	//PreDraw();
	//Draw();
	//PostDraw();

	m_pRenderManager->RenderFrame();
	ProcessInput();
}

// Input Handler

void CApplication::ProcessInput()
{
	// Template Inputs
	if (m_pKeyPress[VK_F1])
	{

		m_pRenderManager->ToggleFullscreen();
		m_pKeyPress[VK_F1] = false;
	}

	// Application Specific Inputs
}

void CApplication::SetKeyPress(int _keyIndex, bool _press)
{
	m_pKeyPress[_keyIndex] = _press;
}