/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Physics_World_2D.cpp
* Description : Simulates all 2D physics for the application
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// This Include
#include "Physics_World_2D.h"

Physics_World_2D::Physics_World_2D()
{
	// Nullify pointers
	m_pWorld = 0;
	m_pBreakListener = 0;
}

Physics_World_2D::~Physics_World_2D()
{
	ReleasePtr(m_pBreakListener);
	ReleasePtr(m_pWorld);
}

bool Physics_World_2D::Initialise(float _metersPerPixel)
{
	// Assign member variables
	m_metersPerPixel = _metersPerPixel;

	// Set the Gravity to earths and allow sleeping on objects given tot the world
	b2Vec2 gravity(0.0f, 9.81f);
	m_allowSleep = true;

	// Set the time step to link with an application running 60 FPS
	m_timeStep = 1.0f / 60.0f ;
	m_velocityIterations = 6;
	m_posIterations = 2;
	
	// Create a new World
	m_pWorld = new b2World(gravity);

	if (m_pWorld == 0)
	{
		// If the pointer is still 0 then the world failed to create
		return false;
	}
	m_pWorld->SetAllowSleeping(m_allowSleep);

	// Create a listener for tracking collisions with breakable objects
	m_pBreakListener = new Physics_Collision_Listener();
	m_pWorld->SetContactListener(m_pBreakListener);

	return true;
}

void Physics_World_2D::Process()
{
	m_pWorld->Step(m_timeStep, m_velocityIterations, m_posIterations);
}

Physics_Body_2D* Physics_World_2D::CreatePhysicsObject(TPhysicsProperties _props)
{
	// Check if the object to be created is a circle or not
	if (_props.circleObject == true)
	{
		return (CreatePhysicsCircle(_props));
	}
	else
	{
		return (CreatePhysicsPolygon(_props));
	}
}

Physics_Body_2D* Physics_World_2D::CreatePhysicsPolygon(TPhysicsProperties _props)
{
	b2Body* body;
	b2Vec2* pPts = new b2Vec2[_props.size];				// Create a new points list in Box2D vector system
	v2float convertPos = _props.pos / m_metersPerPixel;	// Convert the position of the object into physics world units

	// Convert all points into the b2Vec2s and convert the units into the physics world units
	for (UINT i = 0; i < _props.size; i++)
	{
		(pPts[i]) = { _props.pPoints[i].x / m_metersPerPixel, _props.pPoints[i].y / m_metersPerPixel };
	}

	b2FixtureDef fixtureDef;
	b2BodyDef bodyDef;
	b2PolygonShape shape;

	// Check if the object is to be static or unmoving
	if (_props.isStatic == true)
	{
		// Static Body
		bodyDef.type = b2_staticBody;
		fixtureDef.density = 0;
	}
	else
	{
		// Dynamic Body
		bodyDef.type = b2_dynamicBody;
		fixtureDef.density = _props.density;
	}
	// Set the body definition structure
	bodyDef.position.Set(convertPos.x, convertPos.y);
	bodyDef.angle = _props.angle;
	bodyDef.linearVelocity = { _props.linearVelocity.x, _props.linearVelocity.y };
	body = m_pWorld->CreateBody(&bodyDef);

	// Create a convex shape based on the points given
	shape.Set(pPts, _props.size);

	// Set the Fixture definition structure
	fixtureDef.shape = &shape;
	fixtureDef.friction = _props.friction;
	fixtureDef.restitution = _props.restitution;
	fixtureDef.filter.categoryBits = _props.collisionType;
	fixtureDef.filter.maskBits = _props.collideWith;
	body->CreateFixture(&fixtureDef);

	// Create a new Physics Body object to house the created physics body
	Physics_Body_2D* pPhysicsBody = new Physics_Body_2D(m_pWorld, body, _props, m_metersPerPixel);
	// Save a reference of the Physics body object for use in contact listeners
	body->SetUserData(pPhysicsBody);

	// Release temporary pointer
	ReleasePtr(pPts);
	return pPhysicsBody;
}

