/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10_Mesh_Generic.h
* Description : A Generic Mesh (Abstract class)
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __DX10_MESH_GENERIC_H__
#define __DX10_MESH_GENERIC_H__

// Local Includes
#include "../DX10_Renderer.h"

class DX10_Mesh_Generic
{
public:
	/***********************
	* CGeometricMesh: Default Constructor for Geometric Mesh class
	* @author: Callan Moore
	********************/
	DX10_Mesh_Generic() {}

	/***********************
	* ~CGeometricMesh: Default Destructor for Geometric Mesh class
	* @author: Callan Moore
	********************/
	virtual ~DX10_Mesh_Generic() {}

	/***********************
	* Initialise: Initialise the Generic mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the Mesh
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(DX10_Renderer* _pRenderer, TVertexBasic _vert, v3float _scalar) = 0;

	/***********************
	* Initialise: Initialise the Generic mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the Geometric Mesh
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(DX10_Renderer* _pRenderer, TVertexColor _vert, v3float _scale) = 0;

	/***********************
	* Initialise: Initialise the Generic mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the finite plane Mesh
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(DX10_Renderer* _pRenderer, TVertexColorUV _vert, v3float _scale) = 0;

	/***********************
	* Initialise: Initialise the Generic mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: Renderer for the Application
	* @parameter: _vert: Vertex Structure to use
	* @parameter: _scale: Scale factor for the finite plane Mesh
	* @return: bool: Successful or not
	********************/
	virtual bool Initialise(DX10_Renderer* _pRenderer, TVertexNormalUV _vert, v3float _scale) = 0;

	/***********************
	* Render: Render the Mesh
	* @author: Callan Moore
	* @return: void
	********************/
	virtual void Render() = 0;
	
	/***********************
	* GetVertexType: Retrieve the Vertex Type that the Mesh uses
	* @author: Callan Moore
	* @return: eVertexType: The Vertex Type
	********************/
	eVertexType GetVertexType() { return m_vertType; };

	/***********************
	* GetPrimTopology: Retrieve the Primitive topology that the Mesh uses
	* @author: Callan Moore
	* @return: eVertexType: The Vertex Type
	********************/
	D3D_PRIMITIVE_TOPOLOGY GetPrimTopology() { return m_primTopology; };

	/***********************
	* GetScale: Gets the Scale of the Mesh
	* @author: Jc Fowles
	* @return: float: The Scale of the Mesh
	********************/
	v3float GetScale(){ return m_scale; };

	/***********************
	* SetScale: Sets the Scale of the Mesh
	* @author: Jc Fowles
	* @return: float: The Scale of the Mesh
	********************/
	void SetScale(){ /* TO DO CAL: Possible name Resize()*/ };

protected:
	DX10_Renderer* m_pRenderer;
	DX10_Buffer* m_pBuffer;
	eVertexType m_vertType;
	D3D_PRIMITIVE_TOPOLOGY m_primTopology;

	v3float m_scale;
};

#endif	// __DX10_MESH_GENERIC_H__

