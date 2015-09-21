/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10_Buffer.h
* Description : Wrapper class to hold all information for Vertex and Index Buffers for use in DirectX 10
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __DX10_BUFFER_H__
#define __DX10_BUFFER_H__

// Local Includes
#include "../DX10_Utilities.h"

class DX10_Buffer
{
public:
	/***********************
	* DX10_Buffer: Default Constructor for Buffer class
	* @author: Callan Moore
	* @parameter: _pDX10Device: The Device of the Renderer
	********************/
	DX10_Buffer(ID3D10Device* _pDX10Device)
	{
		m_pDX10Device = _pDX10Device;
	}

	/***********************
	* ~DX10_Buffer: Default Destructor for Buffer class
	* @author: Callan Moore
	********************/
	~DX10_Buffer()
	{
		ReleaseCOM(m_pVertexBuffer);
		ReleaseCOM(m_pIndexBuffer);
	}
	
	/***********************
	* Initialise: Creates a buffer that holds all information for Vertex and Index Buffers for an Object
	* @author: Callan Moore
	* @parameter: _pVertices: The array of Vertices
	* @parameter: _pIndices: The array of Indices
	* @parameter: _vertCount: Number of Vertices
	* @parameter: _indexCount: Number of Indices
	* @parameter: _usage: Buffer usage type
	* @parameter: _stride: Stride size for each Vertex
	* @parameter: _bufferID: Storage variable to hold the ID of the created buffer
	* @return: bool: Successful or not
	********************/
	template<typename TIndices, typename TVertices>
	bool Initialise(	typename TVertices* _pVertices, typename TIndices* _pIndices,
						UINT _vertCount, UINT _indexCount, UINT _stride,
						D3D10_USAGE _vertexUsage, D3D10_USAGE _indexUsage)
	{
		m_vertexCount = _vertCount;
		m_indexCount = _indexCount;
		m_stride = _stride;

		D3D10_BUFFER_DESC vertexBufferDesc;
		vertexBufferDesc.Usage = _vertexUsage;
		vertexBufferDesc.ByteWidth = sizeof(TVertices) * m_vertexCount;
		vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		(_vertexUsage == D3D10_USAGE_DYNAMIC) ? vertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE : vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;

		D3D10_SUBRESOURCE_DATA subResourceData;
		subResourceData.pSysMem = _pVertices;

		if (FAILED(m_pDX10Device->CreateBuffer(&vertexBufferDesc, &subResourceData, &m_pVertexBuffer)))
		{
			// Release a potentially created buffer
			ReleaseCOM(m_pVertexBuffer);
			return false;
		}

		if (m_indexCount != 0)
		{
			m_indexFormat = sizeof(TIndices) >= 4 ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT;

			D3D10_BUFFER_DESC indexBufferDesc;
			indexBufferDesc.Usage = _indexUsage;
			indexBufferDesc.ByteWidth = sizeof(TIndices) * m_indexCount;
			indexBufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
			(_indexUsage == D3D10_USAGE_DYNAMIC) ? indexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE : indexBufferDesc.CPUAccessFlags = 0;
			indexBufferDesc.MiscFlags = 0;
			D3D10_SUBRESOURCE_DATA subResourceData;
			subResourceData.pSysMem = _pIndices;

			if (FAILED(m_pDX10Device->CreateBuffer(&indexBufferDesc, &subResourceData, &m_pIndexBuffer)))
			{
				// Release a potentially created buffer
				ReleaseCOM(m_pVertexBuffer);
				ReleaseCOM(m_pIndexBuffer);
				return false;
			}
		}
		else
		{
			m_indexFormat = DXGI_FORMAT_UNKNOWN;
		}

		return true;
	}
	
	/***********************
	* Render: Render the Buffer to the current back buffer
	* @author: Callan Moore
	* @return: void
	********************/
	void Render()
	{
		UINT offset = 0;
		m_pDX10Device->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &m_stride, &offset);
		m_pDX10Device->IASetIndexBuffer(m_pIndexBuffer, m_indexFormat, 0);
		m_pDX10Device->DrawIndexed(m_indexCount, 0, 0);
	}

	/***********************
	* GetVertexBuffer: Retrieve the Vertex Buffer
	* @author: Callan Moore
	* @return: ID3D10Buffer*: The Vertex Buffer
	********************/
	ID3D10Buffer* GetVertexBuffer()
	{
		return m_pVertexBuffer;
	}

private:
	ID3D10Device* m_pDX10Device;
	ID3D10Buffer* m_pVertexBuffer;
	ID3D10Buffer* m_pIndexBuffer;

	DXGI_FORMAT m_indexFormat;

	UINT m_vertexCount;
	UINT m_indexCount;
	UINT m_stride;
};
#endif	// __DX10_BUFFER_H__

