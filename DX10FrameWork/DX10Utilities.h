/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10Utilities.h
* Description : General Utilitis used for DirectX 10 
* Author :	Jc Fowles
* Mail :	Jc.Fowles@mediadesign.school.nz
*/

#pragma once
#ifndef __DX10_UTILS_H__
#define __DX10_UTILS_H__

// Linker Includes
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10d.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "dxguid.lib")

// Library Includes
#include <d3d10.h>
#include <d3dx10.h>
#include <dxerr.h>

// Local Includes
#include "GenUtilities.h"

// Defines 

#if defined(DEBUG) || defined(_DEBUG)
	#ifndef D3D_DEBUG_INFO
		#define D3D_DEBUG_INFO
	#endif
#endif


#if defined(DEBUG) || defined(_DEBUG)
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif

// Success Check on HResults 
#if defined(DEBUG) | defined(_DEBUG)
	#ifndef VALIDATE_HRESULT
		#define VALIDATE_HRESULT(x)									\
		{															\
			HRESULT hr = (x);										\
			if(FAILED(hr))											\
			{														\
				DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true);	\
				return false;										\
			}														\
		}
	#endif
#else
		#ifndef VALIDATE_HRESULT
			#define VALIDATE_HRESULT(x) (x)
		#endif
#endif

// Release COM Objects
#define ReleaseCOM(x) { if (x){ x->Release(); x = 0; } }


// Constants

// Colors
namespace Color
{
	const D3DXCOLOR WHITE(1.0f, 1.0f, 1.0f, 1.0f);
	const D3DXCOLOR BLACK(0.0f, 0.0f, 0.0f, 1.0f);
	const D3DXCOLOR RED(1.0f, 0.0f, 0.0f, 1.0f);
	const D3DXCOLOR GREEN(0.0f, 1.0f, 0.0f, 1.0f);
	const D3DXCOLOR BLUE(0.0f, 0.0f, 1.0f, 1.0f);
	const D3DXCOLOR YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
	const D3DXCOLOR CYAN(0.0f, 1.0f, 1.0f, 1.0f);
	const D3DXCOLOR MAGENTA(1.0f, 0.0f, 1.0f, 1.0f);
	const D3DXCOLOR ORANGE(1.0f, 0.5f, 0.0f, 1.0f);

	const D3DXCOLOR BEACH_SAND(1.0f, 0.96f, 0.62f, 1.0f);
	const D3DXCOLOR LIGHT_YELLOW_GREEN(0.48f, 0.77f, 0.46f, 1.0f);
	const D3DXCOLOR DARK_YELLOW_GREEN(0.1f, 0.48f, 0.19f, 1.0f);
	const D3DXCOLOR DARKBROWN(0.45f, 0.39f, 0.34f, 1.0f);
};



#endif //__DX10_UTILS_H__