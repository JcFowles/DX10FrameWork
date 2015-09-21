/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10_Mesh_Finite_Plane.cpp
* Description : Creates a Mesh for a Finite Plane
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "DX10_Mesh_Finite_Plane.h"

DX10_Mesh_Finite_Plane::DX10_Mesh_Finite_Plane()
{
}

DX10_Mesh_Finite_Plane::~DX10_Mesh_Finite_Plane()
{
}

bool DX10_Mesh_Finite_Plane::Initialise(DX10_Renderer* _pRenderer, TVertexBasic _vert, v3float _scale)
{
	// Save the renderer on the Cube
	m_pRenderer = _pRenderer;

	bool randomYawValues;
	_scale.y != 0.0f ? randomYawValues = true : randomYawValues = false;

	const UINT kVertexCount = 400;
	int size = (int)sqrt(kVertexCount);
	int sizeFromOrigin = (size / 2);

	TVertexColor vertices[kVertexCount];

	if (randomYawValues == true)
	{
		for (int length = -sizeFromOrigin; length < sizeFromOrigin; length++)
		{
			for (int width = -sizeFromOrigin; width < sizeFromOrigin; width++)
			{

				int index = (length + sizeFromOrigin) * size + (width + sizeFromOrigin);

				float yPos = (float)(rand() % 2);
				vertices[index].pos = D3DXVECTOR3((width * _scale.x), (yPos), (length * _scale.z));
			}
		}
	}
	else
	{
		for (int length = -sizeFromOrigin; length < sizeFromOrigin; length++)
		{
			for (int width = -sizeFromOrigin; width < sizeFromOrigin; width++)
			{
				int index = (length + sizeFromOrigin) * size + (width + sizeFromOrigin);
				vertices[index].pos = D3DXVECTOR3((width * _scale.x), 0, (length * _scale.z));
			}
		}
	}

	// Save the information for the Vertex Buffer
	m_vertType = VT_COLOR;
	UINT stride = sizeof(*vertices);

	const UINT kIndexCount = 778;
	DWORD indices[kIndexCount];
	int index = 0;
	// Cycle through all rows except last one
	for (int row = 0; row < size - 1; row++)
	{
		if (row % 2 == 0)	// Even Row
		{
			// Even Rows go Right to Left for Clockwise winding order
			for (int col = (int)(size - 1); col >= 0; col--)
			{
				indices[index++] = (col + (row * size));
				indices[index++] = (col + ((row + 1) * size));
			}

			// Add Degenerate triangle at end of each row
			if (row != size - 2)
			{
				indices[index++] = (0 + ((row + 1) * size));
			}
		}
		else	// Odd Row
		{
			// Even Rows go Left to Right for Clockwise winding order
			for (int col = 0; col < size; col++)
			{
				indices[index++] = (col + (row * size));
				indices[index++] = (col + ((row + 1) * size));
			}

			// Add Degenerate triangle at end of each row
			if (row != size - 2)
			{
				indices[index++] = ((size - 1) + ((row + 1)  * size));
			}
		}
	}

	m_primTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

	// Create the buffer and store the ID
	m_pRenderer->CreateBuffer(vertices, indices, kVertexCount, kIndexCount, stride, m_pBuffer);

	return true;
}

bool DX10_Mesh_Finite_Plane::Initialise(DX10_Renderer* _pRenderer, TVertexColor _vert, v3float _scale, D3DXCOLOR _color)
{
	// Save the renderer on the Cube
	m_pRenderer = _pRenderer;

	bool randomYawValues;
	_scale.y != 0.0f ? randomYawValues = true : randomYawValues = false;

	const UINT kVertexCount = 400;
	int size = (int)sqrt(kVertexCount);
	int sizeFromOrigin = (size / 2);

	TVertexColor vertices[kVertexCount];

	if (randomYawValues == true)
	{
		for (int length = -sizeFromOrigin; length < sizeFromOrigin; length++)
		{
			for (int width = -sizeFromOrigin; width < sizeFromOrigin; width++)
			{

				int index = (length + sizeFromOrigin) * size + (width + sizeFromOrigin);

				float yPos = (float)(rand() % 2);
				vertices[index].pos = D3DXVECTOR3((width * _scale.x), (yPos), (length * _scale.z));
				D3DXCOLOR gradientColor = _color * (yPos * 2.0f / 255) / 10.0f;
				vertices[index].color = gradientColor;
			}
		}
	}
	else
	{
		for (int length = -sizeFromOrigin; length < sizeFromOrigin; length++)
		{
			for (int width = -sizeFromOrigin; width < sizeFromOrigin; width++)
			{
				int index = (length + sizeFromOrigin) * size + (width + sizeFromOrigin);
				vertices[index].pos = D3DXVECTOR3((width * _scale.x), 0, (length * _scale.z));
				vertices[index].color = _color;
			}
		}
	}

	// Save the information for the Vertex Buffer
	m_vertType = VT_COLOR;
	UINT stride = sizeof(*vertices);

	const UINT kIndexCount = 778;
	DWORD indices[kIndexCount];
	int index = 0;
	// Cycle through all rows except last one
	for (int row = 0; row < size - 1; row++)
	{
		if (row % 2 == 0)	// Even Row
		{
			// Even Rows go Right to Left for Clockwise winding order
			for (int col = (int)(size - 1); col >= 0; col--)
			{
				indices[index++] = (col + (row * size));
				indices[index++] = (col + ((row + 1) * size));
			}

			// Add Degenerate triangle at end of each row
			if (row != size - 2)
			{
				indices[index++] = (0 + ((row + 1) * size));
			}
		}
		else	// Odd Row
		{
			// Even Rows go Left to Right for Clockwise winding order
			for (int col = 0; col < size; col++)
			{
				indices[index++] = (col + (row * size));
				indices[index++] = (col + ((row + 1) * size));
			}

			// Add Degenerate triangle at end of each row
			if (row != size - 2)
			{
				indices[index++] = ((size - 1) + ((row + 1)  * size));
			}
		}
	}

	m_primTopology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

	// Create the buffer and store the ID
	m_pRenderer->CreateBuffer(vertices, indices, kVertexCount, kIndexCount, stride, m_pBuffer);

	return true;
}

void DX10_Mesh_Finite_Plane::Render()
{
	m_pRenderer->RenderBuffer(m_pBuffer);
}