/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Physics_Pulley_2D.cpp
* Description : Physics representation of a pulley system
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "Physics_Pulley_2D.h"

Physics_Pulley_2D::Physics_Pulley_2D(b2World* _physWorld, b2PulleyJoint* _pJoint, float _metersPerPixel)
{
	// Assign member variables
	m_physWorld = _physWorld;
	m_pPulleyJoint = _pJoint;
	m_metersPerPixel = _metersPerPixel;
}

Physics_Pulley_2D::~Physics_Pulley_2D()
{
	m_physWorld->DestroyJoint(m_pPulleyJoint);
	m_pPulleyJoint = 0;
}

v2float Physics_Pulley_2D::GetAnchorA()
{
	b2Vec2 b2Anchor = m_pPulleyJoint->GetAnchorA();
	return{ b2Anchor.x * m_metersPerPixel, b2Anchor.y * m_metersPerPixel };
}

v2float Physics_Pulley_2D::GetAnchorB()
{
	b2Vec2 b2Anchor = m_pPulleyJoint->GetAnchorB();
	return{ b2Anchor.x * m_metersPerPixel, b2Anchor.y * m_metersPerPixel };
}

v2float Physics_Pulley_2D::GetGroundAnchorA()
{
	b2Vec2 b2GroundAnchor = m_pPulleyJoint->GetGroundAnchorA();
	return{ b2GroundAnchor.x * m_metersPerPixel, b2GroundAnchor.y * m_metersPerPixel };
}

v2float Physics_Pulley_2D::GetGroundAnchorB()
{
	b2Vec2 b2GroundAnchor = m_pPulleyJoint->GetGroundAnchorB();
	return{ b2GroundAnchor.x * m_metersPerPixel, b2GroundAnchor.y * m_metersPerPixel };
}

