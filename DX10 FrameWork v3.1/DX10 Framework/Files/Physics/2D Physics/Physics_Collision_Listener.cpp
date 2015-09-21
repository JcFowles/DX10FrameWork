/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Physics_Break_Listener.cpp
* Description : Contact listener that detects all collisions within the world
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "Physics_Collision_Listener.h"

Physics_Collision_Listener::Physics_Collision_Listener()
{
}

Physics_Collision_Listener::~Physics_Collision_Listener()
{
}

void Physics_Collision_Listener::BeginContact(b2Contact* _contact)
{
	// Check if at least one of the colliding objects is breakable
	if (_contact->GetFixtureA()->GetFilterData().categoryBits == CT_BREAKABLE || _contact->GetFixtureA()->GetFilterData().categoryBits == CT_BREAKABLE_ENEMY
		|| _contact->GetFixtureB()->GetFilterData().categoryBits == CT_BREAKABLE || _contact->GetFixtureB()->GetFilterData().categoryBits == CT_BREAKABLE_ENEMY)
	{
		// Resolve the breaking of the breakable object
		ResolveBreak(_contact);
	}
	else if (_contact->GetFixtureA()->GetFilterData().categoryBits == CT_GEM && _contact->GetFixtureB()->GetFilterData().categoryBits == CT_ENEMY)
	{
		// Gem contact enemy. Set loss condition of the gem to true
		Physics_Body_2D* pPhysicsBody = (Physics_Body_2D*)(_contact->GetFixtureA()->GetBody()->GetUserData());
		TCollisionProperties collisionProps = *pPhysicsBody->GetCollisionProperties();
		collisionProps.isLevelLost = true;
		pPhysicsBody->SetCollisionProperties(collisionProps);
	}
	else if (_contact->GetFixtureA()->GetFilterData().categoryBits == CT_ENEMY && _contact->GetFixtureB()->GetFilterData().categoryBits == CT_GEM)
	{
		// Gem contact enemy. Set loss condition of the gem to true
		Physics_Body_2D* pPhysicsBody = (Physics_Body_2D*)(_contact->GetFixtureB()->GetBody()->GetUserData());
		TCollisionProperties collisionProps = *pPhysicsBody->GetCollisionProperties();
		collisionProps.isLevelLost = true;
		pPhysicsBody->SetCollisionProperties(collisionProps);
	}
	else if (_contact->GetFixtureA()->GetFilterData().categoryBits == CT_GEM && _contact->GetFixtureB()->GetFilterData().categoryBits == CT_WINZONE)
	{
		// Gem contact Win Zone. Set win condition of the gem to true
		Physics_Body_2D* pPhysicsBody = (Physics_Body_2D*)(_contact->GetFixtureB()->GetBody()->GetUserData());
		TCollisionProperties collisionProps = *pPhysicsBody->GetCollisionProperties();
		collisionProps.isLevelWon = true;
		pPhysicsBody->SetCollisionProperties(collisionProps);
	}
	else if (_contact->GetFixtureA()->GetFilterData().categoryBits == CT_WINZONE && _contact->GetFixtureB()->GetFilterData().categoryBits == CT_GEM)
	{
		// Gem contact Win Zone. Set win condition of the gem to true
		Physics_Body_2D* pPhysicsBody = (Physics_Body_2D*)(_contact->GetFixtureB()->GetBody()->GetUserData());
		TCollisionProperties collisionProps = *pPhysicsBody->GetCollisionProperties();
		collisionProps.isLevelWon = true;
		pPhysicsBody->SetCollisionProperties(collisionProps);
	}
}

void Physics_Collision_Listener::EndContact(b2Contact* _contact)
{
}

void Physics_Collision_Listener::PreSolve(b2Contact* _contact, const b2Manifold* _oldManifold)
{
}

void Physics_Collision_Listener::PostSolve(b2Contact* _contact, const b2ContactImpulse* _impulse)
{
}

void Physics_Collision_Listener::ResolveBreak(b2Contact* _contact)
{
	int numPoints = _contact->GetManifold()->pointCount;

	// Get the collision points from the contact manifold
	b2WorldManifold worldmanifold;
	_contact->GetWorldManifold(&worldmanifold);
	b2Vec2* collisionPoint = worldmanifold.points;

	// Convert the collision points into v2floats
	v2float* pPoints = new v2float[numPoints];
	for (int i = 0; i < numPoints; i++)
	{
		pPoints[i] = { collisionPoint[i].x, collisionPoint[i].y };
	}

	// Get the velocity of each object in the collision
	b2Vec2 velocityA = _contact->GetFixtureA()->GetBody()->GetLinearVelocityFromWorldPoint(collisionPoint[0]);
	b2Vec2 velocityB = _contact->GetFixtureB()->GetBody()->GetLinearVelocityFromWorldPoint(collisionPoint[0]);

	Physics_Body_2D* pPhysicsBody = 0;
	v2float impactVelocity;
	b2Vec2 linearVelocity;
	float impactSpeed;

	// Set the break properties of the first object if its breakable
	if (_contact->GetFixtureA()->GetFilterData().categoryBits == CT_BREAKABLE)
	{
		// Calculate the impact velocity of the other object
		b2Vec2 b2ImpactVelocity = velocityA - velocityB;
		impactVelocity = { b2ImpactVelocity.x, b2ImpactVelocity.y };
		impactSpeed = impactVelocity.Magnitude();

		if (impactSpeed > 1.0f)
		{
			// Retrieve the physics body of the object that needs breaking
			pPhysicsBody = (Physics_Body_2D*)(_contact->GetFixtureA()->GetBody()->GetUserData());
			linearVelocity = _contact->GetFixtureA()->GetBody()->GetLinearVelocity();

			// Set the collision properties of the object to be broken
			TCollisionProperties collisionProps;
			collisionProps.isBreaking = true;
			collisionProps.pCollisionWorldPoints = pPoints;
			collisionProps.impactVelocity = impactVelocity;
			collisionProps.linearVelocity = { linearVelocity.x, linearVelocity.y };
			pPhysicsBody->SetCollisionProperties(collisionProps);
		}
		else
		{
			// Delete allocated memory that will not be stored
			ReleasePtr(pPoints);
		}
	}

	// Set the break properties of the second object if its breakable
	if (_contact->GetFixtureB()->GetFilterData().categoryBits == CT_BREAKABLE)
	{
		// Calculate the impact velocity of the other object
		b2Vec2 b2ImpactVelocity = velocityB - velocityA;
		impactVelocity = { b2ImpactVelocity.x, b2ImpactVelocity.y };
		impactSpeed = impactVelocity.Magnitude();

		if (impactSpeed > 1.0f)
		{
			// Retrieve the physics body of the object that needs breaking
			pPhysicsBody = (Physics_Body_2D*)(_contact->GetFixtureB()->GetBody()->GetUserData());
			linearVelocity = _contact->GetFixtureB()->GetBody()->GetLinearVelocity();

			// Set the collision properties of the object to be broken
			TCollisionProperties collisionProps;
			collisionProps.isBreaking = true;
			collisionProps.pCollisionWorldPoints = pPoints;
			collisionProps.impactVelocity = impactVelocity;
			collisionProps.linearVelocity = { linearVelocity.x, linearVelocity.y };
			pPhysicsBody->SetCollisionProperties(collisionProps);
		}
		else
		{
			// Delete allocated memory that will not be stored
			ReleasePtr(pPoints);
		}
	}
}
