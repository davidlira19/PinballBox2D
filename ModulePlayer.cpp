#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"

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
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		App->renderer->Blit(grandeizq, 145, 818,0,1.0f,(0,-50),10,15);
		App->renderer->Blit(pequenaizq, 137, 730, 0, 1.0f, (0, -50),10,15);
	
	}
	else 
	{
		App->renderer->Blit(grandeizq, 145, 818);
		App->renderer->Blit(pequenaizq, 137, 730);
	}

	//RIGHT BARS TEXTURES
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		App->renderer->Blit(grandeder, 240, 818, 0, 1.0f, (0, 50), 50, 5);
		App->renderer->Blit(pequenader, 271, 730, 0, 1.0f, (0, 50), 50, 15);
	}
	else
	{
		App->renderer->Blit(grandeder, 240, 818);
		App->renderer->Blit(pequenader, 275, 730);
	}

	
	return UPDATE_CONTINUE;
}



