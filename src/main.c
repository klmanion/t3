//main.c
//

#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <err.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "SDL_err_ext.h"

#define SDL_CWAR SDL_CreateWindowAndRenderer

#define HEIGHT	(480)
#define WIDTH	(640)

#define window_flags SDL_WINDOW_SHOWN

SDL_Window *window = NULL;
SDL_Renderer *R = NULL;

int
main(
	int argc,
	char *const argv[])
{
	int debuf, running;
	SDL_Event e;
	time_t t0;
	
	debuf = running = 1;
	srand((unsigned int)time(&t0));

	/* SDL initiallization */
	if (SDL_Init(1) < 0)
		SDL_die();

	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);
	
	//ser texture filling to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		warnx("Linear texture filtering not enabled!");

	if (SDL_CWAR(WIDTH, HEIGHT, window_flags, &window, &R)!=0)
		SDL_die();

	while (running) {
		while (SDL_PollEvent(&e)) {
			switch (e.type)
			{
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{

				}
				break;;
			case SDL_KEYUP
				debuf = 1;
				break;;
			case SDL_QUIT:
				running = 0;
				break;;
			}
		}
		SDL_Delay(100);
		SDL_SetRenderColor(R, (SDL_Color){0x0, 0x0, 0x0, 0xFF});
		SDL_RenderClear(R);
		//add drawing commands here
		SDL_RenderPresent(R);
	}


	/* SDL cleanup */
	SDL_DestroyRenderer(R); R=NULL;
	SDL_DestroyWindow(window); window=NULL;

	SDL_VideoQuit();
	SDL_Quit();

	return EXIT_SUCCESS;
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
