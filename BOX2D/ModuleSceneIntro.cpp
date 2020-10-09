#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePhysics.h"
#include "Box2D/Box2D/Box2D.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}
void ModulePhysics::CreateCircles()
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	float radius = PIXEL_TO_METERS(25);
	body.position.Set(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = radius;
	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);
}
void ModulePhysics::CreateRectangles()
{
	b2BodyDef boxBody;
	boxBody.type = b2_dynamicBody;
	boxBody.position.Set(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));

	b2Body* bo = world->CreateBody(&boxBody);

	b2PolygonShape polygon;
	b2FixtureDef fixture;

	fixture.shape = &polygon;
	fixture.density = 1.0f;

	polygon.SetAsBox(PIXEL_TO_METERS(20), PIXEL_TO_METERS(10), b2Vec2(0, 0), 0);//ground
	bo->CreateFixture(&fixture);
}
void ModulePhysics::CreateChains()
{
	b2BodyDef ChainBody;
	ChainBody.type = b2_dynamicBody;
	ChainBody.position.Set(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));

	b2Body* ch = world->CreateBody(&ChainBody);

	b2ChainShape chain;
	b2FixtureDef ChainFixture;

	ChainFixture.shape = &chain;
	ChainFixture.density = 1.0f;

	b2Vec2 points[12];
	points[0] = { PIXEL_TO_METERS(-38),PIXEL_TO_METERS(80) };
	points[1] = { PIXEL_TO_METERS(-44),PIXEL_TO_METERS(-54) };
	points[2] = { PIXEL_TO_METERS(-16),PIXEL_TO_METERS(-60) };
	points[3] = { PIXEL_TO_METERS(-16),PIXEL_TO_METERS(-17) };
	points[4] = { PIXEL_TO_METERS(19),PIXEL_TO_METERS(-19) };
	points[5] = { PIXEL_TO_METERS(19),PIXEL_TO_METERS(-79) };
	points[6] = { PIXEL_TO_METERS(61),PIXEL_TO_METERS(-77) };
	points[7] = { PIXEL_TO_METERS(57),PIXEL_TO_METERS(73) };
	points[8] = { PIXEL_TO_METERS(17),PIXEL_TO_METERS(78) };
	points[9] = { PIXEL_TO_METERS(20),PIXEL_TO_METERS(16) };
	points[10] = { PIXEL_TO_METERS(-25),PIXEL_TO_METERS(13) };
	points[11] = { PIXEL_TO_METERS(-9),PIXEL_TO_METERS(72) };

	chain.CreateLoop(points, 12);

	ch->CreateFixture(&ChainFixture);
}
// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// TODO 5: Move all creation of bodies on 1,2,3 key press here in the scene
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		App->physics->CreateCircles();
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		// TODO 1: When pressing 2, create a box on the mouse position

		App->physics->CreateRectangles();
		// TODO 2: To have the box behave normally, set fixture's density to 1.0f

	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		App->physics->CreateChains();
		// TODO 3: Create a chain shape using those vertices
		// remember to convert them from pixels to meters!
		/*
		int points[24] = {
			-38, 80,
			-44, -54,
			-16, -60,
			-16, -17,
			19, -19,
			19, -79,
			61, -77,
			57, 73,
			17, 78,
			20, 16,
			-25, 13,
			-9, 72
		};
		*/
	}
	// TODO 7: Draw all the circles using "circle" texture

	return UPDATE_CONTINUE;
}
