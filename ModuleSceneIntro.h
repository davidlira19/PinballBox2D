#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
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
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> walls;
	int blancas = -1;
	char _scoreText[7] = { "\0" };
	PhysBody* sensor;
	bool sensed;
	SDL_Texture* gameOver;
	SDL_Texture* background;
	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	uint bonus_fx;
	int music;
	p2Point<int> ray;
	bool ray_on;

	bool sumLifes;
	int Lifes;
	int Points;
	int maxPoints;
	int prevPoints;
	bool dead;
};
