#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

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
	App->renderer->Blit(grandeder, 246, 814);
	App->renderer->Blit(grandeizq, 145, 818);
	App->renderer->Blit(pequenaizq, 137, 730);
	App->renderer->Blit(pequenader, 281, 720);
	return UPDATE_CONTINUE;
}



