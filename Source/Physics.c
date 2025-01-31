//------------------------------------------------------------------------------
//
// File Name:	Physics.C
// Author(s):	Miles Gage (miles.gage)
// Project:		Project 2
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "DGL.h"
#include "Physics.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "Stream.h"
#include "Transform.h"



typedef struct Physics
{
	// Previous position.  May be used for resolving collisions.
	Vector2D	oldTranslation;

	// Acceleration = inverseMass * (sum of forces)
	Vector2D	acceleration;

	// Velocity may be stored as a direction vector and speed scalar, instead.
	Vector2D	velocity;

	// Used when calculating acceleration due to forces.
	// Used when resolving collision between two dynamic objects.
	//float		inverseMass;

} Physics;




Physics* PhysicsCreate(void) {
	Physics* physics = (Physics*)calloc(1, sizeof(physics)); //<--CHECK VALUES

	if (physics) {
		return physics;
	}
	return 0;
}

void PhysicsFree(Physics** physics) {
	if (physics) {
		free(*physics);
		*physics = NULL;
	}

	/*if(physics && *physics)
	{
		Physics* pptr;
		pptr = *physics;

		free(pptr);
		*physics = NULL;
	}*/
}

void PhysicsRead(Physics* physics, Stream stream) {

	if (stream) {
		StreamReadVector2D(stream, &physics->acceleration);
		StreamReadVector2D(stream, &physics->velocity);

	}
}


const Vector2D* PhysicsGetAcceleration(const Physics* physics) {
	if (physics) {
		return &physics->acceleration;
	}
	return 0;
}

const Vector2D* PhysicsGetVelocity(const Physics* physics) {
	if (physics) {
		return &physics->velocity;
	}
	return 0;
}

const Vector2D* PhysicsGetOldTranslation(Physics* physics) {
	if (physics) {
		return &physics->oldTranslation;
	}
	return 0;
}

void PhysicsSetAcceleration(Physics* physics, const Vector2D* acceleration) {
	physics->acceleration.x = acceleration->x;
	physics->acceleration.y = acceleration->y;
}

void PhysicsSetVelocity(Physics* physics, const Vector2D* velocity) {
	physics->velocity.x = velocity->x;
	physics->velocity.y = velocity->y;
}

void PhysicsUpdate(Physics* physics, Transform* transform, float dt) {
	physics->oldTranslation = *(TransformGetTranslation(transform));
	
	Vector2DScaleAdd(&(physics->velocity), &(physics->acceleration), dt, &(physics->velocity));
	Vector2DScaleAdd(&(physics->oldTranslation), &(physics->velocity), dt, &(physics->oldTranslation));
	TransformSetTranslation(transform, &(physics->oldTranslation));
}