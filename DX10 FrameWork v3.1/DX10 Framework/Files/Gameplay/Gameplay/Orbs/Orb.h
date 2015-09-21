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
#pragma once

#ifndef __ORB_H__
#define __ORB_H__

// Library Include

// Local Includes
#include "../../../DX10/DX10/3D Objects/DX10_Obj_Generic.h"
#include "../../../DX10/DX10/3D Objects/DX10_Obj_LitTex.h"

class Orb :
	public DX10_Obj_LitTex
{
	// Member Functions
public:

	/***********************
	* Orb: Default Constructor for the Player Controlled Orbs
	* @author: Jc Fowles
	* @return:
	********************/
	Orb();

	/***********************
	* Orb: Default Destructor for the Player Controlled Orbs
	* @author: Jc Fowles
	* @return:
	********************/
	~Orb();

	/***********************
	* Initialise: Initialise the Player Controlled Orbs
	* @author: Jc Fowles
	* @parameter: _pRenderer: Renderer for the Orb
	* @parameter: _pMesh: Mesh for the Orb
	* @parameter: _pShader: The Shader for the Orb
	* @parameter: _texName: file name of the single texture for the Orb to display
	* @parameter: _density: The Density of the Orb to calculate its mass
	* @parameter: _speed: The speed at which the Orb accelerates 
	* @parameter: _maxSpeed: The max speed the Orb is allowed to travel at
	* @return: bool : Successful initialization
	********************/
	bool Initialise(DX10_Renderer* _pRenderer, DX10_Mesh* _pMesh, DX10_Shader_LitTex* _pShader, std::string _texName, float _density, float _Speed, float _maxSpeed);


	// TO DO JC:
	void Process(float _dt);
	void Render();

   	void SetSurfaceFriction(float _surfaceFriction){ m_surfaceFriction = _surfaceFriction; };
	void SetAcceleration(v3float _acceleration){ m_acceleration = _acceleration; };
	
	void SetAlive(bool _alive){ m_isAlive = _alive; };
	bool GetAlive(){ return m_isAlive; };

	float GetRadius(){ return m_radius; };
	// TO DO JC: Set radius

	v3float GetVelocity(){ return m_velocity; };
	void SetVelocity(v3float _velocity){ m_velocity = _velocity; };

	float GetBounce(){ return m_bounce; };
	void SetBounce(float _bounce){ m_bounce = _bounce; };

	void Boost(bool _boost);
	void Phase(bool _phase);

	bool GetPhase(){ return m_phase; };

protected:
private:
	// Member Variables
public:
protected:
private:

	v3float m_acceleration;
	v3float m_velocity;
	float m_surfaceFriction;
	float m_speed;
	float m_maxSpeed;
	// TO DO JC: Currently unused
	float m_bounce;
	float m_radius;
	bool m_isAlive;

	bool m_boost;
	bool m_AllowBoost;
	float m_boostAmount;
	float m_boostCooldown;
	float m_boostLimit;
	float m_boostActiveTime;
	float m_boostCoolDownTime;

	bool m_phase;
	bool m_AllowPhase;
	float m_phaseCooldown;
	float m_phaseMaxTime;
	float m_phaseActiveTime;
	float m_phaseCoolDownTime;


	
};

#endif;		// __ORB_H__
