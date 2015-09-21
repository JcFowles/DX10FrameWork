/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : ArenaTile.h
* Description : Tile to hold information about a small section of the Arena Floor
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __ARENATILE_H__
#define __ARENATILE_H__

// Local Includes
#include "../../../DX10/DX10/3D Objects/DX10_Obj_Generic.h"
#include "../../../DX10/DX10/Meshes/DX10_Mesh.h"
#include "../../../DX10/DX10/Shaders/DX10_Shader_LitTex.h"

/***********************
* eBaseTileImages: The image list of textures that can be applied to the base of a tile
* @author: Callan Moore
********************/
enum eBaseTileImages
{
	BTI_STANDARD,	
	BTI_SLIPPERY,	
	BTI_ROUGH,
	BTI_STANDARD_DYING,
	BTI_SLIPPERY_DYING,
	BTI_ROUGH_DYING
};

/***********************
* eOverlayTileImages: The image list of textures that can be overlayed on top of a tile
* @author: Callan Moore
********************/
enum eOverlayTileImages
{
	OTI_BLANK,
	OTI_POWER_CONFUSION,
	OTI_POWER_SIZEINCREASE,
	OTI_POWER_SPEEDINCREASE
};

class ArenaTile :
	public DX10_Obj_Generic
{
public:

	/***********************
	* ArenaTile: Default Constructor for Arena Tile class
	* @author: Callan Moore
	********************/
	ArenaTile();

	/***********************
	* ~ArenaTile: Default Destructor for Arena Tile class
	* @author: Callan Moore
	********************/
	~ArenaTile();

	/***********************
	* Initialise: Initialise the ArenaTilefor use
	* @author: Callan Moore
	* @parameter: _pDX10_Renderer: The renderer for this object
	* @parameter: _pMesh: The mesh to create this tile with
	* @parameter: _pShader: The shader to use for rendering this tile
	* @parameter: _baseImage: Enum to indicate which image to display as the tiles base image
	* @return: bool: Successful or not
	********************/
	bool Initialise(DX10_Renderer* _pDX10_Renderer, DX10_Mesh* _pMesh, DX10_Shader_LitTex* _pShader, eBaseTileImages _baseImage);
	
	/***********************
	* Process: Process the Tile
	* @author: Callan Moore
	* @parameter: _dt: The current delta tick
	* @return: void
	********************/
	void Process(float _dt);
	
	/***********************
	* Render: Render the Tile
	* @author: Callan Moore
	* @return: void
	********************/
	void Render();
	
	/***********************
	* GetBaseImage: Retrieve the Base Image indicator for which image is displayed on the tile
	* @author: Callan Moore
	* @return: eBaseTileImages: Enum for the displayed image
	********************/
	eBaseTileImages GetBaseImageEnum() { return m_baseImage; };
	
	/***********************
	* GetActive: Retrieve the active state of the tile
	* @author: Callan Moore
	* @return: bool: The active state
	********************/
	bool GetActive() { return m_active; };

	/***********************
	* SetOverlayImage: Set the Overlay image to a new one
	* @author: Callan Moore
	* @parameter: _overlay: The new enum to determine the Overlay image
	* @return: void
	********************/
	void SetOverlayImage(eOverlayTileImages _overlay) { m_currentOverlay = _overlay; };

	/***********************
	* SetActive: Set the Active state of the tile
	* @author: Callan Moore
	* @parameter: _active: The new active state
	* @return: void
	********************/
	void SetActive(bool _active){ m_active = _active; };

	/***********************
	* SetDeathTimer: Set the time taken for this tile to die and start that timer
	* @author: Callan Moore
	* @parameter: _deathTime: The time taken for this tile to die and become inactive
	* @return: void
	********************/
	void SetDeathTimer(float _deathTime) { m_deathTimer = 0; m_deathIncrement = _deathTime / 10;};

private:
	DX10_Shader_LitTex* m_pShader_LitTex;
	ID3D10ShaderResourceView* m_pBaseTex[11];
	ID3D10ShaderResourceView* m_pOverlayTex[4];

	eBaseTileImages m_baseImage;
	int m_currentBaseImage;
	eOverlayTileImages m_currentOverlay;

	bool m_active;
	float m_deathTimer;
	float m_deathIncrement;
	float m_reduceAlpha;
	int m_deathFrameCount;
};
#endif	// __ARENATILE_H__
