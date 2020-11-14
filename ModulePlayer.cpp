#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	grandeder =App->textures->Load("pinball/palancadergrande.png");
	grandeizq=App->textures->Load("pinball/palancaizqgrande.png");
	pequenaizq =App->textures->Load("pinball/palancaizqpequena.png");
	pequenader=App->textures->Load("pinball/palancaderpequena.png");
	fliper = App->audio->LoadFx("pinball/flippers_fx.wav");
	collision_fx = App->audio->LoadFx("pinball/collision.wav");
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	//LEFT BARS TEXTURES
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		App->audio->PlayFx(fliper, 0);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		
		App->renderer->Blit(grandeizq, 145, 818,0,1.0f,(0,-50),10,15);
		App->renderer->Blit(pequenaizq, 137, 730, 0, 1.0f, (0, -50),10,15);
		
		App->physics->pi->SetMotorSpeed(-15.0);
		App->physics->gi->SetMotorSpeed(-15.0);
	
	}
	else 
	{
		App->renderer->Blit(grandeizq, 145, 818);
		App->renderer->Blit(pequenaizq, 137, 730);
		App->physics->pi->SetMotorSpeed(15.0);
		App->physics->gi->SetMotorSpeed(15.0);
	}

	//RIGHT BARS TEXTURES
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		App->audio->PlayFx(fliper, 0);
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		App->renderer->Blit(grandeder, 247, 816, 0, 1.0f, (0, 50), 50, 5);
		App->renderer->Blit(pequenader, 268, 735, 0, 1.0f, (0, 50), 50, 15);
		App->physics->pd->SetMotorSpeed(15.0);
		App->physics->gd->SetMotorSpeed(15.0);
	}
	else
	{
		App->renderer->Blit(grandeder, 240, 818);
		App->renderer->Blit(pequenader, 275, 730);
		App->physics->pd->SetMotorSpeed(-15.0);
		App->physics->gd->SetMotorSpeed(-15.0);
	}

	
	return UPDATE_CONTINUE;
}



