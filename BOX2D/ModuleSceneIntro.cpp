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
	
	b2Vec2 pepefrog[23];
	pepefrog[0] = { PIXEL_TO_METERS(780 / 5), PIXEL_TO_METERS(843 / 5) };
	pepefrog[1] = { PIXEL_TO_METERS(568 / 5), PIXEL_TO_METERS(881 / 5) };
	pepefrog[2] = { PIXEL_TO_METERS(405 / 5), PIXEL_TO_METERS(871 / 5) };
	pepefrog[3] = { PIXEL_TO_METERS(198 / 5), PIXEL_TO_METERS(777 / 5) };
	pepefrog[4] = { PIXEL_TO_METERS(92 / 5), PIXEL_TO_METERS(676 / 5) };
	pepefrog[5] = { PIXEL_TO_METERS(92 / 5), PIXEL_TO_METERS(480 / 5) };
	pepefrog[6] = { PIXEL_TO_METERS(167 / 5), PIXEL_TO_METERS(373 / 5) };
	pepefrog[7] = { PIXEL_TO_METERS(191 / 5), PIXEL_TO_METERS(281 / 5) };
	pepefrog[8] = { PIXEL_TO_METERS(277 / 5), PIXEL_TO_METERS(196 / 5) };
	pepefrog[9] = { PIXEL_TO_METERS(433 / 5), PIXEL_TO_METERS(195 / 5) };
	pepefrog[10] = { PIXEL_TO_METERS(542 / 5), PIXEL_TO_METERS(222 / 5) };
	pepefrog[11] = { PIXEL_TO_METERS(610 / 5), PIXEL_TO_METERS(196 / 5) };
	pepefrog[12] = { PIXEL_TO_METERS(708 / 5), PIXEL_TO_METERS(195 / 5) };
	pepefrog[13] = { PIXEL_TO_METERS(820 / 5), PIXEL_TO_METERS(247 / 5) };
	pepefrog[14] = { PIXEL_TO_METERS(928 / 5), PIXEL_TO_METERS(285 / 5) };
	pepefrog[15] = { PIXEL_TO_METERS(943 / 5), PIXEL_TO_METERS(383 / 5) };
	pepefrog[16] = { PIXEL_TO_METERS(911 / 5), PIXEL_TO_METERS(468 / 5) };
	pepefrog[17] = { PIXEL_TO_METERS(852 / 5), PIXEL_TO_METERS(485 / 5) };
	pepefrog[18] = { PIXEL_TO_METERS(922 / 5), PIXEL_TO_METERS(560 / 5) };
	pepefrog[19] = { PIXEL_TO_METERS(927 / 5), PIXEL_TO_METERS(627 / 5) };
	pepefrog[20] = { PIXEL_TO_METERS(867 / 5), PIXEL_TO_METERS(658 / 5) };
	pepefrog[21] = { PIXEL_TO_METERS(911 / 5), PIXEL_TO_METERS(696 / 5) };
	pepefrog[22] = { PIXEL_TO_METERS(898 / 5), PIXEL_TO_METERS(765 / 5) };

	chain.CreateLoop(pepefrog, 23);

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
