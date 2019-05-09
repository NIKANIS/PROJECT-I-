#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleScenePaoPao.h"
#include "ModuleSceneWestSubway.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneCongrats.h"
#include "ModuleSceneGameOver.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleLifeBar.h"
#include "ModulePlayerScore.h"
#include "ModuleFightTimer.h"
#include "ModuleFightManager.h"
#include "ModuleCollision.h"
#include "ModuleRoundDisplay.h"
#include "ModuleSceneChoosePlayer.h"
#include "ModuleSceneMap.h"
#include "ModuleJoeHigashiPlayer.h"

Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();	
	modules[i++] = scene_intro = new ModuleSceneIntro();
	modules[i++] = scene_chooseplayer = new ModuleSceneChoosePlayer();
	modules[i++] = scene_paopao = new ModuleScenePaoPao();
	modules[i++] = scene_westsubway = new ModuleSceneWestSubway();
	modules[i++] = scene_congrats = new ModuleSceneCongrats();
	modules[i++] = scene_gameover = new ModuleSceneGameOver();
	modules[i++] = scene_map = new ModuleSceneMap();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = JoeHigashiPlayer = new ModuleJoeHigashiPlayer();
	modules[i++] = enemy = new ModuleEnemy();
	modules[i++] = fade = new ModuleFadeToBlack();
	modules[i++] = audio = new ModuleAudio();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = lifebar = new ModuleLifeBar(0);
	modules[i++] = lifebar2 = new ModuleLifeBar(1);
	modules[i++] = plscore = new ModulePlayerScore(0);
	modules[i++] = enscore = new ModulePlayerScore(1);
	modules[i++] = fight_timer = new ModuleFightTimer();
	modules[i++] = fight_manager = new ModuleFightManager();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = round_pl = new ModuleRoundDisplay(0);
	modules[i++] = round_en = new ModuleRoundDisplay(1);
	
	
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
	JoeHigashiPlayer->Disable();
	enemy->Disable();
	scene_paopao->Disable();
	scene_westsubway->Disable();
	scene_congrats->Disable();
	scene_gameover->Disable();
	scene_chooseplayer->Disable();
	scene_map->Disable();
	lifebar->Disable();
	lifebar2->Disable();
	plscore->Disable();
	enscore->Disable();
	fight_timer->Disable();
	fight_manager->Disable();
	round_pl->Disable();
	round_en->Disable();

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