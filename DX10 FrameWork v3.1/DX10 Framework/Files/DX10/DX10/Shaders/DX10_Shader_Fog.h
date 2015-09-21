///*
//* Bachelor of Software Engineering
//* Media Design School
//* Auckland
//* New Zealand
//*
//* (c) 2005 - 2015 Media Design School
//*
//* File Name : DX10_Shader_Fog.h
//* Description : Shader Instructions for the Fog shader
//* Author :	Jc Fowles
//* Mail :	Jc.Fowles@mediadesign.school.nz
//*/
//
//// Inclusion Guards
//#pragma once
//#ifndef __DX10_SHADER_FOG_H__
//#define __DX10_SHADER_FOG_H__
//
//// Local Includes
//#include "../../../Utility/Utilities.h"
//#include "../DX10_Utilities.h"
//#include "../DX10_Renderer.h"
//
///***********************
//* TFog: Shader Variables for the Fog FX
//* @author: Jc Fowles
//********************/
//struct TFog
//{
//	DX10_Mesh* pMesh;
//	D3DXMATRIX* pMatWorld;
//};
//
//enum eTech_Fog
//{
//	TECH_FOG_STANDARD,
//};
//
//class DX10_Shader_Fog
//{
//public:
//
//	/***********************
//	* DX10_Shader_Fog: Default Constructor for the Fog Shader class
//	* @author: Jc Fowles
//	* @return:
//	********************/
//	DX10_Shader_Fog()
//	{
//	}
//
//	/***********************
//	* ~DX10_Shader_Fog: Default Destructor for  the Fog Shader class
//	* @author: Jc Fowles
//	* @return:
//	********************/
//	~DX10_Shader_Fog()
//	{
//	}
//
//	/***********************
//	* Initialise: Initialise the shader for use
//	* @author: Callan Moore
//	* @parameter: _pDX10_Renderer: DX10 Renderer for this application
//	* @return: bool: Successful or not
//	********************/
//	bool Initialise(DX10_Renderer* _pDX10_Renderer)
//	{
//		m_pDX10_Renderer = _pDX10_Renderer;
//
//		VALIDATE(BuildFX());
//		VALIDATE(CreateFXVarPointers());
//		VALIDATE(CreateVertexLayout());
//
//		//VALIDATE(m_pDX10_Renderer->CreateTexture("defaultSpecular.dds", m_pSpecularTex));
//
//		return true;
//	}
//
//	/***********************
//	* SetUpPerFrame: Setup the shader file with the variables used for the whole frame
//	* @author: Callan Moore
//	* @return: void
//	********************/
//	void SetUpPerFrame()
//	{
//		m_pMatView->SetMatrix((float*)m_pDX10_Renderer->GetViewMatrix());
//		m_pMatProj->SetMatrix((float*)m_pDX10_Renderer->GetProjMatrix());
//	}
//
//	/***********************
//	* Render: Ready the shader technique with object specific details and setting the objects mesh to render
//	* @author: Callan Moore
//	* @parameter: _litTex: Structure containing all details for a fog object
//	* @parameter: _eTech: Technique Identifier to determine which technique to use
//	* @return: void
//	********************/
//	void Render(TFog _fog, eTech_LitTex _eTech)
//	{
//		// Reset draw states in case they're different
//		m_pDX10_Renderer->RestoreDefaultDrawStates();
//		SetCurrentPtrs(_eTech);
//
//		// Set the Renderer Input layout and primitive topology to be the correct ones for this shader
//		m_pDX10_Renderer->SetInputLayout(m_pCurrentVertexLayout);
//		m_pDX10_Renderer->SetPrimitiveTopology(_litTex.pMesh->GetPrimTopology());
//
//		// Don't transform texture coordinates
//		D3DXMATRIX matTex;
//		D3DXMatrixIdentity(&matTex);
//
//		if (m_pCurrentTech != NULL)
//		{
//			D3D10_TECHNIQUE_DESC techDesc;
//			m_pCurrentTech->GetDesc(&techDesc);
//			for (UINT p = 0; p < techDesc.Passes; ++p)
//			{
//				D3DXMATRIX matWorld = *_litTex.pMatWorld;
//
//				m_pMatWorld->SetMatrix((float*)&matWorld);
//				m_pMatTex->SetMatrix((float*)&matTex);
//				m_pTexture->SetResource(_litTex.pTexBase);
//				m_pMapSpecular->SetResource(m_pSpecularTex);
//				m_pReduceAlpha->SetRawValue(&_litTex.reduceAlpha, 0, sizeof(float));
//
//
//				m_pCurrentTech->GetPassByIndex(p)->Apply(0);
//				_litTex.pMesh->Render();
//			}
//		}
//	}
//
//private:
//
//	/***********************
//	* BuildFX: Build the FX file for the Shader
//	* @author: Jc Fowles
//	* @return: bool: Successful or not
//	********************/
//	bool BuildFX()
//	{
//		VALIDATE(m_pDX10_Renderer->BuildFX("Fog.fx", "FogTech", m_pFX, m_pTech_Fog));
//
//		return true;
//	}
//
//	/***********************
//	* CreateFXVarPointers: Create the pointers to the FX memory on the graphics card
//	* @author: Jc Fowles
//	* @return: bool: Successful or not
//	********************/
//	bool CreateFXVarPointers()
//	{
//		// Per Frame
//		m_pMatView = m_pFX->GetVariableByName("g_matView")->AsMatrix();
//		m_pMatProj = m_pFX->GetVariableByName("g_matProj")->AsMatrix();
//
//		// Per Object
//		m_pMatWorld = m_pFX->GetVariableByName("g_matWorld")->AsMatrix();
//		m_pMatTex = m_pFX->GetVariableByName("g_matTex")->AsMatrix();
//
//		// Globals
//		m_pTexture = m_pFX->GetVariableByName("g_shaderTexture")->AsShaderResource();
//
//
//		VALIDATE(m_pMatView != 0);
//		VALIDATE(m_pMatProj != 0);
//		VALIDATE(m_pMatWorld != 0);
//		VALIDATE(m_pMatTex != 0);
//		VALIDATE(m_pTexture != 0);
//
//
//		return true;
//	}
//
//	/***********************
//	* CreateVertexLayout: Create the vertex layout for this shader
//	* @author: Callan Moore
//	* @return: bool: Successful or not
//	********************/
//	bool CreateVertexLayout()
//	{
//		// Vertex Desc for a basic vertex with Normals and UV coordinates
//		D3D10_INPUT_ELEMENT_DESC vertexDesc[] =
//		{
//			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
//			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
//			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 },
//		};
//		UINT elementNum = sizeof(vertexDesc) / sizeof(vertexDesc[0]);
//
//		m_pDX10_Renderer->CreateVertexLayout(vertexDesc, elementNum, m_pTech_Fog, m_pVertexLayout_Standard);
//
//		return true;
//	}
//
//	/***********************
//	* SetCurrentPtrs: Set the Current Vertex Layout and Technique pointers
//	* @author: Jc Fowles
//	* @parameter: _tech: Enumerator to determine which set of pointers to use as current
//	* @return: void
//	********************/
//	void SetCurrentPtrs(eTech_Fog _tech)
//	{
//		switch (_tech)
//		{
//		case TECH_FOG_STANDARD:
//		{
//			m_pCurrentVertexLayout = m_pVertexLayout_Standard;
//			m_pCurrentTech = m_pTech_Fog;
//		}
//			break;
//		default:
//		{
//			m_pCurrentVertexLayout = 0;
//			m_pCurrentTech = 0;
//		}
//		}	// End Switch
//	}
//
//private:
//
//	ID3D10Effect* m_pFX;
//
//	ID3D10InputLayout* m_pCurrentVertexLayout;
//	ID3D10InputLayout* m_pVertexLayout_Standard;
//
//	ID3D10EffectTechnique* m_pCurrentTech;
//	ID3D10EffectTechnique* m_pTech_Fog;
//
//	DX10_Renderer*						m_pDX10_Renderer;
//
//	ID3D10EffectMatrixVariable*			m_pMatView;
//	ID3D10EffectMatrixVariable*			m_pMatProj;
//
//	ID3D10EffectMatrixVariable*			m_pMatWorld;
//	ID3D10EffectMatrixVariable*			m_pMatTex;
//
//	ID3D10EffectShaderResourceVariable* m_pTexture;
//};
//
//#endif	// __DX10_SHADER_FOG_H__