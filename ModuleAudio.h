#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "SDL\include\SDL_rect.h"

class ModuleAudio : public Module
{
public:

	ModuleAudio();

	// Destructor
	virtual ~ModuleAudio();

	// Called before quitting
	bool Init();

	// Called before quitting
	bool CleanUp();

public:

};

#endif // __ModuleAudio_H__