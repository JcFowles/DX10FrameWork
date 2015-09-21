/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10_Vertex.h
* Description : Holds all the structures for the different Vertex types for DirectX 10
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __DX10_VERTEX_H__
#define __DX10_VERTEX_H__

// Library Includes
#include <d3dx10.h>

// Enumerators
enum eVertexType
{
	VT_BASIC,
	VT_COLOR,
	VT_UV,
	VT_COLOR_UV,
	VT_NORMAL_UV
};

/***********************
* TVertexBasic: Basic Vertex with Position only
* @author: Callan Moore
********************/
struct TVertexBasic
{
	D3DXVECTOR3 pos;
};

/***********************
* TVertexColor: Basic Vertex with Color
* @author: Callan Moore
********************/
struct TVertexColor
{
	D3DXVECTOR3 pos;
	D3DXCOLOR   color;
};

/***********************
* TVertexUV: Basic Vertex with UVs
* @author: Callan Moore
********************/
struct TVertexUV
{
	D3DXVECTOR3 pos;
	v2float		uv;
};

/***********************
* TVertexColorUV: Basic Vertex with Color and UVs
* @author: Callan Moore
********************/
struct TVertexColorUV
{
	D3DXVECTOR3 pos;
	D3DXCOLOR   color;
	v2float		uv;
};

/***********************
* TVertexNormalUV: Basic Vertex with Normals and UVs
* @author: Callan Moore
********************/
struct TVertexNormalUV
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	v2float		uv;
};



#endif // __DX10_VERTEX_H__