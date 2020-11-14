#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFonts.h"
ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	dead = false;
	Lifes = 3;
	Points = 0;
	maxPoints = 0;
	prevPoints = 0;
	char lookupTable_b[] = { "0123456789" };
	blancas = App->fonts->Load("pinball/letras_blancas.png", lookupTable_b, 1);
	circle = App->textures->Load("pinball/ball.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	background = App->textures->Load("pinball/pinball_fondo.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	music = App->audio->PlayMusic("pinball/spongebob_music.ogg");
	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);
	int pinball_fondo[84] = {
			95, -68,
			96, -107,
			81, -118,
			82, -133,
			107, -149,
			141, -173,
			178, -206,
			210, -233,
			253, -273,
			255, -286,
			273, -293,
			270, -339,
			270, -668,
			291, -671,
			288, -68,
			320, -68,
			322, -780,
			294, -839,
			259, -912,
			216, -961,
			151, -1006,
			82, -1025,
			17, -1015,
			-27, -990,
			-62, -960,
			-98, -906,
			-134, -851,
			-167, -796,
			-169, -581,
			-147, -553,
			-151, -299,
			-138, -290,
			-135, -278,
			-122, -261,
			-98, -238,
			-71, -215,
			-38, -186,
			4, -153,
			37, -131,
			35, -113,
			23, -107,
			23, -68
	};
	//-172, -1062
	walls.add(App->physics->CreateChain(172, 1062, pinball_fondo, 84));

	int medusa[52] = {
	180, 343,
	184, 323,
	205, 290,
	208, 258,
	193, 248,
	194, 237,
	180, 224,
	177, 205,
	187, 175,
	202, 153,
	224, 139,
	253, 133,
	278, 145,
	299, 162,
	310, 188,
	309, 212,
	295, 231,
	295, 242,
	274, 253,
	270, 273,
	269, 297,
	281, 323,
	290, 342,
	284, 357,
	258, 354,
	209, 360,
	};

	walls.add(App->physics->CreateChain(0, 0, medusa, 52));

	int coral_der[30] = {
	430, 445,
	417, 440,
	419, 390,
	410, 366,
	425, 317,
	428, 296,
	417, 262,
	425, 254,
	445, 289,
	452, 328,
	463, 343,
	463, 370,
	460, 404,
	437, 417,
	431, 435
	};

	walls.add(App->physics->CreateChain(0, 0, coral_der, 30));

	int coral_izq[30] = {
	64, 446,
	79, 437,
	78, 388,
	88, 362,
	69, 314,
	71, 275,
	81, 258,
	74, 254,
	44, 303,
	41, 323,
	31, 339,
	28, 373,
	37, 403,
	59, 416,
	63, 436
	};

	walls.add(App->physics->CreateChain(0, 0, coral_izq, 30));

	int obstaculo_der[8] = {
	289, 684,
	326, 607,
	335, 660,
	299, 693,
	};

	walls.add(App->physics->CreateChain(0, 0, obstaculo_der, 8));

	int obstaculo_izq[8] = {
	172, 689,
	180, 682,
	137, 610,
	135, 662,
	};

	walls.add(App->physics->CreateChain(0, 0, obstaculo_izq, 8));

	int pieza_der_grande[18] = {
	403, 556,
	415, 554,
	415, 738,
	403, 746,
	328, 818,
	315, 805,
	394, 732,
	404, 720,
	403, 564
	};

	walls.add(App->physics->CreateChain(0, 0, pieza_der_grande, 18));

	int pieza_izq_peq[18] = {
	91, 605,
	100, 604,
	99, 687,
	101, 695,
	132, 722,
	125, 730,
	96, 703,
	89, 687,
	91, 613
	};

	walls.add(App->physics->CreateChain(3, 0, pieza_izq_peq, 18));

	int pieza_izq_grande[18] = {
	54, 565,
	67, 565,
	69, 738,
	78, 746,
	154, 816,
	142, 830,
	65, 757,
	55, 747,
	54, 570
	};

	walls.add(App->physics->CreateChain(-4, 0, pieza_izq_grande, 18));

	int pieza_der_peq[18] = {
	325, 720,
	332, 730,
	368, 692,
	377, 678,
	374, 597,
	366, 599,
	366, 677,
	364, 685,
	330, 715
	};


	walls.add(App->physics->CreateChain(0, 0, pieza_der_peq, 18));

	walls.add(App->physics->CreateStaticCircle(142, 495, 34));

	walls.add(App->physics->CreateStaticCircle(336, 495, 34));

	//walls.add(App->physics->CreateStaticCircle(237, 575, 34));

	circles.add(App->physics->CreateCircle(485, 975, 11));

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->Blit(background, 0, 0);
	
	sprintf_s(_scoreText, 10, "%6d", Points);
	App->fonts->BlitText(180, 70, blancas, _scoreText);
	/*if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}*/

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 11));
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		/*int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		walls.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));*/
	}

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		//if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x-5, y-5, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	/*c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = walls.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}*/

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;
		if (App->physics->isDrawable == true)
		{
			App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);
		}
		

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
