/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Physics_Body_2D.h
* Description : A body that holds all physics information for a 2D object
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Inclusion Guards
#pragma once
#ifndef __PHYSICS_BODY_2D_H__
#define __PHYSICS_BODY_2D_H__

// Library Includes
#include <Box2D.h>

// Local Includes
#include "Physics_Utilities.h"

class Physics_Body_2D
{
public:

	/***********************
	* Physics_Body_2D: Constructor for Physics Body 2D for a circle object
	* @author: Callan Moore
	* @parameter: _pPhysWorld: The physics world that holds this body
	* @parameter: _pBody: The Box2D physics body to govern this objects physics interactions
	* @parameter: _radius: Radius of the circle
	* @parameter: _metersPerPixel: The conversion rate of meters to screen space
	********************/
	Physics_Body_2D(b2World* _pPhysWorld, b2Body* _pBody, float _radius, float _metersPerPixel);

	/***********************
	* Physics_Body_2D: Constructor for Physics Body 2D for a polygon object
	* @author: Callan Moore
	* @parameter: _pPhysWorld: The physics world that holds this body
	* @parameter: _pBody: The Box2D physics body to govern this objects physics interactions
	* @parameter: _pPoints: The points for the body to be created from
	* @parameter: _size: Size of the array of points
	* @parameter: _metersPerPixel: The conversion rate of meters to screen space
	********************/
	Physics_Body_2D(b2World* _pPhysWorld, b2Body* _pBody, TPhysicsProperties _physProps, float _metersPerPixel);

	/***********************
	* ~Physics_Body_2D: Default Destructor for Physics Body 2D class
	* @author: Callan Moore
	********************/
	~Physics_Body_2D();

	/***********************
	* GetBody: Retrieve the Box2D body of this object
	* @author: Callan Moore
	* @return: b2Body*: The Box2d Body of the physics object
	********************/
	b2Body* GetBody() { return m_pBody; };
	
	/***********************
	* GetCollisionProperties: Retrieve the Collision properties of the body
	* @author: Callan Moore
	* @return: TCollsionProperties*: The collison properties of the body
	********************/
	TCollisionProperties* GetCollisionProperties() { return &m_collisionProps; };
	
	/***********************
	* GetRadius: Retrieve the radius for a circle body
	* @author: Callan Moore
	* @return: float: The radius of the circle
	********************/
	float GetRadius() { return m_radius * m_metersPerPixel; };

	/***********************
	* GetPoints: Retrieve the array of points that make up the body
	* @author: Callan Moore
	* @return: v2float*: The array of points
	********************/
	v2float* GetPoints() { return m_pPoints; };

	/***********************
	* GetSize: Retrieve the size of the body array of points
	* @author: Callan Moore
	* @return: UINT: Amount of points for the body
	********************/
	UINT GetSize() { return m_size; };
	
	/***********************
	* GetPosition: Retrieve the position of the Body
	* @author: Callan Moore
	* @return: v2float: The position as a float vector 2D
	********************/
	v2float GetPosition();

	/***********************
	* GetAngle: Retrieve the rotation angle of the Body
	* @author: Callan Moore
	* @return: float: Rotation angle of the Body
	********************/
	float GetAngle() { return m_pBody->GetAngle(); };

	/***********************
	* GetPhysicsProperties: Retrieve the physics properties struct of the body
	* @author: Callan Moore
	* @return: TPhysicsProperties: The physics properties structure of the body
	********************/
	TPhysicsProperties GetPhysicsProperties() { return m_physProps; };
	
	/***********************
	* SetCollisionProperties: Set a new Collision properties structure for the Body
	* @author: Callan Moore
	* @parameter: _collisionProps: The new collision properties structure
	* @return: void
	********************/
	void SetCollisionProperties(TCollisionProperties _collisionProps) { m_collisionProps = _collisionProps; };

private:
	b2World* m_pPhysWorld;
	b2Body* m_pBody;
	TCollisionProperties m_collisionProps;
	float m_metersPerPixel;
	TPhysicsProperties m_physProps;

	// Circle Properties
	float m_radius;

	// Polygon Properties
	v2float* m_pPoints;
	UINT m_size;	
};
#endif	// __PHYSICS_BODY_2D_H__
