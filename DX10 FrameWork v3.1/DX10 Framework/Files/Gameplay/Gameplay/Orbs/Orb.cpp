//
// Bachelor of Software Engineering
// Media Design School 
// Auckland
// New Zealand 
// 
// (c) 2005 - 2015 Media Design School 
// 
// File Name : Orb.h
// Description : Class to handle all funtionality of the Player Controlled Orbs
// Author : Jc Fowles 
// Mail : Jc.Fowles@mediadesign.school.nz 
//

// This Include
#include "Orb.h"
 
Orb::Orb()
{
	m_acceleration = {0.0f,0.0f,0.0f};
	m_velocity = { 0.0f, 0.0f, 0.0f };
	m_bounce = 0.0f;
	m_maxSpeed = 0.0f;
	m_isAlive = true;
}

Orb::~Orb()
{
	
}

bool Orb::Initialise(DX10_Renderer* _pRenderer, DX10_Mesh* _pMesh, DX10_Shader_LitTex* _pShader, std::string _texName, float _density, float _speed, float _maxSpeed)
{	
 	// Initialise the object this is derived from
	VALIDATE(DX10_Obj_LitTex::Initialise(_pRenderer, _pMesh, _pShader, _texName));

	// Check the passed in parameters
	if ((_density < 0.0f) || (_maxSpeed < 0.0f))
	{
		return false;
	}

	// Store the initial state of the variables
	m_bounce = _density;
	m_radius = _pMesh->GetScale().x / 2;
	m_speed = _speed;
	m_maxSpeed = _maxSpeed;
	m_isAlive = true;

	// TO DO JC
	m_boostAmount = 5.0f;
	m_boostCooldown = 5.0f;
	m_boostLimit = 1.0f;
	m_boostActiveTime = 0.0f;
	m_boostCoolDownTime = 0.0f;
	m_AllowBoost = true;
	m_boost = false;
	   
	m_phaseCooldown = 2.0f;
	m_phaseMaxTime = 5.0f;
	m_phaseActiveTime = 0.0f;
	m_phaseCoolDownTime = 0.0f;
	m_AllowPhase = true;
	m_phase = false;

	// Successful Initialization
	return true;
}
  
void Orb::Process(float _dt)
{
	
	m_velocity += ((m_acceleration* _dt)* m_speed);
	m_acceleration *= 0.0f;
	m_velocity = m_velocity - (m_velocity * m_surfaceFriction* _dt);
	m_velocity.Limit(m_maxSpeed);
		

	if (m_boost)
	{
		m_boostActiveTime += _dt;

		if (m_boostActiveTime < m_boostLimit)
		{
			m_pos += m_velocity * m_boostAmount;
		}
		else
		{
			m_boostActiveTime = 0.0f;
			m_boost = false;
			m_pos += m_velocity;
			m_AllowBoost = false;
		}
	}
	else
	{
		if (m_AllowBoost == false)
		{
			m_boostCoolDownTime += _dt;

			if (m_boostCoolDownTime > m_boostCooldown)
			{
				m_boostCoolDownTime = 0.0f;
				m_AllowBoost = true;
			}
		}

		m_pos += m_velocity;
	}

	if (m_phase)
	{
		m_phaseActiveTime += _dt;

		if (m_phaseActiveTime < m_phaseMaxTime)
		{			
			
		}
		else
		{
			m_phaseActiveTime = 0.0f;
			m_phase = false;
			m_AllowPhase = false;
		}
	}
	else
	{
		if (m_AllowPhase == false)
		{
			m_phaseCoolDownTime += _dt;

			if (m_phaseCoolDownTime > m_phaseCooldown)
			{
				m_phaseCoolDownTime = 0.0f;
				m_AllowPhase = true;
			}
		}
	}


	// Yaw 
	// Pitch
	//SetRotPerSecondPitch(m_pos.y);
	//SetRotPerSecondYaw(-m_pos.x);

	DX10_Obj_LitTex::Process(_dt);
}

void Orb::Render()
{
	TLitTex _litTex;
	_litTex.pMesh = m_pMesh;
	_litTex.pMatWorld = &m_matWorld;
	_litTex.pTexBase = (*m_pTextures)[m_texIndex];
	
	if (m_phase)
	{
		_litTex.reduceAlpha = 0.5f;
	}
	else
	{
		_litTex.reduceAlpha = 0.0f;
	}

	m_pShader->Render(_litTex, TECH_LITTEX_FADE);
	
}

void Orb::Boost(bool _boost)
{
	if (_boost == true)
	{
		if (m_AllowBoost == true)
		{
			// Boost
			m_boost = true;
		}
	}
	else
	{
		// Stop boosting and start recharge
		m_boost = false;
	}
}

void Orb::Phase(bool _phase)
{
	if (_phase == true)
	{
		if (m_AllowPhase == true)
		{
			// Boost
			m_phase = true;
		}
	}
	else
	{
		// Stop boosting and start recharge
		m_phase = false;
		
		if (m_phaseActiveTime > 0.0f)
		{
			m_AllowPhase = false;
		}
		m_phaseActiveTime = 0.0f;
	}
}
