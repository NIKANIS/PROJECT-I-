#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 12

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleScenePaoPao;
class ModuleSceneIntro;
class ModulePlayer;
class ModuleFadeToBlack;
class Module;
class ModuleAudio;
class ModuleParticles;
class ModuleLifeBar;
class ModulePlayerScore;

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
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleParticles* particles;
	ModuleLifeBar* lifebar;
	ModulePlayerScore* plscore;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__