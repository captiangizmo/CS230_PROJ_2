//------------------------------------------------------------------------------
//
// File Name:	Level1Scene.c
// Author(s):	Miles Gage (miles.gage) (0067845)
// Project:		Project 2
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------




#include "stdafx.h"

#include "Stream.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "Trace.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Mesh.h"
#include "Transform.h"
#include "Entity.h"
#include "Vector2D.h"
#include "EntityFactory.h"
#include "Physics.h"




//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
static const float groundHeight = -150.0f;
static const float moveVelocity = 500.0f;
static const float jumpVelocity = 1000.0f;
static const Vector2D gravityNormal = { 0.0f, -1500.0f };
static const Vector2D gravityNone = { 0.0f, 0.0f };
//

//test vars
//Sprite* spriteTest;
//Transform* transformTest;
//Mesh* meshTest;
//SpriteSource* sourceTest;
//Entity* entityTest;
//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Level1Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	int numLives;
	Mesh* mesh;
	SpriteSource* spriteSource;
	Entity* entity;
} Level1Scene;


//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void Level1SceneLoad(void);
static void Level1SceneInit(void);
static void Level1SceneUpdate(float dt);
static void Level1SceneExit(void);
static void Level1SceneUnload(void);
static void Level1SceneRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level1Scene instance =
{
	// Initialize the base structure:
	{ "Level1", Level1SceneLoad, Level1SceneInit, Level1SceneUpdate, Level1SceneRender, Level1SceneExit, Level1SceneUnload },

	// Initialize any scene-specific variables: 
	.numLives = 0,
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Level1 Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* Level1SceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void Level1SceneLoad(void)
{

	Stream stream = StreamOpen("./Data/Level1_Lives.txt");
	if (stream) {
		instance.numLives = StreamReadInt(stream);
		StreamClose(&stream);
	}

	//UNCOMMENT THESE - WORD INSTRUCTIONS_____________________________________
	instance.mesh = MeshCreate();
	MeshBuildQuad(instance.mesh, 0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");
	instance.spriteSource = SpriteSourceCreate();
	SpriteSourceLoadTexture(instance.spriteSource, 1, 1, "PlanetTexture.png");


}

// Initialize the entities and variables used by the scene.
static void Level1SceneInit()
{
	////TESTS
	////test create  mesh
	//meshTest = MeshCreate();
	//MeshBuildQuad(meshTest, 50.f, 50.0f, 10.0f, 10.0f, "Mesh1x1");
	//
	//
	////test create sprite+transform
	//spriteTest = SpriteCreate();
	//transformTest = TransformCreate();
	//SpriteSetFrame(spriteTest, 0);
	//SpriteSetAlpha(spriteTest, 1.0f);

	////test create spritesource
	//sourceTest = SpriteSourceCreate();
	//SpriteSourceLoadTexture(sourceTest, 1, 1, "PlanetTexture.png");
	//
	////test set spritesource
	//SpriteSetSpriteSource(spriteTest, sourceTest);
	//SpriteSetMesh(spriteTest, meshTest);

	//SpriteSourceSetTexture(sourceTest);

	////Test set transform
	//TransformSetTranslation(transformTest, &(Vector2D) { 1.f, 1.f });
	//TransformSetScale(transformTest, &(Vector2D) { 1.f, 1.f });
	


	instance.entity = EntityFactoryBuild("./Data/PlanetJump.txt");
	if (instance.entity) {
		//confused about how to set entity stuff sooo three dif ways...
		//Sprite* cranberry = EntityGetSprite(instance.entity);

		SpriteSetMesh(EntityGetSprite(instance.entity), instance.mesh);
		SpriteSetSpriteSource(EntityGetSprite(instance.entity), instance.spriteSource);
		SpriteSetFrame(EntityGetSprite(instance.entity), 0);
		SpriteSetAlpha(EntityGetSprite(instance.entity), 1.0f);
	    DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	






	//	//NEW VAR ASIGNED BACK TO INSTANCE ENTITY
	//	/*Sprite* cool = EntityGetSprite(instance.entity);
	//	SpriteSetMesh(cool, instance.mesh);
	//	SpriteSetSpriteSource(cool, instance.spriteSource);
	//	SpriteSetFrame(cool, 0);
	//	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	//	EntityAddSprite(instance.entity, cool);*/

	//	//JUST NEW VAR
	//	/*Sprite* planetSprite = EntityGetSprite(instance.entity);
	//	SpriteSetMesh(planetSprite, instance.mesh);
	//	SpriteSetSpriteSource(planetSprite, instance.spriteSource);
	//	SpriteSetFrame(planetSprite, 0);
	//	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);*/
	}
	DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 1.0f, 1.0f, 1.0f, 1.0f });
}

static void Level1SceneMovementController(Entity* entity) {
	Physics* fizz = EntityGetPhysics(entity);
	Transform* trans = EntityGetTransform(entity);

	if (fizz && trans) {
		Vector2D velocity = *(PhysicsGetVelocity(fizz));

		if (DGL_Input_KeyDown(VK_LEFT)) {
			velocity.x = -moveVelocity;
		}
		if (DGL_Input_KeyDown(VK_RIGHT)) {
			velocity.x = moveVelocity;
		}

		if (!DGL_Input_KeyDown(VK_LEFT)&& !DGL_Input_KeyDown(VK_RIGHT)) {
			velocity.x = 0;
		}

		if (DGL_Input_KeyTriggered(VK_UP)) {
			velocity.y = jumpVelocity;
			PhysicsSetAcceleration(EntityGetPhysics(entity), &gravityNormal);
		}

		//check for landing
		Vector2D curTrans = *TransformGetTranslation(trans);

		if (curTrans.y < groundHeight) {
			//set y trans grnd height
			curTrans.y = groundHeight;
			TransformSetTranslation(trans, &curTrans);

			//set vel.y = 0
			velocity.y = 0;

			//set accel 
			PhysicsSetAcceleration(fizz, &gravityNone);
			instance.numLives--;
			if (instance.numLives <= 0) {
				//SceneSystemSetNext(Level2SceneGetInstance());
				SceneSystemSetNext(NULL);
			}
		}
		PhysicsSetVelocity(fizz, &velocity);

	}

}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level1SceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);

	Level1SceneMovementController(instance.entity);
	EntityUpdate(instance.entity,dt);
}

// Render any objects associated with the scene.
void Level1SceneRender(void)
{
	EntityRender(instance.entity);
	//MeshRender(instance.mesh);

	//TESTING STUFF
	//MeshRender(meshTest);
	//SpriteRender(spriteTest, transformTest);



	//SpriteRender(EntityGetSprite(instance.entity), EntityGetTransform(instance.entity));

}

// Free any objects associated with the scene.
static void Level1SceneExit()
{
	EntityFree(&instance.entity);
}

// Unload any resources used by the scene.
static void Level1SceneUnload(void)
{
	SpriteSourceFree(&instance.spriteSource);
	MeshFree(&instance.mesh);

}

