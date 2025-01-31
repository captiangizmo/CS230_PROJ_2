//------------------------------------------------------------------------------
//
// File Name:	Vector2D.c
// Author(s):	Miles Gage (miles.gage) (0067845)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Vector2D.h"

#define _USE_MATH_DEFINES
#include <math.h>


void Vector2DZero(Vector2D* pResult){
	pResult->x = 0; 
	pResult->y = 0;
}

void Vector2DSet(Vector2D* pResult, float x, float y) {
	pResult->x = x;
	pResult->y = y;
}

void Vector2DNeg(Vector2D* pResult, const Vector2D* pVec0) {
	float x = pVec0->x;
	float y = pVec0->y;
	
	pResult->x = x *-1.0f;
	pResult->y = y * -1.0f;
}

void Vector2DAdd(Vector2D* pResult, const Vector2D* pVec0, const Vector2D* pVec1) {
	float x1 = pVec0->x;
	float y1 = pVec0->y;
	
	float x2 = pVec1->x;
	float y2= pVec1->y;

	pResult->x = x1 + x2;
	pResult->y = y1 + y2;

}

void Vector2DSub(Vector2D* pResult, const Vector2D* pVec0, const Vector2D* pVec1) {
	float x1 = pVec0->x;
	float y1 = pVec0->y;

	float x2 = pVec1->x;
	float y2 = pVec1->y;

	pResult->x = x1 - x2;
	pResult->y = y1 - y2;
}

void Vector2DNormalize(Vector2D* pResult, const Vector2D* pVec0) {
	float x = pVec0->x;
	float y = pVec0->y;

	float mag = sqrtf((x * x) + (y * y));
	float normX = x / mag;
	float normY = y / mag;
	
	pResult->x = normX;
	pResult->y = normY;

}

void Vector2DScale(Vector2D* pResult, const Vector2D* pVec0, float scale) {
	float scaleX = pVec0->x * scale;
	float scaleY = pVec0->y * scale;

	pResult->x = scaleX;
	pResult->y = scaleY;
}


void Vector2DScaleAdd(Vector2D* pResult, const Vector2D* pVec0, float scale, const Vector2D* pVec1) {
	float scaleX = pVec0->x * scale;
	float scaleY = pVec0->y * scale;

	pResult->x = scaleX + pVec1->x;
	pResult->y = scaleY + pVec1->y;
}


void Vector2DScaleSub(Vector2D* pResult, const Vector2D* pVec0, float scale, const Vector2D* pVec1) {
	float scaleX = pVec0->x * scale;
	float scaleY = pVec0->y * scale;

	pResult->x = scaleX - pVec1->x;
	pResult->y = scaleY - pVec1->y;
}

float Vector2DLength(const Vector2D* pVec0) {
	//(square + square) square rooted
	float x = pVec0->x;
	float y = pVec0->y;
	
	return sqrtf(powf(x, 2.0f) + powf(y, 2.0f));


}

float Vector2DSquareLength(const Vector2D* pVec0) {
	//(square + square) square rooted
	float x = pVec0->x;
	float y = pVec0->y;

	return powf(x, 2.0f) + powf(y, 2.0f);
}

float Vector2DDistance(const Vector2D* pVec0, const Vector2D* pVec1) {
	
	float x = pVec0->x;
	float y = pVec0->y;
	
	float x2 = pVec1->x;
	float y2 = pVec1->y;

	float dist = sqrtf(powf(x - x2, 2.0f) + powf(y - y2, 2.0f));
	return dist;
}

float Vector2DSquareDistance(const Vector2D* pVec0, const Vector2D* pVec1) {
	float x = pVec0->x;
	float y = pVec0->y;

	float x2 = pVec1->x;
	float y2 = pVec1->y;

	float dist = powf(x - x2, 2.0f) + powf(y - y2, 2.0f);
	return dist;
}

float Vector2DDotProduct(const Vector2D* pVec0, const Vector2D* pVec1) {
	float x = pVec0->x;
	float y = pVec0->y;

	float x2 = pVec1->x;
	float y2 = pVec1->y;

	return ((x * x2) + (y * y2));

}


void Vector2DFromAngleDeg(Vector2D* pResult, float angle) {
	float radians = (angle * (float)M_PI) / 180.0f;

	float x = cosf(radians);
	float y = sinf(radians);

	pResult->x = x;
	pResult->y = y;
}

void Vector2DFromAngleRad(Vector2D* pResult, float angle) {
	float x = cosf(angle);
	float y = sinf(angle);

	pResult->x = x;
	pResult->y = y;

}

float Vector2DToAngleRad(const Vector2D* pVec) {
	if (!pVec) {
		return 0;
	}
	float x = pVec->x;
	float y = pVec->y;


	float angle = atan2f(y, x);
	return angle;
}
