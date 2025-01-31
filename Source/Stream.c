//------------------------------------------------------------------------------
//
// File Name:	Stream.c
// Author(s):	Miles Gage (miles.gage)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Stream.h"
#include "Trace.h"
#include "SceneSystem.h"
#include "Scene.h"
#include "DGL.h"


static char tokenBuffer[1024];


Stream StreamOpen(const char* FilePath) {
	Stream stream;

	fopen_s(&stream, FilePath, "rt");
	if (!stream) {
		char buffer[100];
		TraceMessage("Error: StreamOpen could not open file %s; %s", FilePath, strerror_s(buffer, 80, errno));
		return 0;
	}
	else
	{
		return stream;
	}

}

int StreamReadInt(Stream stream) {
	int curInt;
	if (stream)
	{
		int read;
		read = fscanf_s(stream, "%i\n", &curInt);
		if (curInt)
		{
			return curInt;
		}

	}
	return 0;

}


float StreamReadFloat(Stream stream) {
	float curFloat;
	if (stream)
	{
		int read;
		read = fscanf_s(stream, "%f\n", &curFloat);
		if (curFloat)
		{
			return curFloat;
		}
	}
	return 0;
}

void StreamReadVector2D(Stream stream, Vector2D* vector) {
	if (stream) {
		float x = 0.0f;
		float y = 0.0f;

		int read;
		read = fscanf_s(stream, "%f %f", &x, &y);
		if (vector)
		{
			vector->x = x;
			vector->y = y;
		}
	}
}

void StreamClose(Stream* stream) {
	if (stream) {
		fclose(*stream);
		*stream = NULL;
	}
}

const char* StreamReadToken(Stream stream) {
	tokenBuffer[0] = 0;
	if (stream) {
		fscanf_s(stream, "%s", tokenBuffer, (int)_countof(tokenBuffer));
		return tokenBuffer;
	}
	return 0;

}