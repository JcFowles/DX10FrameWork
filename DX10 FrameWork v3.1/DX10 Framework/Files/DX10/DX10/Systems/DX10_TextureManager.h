/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : DX10_TextureManager.h
* Description : Class to manager creation and deletions of textures as ID3D10ShaderResourceView
* Author :	Jc Fowles
* Mail :	Jc.Fowles@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

// Local Includes
#include "../DX10_Utilities.h"
#include "../../../Utility/Utilities.h"

class DX10_TextureManager
{
public:

	/***********************
	* DX10_TextureManager: Default Constructor for Texture Manager class
	* @author: Jc Fowles
	* @parameter: _pDX10Device: The Device of the Renderer
	* @return:
	********************/
	DX10_TextureManager(ID3D10Device* _pDX10Device)
	{
		m_pDX10Device = _pDX10Device;
	};

	/***********************
	* ~DX10_TextureManager: Default Destuctor for Texture Manager class
	* @author: Jc Fowles
	* @return:
	********************/
	~DX10_TextureManager()
	{
		// Delete the Graphics memory stored as DX10 Textures
		std::map<std::string, ID3D10ShaderResourceView*>::iterator iterTexture = m_textures.begin();
		while (iterTexture != m_textures.end())
		{
			ReleaseCOM(iterTexture->second);
			iterTexture++;
		}

		//ReleaseCOM(mRandomTexRV);
	};

	/***********************
	* CreateTexure: Create a Texture from a file
	* @author: Jc Fowles
	* @parameter: _texFileName: The Filename of the Texture
	* @return: ID3D10ShaderResourceView*: The Texture as a ID3D10ShaderResourceView Pointer
	********************/
	ID3D10ShaderResourceView* CreateTexure(std::string _texFileName)
	{
		ID3D10ShaderResourceView* pTexture = 0;

		// Look for the texture by name to see if it is already loaded
		std::map<std::string, ID3D10ShaderResourceView*>::iterator texCheck;
		texCheck = m_textures.find(_texFileName);

		// Check if the Texture exists
		if (texCheck != m_textures.end())
		{
			// Texture is already loaded. Save its ID
			pTexture = texCheck->second;
		}
		else
		{
			// Texture is new, create and save.
			std::string filePath = TEXTUREFILEPATH;
			filePath.append(_texFileName);

			CHECKHR(D3DX10CreateShaderResourceViewFromFileA(m_pDX10Device,
				filePath.c_str(), 0, 0, &pTexture, 0));

			std::pair<std::string, ID3D10ShaderResourceView*> texPair(_texFileName, pTexture);

			if ((m_textures.insert(texPair).second) == false)
			{
				ReleaseCOM(pTexture);
				return 0;
			};
		}

		return pTexture;
		
	};

	/***********************
	* CreateTexureArray: Create a Texture Array from multiple files stored in a single folder
	* @author: Jc Fowles
	* @parameter: _folderName: The filename of the folder the textures are stored in
	* @parameter: _texFileNames: The list of texture files
	* @return: ID3D10ShaderResourceView*: The Texture Array as a ID3D10ShaderResourceView Pointer
	********************/
	ID3D10ShaderResourceView* CreateTexureArray(std::string _folderName, const std::vector<std::string>& _texFileNames)
	{
		ID3D10ShaderResourceView* pTextureArray = 0;

		// Look for the texture array by folder name to see if it is already loaded
		std::map<std::string, ID3D10ShaderResourceView*>::iterator texCheck;
		texCheck = m_textures.find(_folderName);

		// Check if the Texture Array exists
		if (texCheck != m_textures.end())
		{
			pTextureArray = texCheck->second;
		}
		else
		{
			// Texture is new, create and save.


			// Load the Texture Elements Individually from the File. 
			UINT arraySize = (UINT)_texFileNames.size();

			std::vector<ID3D10Texture2D*> srcTexure(arraySize, 0);
			for (UINT i = 0; i < arraySize; ++i)
			{
				D3DX10_IMAGE_LOAD_INFO loadInfo;

				loadInfo.Width = D3DX10_FROM_FILE;
				loadInfo.Height = D3DX10_FROM_FILE;
				loadInfo.Depth = D3DX10_FROM_FILE;
				loadInfo.FirstMipLevel = 0;
				loadInfo.MipLevels = D3DX10_FROM_FILE;
				loadInfo.Usage = D3D10_USAGE_STAGING;
				loadInfo.BindFlags = 0;
				loadInfo.CpuAccessFlags = D3D10_CPU_ACCESS_WRITE | D3D10_CPU_ACCESS_READ;
				loadInfo.MiscFlags = 0;
				loadInfo.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				loadInfo.Filter = D3DX10_FILTER_NONE;
				loadInfo.MipFilter = D3DX10_FILTER_NONE;
				loadInfo.pSrcInfo = 0;

				std::string filePath = TEXTUREFILEPATH;
				filePath.append(_texFileNames[i]);

				CHECKHR(D3DX10CreateTextureFromFileA(m_pDX10Device, filePath.c_str(),
				&loadInfo, 0, (ID3D10Resource**)&srcTexure[i], 0));
			}

			// Create the Texture Array with each Element having the same Format/Dimensions. 

			D3D10_TEXTURE2D_DESC texureElementDesc;
			srcTexure[0]->GetDesc(&texureElementDesc);

			D3D10_TEXTURE2D_DESC texureArrayDesc;
			texureArrayDesc.Width = texureElementDesc.Width;
			texureArrayDesc.Height = texureElementDesc.Height;
			texureArrayDesc.MipLevels = texureElementDesc.MipLevels;
			texureArrayDesc.ArraySize = arraySize;
			texureArrayDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			texureArrayDesc.SampleDesc.Count = 1;
			texureArrayDesc.SampleDesc.Quality = 0;
			texureArrayDesc.Usage = D3D10_USAGE_DEFAULT;
			texureArrayDesc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
			texureArrayDesc.CPUAccessFlags = 0;
			texureArrayDesc.MiscFlags = 0;

			ID3D10Texture2D* tmpTexureArray = 0;
			CHECKHR(m_pDX10Device->CreateTexture2D(&texureArrayDesc, 0, &tmpTexureArray));

			// Copy each Individual Texture Elements into the texture array.

			for (UINT i = 0; i < arraySize; ++i)
			{
				// Go through every Mipmap Level
				for (UINT j = 0; j < texureElementDesc.MipLevels; ++j)
				{
					D3D10_MAPPED_TEXTURE2D mappedTex2D;
					srcTexure[i]->Map(j, D3D10_MAP_READ, 0, &mappedTex2D);

					// Add each of the texture to the 2D Texture tmpTexureArray
					UINT dstSubresource = D3D10CalcSubresource(j, i, texureElementDesc.MipLevels);
					m_pDX10Device->UpdateSubresource(tmpTexureArray, dstSubresource, 0, mappedTex2D.pData, mappedTex2D.RowPitch, 0);

					srcTexure[i]->Unmap(j);
				}
			}

			// Create a resource view from the 2D Texture tmpTexureArray.
			D3D10_SHADER_RESOURCE_VIEW_DESC viewDesc;
			viewDesc.Format = texureArrayDesc.Format;
			viewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2DARRAY;
			viewDesc.Texture2DArray.MostDetailedMip = 0;
			viewDesc.Texture2DArray.MipLevels = texureArrayDesc.MipLevels;
			viewDesc.Texture2DArray.FirstArraySlice = 0;
			viewDesc.Texture2DArray.ArraySize = arraySize;

			CHECKHR(m_pDX10Device->CreateShaderResourceView(tmpTexureArray, &viewDesc, &pTextureArray));

			// Clean Up
			ReleaseCOM(tmpTexureArray);

			for (UINT i = 0; i < arraySize; ++i)
			{
				ReleaseCOM(srcTexure[i]);
			}

			// Add the texture to the map
			std::pair<std::string, ID3D10ShaderResourceView*> texPair(_folderName, pTextureArray);

			if ((m_textures.insert(texPair).second) == false)
			{
				ReleaseCOM(pTextureArray);
				return 0;
			};
		}

		// Return the Texture Array
		return pTextureArray;

	};

