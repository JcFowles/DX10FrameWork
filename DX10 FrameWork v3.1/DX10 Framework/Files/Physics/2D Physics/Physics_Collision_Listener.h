/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Physics_Collision_Listener.h
* Description : Contact listener that detects all collisions within the world
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __PHYSICS_COLLISION_LISTENER_H__
#define __PHYSICS_COLLISION_LISTENER_H__

// Library Includes
#include <Box2D.h>

// Local Includes
#include "Physics_Utilities.h"
#include "Physics_Body_2D.h"

class Physics_Collision_Listener :
	public b2ContactListener
{
public:
	/***********************
	* Physics_Collision_Listener: Default Constructor for Break Listener class
	* @author: Callan Moore
	********************/
	Physics_Collision_Listener();

	/***********************
	* ~Physics_Collision_Listener: Default Destructor for Break Listener class
	* @author: Callan Moore
	********************/
	~Physics_Collision_Listener();
	
	/***********************
	* BeginContact: Called when a collision is first detected
	* @author: Callan Moore
	* @parameter: _contact: Contact information for the collision
	* @return: void
	********************/
	void BeginContact(b2Contact* _contact);
	
	/***********************
	* EndContact: Called when a collision is finished
	* @author: Callan Moore
	* @parameter: _contact: Contact information for the collision
	* @return: void
	********************/
	void EndContact(b2Contact* _contact);
	
	/***********************
	* PreSolve: Called before adding small impulses to try and resolve the overlapping colliding objects 
	* @author: Callan Moore
	* @parameter: _contact: Contact information for the collision
	* @parameter: _oldManifold: collision point of the objects
	* @return: void
	********************/
	void PreSolve(b2Contact* _contact, const b2Manifold* _oldManifold);
	
	/***********************
	* PostSolve: Called after adding small impulses to try and resolve the overlapping colliding objects 
	* @author: Callan Moore
	* @parameter: _contact: Contact information for the collision
	* @parameter: _impulse: Impulse added to each object
	* @return: void
	********************/
	void PostSolve(b2Contact* _contact, const b2ContactImpulse* _impulse);

protected:
	
	/***********************
	* ResolveBreak: Resolve a collision that results in a broken object
	* @author: Callan Moore
	* @parameter: _contact: The details about the collision
	* @return: void
	********************/
	void ResolveBreak(b2Contact* _contact);

};

#endif	// __PHYSICS_COLLISION_LISTENER_H__

