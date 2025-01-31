//------------------------------------------------------------------------------
//
// File Name:	Mesh.C
// Author(s):	Miles Gage (miles.gage)
// Project:		Project 2
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Mesh.h"
#include "DGL.h"
#include "SpriteSource.h"
#include "Sprite.h"
#include "Transform.h"



typedef struct Mesh
{
	// The name of the Mesh.  This will be used later in the semester.
	char name[32];

	// Pointer to the DGL_Mesh resource.
	const DGL_Mesh* meshResource;

	// The draw mode to use when rendering the mesh (Usually "DGL_DM_TRIANGLELIST").
	DGL_DrawMode drawMode;
} Mesh;


//colors from demoscene
static const DGL_Color DGL_Color_Black = { 0.0f, 0.0f, 0.0f, 1.0f };
static const DGL_Color DGL_Color_White = { 1.0f, 1.0f, 1.0f, 1.0f };
static const DGL_Color DGL_Color_Red = { 1.0f, 0.0f, 0.0f, 1.0f };
static const DGL_Color DGL_Color_Green = { 0.0f, 1.0f, 0.0f, 1.0f };
static const DGL_Color DGL_Color_Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
static const DGL_Color DGL_Color_Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
static const DGL_Color DGL_Color_Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
static const DGL_Color DGL_Color_Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };



Mesh* MeshCreate() {
	Mesh* mesh = (Mesh*)calloc(1, sizeof(Mesh)); //<--CHECK VALUES

	if (mesh) {
		return mesh;
	}
	return 0;
}



//MAKE SURE TO UPDATE UV VALUESS
void MeshBuildQuad(Mesh* mesh, float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name) {
	// Create a simple, colored mesh.

    //DGL SETTINGS
    //setshader mode
    //set cb alpha
    //settintcolor


    mesh->drawMode = DGL_DM_TRIANGLELIST;

    strcpy_s(mesh->name, _countof(mesh->name), name); 

    DGL_Color color = { 0.0f, 0.0f, 0.0f, 1.0f };
    
    //first triangle
    DGL_Graphics_StartMesh();

    DGL_Graphics_AddTriangle(
        &(DGL_Vec2) { -xHalfSize, -yHalfSize}, & color, & (DGL_Vec2){ 0.0f, vSize },
        & (DGL_Vec2) {xHalfSize, yHalfSize}, & color, & (DGL_Vec2){ uSize, 0.0f },
        & (DGL_Vec2) {xHalfSize, -yHalfSize}, & color, & (DGL_Vec2){ uSize, vSize}
    );

    //second triangle
    DGL_Graphics_AddTriangle(
        &(DGL_Vec2) { -xHalfSize, -yHalfSize }, & color, & (DGL_Vec2){ 0.0f, vSize },
        & (DGL_Vec2) { -xHalfSize, yHalfSize}, & color, & (DGL_Vec2){ 0.0f, 0.0f },
        & (DGL_Vec2) {xHalfSize, yHalfSize}, & color, & (DGL_Vec2){ uSize, 0.0f}
    );
    
   mesh->meshResource=DGL_Graphics_EndMesh();
}




void MeshBuildSpaceship(Mesh* mesh) {
    mesh->drawMode = DGL_DM_TRIANGLELIST;


    DGL_Color color = { 100.0f, 150.0f, 50.0f, 1.0f };

    DGL_Graphics_StartMesh();

    DGL_Graphics_AddTriangle(
        &(DGL_Vec2) { -0.5f, -0.5f}, & color, & (DGL_Vec2){ 0.0f, 0.0f },
        & (DGL_Vec2) {0.5f, 0.5f}, & color, & (DGL_Vec2){ 0.0f, 0.0f },
        & (DGL_Vec2) {0.5f, -0.5f}, & color, & (DGL_Vec2){ 0.0f, 0.0f}
    );

    //second triangle
    DGL_Graphics_AddTriangle(
        &(DGL_Vec2) { -0.5f, -0.5f }, & color, & (DGL_Vec2){ 0.0f, 0.0f },
        & (DGL_Vec2) {-0.5f, 0.5f}, & color, & (DGL_Vec2){ 0.0f, 0.0f },
        & (DGL_Vec2) {0.5f, 0.5f}, & color, & (DGL_Vec2){ 0.0f, 0.0f}
    );

    mesh->meshResource = DGL_Graphics_EndMesh();

}



void MeshRender(const Mesh* mesh) {

    //DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
    //DGL_Graphics_SetTexture(NULL);
    //DGL_Graphics_SetCB_Alpha(1.0f);
    //DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });
    //DGL_Graphics_SetCB_TransformData(&(DGL_Vec2){1.0f,1.0f}, & (DGL_Vec2) { 1.0f, 1.0f }, 0.f);
    ////DGL_Graphics_DrawMesh(meshColor, DGL_DM_TRIANGLELIST);

    DGL_Graphics_DrawMesh(mesh->meshResource, mesh->drawMode);
}


void MeshFree(Mesh** mesh) {
    if (mesh) {
        DGL_Graphics_FreeMesh(&(*mesh)->meshResource);
        free(*mesh);
        *mesh = NULL;
    }
}