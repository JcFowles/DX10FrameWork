/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Game.cpp
* Description : Runs all Game play processes
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
	ReleasePtr(m_pArenaFloor);
	ReleasePtr(m_pShader_LitTex);

	// TO DO CAL: To move to a shut down

	while (m_pContollers.empty() == false)
	{
		ReleasePtr(m_pContollers.back());
		m_pContollers.pop_back();
	}

	while (m_pOrbs.empty() == false)
	{
		ReleasePtr(m_pOrbs.back());
		m_pOrbs.pop_back();
	}

	ReleasePtr(m_pOrbMesh);

}

bool Game::Initialise(DX10_Renderer* _pDX10_Renderer, int _numPlayers)
{
	if (_pDX10_Renderer == 0)
	{
		// If the Renderer is NULL the Game cannot be utilized
		return false;
	}

	m_numPlayers = _numPlayers;
	m_numAlivePlayers = _numPlayers;
	m_pDX10_Renderer = _pDX10_Renderer;
														
	// Create the Shader for the Game Objects
	m_pShader_LitTex = new DX10_Shader_LitTex();
	VALIDATE(m_pShader_LitTex->Initialise(m_pDX10_Renderer));


	// Create the Orb Mesh
	float OrbRadius = 1.0f;
	m_pOrbMesh = new DX10_Mesh;
	v3float orbScale = { OrbRadius * 2, OrbRadius * 2, OrbRadius * 2 };
	VALIDATE(m_pOrbMesh->Initialise(m_pDX10_Renderer, MT_SPHERE, orbScale));

	// TO DO JC: This will be based on the number of players selected for a given match
	// Create the Controllers and the player orbs

	std::string temp;
	for (int i = 0; i < m_numPlayers; i++)
	{
		m_pContollers.push_back(new InputGamePad());
		VALIDATE(m_pContollers[i]->Initialise(i + 1));

		m_pOrbs.push_back(new Orb());
		switch (i)
		{
		case 0:
			temp = "pBall.png";
			break;
		case 1:
			temp = "gBall.png";
			break;
		case 2:
			temp = "Tron/Tile/tron_tile_green.png";
			break;
		case 3:
			temp = "Tron/Tile/tron_tile_white.png";
			break;
		}
		VALIDATE(m_pOrbs[i]->Initialise(m_pDX10_Renderer, m_pOrbMesh, m_pShader_LitTex, temp, 2.0f, 1.0f, 100.0f));
		m_pOrbs[i]->SetPosition({ (float(i)*5.0f), 0.0f, -2.0f });

		//VALIDATE(m_pContollers[i]->Connected());
	}
   
	// Create and Initialise the Arena Floor
	m_pArenaFloor = new ArenaFloor();
	m_tileScale = { 4, 4, 4 };
	m_areaSize = 15;
	VALIDATE(m_pArenaFloor->Initialise(m_pDX10_Renderer, m_pShader_LitTex, m_areaSize, m_tileScale, 90.0f));
	
	m_pArenaTiles = m_pArenaFloor->GetArenaTiles();

	return true;
}

