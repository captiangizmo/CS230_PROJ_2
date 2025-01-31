//------------------------------------------------------------------------------
//
// File Name:	Entity.C
// Author(s):	Miles Gage (miles.gage)
// Project:		Project 2
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "SandboxScene.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "Vector2D.h"
#include "DGL.h"
#include "Stream.h"
#include "Physics.h"
#include "Sprite.h"
#include "Entity.h"
#include "Transform.h"


typedef struct Entity
{
	// The name of the entity.
	// A buffer is used to allow each entity to have a unique name.
	// The buffer is hardcoded to an arbitrary length that will be sufficient
	//	 for all CS230 assignments.  You may, instead, use dynamically-allocated
	//	 arrays for this purpose but the additional complexity is unnecessary
	//	 and it is your responsibility to ensure that the memory is successfully
	//	 allocated and deallocated in all possible situations.
	// [NOTE: When setting the name, use strcpy_s() to reduce the risk of
	//	 buffer overruns. Additionally, do NOT hardcode the number "32" when
	//	 calling this function!  Instead, use the _countof() macro to get the
	//	 size of the "name" array.]
	char name[32];

	// Pointer to an attached physics component.
	Physics* physics;

	// Pointer to an attached sprite component.
	Sprite* sprite;

	// Pointer to an attached transform component.
	Transform* transform;

} Entity;



Entity* EntityCreate(void) {
	Entity* entity = (Entity*)calloc(1, sizeof(entity)); //<--CHECK VALUES

	if (entity) {
		return entity;
	}
	return 0;
}

void EntityFree(Entity** entity) {

	if (entity) {
		//Entity* entptr = *entity;

		PhysicsFree(&(*entity)->physics);
		SpriteFree(&(*entity)->sprite);
		TransformFree(&(*entity)->transform);

		free(*entity);
		*entity = NULL;
	}
}

void EntityRead(Entity* entity, Stream stream) {
	
	if (entity && stream) {	
		EntitySetName(entity, StreamReadToken(stream));

		while(true) 
		{
			char toke[32];
			strcpy_s(toke, _countof(toke), StreamReadToken(stream));

			if (strncmp("Transform", toke , _countof("Transform"))==0)
			{
				Transform* transform = TransformCreate();
				TransformRead(transform, stream);
				EntityAddTransform(entity, transform);
			}
			else if (strncmp("Physics", toke, _countof("Physics")) == 0)
			{
				Physics* physics = PhysicsCreate();
				PhysicsRead(physics, stream);
				EntityAddPhysics(entity, physics);

			}
			else if (strncmp("Sprite", toke, _countof("Sprite")) == 0)
			{
				Sprite* sprite = SpriteCreate();
				SpriteRead(sprite, stream);
				EntityAddSprite(entity, sprite);
			}
			else if (strlen(toke) == 0) {
				break;
			}
		}
	}
}

void EntityAddPhysics(Entity* entity, Physics* physics) {
	entity->physics = physics;
}

void EntityAddSprite(Entity* entity, Sprite* sprite) {
	entity->sprite = sprite;
}

void EntityAddTransform(Entity* entity, Transform* transform) {
	entity->transform = transform;
}

void EntitySetName(Entity* entity, const char* name) {
	if (entity && name) {
		strcpy_s(entity->name, _countof(entity->name), name);
	}
}

const char* EntityGetName(const Entity* entity) {
	if (entity) {
		return entity->name;
	}
	return 0;
}

Physics* EntityGetPhysics(const Entity* entity) {
	if (entity) {
		return entity->physics;
	}
	return 0;
}

Sprite* EntityGetSprite(const Entity* entity) {
	if (entity) {
		return entity->sprite;
	}
	return 0;
}

Transform* EntityGetTransform(const Entity* entity) {
	if (entity) {
		return entity->transform;
	}
	return 0;
}

void EntityUpdate(Entity* entity, float dt) {
	if (entity) {
		PhysicsUpdate(entity->physics, entity->transform, dt);
	}
}

void EntityRender(Entity* entity) {
	if (entity) {
		SpriteRender(entity->sprite, entity->transform);
	}
}