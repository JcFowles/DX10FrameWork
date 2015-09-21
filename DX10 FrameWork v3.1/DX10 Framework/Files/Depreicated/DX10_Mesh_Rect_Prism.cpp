/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10_Mesh_Rect_Prism.cpp
* Description : Mesh for a Geometric Rectangular Prism
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "DX10_Mesh_Rect_Prism.h"

DX10_Mesh_Rect_Prism::DX10_Mesh_Rect_Prism()
{
}

DX10_Mesh_Rect_Prism::~DX10_Mesh_Rect_Prism()
{
}

bool DX10_Mesh_Rect_Prism::Initialise(DX10_Renderer* _pRenderer, TVertexBasic _vert, v3float _scale)
{
	// Save the renderer on the Rectangular Prism
	m_pRenderer = _pRenderer;

	float vertScaleX = _scale.x / 2;
	float vertScaleY = _scale.y / 2;
	float vertScaleZ = _scale.z / 2;

	// Create vertex buffer
	TVertexColor vertices[] =
	{
		// Front
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, -vertScaleZ) },
		{ D3DXVECTOR3(vertScaleX, vertScaleY, -vertScaleZ) },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, -vertScaleZ) },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, -vertScaleZ) },

		// Left
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, vertScaleZ) },
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, -vertScaleZ) },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, -vertScaleZ) },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, vertScaleZ) },

		// Right
		{ D3DXVECTOR3(vertScaleX, vertScaleY, -vertScaleZ) },
		{ D3DXVECTOR3(vertScaleX, vertScaleY, vertScaleZ) },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, vertScaleZ) },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, -vertScaleZ) },

		// Back
		{ D3DXVECTOR3(vertScaleX, vertScaleY, vertScaleZ) },
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, vertScaleZ) },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, vertScaleZ) },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, vertScaleZ) },

		// Top
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, vertScaleZ) },
		{ D3DXVECTOR3(vertScaleX, vertScaleY, vertScaleZ) },
		{ D3DXVECTOR3(vertScaleX, vertScaleY, -vertScaleZ) },
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, -vertScaleZ) },

		// Bottom
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, -vertScaleZ) },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, -vertScaleZ) },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, vertScaleZ) },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, vertScaleZ) }
	};
	m_vertType = VT_BASIC;
	UINT stride = sizeof(*vertices);
	UINT vertexCount = (sizeof(vertices) / stride);

	// Create the Index Buffer
	DWORD indices[] = {
		// Front Face
		0, 1, 2,
		0, 2, 3,

		// Left Face
		4, 5, 6,
		4, 6, 7,

		// Right Face
		8, 9, 10,
		8, 10, 11,

		// Back Face
		12, 13, 14,
		12, 14, 15,

		// Top Face
		16, 17, 18,
		16, 18, 19,

		// Bottom Face
		20, 21, 22,
		20, 22, 23
	};
	m_primTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	UINT indexCount = (sizeof(indices) / sizeof(*indices));

	// Create the buffer and store the ID
	m_pRenderer->CreateBuffer(vertices, indices, vertexCount, indexCount, stride, m_pBuffer);

	return true;
}

