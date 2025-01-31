//------------------------------------------------------------------------------
//
// File Name:	Transform.C
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
#include "Trace.h"

typedef struct Sprite
{
	// The frame currently being displayed (for sprite sheets).
	unsigned int frameIndex;

	// The alpha transparency to use when drawing the sprite.
	float alpha;

	// The sprite source used when drawing (NULL = simple colored mesh).
	const SpriteSource* spriteSource;

	// The mesh used to draw the sprite.
	const Mesh* mesh;

} Sprite;


Sprite* SpriteCreate(void) {
	Sprite* sprite = (Sprite*)calloc(1, sizeof(Sprite)); //<--CHECK VALUES

	if (sprite) {
		sprite->alpha = 1.0f;
		return sprite;
	}
	return 0;
}

void SpriteFree(Sprite** sprite) {
	if (sprite) {
		free(*sprite);
		*sprite = NULL;
	}
	
}

void SpriteRead(Sprite* sprite, Stream stream) {
	sprite->frameIndex = StreamReadInt(stream);
	sprite->alpha = StreamReadFloat(stream);

}


void SpriteSetMesh(Sprite* sprite, const Mesh* mesh) {
	if (sprite&&mesh) {
		sprite->mesh = mesh;
	}
}

void SpriteRender(const Sprite* sprite, Transform* transform) {
	
	if (sprite->spriteSource) {
		DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
		SpriteSourceSetTexture(sprite->spriteSource);
		SpriteSourceSetTextureOffset(sprite->spriteSource, sprite->frameIndex);
	}
	else {
		DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
	}

	DGL_Graphics_SetCB_TransformData(TransformGetTranslation(transform), TransformGetScale(transform), TransformGetRotation(transform));
	DGL_Graphics_SetCB_Alpha(sprite->alpha);
	DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });

	MeshRender(sprite->mesh);

}


float SpriteGetAlpha(const Sprite* sprite) {
	if (sprite) {
		return sprite->alpha;
	}
	return 0.0f;
}


void SpriteSetAlpha(Sprite* sprite, float alpha) {
	float champ;
	champ = min(alpha, 1.0f);
	champ = max(alpha, 0.0f);

	sprite->alpha = champ;

}


void SpriteSetFrame(Sprite* sprite, unsigned int frameIndex) {

	unsigned int frameCount = SpriteSourceGetFrameCount(sprite->spriteSource);

	if ((frameIndex>=0) &&frameIndex < frameCount) {
		sprite->frameIndex = frameIndex;
		TraceMessage("SpriteSetFrame: frame index = %d", frameIndex);
	}
	
		
}


void SpriteSetSpriteSource(Sprite* sprite, const SpriteSource* spriteSource) {
	sprite->spriteSource = spriteSource;

}