Physics_Body_2D* Physics_World_2D::CreatePhysicsCircle(TPhysicsProperties _props)
{
	b2Body* body;

	// Convert client space coordinates into physics world coordinates
	v2float convertPos = _props.pos / m_metersPerPixel;
	float convertRadius = _props.radius / m_metersPerPixel;

	b2BodyDef bodyDef;
	b2CircleShape shape;
	b2FixtureDef fixtureDef;

	// Check if the object is to be static or unmoving
	if (_props.isStatic == true)
	{
		// Static Body
		bodyDef.type = b2_staticBody;
		fixtureDef.density = 0;
	}
	else
	{
		// Dynamic Body
		bodyDef.type = b2_dynamicBody;
		fixtureDef.density = _props.density;
	}
	// Set the body definition structure
	bodyDef.position.Set(convertPos.x, convertPos.y);
	bodyDef.angle = _props.angle;
	bodyDef.angularDamping = _props.damping;
	body = m_pWorld->CreateBody(&bodyDef);

	// Create a circle shape
	shape.m_p.Set(0, 0);
	shape.m_radius = convertRadius;

	// Set the Fixture definition structure
	fixtureDef.shape = &shape;
	fixtureDef.friction = _props.friction;
	fixtureDef.filter.categoryBits = _props.collisionType;
	fixtureDef.filter.maskBits = _props.collideWith;
	fixtureDef.restitution = _props.restitution;
	body->CreateFixture(&fixtureDef);

	// Create a new Physics Body object to house the created physics body
	Physics_Body_2D* pPhysicsBody = new Physics_Body_2D(m_pWorld, body, convertRadius, m_metersPerPixel);
	// Save a reference of the Physics body object for use in contact listeners
	body->SetUserData(pPhysicsBody);
	return pPhysicsBody;
}

void Physics_World_2D::CreateRevoluteJoint(Physics_Body_2D* _bodyA, Physics_Body_2D* _bodyB, v2float _jointPos, bool _collide)
{
	// Convert the input position into a usable b2Vec2
	b2Vec2 b2jointPos = { _jointPos.x / m_metersPerPixel, _jointPos.y / m_metersPerPixel };

	// Initialise the Joint
	b2RevoluteJointDef jointDef;
	//jointDef.Initialize(_bodyA->GetBody(), _bodyB->GetBody(), b2jointPos);
	jointDef.collideConnected = _collide;
	jointDef.bodyA = _bodyA->GetBody();
	jointDef.bodyB = _bodyB->GetBody();
	jointDef.localAnchorA = _bodyA->GetBody()->GetLocalPoint(b2jointPos);
	jointDef.localAnchorB = _bodyB->GetBody()->GetLocalPoint(b2jointPos);

	// Create the Joint
	m_pWorld->CreateJoint(&jointDef);
}

Physics_Rope_2D* Physics_World_2D::CreateRope(Physics_Body_2D* _bodyA, Physics_Body_2D* _bodyB, v2float _relativeAnchorA, v2float _relativeAnchorB, bool _collide)
{
	b2RopeJointDef ropeJointDef;
	b2Vec2 pointA, pointB, maxRopeLength;

	// Whether the connected objects will collide with each other
	ropeJointDef.collideConnected = _collide;

	// Store the Bodies and anchors into the Rope Joint Definition
	ropeJointDef.bodyA = _bodyA->GetBody();
	ropeJointDef.bodyB = _bodyB->GetBody();
	ropeJointDef.localAnchorA.Set(_relativeAnchorA.x / m_metersPerPixel, _relativeAnchorA.y / m_metersPerPixel);
	ropeJointDef.localAnchorB.Set(_relativeAnchorB.x / m_metersPerPixel, _relativeAnchorB.y / m_metersPerPixel);
	pointA = ropeJointDef.bodyA->GetWorldPoint(ropeJointDef.localAnchorA);
	pointB = ropeJointDef.bodyB->GetWorldPoint(ropeJointDef.localAnchorB);
	maxRopeLength = (pointB - pointA);
	ropeJointDef.maxLength = maxRopeLength.Length();
	b2Joint* pJoint = m_pWorld->CreateJoint(&ropeJointDef);

	// Save the Created joint
	Physics_Rope_2D* pPhysicsJoint = new Physics_Rope_2D(m_pWorld, pJoint, m_metersPerPixel);
	return pPhysicsJoint;
}