bool DX10_Mesh_Rect_Prism::Initialise(DX10_Renderer* _pRenderer, TVertexColor _vert, v3float _scale)
{
	// Save the renderer on the Rectangular Prism
	m_pRenderer = _pRenderer;

	float vertScaleX = _scale.x / 2;
	float vertScaleY = _scale.y / 2;
	float vertScaleZ = _scale.z / 2;

	// Create vertex buffer
	TVertexColor vertices[] =
	{
		// Front
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, -vertScaleZ), YELLOW },
		{ D3DXVECTOR3(vertScaleX, vertScaleY, -vertScaleZ), YELLOW },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, -vertScaleZ), YELLOW },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, -vertScaleZ), YELLOW },

		// Left
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, vertScaleZ), YELLOW },
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, -vertScaleZ), YELLOW },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, -vertScaleZ), YELLOW },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, vertScaleZ), YELLOW },

		// Right
		{ D3DXVECTOR3(vertScaleX, vertScaleY, -vertScaleZ), YELLOW },
		{ D3DXVECTOR3(vertScaleX, vertScaleY, vertScaleZ), YELLOW },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, vertScaleZ), YELLOW },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, -vertScaleZ), YELLOW },

		// Back
		{ D3DXVECTOR3(vertScaleX, vertScaleY, vertScaleZ), YELLOW },
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, vertScaleZ), YELLOW },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, vertScaleZ), YELLOW },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, vertScaleZ), YELLOW },

		// Top
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, vertScaleZ), YELLOW },
		{ D3DXVECTOR3(vertScaleX, vertScaleY, vertScaleZ), YELLOW },
		{ D3DXVECTOR3(vertScaleX, vertScaleY, -vertScaleZ), YELLOW },
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, -vertScaleZ), YELLOW },

		// Bottom
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, -vertScaleZ), YELLOW },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, -vertScaleZ), YELLOW },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, vertScaleZ), YELLOW },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, vertScaleZ), YELLOW }
	};
	m_vertType = VT_COLOR;
	UINT stride = sizeof(*vertices);
	UINT vertexCount = (sizeof(vertices) / stride);

	// Create the Index Buffer
	DWORD indices[] = {
		// Front Face
		0, 1, 2,
		0, 2, 3,

		// Left Face
		4, 5, 6,
		4, 6, 7,

		// Right Face
		8, 9, 10,
		8, 10, 11,

		// Back Face
		12, 13, 14,
		12, 14, 15,

		// Top Face
		16, 17, 18,
		16, 18, 19,

		// Bottom Face
		20, 21, 22,
		20, 22, 23
	};
	m_primTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	UINT indexCount = (sizeof(indices) / sizeof(*indices));

	// Create the buffer and store the ID
	m_pRenderer->CreateBuffer(vertices, indices, vertexCount, indexCount, stride, m_pBuffer);

	return true;
}

bool DX10_Mesh_Rect_Prism::Initialise(DX10_Renderer* _pRenderer, TVertexColorUV _vert, v3float _scale)
{
	// Save the renderer on the Rectangular Prism
	m_pRenderer = _pRenderer;

	float vertScaleX = _scale.x / 2;
	float vertScaleY = _scale.y / 2;
	float vertScaleZ = _scale.z / 2;
	
	// Create vertex buffer
	TVertexColorUV vertices[] =
	{
		// Front
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, -vertScaleZ), YELLOW,  { 0.0f, 0.0f } },
		{ D3DXVECTOR3(vertScaleX, vertScaleY, -vertScaleZ), YELLOW, { 0.0f, 1.0f } },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, -vertScaleZ), YELLOW, { 1.0f, 1.0f } },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, -vertScaleZ), YELLOW, { 1.0f, 0.0f } },

		// Left
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, vertScaleZ), YELLOW, { 0.0f, 0.0f } },
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, -vertScaleZ), YELLOW, { 0.0f, 1.0f } },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, -vertScaleZ), YELLOW, { 1.0f, 1.0f } },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, vertScaleZ), YELLOW, { 1.0f, 0.0f } },

		// Right
		{ D3DXVECTOR3(vertScaleX, vertScaleY, -vertScaleZ), YELLOW, { 0.0f, 0.0f } },
		{ D3DXVECTOR3(vertScaleX, vertScaleY, vertScaleZ), YELLOW, { 0.0f, 1.0f } },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, vertScaleZ), YELLOW, { 1.0f, 1.0f } },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, -vertScaleZ), YELLOW, { 1.0f, 0.0f } },

		// Back
		{ D3DXVECTOR3(vertScaleX, vertScaleY, vertScaleZ), YELLOW, { 0.0f, 0.0f } },
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, vertScaleZ), YELLOW, { 0.0f, 1.0f } },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, vertScaleZ), YELLOW, { 1.0f, 1.0f } },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, vertScaleZ), YELLOW, { 1.0f, 0.0f } },

		// Top
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, vertScaleZ), YELLOW, { 0.0f, 0.0f } },
		{ D3DXVECTOR3(vertScaleX, vertScaleY, vertScaleZ), YELLOW, { 0.0f, 1.0f } },
		{ D3DXVECTOR3(vertScaleX, vertScaleY, -vertScaleZ), YELLOW, { 1.0f, 1.0f } },
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, -vertScaleZ), YELLOW, { 1.0f, 0.0f } },

		// Bottom
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, -vertScaleZ), YELLOW, { 0.0f, 0.0f } },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, -vertScaleZ), YELLOW, { 0.0f, 1.0f } },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, vertScaleZ), YELLOW, { 1.0f, 1.0f } },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, vertScaleZ), YELLOW, { 1.0f, 0.0f } }
	};
	m_vertType = VT_COLOR;
	UINT stride = sizeof(*vertices);
	UINT vertexCount = (sizeof(vertices) / stride);

	// Create the Index Buffer
	DWORD indices[] = {
		// Front Face
		0, 1, 2,
		0, 2, 3,

		// Left Face
		4, 5, 6,
		4, 6, 7,

		// Right Face
		8, 9, 10,
		8, 10, 11,

		// Back Face
		12, 13, 14,
		12, 14, 15,

		// Top Face
		16, 17, 18,
		16, 18, 19,

		// Bottom Face
		20, 21, 22,
		20, 22, 23
	};
	m_primTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	UINT indexCount = (sizeof(indices) / sizeof(*indices));

	// Create the buffer and store the ID
	m_pRenderer->CreateBuffer(vertices, indices, vertexCount, indexCount, stride, m_pBuffer);

	return true;
}

