/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10_Utilities.h
* Description : Extra functionality for DirectX 10
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

//Inclusion Guards
#pragma once
#ifndef __DX10_UTILITIES_H__
#define __DX10_UTILITIES_H__
#pragma message("Included DX10_Utilities.h")

// Library Includes
#include <d3d10.h>
#include <d3dx10.h>
#include <dxerr.h>

// Local Includes
#include "../../Utility/Utilities.h"

// Defines
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

// Macros
#define ReleaseCOM(x) { if (x){ x->Release(); x = 0; } }

// Useful Macro for Validating a HRESULT returning 'OK'
#if defined(DEBUG) | defined(_DEBUG)
#ifndef VALIDATEHR
#define VALIDATEHR(x)		                                   \
	{														   \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
			return false;									   \
		}                                                      \
	}
#endif
#ifndef HR
#define CHECKHR(x)                                             \
	{                                                          \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
		}                                                      \
	}
#endif
#else
	#ifndef VALIDATEHR
	#define VALIDATEHR(x) (x)
	#endif
#endif 

// Filepaths
const std::string TEXTUREFILEPATH = "Resources/Textures/";

// Constants
const D3DXCOLOR WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR RED(1.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const D3DXCOLOR YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR CYAN(0.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR MAGENTA(1.0f, 0.0f, 1.0f, 1.0f);

const D3DXCOLOR BEACH_SAND(1.0f, 0.96f, 0.62f, 1.0f);
const D3DXCOLOR LIGHT_YELLOW_GREEN(0.48f, 0.77f, 0.46f, 1.0f);
const D3DXCOLOR DARK_YELLOW_GREEN(0.1f, 0.48f, 0.19f, 1.0f);
const D3DXCOLOR DARKBROWN(0.45f, 0.39f, 0.34f, 1.0f);

namespace d3dxColors
{
	const D3DXCOLOR AliceBlue = 0xFFF0F8FF;
	const D3DXCOLOR AntiqueWhite = 0xFFFAEBD7;
	const D3DXCOLOR Aqua = 0xFF00FFFF;
	const D3DXCOLOR Aquamarine = 0xFF7FFFD4;
	const D3DXCOLOR Azure = 0xFFF0FFFF;
	const D3DXCOLOR Beige = 0xFFF5F5DC;
	const D3DXCOLOR Bisque = 0xFFFFE4C4;
	const D3DXCOLOR Black = 0xFF000000;
	const D3DXCOLOR BlanchedAlmond = 0xFFFFEBCD;
	const D3DXCOLOR Blue = 0xFF0000FF;
	const D3DXCOLOR BlueViolet = 0xFF8A2BE2;
	const D3DXCOLOR Brown = 0xFFA52A2A;
	const D3DXCOLOR BurlyWood = 0xFFDEB887;
	const D3DXCOLOR CadetBlue = 0xFF5F9EA0;
	const D3DXCOLOR Chartreuse = 0xFF7FFF00;
	const D3DXCOLOR Chocolate = 0xFFD2691E;
	const D3DXCOLOR Coral = 0xFFFF7F50;
	const D3DXCOLOR CornflowerBlue = 0xFF6495ED;
	const D3DXCOLOR Cornsilk = 0xFFFFF8DC;
	const D3DXCOLOR Crimson = 0xFFDC143C;
	const D3DXCOLOR Cyan = 0xFF00FFFF;
	const D3DXCOLOR DarkBlue = 0xFF00008B;
	const D3DXCOLOR DarkCyan = 0xFF008B8B;
	const D3DXCOLOR DarkGoldenrod = 0xFFB8860B;
	const D3DXCOLOR DarkGray = 0xFFA9A9A9;
	const D3DXCOLOR DarkGreen = 0xFF006400;
	const D3DXCOLOR DarkKhaki = 0xFFBDB76B;
	const D3DXCOLOR DarkMagenta = 0xFF8B008B;
	const D3DXCOLOR DarkOliveGreen = 0xFF556B2F;
	const D3DXCOLOR DarkOrange = 0xFFFF8C00;
	const D3DXCOLOR DarkOrchid = 0xFF9932CC;
	const D3DXCOLOR DarkRed = 0xFF8B0000;
	const D3DXCOLOR DarkSalmon = 0xFFE9967A;
	const D3DXCOLOR DarkSeaGreen = 0xFF8FBC8B;
	const D3DXCOLOR DarkSlateBlue = 0xFF483D8B;
	const D3DXCOLOR DarkSlateGray = 0xFF2F4F4F;
	const D3DXCOLOR DarkTurquoise = 0xFF00CED1;
	const D3DXCOLOR DarkViolet = 0xFF9400D3;
	const D3DXCOLOR DeepPink = 0xFFFF1493;
	const D3DXCOLOR DeepSkyBlue = 0xFF00BFFF;
	const D3DXCOLOR DimGray = 0xFF696969;
	const D3DXCOLOR DodgerBlue = 0xFF1E90FF;
	const D3DXCOLOR Firebrick = 0xFFB22222;
	const D3DXCOLOR FloralWhite = 0xFFFFFAF0;
	const D3DXCOLOR ForestGreen = 0xFF228B22;
	const D3DXCOLOR Fuchsia = 0xFFFF00FF;
	const D3DXCOLOR Gainsboro = 0xFFDCDCDC;
	const D3DXCOLOR GhostWhite = 0xFFF8F8FF;
	const D3DXCOLOR Gold = 0xFFFFD700;
	const D3DXCOLOR Goldenrod = 0xFFDAA520;
	const D3DXCOLOR Gray = 0xFF808080;
	const D3DXCOLOR Green = 0xFF008000;
	const D3DXCOLOR GreenYellow = 0xFFADFF2F;
	const D3DXCOLOR Honeydew = 0xFFF0FFF0;
	const D3DXCOLOR HotPink = 0xFFFF69B4;
	const D3DXCOLOR IndianRed = 0xFFCD5C5C;
	const D3DXCOLOR Indigo = 0xFF4B0082;
	const D3DXCOLOR Ivory = 0xFFFFFFF0;
	const D3DXCOLOR Khaki = 0xFFF0E68C;
	const D3DXCOLOR Lavender = 0xFFE6E6FA;
	const D3DXCOLOR LavenderBlush = 0xFFFFF0F5;
	const D3DXCOLOR LawnGreen = 0xFF7CFC00;
	const D3DXCOLOR LemonChiffon = 0xFFFFFACD;
	const D3DXCOLOR LightBlue = 0xFFADD8E6;
	const D3DXCOLOR LightCoral = 0xFFF08080;
	const D3DXCOLOR LightCyan = 0xFFE0FFFF;
	const D3DXCOLOR LightGoldenrodYellow = 0xFFFAFAD2;
	const D3DXCOLOR LightGray = 0xFFD3D3D3;
	const D3DXCOLOR LightGreen = 0xFF90EE90;
	const D3DXCOLOR LightPink = 0xFFFFB6C1;
	const D3DXCOLOR LightSalmon = 0xFFFFA07A;
	const D3DXCOLOR LightSeaGreen = 0xFF20B2AA;
	const D3DXCOLOR LightSkyBlue = 0xFF87CEFA;
	const D3DXCOLOR LightSlateGray = 0xFF778899;
	const D3DXCOLOR LightSteelBlue = 0xFFB0C4DE;
	const D3DXCOLOR LightYellow = 0xFFFFFFE0;
	const D3DXCOLOR Lime = 0xFF00FF00;
	const D3DXCOLOR LimeGreen = 0xFF32CD32;
	const D3DXCOLOR Linen = 0xFFFAF0E6;
	const D3DXCOLOR Magenta = 0xFFFF00FF;
	const D3DXCOLOR Maroon = 0xFF800000;
	const D3DXCOLOR MediumAquamarine = 0xFF66CDAA;
	const D3DXCOLOR MediumBlue = 0xFF0000CD;
	const D3DXCOLOR MediumOrchid = 0xFFBA55D3;
	const D3DXCOLOR MediumPurple = 0xFF9370DB;
	const D3DXCOLOR MediumSeaGreen = 0xFF3CB371;
	const D3DXCOLOR MediumSlateBlue = 0xFF7B68EE;
	const D3DXCOLOR MediumSpringGreen = 0xFF00FA9A;
	const D3DXCOLOR MediumTurquoise = 0xFF48D1CC;
	const D3DXCOLOR MediumVioletRed = 0xFFC71585;
	const D3DXCOLOR MidnightBlue = 0xFF191970;
	const D3DXCOLOR MintCream = 0xFFF5FFFA;
	const D3DXCOLOR MistyRose = 0xFFFFE4E1;
	const D3DXCOLOR Moccasin = 0xFFFFE4B5;
	const D3DXCOLOR NavajoWhite = 0xFFFFDEAD;
	const D3DXCOLOR Navy = 0xFF000080;
	const D3DXCOLOR OldLace = 0xFFFDF5E6;
	const D3DXCOLOR Olive = 0xFF808000;
	const D3DXCOLOR OliveDrab = 0xFF6B8E23;
	const D3DXCOLOR Orange = 0xFFFFA500;
	const D3DXCOLOR OrangeRed = 0xFFFF4500;
	const D3DXCOLOR Orchid = 0xFFDA70D6;
	const D3DXCOLOR PaleGoldenrod = 0xFFEEE8AA;
	const D3DXCOLOR PaleGreen = 0xFF98FB98;
	const D3DXCOLOR PaleTurquoise = 0xFFAFEEEE;
	const D3DXCOLOR PaleVioletRed = 0xFFDB7093;
	const D3DXCOLOR PapayaWhip = 0xFFFFEFD5;
	const D3DXCOLOR PeachPuff = 0xFFFFDAB9;
	const D3DXCOLOR Peru = 0xFFCD853F;
	const D3DXCOLOR Pink = 0xFFFFC0CB;
	const D3DXCOLOR Plum = 0xFFDDA0DD;
	const D3DXCOLOR PowderBlue = 0xFFB0E0E6;
	const D3DXCOLOR Purple = 0xFF800080;
	const D3DXCOLOR Red = 0xFFFF0000;
	const D3DXCOLOR RosyBrown = 0xFFBC8F8F;
	const D3DXCOLOR RoyalBlue = 0xFF4169E1;
	const D3DXCOLOR SaddleBrown = 0xFF8B4513;
	const D3DXCOLOR Salmon = 0xFFFA8072;
	const D3DXCOLOR SandyBrown = 0xFFF4A460;
	const D3DXCOLOR SeaGreen = 0xFF2E8B57;
	const D3DXCOLOR SeaShell = 0xFFFFF5EE;
	const D3DXCOLOR Sienna = 0xFFA0522D;
	const D3DXCOLOR Silver = 0xFFC0C0C0;
	const D3DXCOLOR SkyBlue = 0xFF87CEEB;
	const D3DXCOLOR SlateBlue = 0xFF6A5ACD;
	const D3DXCOLOR SlateGray = 0xFF708090;
	const D3DXCOLOR Snow = 0xFFFFFAFA;
	const D3DXCOLOR SpringGreen = 0xFF00FF7F;
	const D3DXCOLOR SteelBlue = 0xFF4682B4;
	const D3DXCOLOR Tan = 0xFFD2B48C;
	const D3DXCOLOR Teal = 0xFF008080;
	const D3DXCOLOR Thistle = 0xFFD8BFD8;
	const D3DXCOLOR Tomato = 0xFFFF6347;
	const D3DXCOLOR Transparent = 0x00FFFFFF;
	const D3DXCOLOR Turquoise = 0xFF40E0D0;
	const D3DXCOLOR Violet = 0xFFEE82EE;
	const D3DXCOLOR Wheat = 0xFFF5DEB3;
	const D3DXCOLOR White = 0xFFFFFFFF;
	const D3DXCOLOR WhiteSmoke = 0xFFF5F5F5;
	const D3DXCOLOR Yellow = 0xFFFFFF00;
	const D3DXCOLOR YellowGreen = 0xFF9ACD32;


}

// Structs
struct Light
{
	Light()
	{
		// Ensure the Memory is zeroed on creation
		ZeroMemory(this, sizeof(Light));
	}

	D3DXVECTOR3 pos;
	float pad1;      // not used
	D3DXVECTOR3 dir;
	float pad2;      // not used
	D3DXCOLOR ambient;
	D3DXCOLOR diffuse;
	D3DXCOLOR specular;
	D3DXVECTOR3 attenuation;
	float spotPower;
};


#endif // __DX10_UTILITIES_H__