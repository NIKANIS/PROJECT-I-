#include <iostream>
#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"
#include "SDL_Mixer/include/SDL_mixer.h"


#pragma comment (lib, "SDL/SDL2main.lib")
#pragma comment (lib, "SDL/SDL2.lib")
#pragma comment (lib, "SDL/SDL2_image.lib")
#pragma comment (lib, "SDL/SDL2_mixer.lib")

using namespace std;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) //if SDL initializes correctly, it returns a 0. If it doesn't, it returns a 1.
	{
		SDL_Log("SDL was unable to iniatialize because %s", SDL_GetError()); //SDL_Log is like a print_f, and SDL_GetError gives the error of why that happens
		return 1; // to finish the program.
	}


	SDL_Window *window = SDL_CreateWindow("windowtest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 620, 480, 0); //PREGUNTA:::: perque 0? que fa SDL_WINDOW_OPENGL? (estava en el codi d'exemple)
	//PREGUNTA::::perque el punter ha de ser de class SDL_Window? que fa aquest punter?
	if (window == NULL)
	{
		SDL_Log("Window was unable to be created because %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0); //Aquí crea el renderer.
	
	if (renderer == NULL)
	{
		SDL_Log("Renderer was unable to be created because %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	int Imageflags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted1 = IMG_Init(Imageflags);
	if ((initted1&Imageflags) != Imageflags) {
		
		SDL_Log("IMG_Init: Failed to init required jpg and png support because %s", SDL_GetError());
		SDL_Quit();
		return 1;
		// handle error
	}
	int Audioflags = MIX_INIT_OGG | MIX_INIT_MOD;
	int initted2 = Mix_Init(Audioflags);
	if (initted2&Audioflags != Audioflags) {
		printf("Mix_Init: Failed to init required ogg and mod support!\n");
		printf("Mix_Init: %s\n", Mix_GetError());
		// handle error
	}	
	if (SDL_Init(SDL_INIT_AUDIO) == -1) {
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}
	// open 44.1KHz, signed 16bit, system byte order,
	//      stereo audio, using 1024 byte chunks
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}
	int moveright = 1;

	SDL_Texture* background = nullptr;
	background = IMG_LoadTexture(renderer, "Assets/background.png");

	SDL_Rect backrect;
	backrect.x = 0;
	backrect.y = 0;
	backrect.w = 620;
	backrect.h = 480;

	if (background == NULL)
	{
		SDL_Log("Couldn't load image because %s", SDL_GetError());
		SDL_Quit();
		return 1;
		// handle error
	}

	SDL_Texture* weapon = nullptr;
	weapon = IMG_LoadTexture(renderer, "Assets/m4.png");

	SDL_Rect rectangle;
	rectangle.x = 200; //posicio de X
	rectangle.y = 170; //posicio de Y
	rectangle.w = 200; //width del rectangle
	rectangle.h = 100; //height del rectangle

	SDL_Texture* bullet = nullptr;
	bullet = IMG_LoadTexture(renderer, "Assets/bullet.png");

	SDL_Rect bulletr;
	bulletr.x = 75;
	bulletr.y = 0;
	bulletr.w = 30; //width del rectangle
	bulletr.h = 20; //height del rectangle

	Mix_Chunk *Shot = Mix_LoadWAV("Assets/m4sound.wav");
	Mix_Music *backgroundM = Mix_LoadMUS("Assets/bgm.ogg");

	Mix_PlayMusic(backgroundM,-1);

	bool isRuning = true;
	while (isRuning) //aixo es el loop dels frames
	{
		

		SDL_Event event;

		SDL_RenderCopy(renderer, background, NULL,&backrect);
		SDL_RenderCopy(renderer, weapon, NULL, &rectangle);
		SDL_RenderPresent(renderer); //actualitza el renderer
		
		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.scancode == SDL_SCANCODE_A)
				{
					if (rectangle.x != 0)
					{
						rectangle.x -= 10;
					}
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_D)
				{
					if (rectangle.x != 620 - 150)
					{
						rectangle.x += 10;
					}
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_W)
				{
					if (rectangle.y != 0)
					{
						rectangle.y -= 10;
					}
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_S)
				{
					if (rectangle.y != 480 - 100)
					{
						rectangle.y += 10;
					}
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				{

					bulletr.x = rectangle.x + 200;
					bulletr.y = rectangle.y + 27;
					SDL_RenderCopy(renderer, bullet, NULL, &bulletr);
					Mix_PlayChannel(-1, Shot, 0);
					SDL_RenderPresent(renderer); //actualitza el renderer
					
					

					while (bulletr.x != 1000)
					{
						bulletr.x += 2;

						SDL_RenderCopy(renderer, background, NULL, &backrect);
						SDL_RenderCopy(renderer, weapon, NULL, &rectangle);
						SDL_RenderCopy(renderer, bullet, NULL, &bulletr);
						SDL_RenderPresent(renderer); //actualitza el renderer
					}
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					isRuning = false;
				}

			}
			if (event.type == SDL_QUIT)
			{
				isRuning = false;
			}
		}
	}
	//Free the surfaces
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(renderer); //destruir el renderer per estalviar memoria suposo
	SDL_DestroyWindow(window); //destruir la finestra
	SDL_Quit();
	return 0;
}