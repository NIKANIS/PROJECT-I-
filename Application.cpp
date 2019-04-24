#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleScenePaoPao.h"
#include "ModuleSceneIntro.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleLifeBar.h"
#include "ModulePlayerScore.h"
#include "ModuleFightTimer.h"
#include "ModuleFightManager.h"
#include "ModuleCollision.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = scene_intro = new ModuleSceneIntro();
	modules[5] = scene_paopao = new ModuleScenePaoPao();
	modules[6] = player = new ModulePlayer(0);
	modules[7] = enemy = new ModulePlayer(1);
	modules[8] = fade = new ModuleFadeToBlack();
	modules[9] = audio = new ModuleAudio();
	modules[10] = particles = new ModuleParticles();
	modules[11] = lifebar = new ModuleLifeBar(0);
	modules[12] = lifebar2 = new ModuleLifeBar(1);
	modules[13] = plscore = new ModulePlayerScore(0);
	modules[14] = enscore = new ModulePlayerScore(1);
	modules[15] = fight_timer = new ModuleFightTimer();
	modules[16] = fight_manager = new ModuleFightManager();
	modules[17] = collision = new ModuleCollision();
	
	
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Player will be enabled on the first update of a new scene
	player->Disable();
	enemy->Disable();
	scene_paopao->Disable();
	lifebar->Disable();
	lifebar2->Disable();
	plscore->Disable();
	enscore->Disable();
	fight_timer->Disable();
	fight_manager->Disable();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}