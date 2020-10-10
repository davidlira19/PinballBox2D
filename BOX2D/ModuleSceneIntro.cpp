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

	/*
	b2Vec2 pepefrog[41];
	pepefrog[0] = { PIXEL_TO_METERS(86 / 5), PIXEL_TO_METERS(586 / 5) };
	pepefrog[1] = { PIXEL_TO_METERS(39 / 5), PIXEL_TO_METERS(541 / 5) };
	pepefrog[2] = { PIXEL_TO_METERS(16 / 5), PIXEL_TO_METERS(462 / 5) };
	pepefrog[3] = { PIXEL_TO_METERS(23 / 5), PIXEL_TO_METERS(402 / 5) };
	pepefrog[4] = { PIXEL_TO_METERS(61 / 5), PIXEL_TO_METERS(362 / 5) };
	pepefrog[5] = { PIXEL_TO_METERS(109 / 5), PIXEL_TO_METERS(238 / 5) };
	pepefrog[6] = { PIXEL_TO_METERS(145 / 5), PIXEL_TO_METERS(210 / 5) };
	pepefrog[7] = { PIXEL_TO_METERS(205 / 5), PIXEL_TO_METERS(112 / 5) };
	pepefrog[8] = { PIXEL_TO_METERS(275 / 5), PIXEL_TO_METERS(55 / 5) };
	pepefrog[9] = { PIXEL_TO_METERS(364 / 5), PIXEL_TO_METERS(50 / 5) };
	pepefrog[10] = { PIXEL_TO_METERS(433 / 5), PIXEL_TO_METERS(72 / 5) };
	pepefrog[11] = { PIXEL_TO_METERS(452 / 5), PIXEL_TO_METERS(98 / 5) };
	pepefrog[12] = { PIXEL_TO_METERS(553 / 5), PIXEL_TO_METERS(56 / 5) };
	pepefrog[13] = { PIXEL_TO_METERS(617 / 5), PIXEL_TO_METERS(65 / 5) };
	pepefrog[14] = { PIXEL_TO_METERS(660 / 5), PIXEL_TO_METERS(121 / 5) };
	pepefrog[15] = { PIXEL_TO_METERS(662 / 5), PIXEL_TO_METERS(147 / 5) };
	pepefrog[16] = { PIXEL_TO_METERS(739 / 5), PIXEL_TO_METERS(199 / 5) };
	pepefrog[17] = { PIXEL_TO_METERS(754 / 5), PIXEL_TO_METERS(223 / 5) };
	pepefrog[18] = { PIXEL_TO_METERS(774 / 5), PIXEL_TO_METERS(245 / 5) };
	pepefrog[19] = { PIXEL_TO_METERS(766 / 5), PIXEL_TO_METERS(259 / 5) };
	pepefrog[20] = { PIXEL_TO_METERS(770 / 5), PIXEL_TO_METERS(281 / 5) };
	pepefrog[21] = { PIXEL_TO_METERS(757 / 5), PIXEL_TO_METERS(293 / 5) };
	pepefrog[22] = { PIXEL_TO_METERS(751 / 5), PIXEL_TO_METERS(309 / 5) };
	pepefrog[23] = { PIXEL_TO_METERS(733 / 5), PIXEL_TO_METERS(315 / 5) };
	pepefrog[24] = { PIXEL_TO_METERS(706 / 5), PIXEL_TO_METERS(341 / 5) };
	pepefrog[25] = { PIXEL_TO_METERS(671 / 5), PIXEL_TO_METERS(355 / 5) };
	pepefrog[26] = { PIXEL_TO_METERS(681 / 5), PIXEL_TO_METERS(386 / 5) };
	pepefrog[27] = { PIXEL_TO_METERS(713 / 5), PIXEL_TO_METERS(419 / 5) };
	pepefrog[28] = { PIXEL_TO_METERS(730 / 5), PIXEL_TO_METERS(465 / 5) };
	pepefrog[29] = { PIXEL_TO_METERS(740 / 5), PIXEL_TO_METERS(469 / 5) };
	pepefrog[30] = { PIXEL_TO_METERS(743 / 5), PIXEL_TO_METERS(489 / 5) };
	pepefrog[31] = { PIXEL_TO_METERS(724 / 5), PIXEL_TO_METERS(509 / 5) };
	pepefrog[32] = { PIXEL_TO_METERS(708 / 5), PIXEL_TO_METERS(513 / 5) };
	pepefrog[33] = { PIXEL_TO_METERS(703 / 5), PIXEL_TO_METERS(542 / 5) };
	pepefrog[34] = { PIXEL_TO_METERS(669 / 5), PIXEL_TO_METERS(562 / 5) };
	pepefrog[35] = { PIXEL_TO_METERS(602 / 5), PIXEL_TO_METERS(609 / 5) };
	pepefrog[36] = { PIXEL_TO_METERS(546 / 5), PIXEL_TO_METERS(630 / 5) };
	pepefrog[37] = { PIXEL_TO_METERS(537 / 5), PIXEL_TO_METERS(646 / 5) };
	pepefrog[38] = { PIXEL_TO_METERS(413 / 5), PIXEL_TO_METERS(677 / 5) };
	pepefrog[39] = { PIXEL_TO_METERS(223 / 5), PIXEL_TO_METERS(648 / 5) };
	pepefrog[40] = { PIXEL_TO_METERS(86 / 5), PIXEL_TO_METERS(586 / 5) };

	chain.CreateLoop(pepefrog, 41);*/

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
