/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Physics_Body_2D.cpp
* Description : A body that holds all physics information for a 2D object
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "Physics_Body_2D.h"

Physics_Body_2D::Physics_Body_2D(b2World* _pPhysWorld, b2Body* _pBody, float _radius, float _metersPerPixel)
{
	// Assign member variables
	m_pPhysWorld = _pPhysWorld;
	m_pBody = _pBody;
	m_radius = _radius;
	m_metersPerPixel = _metersPerPixel;
	m_pPoints = 0;

	// Zero the memory of the struct so that there is no rogue data
	ZeroMemory(&m_collisionProps, sizeof(m_collisionProps));
}

Physics_Body_2D::Physics_Body_2D(b2World* _pPhysWorld, b2Body* _pBody, TPhysicsProperties _physProps, float _metersPerPixel)
{
	// Assign member variables
	m_pPhysWorld = _pPhysWorld;
	m_pBody = _pBody;
	m_pPoints = _physProps.pPoints;
	m_size = _physProps.size;
	m_metersPerPixel = _metersPerPixel;
	m_physProps = _physProps;

	// Zero the memory of the struct so that there is no rogue data
	ZeroMemory(&m_collisionProps, sizeof(m_collisionProps));
}

Physics_Body_2D::~Physics_Body_2D()
{
	m_pPhysWorld->DestroyBody(GetBody());
	ReleasePtrArray(m_pPoints);
}

v2float Physics_Body_2D::GetPosition()
{
	// Converts the position from the physics world into screen space and a v2float
	b2Vec2 bodyPos = m_pBody->GetPosition();
	v2float pos;
	pos.x = bodyPos.x * m_metersPerPixel;
	pos.y = bodyPos.y * m_metersPerPixel;

	return pos;
}