bool DX10_Mesh_Rect_Prism::Initialise(DX10_Renderer* _pRenderer, TVertexNormalUV _vert, v3float _scale)
{
	// Save the renderer on the Rectangular Prism
	m_pRenderer = _pRenderer;

	float vertScaleX = _scale.x / 2;
	float vertScaleY = _scale.y / 2;
	float vertScaleZ = _scale.z / 2;
	m_scale = _scale;

	// Create vertex buffer
	TVertexNormalUV vertices[] =
	{
		// Front
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, -vertScaleZ), D3DXVECTOR3(-1.0f, 1.0f, -1.0f), { 0.0f, 0.0f } },
		{ D3DXVECTOR3(vertScaleX, vertScaleY, -vertScaleZ), D3DXVECTOR3(1.0f, 1.0f, -1.0f), { 1.0f, 0.0f } },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, -vertScaleZ), D3DXVECTOR3(1.0f, -1.0f, -1.0f), { 1.0f, 1.0f } },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, -vertScaleZ), D3DXVECTOR3(-1.0f, -1.0f, -1.0f), { 0.0f, 1.0f } },

		// Left
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, vertScaleZ), D3DXVECTOR3(-1.0f, 1.0f, 1.0f), { 0.0f, 0.0f } },
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, -vertScaleZ), D3DXVECTOR3(-1.0f, 1.0f, -1.0f), { 1.0f, 0.0f } },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, -vertScaleZ), D3DXVECTOR3(-1.0f, -1.0f, -1.0f), { 1.0f, 1.0f } },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, vertScaleZ), D3DXVECTOR3(-1.0f, -1.0f, 1.0f), { 0.0f, 1.0f } },

		// Right
		{ D3DXVECTOR3(vertScaleX, vertScaleY, -vertScaleZ), D3DXVECTOR3(1.0f, 1.0f, -1.0f), { 0.0f, 0.0f } },
		{ D3DXVECTOR3(vertScaleX, vertScaleY, vertScaleZ), D3DXVECTOR3(1.0f, 1.0f, 1.0f), { 1.0f, 0.0f } },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, vertScaleZ), D3DXVECTOR3(1.0f, -1.0f, 1.0f), { 1.0f, 1.0f } },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, -vertScaleZ), D3DXVECTOR3(1.0f, -1.0f, -1.0f), { 0.0f, 1.0f } },

		// Back
		{ D3DXVECTOR3(vertScaleX, vertScaleY, vertScaleZ), D3DXVECTOR3(1.0f, 1.0f, 1.0f), { 0.0f, 0.0f } },
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, vertScaleZ), D3DXVECTOR3(-1.0f, 1.0f, 1.0f), { 1.0f, 0.0f } },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, vertScaleZ), D3DXVECTOR3(-1.0f, -1.0f, 1.0f), { 1.0f, 1.0f } },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, vertScaleZ), D3DXVECTOR3(1.0f, -1.0f, 1.0f), { 0.0f, 1.0f } },

		// Top
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, vertScaleZ), D3DXVECTOR3(-1.0f, 1.0f, 1.0f), { 0.0f, 0.0f } },
		{ D3DXVECTOR3(vertScaleX, vertScaleY, vertScaleZ), D3DXVECTOR3(1.0f, 1.0f, 1.0f), { 1.0f, 0.0f } },
		{ D3DXVECTOR3(vertScaleX, vertScaleY, -vertScaleZ), D3DXVECTOR3(1.0f, 1.0f, -1.0f), { 1.0f, 1.0f } },
		{ D3DXVECTOR3(-vertScaleX, vertScaleY, -vertScaleZ), D3DXVECTOR3(-1.0f, 1.0f, -1.0f), { 0.0f, 1.0f } },

		// Bottom
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, -vertScaleZ), D3DXVECTOR3(-1.0f, -1.0f, -1.0f), { 0.0f, 0.0f } },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, -vertScaleZ), D3DXVECTOR3(1.0f, -1.0f, -1.0f), { 1.0f, 0.0f } },
		{ D3DXVECTOR3(vertScaleX, -vertScaleY, vertScaleZ), D3DXVECTOR3(1.0f, -1.0f, 1.0f), { 1.0f, 1.0f } },
		{ D3DXVECTOR3(-vertScaleX, -vertScaleY, vertScaleZ), D3DXVECTOR3(-1.0f, -1.0f, 1.0f), { 0.0f, 1.0f } }
	};
	m_vertType = VT_NORMAL_UV;
	UINT stride = sizeof(*vertices);
	UINT vertexCount = (sizeof(vertices) / stride);

	// Create the Index Buffer
	DWORD indices[] = {
		// Front Face
		0, 1, 2,
		0, 2, 3,

		// Left Face
		4, 5, 6,
		4, 6, 7,

		// Right Face
		8, 9, 10,
		8, 10, 11,

		// Back Face
		12, 13, 14,
		12, 14, 15,

		// Top Face
		16, 17, 18,
		16, 18, 19,

		// Bottom Face
		20, 21, 22,
		20, 22, 23
	};
	m_primTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	UINT indexCount = (sizeof(indices) / sizeof(*indices));

	// Create the buffer
	m_pRenderer->CreateBuffer(vertices, indices, vertexCount, indexCount, stride, m_pBuffer);

	return true;
}

void DX10_Mesh_Rect_Prism::Render()
{
	m_pRenderer->RenderBuffer(m_pBuffer);
}

bool DX10_Mesh_Rect_Prism::Initialise(DX10_Renderer* _pRenderer, v3float _scale)
{
	// Save the renderer on the Rectangular Prism
	m_pRenderer = _pRenderer;

	m_scale = _scale;
	m_vertType = VT_NORMAL_UV;
	m_primTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	TVertexNormalUV* pVertexBuffer = 0;
	DWORD* pIndexBuffer = 0;
	int vertexCount;
	int indexCount;
	std::string fileName = "Resources/Meshes/Mesh_FinitePlane.txt";
	int stride = sizeof(TVertexNormalUV);

	VALIDATE(m_pRenderer->LoadMeshObj(fileName, pVertexBuffer, pIndexBuffer, &vertexCount, &indexCount, m_scale));

	// Create the buffer
	VALIDATE(m_pRenderer->CreateBuffer(pVertexBuffer, pIndexBuffer, vertexCount, indexCount, stride, m_pBuffer));

	return true;
}