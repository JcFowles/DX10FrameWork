/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Game.h
* Description : Runs all Game play processes
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __GAME_H__
#define __GAME_H__

// Local Includes
#include "../../DX10/DX10/DX10_Renderer.h"
#include "Arena/ArenaFloor.h"
#include "Orbs\Orb.h"
#include "../../Input/InputGamePad.h"


class Game
{
public:

	/***********************
	* Game: Default Constructor for Game class
	* @author: Callan Moore
	********************/
	Game();

	/***********************
	* ~Game: Default Destructor for Game class
	* @author: Callan Moore
	********************/
	~Game();

	/***********************
	* Initialise: Initialise the Game for use
	* @author: Callan Moore
	* @parameter: _pDX10_Renderer: The renderer for this Game
	* @return: bool: Successful or not
	********************/
	bool Initialise(DX10_Renderer* _pDX10_Renderer, int _numPlayers);
	
	/***********************
	* Process: Process the Game
	* @author: Callan Moore
	* @parameter: _dt: The current delta tick
	* @return: void
	********************/
	bool Process(float _dt);
	
	/***********************
	* Render: Render the Game
	* @author: Callan Moore
	* @return: void
	********************/
	void Render();

	// TO DO JC
	void HandleInput();

	bool IsOrbsColliding(Orb* _OrbA, Orb* _OrbB);

	void HandleCollisions(Orb* _OrbA, Orb* _OrbB);

	void KillOrb(Orb* _Orb);

private:
	DX10_Renderer* m_pDX10_Renderer;
	ArenaFloor* m_pArenaFloor;
	DX10_Shader_LitTex* m_pShader_LitTex;

	// Players
	int m_numPlayers;
	int m_numAlivePlayers;


	// Contollers
	XButtonIDs m_XButtons;
	XStickDirectionIDs m_XStickDirections;
	std::vector<InputGamePad*> m_pContollers;

	// Player Controller Orbs
	std::vector<Orb*> m_pOrbs;

	DX10_Mesh* m_pOrbMesh;


	// TO DO JC: Temp remove
	std::vector<std::vector<ArenaTile*>*>* m_pArenaTiles;
	v3float m_tileScale;
	int m_areaSize;



};
#endif	//__GAME_H__

