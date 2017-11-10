//main.c
//

#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <err.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "dimensions.h"
#include "field.h"
#include "SDL_err_ext.h"

#include "../config.h"

#define SDL_CWAR SDL_CreateWindowAndRenderer

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
	field_t *field = NULL;
	
	debuf = running = 1;
	srand((unsigned int)time(&t0));
	field_generate(3, &field);

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
			case SDL_KEYUP:
				debuf = 1;
				break;;
			case SDL_QUIT:
				running = 0;
				break;;
			}
		}
		SDL_Delay(100);
		SDL_SetRenderDrawColor(R, 0x0, 0x0, 0x0, 0xFF);
		SDL_RenderClear(R);
		field_render(R, field);
		SDL_RenderPresent(R);
	}

	/* SDL cleanup */
	SDL_DestroyRenderer(R); R=NULL;
	SDL_DestroyWindow(window); window=NULL;

	SDL_VideoQuit();
	SDL_Quit();

	/* generic cleanup */
	field = field_free(field);

	return EXIT_SUCCESS;
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