bool Game::IsOrbsColliding(Orb* _OrbA, Orb* _OrbB)
{
	if ((_OrbA != _OrbB))
	{
		if (_OrbA->GetPhase() == _OrbB->GetPhase())
		{
			// Calculate the distance between the two orbs
			float distance = (_OrbA->GetPosition() - _OrbB->GetPosition()).Magnitude();
			// Calculate the combined Radius of the two orbs
			float combinedRadius = _OrbA->GetRadius() + _OrbB->GetRadius();

			// Check if the orbs are colliding
			if (distance < combinedRadius)
			{
				
				// Move objects out of colliding with each other
				while (distance < combinedRadius)
				{
					// Calculate Peirce
					float peirce = combinedRadius - distance;

					// Calculate the direction of collision
					v3float Direction = (_OrbA->GetPosition() - _OrbB->GetPosition());
			
					_OrbA->SetPosition(_OrbA->GetPosition() + (Direction *  peirce));
					_OrbB->SetPosition(_OrbB->GetPosition() + (Direction *  -peirce));
					
					// Calculate the distance between the two orbs
					distance = (_OrbA->GetPosition() - _OrbB->GetPosition()).Magnitude();
					// Calculate the combined Radius of the two orbs
					combinedRadius = _OrbA->GetRadius() + _OrbB->GetRadius();
				}
				

				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void Game::HandleCollisions(Orb* _OrbA, Orb* _OrbB)
{
	v3float orbVelocity_A = _OrbA->GetVelocity();
	v3float orbVelocity_B = _OrbB->GetVelocity();

	float velocityMax = orbVelocity_A.Magnitude();

	if (velocityMax < orbVelocity_B.Magnitude())
	{
		_OrbA->SetVelocity((orbVelocity_B * _OrbB->GetBounce()));
		// TO DO JC: Take a small multiple of of the other orbs velocity 
		_OrbB->SetVelocity({0.0f,0.0f,0.0f});
	}
	else
	{
		_OrbA->SetVelocity({ 0.0f, 0.0f, 0.0f });
		// TO DO JC: Take a small multiple of of the other orbs velocity 
		_OrbB->SetVelocity((orbVelocity_A * _OrbA->GetBounce()));

	}

}

void Game::KillOrb(Orb* _Orb)
{
	if (_Orb->GetAlive())
	{
		_Orb->SetAlive(false);
		m_numAlivePlayers--;
	}
}

bool Game::Process(float _dt)
{
	
	HandleInput();

	// Game has Ended
	if (m_numAlivePlayers <= 1)
	{
		int Winner = 0;
		if (m_numAlivePlayers == 1)
		{
			// Game has Ended with a Winner 
			for (UINT i = 0; i < m_pOrbs.size(); i++)
			{
				if (m_pOrbs[i]->GetAlive())
				{
					Winner = i + 1;
					break;
				}
			}
		}

		if (Winner == 0)
		{
			// No Winner the Game is a Draw
		}
		else
		{
			// Player 'Winner' has won
		}
		// This Player has won
		// TO DO JUR: Print Winner and Press A to Continue

		for (UINT i = 0; i < m_pContollers.size(); i++)
		{
			m_pContollers[i]->PreProcess();
			if (m_pContollers[i]->GetButtonPressed(m_XButtons.ActionButton_A))
			{
				// Return the game end
				return false;
			}
			m_pContollers[i]->PostProcess();
		}
		
	}
	else
	{

		m_pShader_LitTex->SetUpPerFrame();
		m_pArenaFloor->Process(_dt);

		for (UINT i = 0; i < m_pOrbs.size(); i++)
		{
			if (m_pOrbs[i]->GetAlive())
			{
				// Get and set the surface friction

				// Check Collisions
				for (UINT j = 0; j < m_pOrbs.size(); j++)
				{
					if ((i != j))
					{
						if (m_pOrbs[j]->GetAlive())
						{
							if (IsOrbsColliding(m_pOrbs[i], m_pOrbs[j]))
							{
								HandleCollisions(m_pOrbs[i], m_pOrbs[j]);
							}
						}
					}
				}

				v3float OrbPos = m_pOrbs[i]->GetPosition();
				v3float tilePos;
				OrbPos += m_tileScale / 2;
				int row = (int)((OrbPos.x / m_tileScale.x) + ((m_areaSize - 1) / 2));
				int col = (int)((OrbPos.y / m_tileScale.y) + ((m_areaSize - 1) / 2));

				if (row < 0)
				{
					row = 0;
					KillOrb(m_pOrbs[i]);
				}
				else if (row > (int)m_pArenaTiles->size() - 1)
				{
					row = m_pArenaTiles->size() - 1;
					KillOrb(m_pOrbs[i]);
				}
				if (col < 0)
				{
					col = 0;
					KillOrb(m_pOrbs[i]);
				}
				else if (col > (int)m_pArenaTiles->size() - 1)
				{
					col = m_pArenaTiles->size() - 1;
					KillOrb(m_pOrbs[i]);
				}

				switch ((*(*m_pArenaTiles)[row])[col]->GetBaseImageEnum())
				{
				case BTI_SLIPPERY:
				{
					//m_pOrbs[i]->SetSurfaceFriction(0.0f);
					m_pOrbs[i]->SetSurfaceFriction(0.05f / _dt);
				}
					break;
				case BTI_ROUGH:
				{
					//m_pOrbs[i]->SetSurfaceFriction(0.5f / _dt);
					m_pOrbs[i]->SetSurfaceFriction(0.05f / _dt);
				}
					break;
				case BTI_STANDARD:
				{
					m_pOrbs[i]->SetSurfaceFriction(0.05f / _dt);
				}
				default: break;
				}

					// Kill Orb if its on a Dead Tile
				if ((*(*m_pArenaTiles)[row])[col]->GetActive() == false)
				{
					KillOrb(m_pOrbs[i]);
				}

				m_pOrbs[i]->Process(_dt);
			}
		}
	}

	return true;
}

void Game::Render()
{
	m_pArenaFloor->Render();

	// Draw all un phased Orbs
	for (UINT i = 0; i < m_pOrbs.size(); i++)
	{
		if (m_pOrbs[i]->GetAlive())
		{
			if (m_pOrbs[i]->GetPhase() == false)
			{
				m_pOrbs[i]->Render();
			}
		}
	}

	// Draw all phased Orbs
	for (UINT i = 0; i < m_pOrbs.size(); i++)
	{
		if (m_pOrbs[i]->GetAlive())
		{
			if (m_pOrbs[i]->GetPhase() == true)
			{
				m_pOrbs[i]->Render();
			}
		}
	}
}

void Game::HandleInput()
{
	// Handle the Controller Inputs
	for (UINT i = 0; i < m_pContollers.size(); i++)
	{
		if (m_pOrbs[i]->GetAlive())
		{
			if (m_pContollers[i]->Connected())
			{
				m_pContollers[i]->PreProcess();

				// Movement
				v2float LeftAxis;
				if (!m_pContollers[i]->LStick_InDeadZone())
				{
					LeftAxis = m_pContollers[i]->GetLStickAxis();
					m_pOrbs[i]->SetAcceleration({ LeftAxis.x, LeftAxis.y, 0.0f });
				}

				// Boost
				m_pOrbs[i]->Boost(m_pContollers[i]->GetButtonPressed(m_XButtons.Bumper_R));
				
				m_pOrbs[i]->Phase(m_pContollers[i]->GetButtonPressed(m_XButtons.Bumper_L));

				m_pContollers[i]->PostProcess();
			}
		}
		else
		{
			// 
		}
		
	}
}