Physics_Pulley_2D* Physics_World_2D::CreatePulley(Physics_Body_2D* _bodyA, Physics_Body_2D* _bodyB, v2float _relativeAnchorA, v2float _relativeAnchorB, v2float _worldAnchorA, v2float _worldAnchorB)
{
	// Convert the local and ground anchors into Box2D vector and physics world units
	b2Vec2 localAnchorA = { _bodyA->GetBody()->GetPosition().x + _relativeAnchorA.x / m_metersPerPixel, _bodyA->GetBody()->GetPosition().y + _relativeAnchorA.y / m_metersPerPixel };
	b2Vec2 localAnchorB = { _bodyB->GetBody()->GetPosition().x + _relativeAnchorB.x / m_metersPerPixel, _bodyB->GetBody()->GetPosition().y + _relativeAnchorB.y / m_metersPerPixel };
	b2Vec2 groundAnchorA = b2Vec2(_worldAnchorA.x / m_metersPerPixel, _worldAnchorA.y / m_metersPerPixel);
	b2Vec2 groundAnchorB = b2Vec2(_worldAnchorB.x / m_metersPerPixel, _worldAnchorB.y / m_metersPerPixel);

	float ratio = 1.0f;

	// Create the pulley joint definition and save the bodies and anchor points
	b2PulleyJointDef pulleyJointDef;
	pulleyJointDef.Initialize(_bodyA->GetBody(), _bodyB->GetBody(), groundAnchorA, groundAnchorB, localAnchorA, localAnchorB, ratio);
	pulleyJointDef.lengthA = (localAnchorA - groundAnchorA).Length();
	pulleyJointDef.lengthB = (localAnchorB - groundAnchorB).Length();

	// Create a pulley joint and save it in physics pulley object
	b2PulleyJoint* pPulleyJoint = (b2PulleyJoint*)m_pWorld->CreateJoint(&pulleyJointDef);
	Physics_Pulley_2D* pPhysicsJoint = new Physics_Pulley_2D(m_pWorld, pPulleyJoint, m_metersPerPixel);

	return pPhysicsJoint;	
}

 void Physics_World_2D::CreateSpring(Physics_Body_2D* _bodyA, Physics_Body_2D* _bodyB, v2float _relativeAnchorA, v2float _relativeAnchorB, float _freq, float _damping, float _extraDist)
{
	b2Vec2 worldAnchorA = _bodyA->GetBody()->GetWorldPoint({ _relativeAnchorA.x / m_metersPerPixel, _relativeAnchorA.y / m_metersPerPixel });
	b2Vec2 worldAnchorB = _bodyB->GetBody()->GetWorldPoint({ _relativeAnchorB.x / m_metersPerPixel, _relativeAnchorB.y / m_metersPerPixel });

	// Create a distance joint to limit the spring length and get the physics to enforce its resting position
	b2DistanceJointDef distJointDef;
	distJointDef.frequencyHz = _freq;
	distJointDef.dampingRatio = _damping;
	distJointDef.bodyA = _bodyA->GetBody();
	distJointDef.bodyB = _bodyB->GetBody();
	distJointDef.length = (worldAnchorA - worldAnchorB).Length() + (_extraDist / m_metersPerPixel);
	distJointDef.localAnchorA = { _relativeAnchorA.x / m_metersPerPixel, _relativeAnchorA.y / m_metersPerPixel };
	distJointDef.localAnchorB = { _relativeAnchorB.x / m_metersPerPixel, _relativeAnchorB.y / m_metersPerPixel };
	distJointDef.collideConnected = false;
	b2DistanceJoint* pDistJoint = (b2DistanceJoint*)m_pWorld->CreateJoint(&distJointDef);

	// Create a prismatic joint to constrain the spring to one axis of movement
	b2PrismaticJointDef prismaticJointDef;
	prismaticJointDef.bodyA = _bodyA->GetBody();
	prismaticJointDef.bodyB = _bodyB->GetBody();
	prismaticJointDef.localAnchorA = { _relativeAnchorA.x / m_metersPerPixel, _relativeAnchorA.y / m_metersPerPixel };
	prismaticJointDef.localAnchorB = { _relativeAnchorB.x / m_metersPerPixel, _relativeAnchorB.y / m_metersPerPixel };
	prismaticJointDef.referenceAngle = (_bodyB->GetAngle() - _bodyA->GetAngle());
	prismaticJointDef.localAxisA = { worldAnchorA.x - worldAnchorB.x, worldAnchorA.y - worldAnchorB.y };
	prismaticJointDef.localAxisA.Normalize();
	b2PrismaticJoint* pPrismaticJoint = (b2PrismaticJoint*)m_pWorld->CreateJoint(&prismaticJointDef);
}

