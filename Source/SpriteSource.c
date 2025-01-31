//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.C
// Author(s):	Miles Gage (miles.gage)
// Project:		Project 2
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "Sprite.h"
#include "DGL.h"
#include "Stream.h"
#include "Mesh.h"
#include "Transform.h"
#include "SpriteSource.h"

typedef struct SpriteSource
{
	// The dimensions of the sprite sheet.
	// (Hint: These should be initialized to (1, 1).)
	int	numRows;
	int	numCols;

	// Pointer to a texture resource created using the DigiPen Graphics Library (DGL).
	const DGL_Texture* texture;

} SpriteSource;


SpriteSource* SpriteSourceCreate() {
	SpriteSource* spriteSource = (SpriteSource*)calloc(1, sizeof(spriteSource)); //<--CHECK VALUES

	if (spriteSource) {
		spriteSource->numCols = 1;
		spriteSource->numRows= 1;

		return spriteSource;
	}
	return 0;
}

void SpriteSourceFree(SpriteSource** spriteSource) {
	if (spriteSource&& *spriteSource) {
		if ((*spriteSource)->texture) {
			DGL_Graphics_FreeTexture(&(*spriteSource)->texture);
		}
		free(*spriteSource);
		*spriteSource = NULL;

	}
	
}

void SpriteSourceLoadTexture(SpriteSource* spriteSource, int numCols, int numRows, const char* textureName) {
	
	char buffer[200];

	spriteSource->numCols = numCols;
	spriteSource->numRows = numRows;
	sprintf_s(buffer, sizeof(buffer), "Assets/%s", textureName);
	spriteSource->texture= DGL_Graphics_LoadTexture(buffer);

	
}

void SpriteSourceSetTexture(const SpriteSource* spriteSource) {
	DGL_Graphics_SetTexture(spriteSource->texture);
}

void SpriteSourceSetTextureOffset(const SpriteSource* spriteSource, unsigned frameIndex) {
	DGL_Vec2 uv = { 1.0f,1.0f };
	SpriteSourceGetUV(spriteSource, frameIndex, &(uv.x), &(uv.y));
	DGL_Graphics_SetCB_TextureOffset(&uv);
}

unsigned SpriteSourceGetFrameCount(const SpriteSource* spriteSource) {
	if (spriteSource) {
		unsigned int frame = spriteSource->numRows * spriteSource->numCols;
		return frame;
	}
	return 0;
}

void SpriteSourceGetUV(const SpriteSource* spriteSource, unsigned int frameIndex, float* u, float* v) {
	float uSize = 1.0f / spriteSource->numCols;
	float vSize = 1.0f / spriteSource->numRows;

	float uOffset = uSize * (frameIndex % spriteSource->numCols);
	float vOffset = vSize * (frameIndex / spriteSource->numCols);

	*u = uOffset;
	*v = vOffset;

}

