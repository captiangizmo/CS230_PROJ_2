//------------------------------------------------------------------------------
//
// File Name:	SandboxScene.c
// Author(s):	Miles Gage (miles.gage) (0067845)
// Project:		Project 0
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

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct SandboxScene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.

} SandboxScene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void SandboxSceneLoad(void);
static void SandboxSceneInit(void);
static void SandboxSceneUpdate(float dt);
static void SandboxSceneExit(void);
static void SandboxSceneUnload(void);
static void SandboxSceneRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static SandboxScene instance =
{
	// Initialize the base structure:
	{ "Sandbox", SandboxSceneLoad, SandboxSceneInit, SandboxSceneUpdate, SandboxSceneRender, SandboxSceneExit, SandboxSceneUnload },

	// Initialize any scene-specific variables:

};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Sandbox Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* SandboxSceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void SandboxSceneTraceFloat(const char* text, float f) {
	TraceMessage("Vector Test: %s = %f", text, f);
}

static void SandboxSceneTraceVector(const char* text, const Vector2D* v) {
	TraceMessage("Vector Test: %s = [%f, %f]", text, v->x,v->y);
}


// Load any resources used by the scene.
static void SandboxSceneLoad(void)
{
}

// Initialize the entities and variables used by the scene.
static void SandboxSceneInit()
{
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void SandboxSceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);
	Stream stream = StreamOpen("./Data/VectorTests.txt");
	if (stream) {
		Vector2D tVec = { 0.0f,0.0f };

		Vector2DZero(&tVec);
		SandboxSceneTraceVector("Vector2DZero", &tVec);
		Vector2DSet(&tVec, 1.5f, 1.0f);
		SandboxSceneTraceVector("Vector2DSet", &tVec);
		Vector2DNeg(&tVec, &tVec);
		SandboxSceneTraceVector("Vector2DNeg", &tVec);
		Vector2DAdd(&tVec, &tVec, &tVec);
		SandboxSceneTraceVector("Vector2DAdd", &tVec);
		Vector2DSub(&tVec, &tVec, &tVec);
		SandboxSceneTraceVector("Vector2DSub", &tVec);
		StreamReadVector2D(stream, &tVec);
		SandboxSceneTraceVector("StreamReadVector2D", &tVec);
		Vector2DNormalize(&tVec, &tVec);
		SandboxSceneTraceVector("Vector2DNormalize", &tVec);
		float scale = StreamReadFloat(stream);
		SandboxSceneTraceFloat("StreamReadFloat", scale);

		Vector2DScale(&tVec, &tVec, scale);
		SandboxSceneTraceVector("Vector2DScale", &tVec);
		Vector2DScaleAdd(&tVec, &tVec, scale, &tVec);
		SandboxSceneTraceVector("Vector2DScaleAdd", &tVec);
		Vector2DScaleSub(&tVec, &tVec, scale, &tVec);
		SandboxSceneTraceVector("Vector2DScaleSub", &tVec);

		SandboxSceneTraceFloat("Vector2DLength", Vector2DLength(&tVec));
		
		
		SandboxSceneTraceFloat("Vector2DSquareLength", Vector2DSquareLength(&tVec));
		
		//two new vectors
		Vector2D aVec = { 0.0f,0.0f };
		Vector2D bVec = { 0.0f,0.0f };
		
		

		StreamReadVector2D(stream, &aVec);
		SandboxSceneTraceVector("StreamReadVector2D", &aVec);

		StreamReadVector2D(stream, &bVec);
		SandboxSceneTraceVector("StreamReadVector2D", &bVec);


		SandboxSceneTraceFloat("Vector2DDistance", Vector2DDistance(&aVec, &bVec));
		
		SandboxSceneTraceFloat("Vector2DSquareDistance", Vector2DSquareDistance(&aVec, &bVec));

		SandboxSceneTraceFloat("Vector2DDotProduct", Vector2DDotProduct(&aVec, &bVec));

		//final vector
		Vector2D cVec = { 0.0f,0.0f };
		float angle = StreamReadFloat(stream);
		SandboxSceneTraceFloat("StreamReadFloat", angle);

		Vector2DFromAngleDeg(&cVec, angle);
		SandboxSceneTraceVector("Vector2DFromAngleDeg", &cVec);

		angle = StreamReadFloat(stream);
		SandboxSceneTraceFloat("StreamReadFloat", angle);

		Vector2DFromAngleRad(&cVec, angle);
		SandboxSceneTraceVector("Vector2DFromAngleRad", &cVec);

		SandboxSceneTraceFloat("Vector2DToAngleRad", Vector2DToAngleRad(&cVec));
		StreamClose(&stream);
	}



	// NOTE: This call causes the engine to exit immediately.  Make sure to remove
	//   it when you are ready to test out a new scene.
	SceneSystemSetNext(NULL);
}

// Render any objects associated with the scene.
void SandboxSceneRender(void)
{
}

// Free any objects associated with the scene.
static void SandboxSceneExit()
{
}

// Unload any resources used by the scene.
static void SandboxSceneUnload(void)
{
}

