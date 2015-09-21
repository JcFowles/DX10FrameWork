/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Physics_Pulley_2D.h
* Description : Physics representation of a pulley system
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __PHYSICS_PULLEY_H__
#define __PHYSICS_PULLEY_H__

// Library Includes
#include <Box2D.h>

// Local Includes
#include "Physics_Utilities.h"

class Physics_Pulley_2D
{
public:
	/***********************
	* Physics_Pulley_2D: Constructor for the Physics Pulley class
	* @author: Callan Moore
	* @parameter: _pPhysWorld: The physics world that this object belongs to
	* @parameter: _pJoint: The joint that represents the Pulley System
	* @parameter: _metersPerPixel: The conversion rate of meters to screen space
	********************/
	Physics_Pulley_2D(b2World* _pPhysWorld, b2PulleyJoint* _pJoint, float _metersPerPixel);

	/***********************
	* Physics_Pulley_2D: Default Destructor for the Physics Pulley class
	* @author: Callan Moore
	********************/
	~Physics_Pulley_2D();

	/***********************
	* GetAnchorA: Retrieve the anchor point for the first body of the pulley
	* @author: Callan Moore
	* @return: v2float: The anchor point for physics body A
	********************/
	v2float GetAnchorA();
	
	/***********************
	* GetAnchorB: Retrieve the anchor point for the second body of the pulley
	* @author: Callan Moore
	* @return: v2float: The anchor point for physics body B
	********************/
	v2float GetAnchorB();
	
	/***********************
	* GetGroundAnchorA: Retrieve the ground anchor for the first body of the pulley
	* @author: Callan Moore
	* @return: v2float: The ground anchor for physics body A
	********************/
	v2float GetGroundAnchorA();
	
	/***********************
	* GetGroundAnchorB: Retrieve the ground anchor for the second body of the pulley
	* @author: Callan Moore
	* @return: v2float: The ground anchor for physics body B
	********************/
	v2float GetGroundAnchorB();

private:
	b2World* m_physWorld;
	b2PulleyJoint* m_pPulleyJoint;
	float m_metersPerPixel;
};
#endif	// __PHYSICS_PULLEY_H__