std::vector<Physics_Body_2D*>* Physics_World_2D::BreakObject(Physics_Body_2D* _body)
{
	// Retrieve the original objects points, position and size
	v2float* pPoints = _body->GetPoints();
	v2float position = _body->GetPosition();
	UINT size = _body->GetSize();
	
	// Retrieve the collision points and impact velocity from the Objects break structure
	v2float collisionPoint = _body->GetCollisionProperties()->pCollisionWorldPoints[0] * m_metersPerPixel;
	//v2float impactVelocity = _body->GetCollisionProperties()->impactVelocity;

	// Convert the relative points of the object into world space coordinates
	v2float* pWorldPoints = new v2float[size];
	for (UINT i = 0; i < size; i++)
	{
		pWorldPoints[i] = { pPoints[i].x + position.x, pPoints[i].y + position.y };
	}

	// Create a new physics Bodies dependent on where the object was hit 
	std::vector<Physics_Body_2D*>* pPhysBodies = new std::vector<Physics_Body_2D*>;
	for (UINT i = 0; i < size; i++)
	{
		// Create a triangle of points using two from the original object and the collision object
		v2float* pTriPoints = new v2float[3];
		pTriPoints[0] = pWorldPoints[i];
		if (i == (size - 1))
		{
			pTriPoints[1] = pWorldPoints[0];
		}
		else
		{
			pTriPoints[1] = pWorldPoints[i + 1];
		}
		pTriPoints[2] = collisionPoint;

		// Calculate the the center point of the new triangle 
		v2float centerPos;
		centerPos.x = pTriPoints[0].x + pTriPoints[1].x + pTriPoints[2].x;
		centerPos.y = pTriPoints[0].y + pTriPoints[1].y + pTriPoints[2].y;
		centerPos = centerPos / 3.0f;

		// Convert the triangle points from world space to relative
		for (UINT i = 0; i < 3; i++)
		{
			pTriPoints[i] -= centerPos;
		}

		// Create a new physics property structure based on the original object
		v2float linearVelocity = _body->GetCollisionProperties()->linearVelocity;
		TPhysicsProperties physProps = _body->GetPhysicsProperties();
		physProps.size = 3;
		physProps.pos = centerPos;
		physProps.pPoints = pTriPoints;
		physProps.linearVelocity = { linearVelocity.x, linearVelocity.y };
		physProps.collisionType = CT_STANDARD;

		Physics_Body_2D* pTempBody = CreatePhysicsObject(physProps);

		pPhysBodies->push_back(pTempBody);
	}

	// Release the temporary memory 
	ReleasePtr(_body->GetCollisionProperties()->pCollisionWorldPoints);
	ReleasePtr(pWorldPoints);

	// return the vector of new bodies
	return pPhysBodies;
}





