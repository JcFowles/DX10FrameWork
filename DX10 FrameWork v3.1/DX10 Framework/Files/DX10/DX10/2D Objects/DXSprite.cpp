// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	:	DXSprite.cpp
// Description	:	The implementation file.
// Author(s)	:	Juran Griffith.
// Mail			:	juran.griffith@mediadesignschool.com
//

// Library Includes

// Local Includes
#include "DXSprite.h"

DXSprite::DXSprite():
	m_previousPosX(-1),
	m_previousPosY(-1),
	m_pDX10_Renderer(0),
	m_pTex(0)
{
}

DXSprite::~DXSprite()
{
}

bool DXSprite::Initialize(HWND* _pHWnd, DX10_Renderer* _pDX10_Renderer, DX10_Shader_Sprite* _pShader, std::string _filename, UINT _imageWidth, UINT _imageHeight, UINT _sliceWidth, UINT _sliceHeight)
{
	// Save the pointer to the device
	m_pDX10_Renderer = _pDX10_Renderer;
	m_pShader = _pShader;

	m_strFilename = _filename;

	m_sliceWidth = _sliceWidth;
	m_sliceHeight = _sliceHeight;

	m_index = 0;
	m_indexPrev = 0;

	POINT temp;
	for (int r = 0; r < m_sliceHeight; ++r)
	{
		for (int c = 0; c < m_sliceWidth; ++c)
		{
			temp.x = c + 1;
			temp.y = r + 1;
			m_imageIndexList.push_back(temp);
		}
	}

	//GetPngSize();

	// Set the size to render the image
	m_imageWidth = _imageWidth;
	m_imageHeight = _imageHeight;

	//m_offsetImageWidth = m_imageWidth;
	//m_offsetImageHeight = m_imageHeight;

	// Save the screen size.
	RECT rect;
	if (GetClientRect(*_pHWnd, &rect))
	{
		m_screenWidth = rect.right - rect.left;
		m_screenHeight = rect.bottom - rect.top;
	}

	// Calculate offsets to reduce the amount of divides in the update call.
	m_offsetScreenWidth = static_cast<float>((m_screenWidth / 2) * -1);
	m_offsetScreenHeight = static_cast<float>(m_screenHeight / 2);

	m_offsetImageWidth = static_cast<float>(_imageWidth / m_sliceWidth);
	m_offsetImageHeight = static_cast<float>(_imageHeight / m_sliceHeight);

	m_offsetU = static_cast<float>(1.0f / m_sliceWidth);
	m_offsetV = static_cast<float>(1.0f / m_sliceHeight);

	// Initialize the vertex and index buffer that hold the geometry for the triangle.
	if (!InitializeBuffers())
		return false;

	VALIDATE(m_pDX10_Renderer->CreateTexture(m_strFilename, m_pTex));

	return true;
}

void DXSprite::SetPosition(float _positionX, float _positionY)
{
	// Re-build the dynamic vertex buffer for rendering to a different location on the screen.
	UpdateBuffers(_positionX, _positionY);
}

int DXSprite::GetIndexCount()
{
	return m_indexCount;
}

int DXSprite::GetSliceWidth()
{
	return m_sliceWidth;
}

int DXSprite::GetSliceHeight()
{
	return m_sliceHeight;
}

UINT DXSprite::GetWidth()
{
	return (UINT)m_offsetImageWidth;
	//return m_imageWidth;
	//return 0;
}

UINT DXSprite::GetHeight()
{
	return (UINT)m_offsetImageHeight;
	//return m_imageHeight;
	//return 0;
}

void DXSprite::SetImageIndex(UINT _index)
{
	if (!m_imageIndexList.empty() && _index < m_imageIndexList.size())
	{
		m_index = _index;
	}
}

void DXSprite::SetSize(float _width, float _height)
{
	m_imageWidth = (UINT)_width;
	m_imageHeight = (UINT)_height;

	m_offsetImageWidth = static_cast<float>(_width / m_sliceWidth);
	m_offsetImageHeight = static_cast<float>(_height / m_sliceHeight);
}

void DXSprite::Render()
{
	// Set the type of primitive
	m_pDX10_Renderer->SetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pShader->Render(m_pBuff, m_pTex);
}

