#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 22

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleScenePaoPao;
class ModuleSceneIntro;
class ModuleSceneCongrats;
class ModuleSceneGameOver;
class ModulePlayer;
class ModuleEnemy;
class ModuleFadeToBlack;
class Module;
class ModuleAudio;
class ModuleParticles;
class ModuleLifeBar;
class ModulePlayerScore;
class ModuleFightTimer;
class ModuleFightManager;
class ModuleCollision;
class ModuleRoundDisplay;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleScenePaoPao* scene_paopao;
	ModuleSceneIntro* scene_intro;
	ModuleSceneCongrats* scene_congrats;
	ModuleSceneGameOver* scene_gameover;
	ModulePlayer* player;
	ModuleEnemy* enemy;
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleParticles* particles;
	ModuleLifeBar* lifebar;
	ModuleLifeBar* lifebar2;
	ModulePlayerScore* plscore;
	ModulePlayerScore* enscore;
	ModuleFightTimer* fight_timer;
	ModuleFightManager* fight_manager;
	ModuleCollision* collision;
	ModuleRoundDisplay* round_pl;
	ModuleRoundDisplay* round_en;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

extern Application* App;

#endif // __APPLICATION_H__