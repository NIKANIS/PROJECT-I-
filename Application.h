#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 11

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleSceneTerry;
class ModuleSceneHonda;
class ModulePlayer;
class ModuleFadeToBlack;
class Module;
class ModuleAudio;
class ModuleParticles;
class ModuleLifeBar;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneTerry* scene_terry;
	ModuleSceneHonda* scene_honda;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleParticles* particles;
	ModuleLifeBar* lifebar;

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