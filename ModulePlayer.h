#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include"ModuleTextures.h"
#include"ModuleRender.h"
#include"Box2D/Box2D/Box2D.h"
#include "ModulePhysics.h"
class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	SDL_Texture* pequenaizq;
	SDL_Texture* pequenader;
	SDL_Texture* grandeizq;
	SDL_Texture* grandeder;
	b2Body* stricker1;
	b2Body* stricker2;
	b2Body* stricker3;
	b2Body* stricker4;

public:

};