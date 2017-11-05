//main.c
//

#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <err.h>

#include <SDL2/SDL.h>
//#include <SDL2_image/SDL_image.h>

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
	if (SDL_Init(1) < 0)
		SDL_die();

	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);
	
	//ser texture filling to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		warnx("Linear texture filtering not enabled!");

	if (SDL_CWAR(WIDTH, HEIGHT, window_flags, &window, &R)!=0)
		SDL_die();

	return EXIT_SUCCESS;
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
