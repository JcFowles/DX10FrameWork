/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10_Mesh_Rect_Prism.h
* Description : Mesh for a Geometric Rectangular Prism
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __DX10_MESH_RECT_PRISM_H__
#define __DX10_MESH_RECT_PRISM_H__

// Local Includes
#include "DX10_Mesh_Generic.h"
#include "../DX10_Renderer.h"

class DX10_Mesh_Rect_Prism :
	public DX10_Mesh_Generic
{
public:
	/***********************
	* CMesh_Rect_Prism: Default Constructor for Mesh Rect Prism class
	* @author: Callan Moore
	********************/
	DX10_Mesh_Rect_Prism();

	/***********************
	* ~CMesh_Rect_Prism: Default Destructor for Mesh Rect Prism class
	* @author: Callan Moore
	********************/
	virtual ~DX10_Mesh_Rect_Prism();

	/***********************
	* Initialise: Initialise the Rect Prism mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the finite plane Mesh
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(DX10_Renderer* _pRenderer, TVertexBasic _vert, v3float _scale);
	
	/***********************
	* Initialise: Initialise the finite plane mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the finite plane Mesh
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(DX10_Renderer* _pRenderer, TVertexColor _vert, v3float _scale);

	/***********************
	* Initialise: Initialise the finite plane mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the finite plane Mesh
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(DX10_Renderer* _pRenderer, TVertexColorUV _vert, v3float _scale);

	/***********************
	* Initialise: Initialise the finite plane mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the finite plane Mesh
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(DX10_Renderer* _pRenderer, TVertexNormalUV _vert, v3float _scale);

	/***********************
	* Render: Render the Rect Prism Mesh
	* @author: Callan Moore
	* @return: void
	********************/
	virtual void Render();

	// TO DO CAL
	bool Initialise(DX10_Renderer* _pRenderer, v3float _scale);
};
#endif	// __DX10_MESH_RECT_PRISM_H__

