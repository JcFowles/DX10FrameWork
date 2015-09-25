/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10.h
* Description : Includes all DX10 Files
* Author :	Callan Moore & Jc Fowles
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __DX10_H__
#define __DX10_H__

// Linker Includes
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10d.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "dxguid.lib")

#if defined(DEBUG) | defined(_DEBUG)
	#include <DXGIDebug.h>
#endif

// DX10 Includes

#include "DX10\DX10_Renderer.h"

// 3D Objects
#include "DX10\3D Objects\DX10_Obj_Generic.h"
#include "DX10\3D Objects\DX10_Obj_LitTex.h"

// 2D Objects
#include "DX10\2D Objects\DXSprite.h"

// Meshes
#include "DX10\Meshes\DX10_Mesh.h"

// Cameras
#include "DX10\Cameras\DX10_Camera_FirstPerson.h"
#include "DX10\Cameras\DX10_Camera_Debug.h"

// Shaders
#include "DX10\Shaders\DX10_Shader_LitTex.h"
#include "DX10\Shaders\DX10_Shader_Fog.h"

// Particle System
#include "DX10\ParticleSystem\DX10_ParticleSystem.h"

#endif	// __DX10_H__