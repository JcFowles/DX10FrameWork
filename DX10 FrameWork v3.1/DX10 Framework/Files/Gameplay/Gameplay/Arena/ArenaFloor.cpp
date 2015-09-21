/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : ArenaFloor.cpp
* Description : Controlling class for all arena related processes. Holds and controls all individual tiles.
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "ArenaFloor.h"

ArenaFloor::ArenaFloor()
{
	m_pDX10_Renderer = 0;
	m_timeElapsed = 0;
}

ArenaFloor::~ArenaFloor()
{
	if (m_pArenaTiles != 0)
	{
		while (m_pArenaTiles->empty() == false)
		{
			while (m_pArenaTiles->back()->empty() == false)
			{
				ReleasePtr(m_pArenaTiles->back()->back());
				m_pArenaTiles->back()->pop_back();
			}

			ReleasePtr(m_pArenaTiles->back());
			m_pArenaTiles->pop_back();
		}
		ReleasePtr(m_pArenaTiles);
	}

	ReleasePtr(m_pTileMesh);
}

bool ArenaFloor::Initialise(DX10_Renderer* _pDX10_Renderer, DX10_Shader_LitTex* _pShader, UINT _arenaSize, v3float _tileScale, float _matchLength)
{
	m_pDX10_Renderer = _pDX10_Renderer;
	m_matchLength = _matchLength;
	m_maxPowerSpawnTimer = 2.0f;
	m_powerSpawnTimer = 2.0f;

	// Create the Mesh for the Arena Tiles
	m_pTileMesh = new DX10_Mesh();
	VALIDATE(m_pTileMesh->Initialise(m_pDX10_Renderer, MT_FINITEPLANE, _tileScale));

	// Create the 2D vector of Arena Tiles
	m_pArenaTiles = new std::vector<std::vector<ArenaTile*>*>;
	for (UINT row = 0; row < _arenaSize; row++)
	{
		std::vector<ArenaTile*>* pRowOfTiles = new std::vector<ArenaTile*>;

		for (UINT col = 0; col < _arenaSize; col++)
		{
			// Create a new Tile
			ArenaTile* pTile = new ArenaTile();

			eBaseTileImages eBaseImage = (eBaseTileImages)(rand() % 3);

			VALIDATE(pTile->Initialise(m_pDX10_Renderer, m_pTileMesh, _pShader, eBaseImage));

			// Set the Position based upon the position in the 2D grid
			v3float tilePos;
			tilePos.x = ((float)row - ((float)_arenaSize / 2.0f)) * _tileScale.x + (_tileScale.x / 2.0f);
			tilePos.y = ((float)col - ((float)_arenaSize / 2.0f)) * _tileScale.y + (_tileScale.y / 2.0f);
			tilePos.z = 0.0f;
			pTile->SetPosition(tilePos);

			// Calculate the World matrix at Initialization only
			pTile->CalcWorldMatrix();

			// Add the new Tile to the Row
			pRowOfTiles->push_back(pTile);
		}
		m_pArenaTiles->push_back(pRowOfTiles);
	}

	// Calculate the time interval for destroying the outer layer
	int evenSize;
	// Ensure the Arena size is even for the next calculation
	(_arenaSize % 2 == 1) ? evenSize = ++_arenaSize : evenSize = _arenaSize;
	m_layerCount = evenSize / 2;
	m_destroyOutsideTime = m_matchLength / (float)m_layerCount + 1;

	m_destroyedLayers = 0;

	return true;
}

void ArenaFloor::Process(float _dt)
{
	m_timeElapsed += _dt;
	if (m_timeElapsed >= m_destroyOutsideTime)
	{
		StartDeathOuterLayer();

		m_timeElapsed = 0.0f;
	}

	m_powerSpawnTimer -= _dt;
	if (m_powerSpawnTimer <= 0.0f)
	{
		//SpawnPowerUp();
		m_powerSpawnTimer = m_maxPowerSpawnTimer;
	}

	// Process all the Tiles in the 2D vector
	// Cycle through all rows
	for (UINT row = 0; row < m_pArenaTiles->size(); row++)
	{
		// Cycle through all columns (elements in the rows)
		for (UINT col = 0; col < (*m_pArenaTiles)[row]->size(); col++)
		{
			(*(*m_pArenaTiles)[row])[col]->Process(_dt);
		}
	}
}

void ArenaFloor::Render()
{
	// Cycle through all rows
	for (UINT row = 0; row < m_pArenaTiles->size(); row++)
	{
		// Cycle through all columns (elements in the rows)
		for (UINT col = 0; col < (*m_pArenaTiles)[row]->size(); col++)
		{
			(*(*m_pArenaTiles)[row])[col]->Render();
		}
	}
}

void ArenaFloor::StartDeathOuterLayer()
{
	if (m_destroyedLayers <= m_layerCount)
	{	
		for (UINT col = m_destroyedLayers; col < (*m_pArenaTiles)[m_destroyedLayers]->size() - m_destroyedLayers - 1; col++)
		{
			int row = m_destroyedLayers;
			StartTileDeath(row, col);		
		}

		for (UINT col = m_destroyedLayers; col < (*m_pArenaTiles)[m_destroyedLayers]->size() - m_destroyedLayers - 1; col++)
		{
			int row = (*m_pArenaTiles)[m_destroyedLayers]->size() - m_destroyedLayers - 1;
			StartTileDeath(row, col);
		}

		for (UINT row = m_destroyedLayers; row < m_pArenaTiles->size() - m_destroyedLayers; row++)
		{
			int col = m_destroyedLayers;
			StartTileDeath(row, col);

			col = (*m_pArenaTiles)[row]->size() - 1 - m_destroyedLayers;
			StartTileDeath(row, col);
		}
	}

	// Increase the Count of destroyed layers
	m_destroyedLayers++;	
}

void ArenaFloor::StartTileDeath(UINT _row, UINT _col)
{
	float modifier = (float)(rand() % 80 - 40);
	modifier = modifier / 100.0f + 1.0f;

	(*(*m_pArenaTiles)[_row])[_col]->SetDeathTimer(m_destroyOutsideTime / 2 * modifier);
}

void ArenaFloor::SpawnPowerUp()
{
	// TO DO CAL - BROKEN

	if (m_destroyedLayers == m_layerCount)
	{
		// Last tile left and on destruction sequence, spawn no more power ups
		return;
	}
	int layersLeft = (m_layerCount * 2 - 2) - (m_destroyedLayers * 2);

	int randomRow = ((rand() % layersLeft) + (m_destroyedLayers * 2));
	int randomCol = ((rand() % layersLeft) + (m_destroyedLayers * 2));

	eOverlayTileImages powerImage = (eOverlayTileImages)(rand() % 3 + 1);

	(*(*m_pArenaTiles)[randomRow])[randomCol]->SetOverlayImage(powerImage);
}
