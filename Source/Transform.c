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

#include "Transform.h"
#include "DGL.h"
#include "Stream.h"

typedef struct Transform
{
	// The translation (or world position) of an entity.
	Vector2D	translation;

	// The rotation (or orientation) of an entity (in radians).
	float	rotation;

	// The scale (or size) of an entity.
	// (Hint: This should be initialized to (1, 1).)
	Vector2D	scale;

} Transform;


Transform* TransformCreate(void) {
	Transform* transform = (Transform*)calloc(1, sizeof(Transform)); //<--CHECK VALUES


	if (transform) {
		
		transform->scale.x = 1;
		transform->scale.y = 1;
		
		return transform;
	}
	return 0;
}



void TransformFree(Transform** transform) {
	free(*transform);
	transform = NULL;
}

void TransformRead(Transform* transform, Stream stream) {
	StreamReadVector2D(stream, &transform->translation);
	transform->rotation = StreamReadFloat(stream);
	StreamReadVector2D(stream, &transform->scale);
}

const Vector2D* TransformGetTranslation(const Transform* transform) {
	if (transform) {
		return &transform->translation;
	}
	return 0;
}


float TransformGetRotation(const Transform* transform) {
	if (transform) {
		return transform->rotation;
	}
	return 0.0f;
}

const Vector2D* TransformGetScale(const Transform* transform) {
	if (transform) {
		return &transform->scale;
	}
	return 0;
}

void TransformSetTranslation(Transform* transform, const Vector2D* translation) {
	transform->translation.x = translation->x;
	transform->translation.y = translation->y;
}

void TransformSetRotation(Transform* transform, float rotation) {
	transform->rotation = rotation;
}

void TransformSetScale(Transform* transform, const Vector2D* scale) {
	transform->scale.x = scale->x;
	transform->scale.y = scale->y;
}
