#pragma once
#include "Module.h"
#include "p2List.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	bodyList list;
	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
};
class bodyList {
public:
	smallClass* arr[50];
	bodyList() {
		for (int a = 0; a < 50; a++) {
			arr[a] = nullptr;
		}
	}
	void savepointer(smallClass* pointer) {
		for (int a = 0; a < 50; a++) {
			if (arr[a] == nullptr) {
				arr[a] = pointer;
				break;
			}
		}
	}

};
