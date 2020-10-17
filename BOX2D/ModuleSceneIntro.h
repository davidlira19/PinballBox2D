#pragma once
#include "Module.h"
#include "p2List.h"
#include "Globals.h"
#include "ModulePhysics.h"
class PhysBody;
//class ModulePhysics;
class  smallClass;
class b2Body;
class bodyList {
public:
	smallClass* arr[50];
	bodyList();
	void savepointer(smallClass* pointer);

};
class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	bodyList list;
	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
};

