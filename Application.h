#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 28

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleSceneNeoGeoIntro;
class ModuleSceneIntro;
class ModuleSceneChoosePlayer;
class ModuleSceneMap;
class ModuleSceneCongrats;
class ModuleSceneGameOver;
class ModuleScenePaoPao;
class ModuleSceneWestSubway;
class ModuleSceneHowardArena;
class ModuleSceneSoundBeach;
class ModulePlayer;
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
	ModuleSceneWestSubway* scene_westsubway;
	ModuleSceneSoundBeach* scene_soundbeach;
	ModuleSceneHowardArena* scene_howardarena;
	ModuleSceneNeoGeoIntro* scene_neogeo;
	ModuleSceneIntro* scene_intro;
	ModuleSceneChoosePlayer* scene_chooseplayer;
	ModuleSceneMap* scene_map;
	ModuleSceneCongrats* scene_congrats;
	ModuleSceneGameOver* scene_gameover;
	ModulePlayer* player;
	ModulePlayer* enemy;
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
	bool Restart();

};

extern Application* App;

#endif // __APPLICATION_H__