	/***********************
	* CreateRandomTexture: Create a Random 1D Texture
	* @author: Jc Fowles
	* @return: ID3D10ShaderResourceView*: The Random 1D Texture as a ID3D10ShaderResourceView Pointer
	********************/
	ID3D10ShaderResourceView* CreateRandomTexture()
	{

		ID3D10ShaderResourceView* pRandomTexure = 0;

		// Check if the Random Texture exists
		std::map<std::string, ID3D10ShaderResourceView*>::iterator texCheck;
		texCheck = m_textures.find("RandomTexture");
		if (texCheck != m_textures.end())
		{
			pRandomTexure = texCheck->second;
		}
		else
		{
			// Create the random data.
			D3DXVECTOR4 randomValues[1024];
			for (int i = 0; i < 1024; ++i)
			{
				randomValues[i].x = RandomFloat(-1.0f, 1.0f);
				randomValues[i].y = RandomFloat(-1.0f, 1.0f);
				randomValues[i].z = RandomFloat(-1.0f, 1.0f);
				randomValues[i].w = RandomFloat(-1.0f, 1.0f);
			}

			D3D10_SUBRESOURCE_DATA initialData;
			initialData.pSysMem = randomValues;
			initialData.SysMemPitch = 1024 * sizeof(D3DXVECTOR4);
			initialData.SysMemSlicePitch = 1024 * sizeof(D3DXVECTOR4);

			// Create the texture.
			D3D10_TEXTURE1D_DESC textureDesc;
			textureDesc.Width = 1024;
			textureDesc.MipLevels = 1;
			textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			textureDesc.Usage = D3D10_USAGE_IMMUTABLE;
			textureDesc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
			textureDesc.CPUAccessFlags = 0;
			textureDesc.MiscFlags = 0;
			textureDesc.ArraySize = 1;

			ID3D10Texture1D* randomTex = 0;
			CHECKHR(m_pDX10Device->CreateTexture1D(&textureDesc, &initialData, &randomTex));

			// Create the resource view.
			D3D10_SHADER_RESOURCE_VIEW_DESC viewDesc;
			viewDesc.Format = textureDesc.Format;
			viewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE1D;
			viewDesc.Texture1D.MipLevels = textureDesc.MipLevels;
			viewDesc.Texture1D.MostDetailedMip = 0;

			CHECKHR(m_pDX10Device->CreateShaderResourceView(randomTex, &viewDesc, &pRandomTexure));

			ReleaseCOM(randomTex);

			std::pair<std::string, ID3D10ShaderResourceView*> texPair("RandomTexture", pRandomTexure);

			if ((m_textures.insert(texPair).second) == false)
			{
				ReleaseCOM(pRandomTexure);
				return 0;
			};
		}

		// return the random Texture
		return pRandomTexure;
	}

private:

	DX10_TextureManager(const DX10_TextureManager& rhs);
	DX10_TextureManager& operator=(const DX10_TextureManager& rhs);

private:
	ID3D10Device* m_pDX10Device;
	std::map<std::string, ID3D10ShaderResourceView*> m_textures;

};


#endif // TEXTURE_MANAGER_H
