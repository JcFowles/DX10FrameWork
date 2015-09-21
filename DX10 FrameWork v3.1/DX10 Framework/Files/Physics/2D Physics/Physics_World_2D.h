/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Physics_World_2D.h
* Description : Simulates all 2D physics for the application
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __PHYSICS_WORLD_2D_H__
#define __PHYSICS_WORLD_2D_H__

// Local Includes
#include "Physics_Utilities.h"
#include "Physics_Body_2D.h"
#include "Physics_Rope_2D.h"
#include "Physics_Pulley_2D.h"
#include "Physics_Collision_Listener.h"

class Physics_World_2D
{
public:

	/***********************
	* C2D_Physics: Default Constructor for 2D Physics class
	* @author: Callan Moore
	********************/
	Physics_World_2D();

	/***********************
	* ~C2D_Physics: Default Destructor for 2D Physics class
	* @author: Callan Moore
	********************/
	~Physics_World_2D();

	/***********************
	* Initialise: Initialise the Physics 2D simulator
	* @author: Callan Moore
	* @parameter: _metersPerPixel: The conversion rate of meters to screen space
	* @return: bool: Successful or not
	********************/
	bool Initialise(float _metersPerPixel);

	/***********************
	* Process: Process the Physics world and step the bodies forward by the timestep
	* @author: Callan Moore
	* @return: void
	********************/
	void Process();

	/***********************
	* CreatePhysicsObject: Create a Physics body for a 2D Object. 
	* @author: Callan Moore
	* @parameter: _props: Properties for the Physics object
	* @return: Physics_Body_2D*: Physics Body for a 2D object
	********************/
	Physics_Body_2D* CreatePhysicsObject(TPhysicsProperties _props);

	/***********************
	* CreatePhysicsPolygon: Create a Physics body for a 2D Polygon
	* @author: Callan Moore
	* @parameter: _props: Properties for the Physics object
	* @return: Physics_Body_2D*: Physics Body for a 2D object
	********************/
	Physics_Body_2D* CreatePhysicsPolygon(TPhysicsProperties _props);

	/***********************
	* CreatePhysicsCircle: Create a Physics body for a 2D Circle
	* @author: Callan Moore
	* @parameter: _props: Properties for the Physics object
	* @return: Physics_Body_2D*: Physics Body for a 2D object
	********************/
	Physics_Body_2D* CreatePhysicsCircle(TPhysicsProperties _props);
	
	/***********************
	* CreateResoluteJoint: Creates a Resolute Joint between two physics objects
	* @author: Callan Moore
	* @parameter: _bodyA: First Physics Body
	* @parameter: _bodyB: Second Physics Body
	* @parameter: _jointPos: Position of the Joint in world space
	* @parameter: _collide: Can the two connect bodies collide with each other
	* @return: void
	********************/
	void CreateRevoluteJoint(Physics_Body_2D* _bodyA, Physics_Body_2D* _bodyB, v2float _jointPos, bool _collide);

	/***********************
	* CreateRope: Create a rope between two Bodies at the given anchor points (relative to the bodies center)
	* @author: Callan Moore
	* @parameter: Physics_Body_2D * _bodyA: First Body to rope
	* @parameter: Physics_Body_2D * _bodyB: Second body to rope
	* @parameter: v2float _relativeAnchorA: Anchor point on the first body
	* @parameter: v2float _relativeAnchorB: Anchor point on the second body
	* @parameter: _collide: Can the two connect bodies collide with each other
	* @return: Physics_Rope_2D*: Reference to the created Rope
	********************/
	Physics_Rope_2D* CreateRope(Physics_Body_2D* _bodyA, Physics_Body_2D* _bodyB, v2float _relativeAnchorA, v2float _relativeAnchorB, bool _collide);
	
	/***********************
	* CreatePulley: Create a Pulley system in the physics world
	* @author: Callan Moore
	* @parameter: _bodyA: First Body to attach to pulley system
	* @parameter: _bodyB: Second Body to attach to pulley system
	* @parameter: _relativeAnchorA: Relative anchor point on the first body
	* @parameter: _relativeAnchorB: Relative anchor point on the second body
	* @parameter: _worldAnchorA: Anchor in world space to attach the first body to
	* @parameter: _worldAnchorB: Anchor in world space to attach the second body to
	* @return: Physics_Pulley_2D*: Reference to the created Pulley System
	********************/
	Physics_Pulley_2D* CreatePulley(Physics_Body_2D* _bodyA, Physics_Body_2D* _bodyB, v2float _relativeAnchorA, v2float _relativeAnchorB, v2float _worldAnchorA, v2float _worldAnchorB);
	
	/***********************
	* CreateSpring: Create a spring physics Joint
	* @author: Callan Moore
	* @parameter: _bodyA: Static object to attach the spring to
	* @parameter: _bodyB: Dynamic object that will act as the spring pad for the spring
	* @parameter: _relativeAnchorA: Relative anchor point of the static object
	* @parameter: _relativeAnchorB: relative anchor point of the dynamic object
	* @parameter: _freq: Frequency of the spring in hz
	* @parameter: _damping: Damping of the spring to determine oscillation amount
	* @parameter: _extraDist: Extra Distance to create a compressed spring
	* @return: void
	********************/
	void CreateSpring(Physics_Body_2D* _bodyA, Physics_Body_2D* _bodyB, v2float _relativeAnchorA, v2float _relativeAnchorB, float _freq, float _damping, float _extraDist = 0.0f);
	
	/***********************
	* BreakObject: Break an object into smaller pieces of the original object
	* @author: Callan Moore
	* @parameter: _body: The original object to break up
	* @return: std::vector<Physics_Body_2D*>*: List of new created objects
	********************/
	std::vector<Physics_Body_2D*>* BreakObject(Physics_Body_2D* _body);

private:

	// World Variables
	b2World* m_pWorld;
	b2ContactListener* m_pBreakListener;
	bool m_allowSleep;
	float m_timeStep;
	int m_velocityIterations;
	int m_posIterations;

	// Conversion to 2D screen space
	float m_metersPerPixel;
};

#endif	// __PHYSICS_WORLD_2D_H__



