//------------------------------------------------------------------------------
//
// File Name:	EntityFactory.C
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
#include "Entity.h"
#include "EntityFactory.h"


Entity* EntityFactoryBuild(const char* filename) {
	if (filename) 
	{
		Stream stream = StreamOpen(filename);
		if (stream) 
		{
			char toke[32];
			strcpy_s(toke, _countof(toke), StreamReadToken(stream));

			if (strncmp("Entity", toke, strlen("Entity")) == 0)
			{
				Entity* entity = EntityCreate();
				EntityRead(entity, stream);
				StreamClose(&stream);
				return entity;
			}
			StreamClose(&stream);
		}

	}
	return 0;
}