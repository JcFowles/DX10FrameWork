/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10_Mesh.h
* Description : A Generic Mesh (Abstract class)
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __DX10_MESH_H__
#define __DX10_MESH_H__

// Local Includes
#include "../DX10_Renderer.h"

enum eMeshType
{
	MT_FINITEPLANE,
	MT_RECTPRISM,
	MT_SPHERE,
	MT_TERRAIN
};

class DX10_Mesh
{
public:
	/***********************
	* DX10_Mesh: Default Constructor for Mesh class
	* @author: Callan Moore
	********************/
	DX10_Mesh() {}

	/***********************
	* ~DX10_Mesh: Default Destructor for Mesh class
	* @author: Callan Moore
	********************/
	virtual ~DX10_Mesh() {}

	/***********************
	* Initialise: Initialise a new mesh
	* @author: Callan Moore
	* @parameter: _pRenderer: The renderer for the mesh
	* @parameter: _meshType: The type fo mesh to create
	* @parameter: _scale: 3D scalar for the mesh
	* @return: bool: Successful or not
	********************/
	bool DX10_Mesh::Initialise(DX10_Renderer* _pRenderer, eMeshType _meshType, v3float _scale)
	{
		// Save the renderer on the Rectangular Prism
		m_pRenderer = _pRenderer;
		m_scale = _scale;
		m_primTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		TVertexNormalUV* pVertexBuffer = 0;
		DWORD* pIndexBuffer = 0;
		int vertexCount;
		int indexCount;		
		int stride = sizeof(TVertexNormalUV);

		// Load the Mesh File
		std::string fileName = GetFilePath(_meshType);
		VALIDATE(m_pRenderer->LoadMeshObj(fileName, pVertexBuffer, pIndexBuffer, &vertexCount, &indexCount, m_scale));

		// Create the buffer
		VALIDATE(m_pRenderer->CreateBuffer(pVertexBuffer, pIndexBuffer, vertexCount, indexCount, stride, m_pBuffer, D3D10_USAGE_DYNAMIC, D3D10_USAGE_DEFAULT));

		ReleasePtrArray(pVertexBuffer);
		ReleasePtrArray(pIndexBuffer);

		return true;
	}

	/***********************
	* Render: Render the Mesh
	* @author: Callan Moore
	* @return: void
	********************/
	virtual void Render()
	{
		m_pRenderer->RenderBuffer(m_pBuffer);
	}
	
	/***********************
	* GetFilePath: Retrieve the file path of the mesh type
	* @author: Callan Moore
	* @parameter: _meshType: The type of mesh to retrieve the file path for
	* @return: std::string: File path
	********************/
	std::string GetFilePath(eMeshType _meshType)
	{
		switch (_meshType)
		{
			case MT_FINITEPLANE:
			{
				return "Resources/Meshes/Mesh_FinitePlane.txt";
			}
			break;
			case MT_RECTPRISM:
			{
				return "Resources/Meshes/Mesh_RectPrism.txt";
			}
			break;
			case MT_SPHERE:
			{
				return "Resources/Meshes/Mesh_Sphere.txt";
			}
			break;
			case MT_TERRAIN:
			{
				return "Resources/Meshes/Mesh_Terrain.txt";
			}
				break;
			default: return "";
		}	// End Switch
	}

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

protected:
	DX10_Renderer* m_pRenderer;
	DX10_Buffer* m_pBuffer;
	D3D_PRIMITIVE_TOPOLOGY m_primTopology;
	v3float m_scale;
};

#endif	// __DX10_MESH_GENERIC_H__

