/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Physics_Break_Listener.h
* Description : Contact listener that detects objects that need to break
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __PHYSICS_UTILITIES_H__
#define __PHYSICS_UTILITIES_H__

// Library Includes
#if defined(DEBUG) | defined(_DEBUG)
	#pragma comment(lib, "Box2D-Debug.lib")
#else
	#pragma comment(lib, "Box2D-Release.lib")
#endif

#include <Box2D.h>

// Local Includes
#include "../../Utility/Utilities.h"

/***********************
* TPhysicsProperties: Properties struct for creating a physics body
* @author: Callan Moore
********************/
struct TPhysicsProperties
{
	bool circleObject;
	float radius;
	float damping;

	v2float* pPoints;
	UINT size;

	v2float	pos;
	float density;
	float friction;
	float restitution;
	float angle;
	UINT16 collisionType;
	UINT16 collideWith;
	bool isStatic;
	v2float linearVelocity;
};

/***********************
* TCollisionProperties: Properties struct for an object that needs to break
* @author: Callan Moore
********************/
struct TCollisionProperties
{
	// Object is Breaking
	bool isBreaking;
	v2float* pCollisionWorldPoints;
	v2float impactVelocity;	
	v2float linearVelocity;

	// Win/Loss conditions
	bool isLevelLost;
	bool isLevelWon;
};

/***********************
* eCollisionType: enum for collision types
* @author: Callan Moore
********************/
enum eCollisionType
{
	CT_BACKGROUND	= 1,
	CT_STANDARD		= 2,
	CT_GEM			= 4,
	CT_WINZONE		= 8,
	CT_ENEMY		= 16,
	CT_BREAKABLE	= 32,
	CT_BREAKABLE_ENEMY = 64
};

#endif	// __PHYSICS_UTILITIES_H__