bool DXSprite::InitializeBuffers()
{
	TVertexUV* pVertices;
	unsigned long* pIndices;

	// Set the number of vertices in the vertex array.
	m_vertexCount = 6;

	// Set the number of indices in the index array.
	m_indexCount = m_vertexCount;

	// Create the vertex array.
	pVertices = new TVertexUV[m_vertexCount];
	if (!pVertices)
	{
		return false;
	}

	// Create the index array.
	pIndices = new unsigned long[m_indexCount];
	if (!pIndices)
	{
		return false;
	}

	// Initialize vertex array to zeros.
	memset(pVertices, 0, (sizeof(TVertexUV) * m_vertexCount));

	// Load the index array with data.
	for (UINT i = 0; i < m_indexCount; ++i)
	{
		pIndices[i] = i;
	}

	VALIDATE(m_pDX10_Renderer->CreateBuffer(pVertices, pIndices, m_vertexCount, m_indexCount, (UINT)sizeof(TVertexUV), m_pBuff, D3D10_USAGE_DYNAMIC, D3D10_USAGE_DEFAULT));

	// Clean up
	delete[] pVertices;
	pVertices = 0;

	delete[] pIndices;
	pIndices = 0;

	return true;
}

bool DXSprite::UpdateBuffers(float _positionX, float _positionY)
{
	// If the position has not changed then don't update the vertex buffer
	if ((_positionX == m_previousPosX) && (_positionY == m_previousPosY) && (m_indexPrev == m_index))
		return true;

	float left, right, top, bottom;
	TVertexUV* vertices;
	void* verticesPtr;

	// Update the position
	m_previousPosX = _positionX;
	m_previousPosY = _positionY;

	m_indexPrev = m_index;

	// Calculate the screen coordinates of the left side of the image.
	left = m_offsetScreenWidth + static_cast<float>(_positionX);

	// Calculate the screen coordinates of the right side of the image.
	//right = left + m_offsetImageWidth;
	right = left + m_imageWidth;

	// Calculate the screen coordinates of the top of the image.
	top = m_offsetScreenHeight - static_cast<float>(_positionY);

	// Calculate the screen coordinates of the bottom of the image.
	//bottom = top - m_offsetImageHeight;
	bottom = top - m_imageHeight;

	// Create the vertex array.
	vertices = new TVertexUV[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Load the vertex array with data.

	// First triangle.
	vertices[0].pos = D3DXVECTOR3(left, top, 0.0f);  // Top left.
	vertices[0].uv = v2float((m_imageIndexList[m_index].x - 1) * m_offsetU, (m_imageIndexList[m_index].y - 1) * m_offsetV);

	vertices[1].pos = D3DXVECTOR3(right, bottom, 0.0f);  // Bottom right.
	vertices[1].uv = v2float(m_imageIndexList[m_index].x * m_offsetU, m_imageIndexList[m_index].y * m_offsetV);

	vertices[2].pos = D3DXVECTOR3(left, bottom, 0.0f);  // Bottom left.
	vertices[2].uv = v2float((m_imageIndexList[m_index].x - 1) * m_offsetU, m_imageIndexList[m_index].y * m_offsetV);
	
	// Second triangle.
	vertices[3].pos = D3DXVECTOR3(left, top, 0.0f);  // Top left.
	vertices[3].uv = v2float((m_imageIndexList[m_index].x - 1) * m_offsetU, (m_imageIndexList[m_index].y - 1) * m_offsetV);

	vertices[4].pos = D3DXVECTOR3(right, top, 0.0f);  // Top right.
	vertices[4].uv = v2float(m_imageIndexList[m_index].x * m_offsetU, (m_imageIndexList[m_index].y - 1) * m_offsetV);

	vertices[5].pos = D3DXVECTOR3(right, bottom, 0.0f);  // Bottom right.
	vertices[5].uv = v2float(m_imageIndexList[m_index].x * m_offsetU, m_imageIndexList[m_index].y * m_offsetV);

	// Initialize the vertex buffer pointer.
	verticesPtr = 0;

	// Lock the vertex buffer.
	ID3D10Buffer* pVertexBuff = m_pBuff->GetVertexBuffer();
	VALIDATEHR(pVertexBuff->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**)&verticesPtr));

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(TVertexUV) * m_vertexCount));

	// Unlock the vertex buffer.
	pVertexBuff->Unmap();

	// Release the vertex array as it is no longer needed.
	delete[] vertices;
	vertices = 0;

	return true;
}

bool DXSprite::GetPngSize() // TO TEST Juran (doesn't work)
{
	std::string filename = TEXTUREFILEPATH;
	filename.append(m_strFilename);
	std::ifstream file(filename, std::ios_base::binary | std::ios_base::in);
	//std::ifstream file(filename);

	if (!file.is_open() || !file) {
		file.close();
		return false;
	}

	// Skip chucks
	file.seekg(16, std::ios_base::cur);

	UINT width, height;

	file.read((char*)&width, 4);
	file.read((char*)&height, 4);

	//width = ntohl(width);
	//height = ntohl(height);

	//m_imageWidth = static_cast<float>(width);
	//m_imageHeight = static_cast<float>(height);

	file.close();

	return true;
}