//main.c
//

#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <getopt.h>
#include <sysexits.h>
#include <ctype.h>
#include <err.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "dimensions.h"
#include "field.h"
#include "SDL_err_ext.h"

#include "../config.h"

#define SDL_CWAR SDL_CreateWindowAndRenderer

#define window_flags SDL_WINDOW_SHOWN

const char *const optstring = "d:";

const struct option longopts[] = {
	{ "dimensions",	required_argument,	NULL,	'd' },
	{ NULL, 0, NULL, 0 }
};

SDL_Window *window = NULL;
SDL_Renderer *R = NULL;

void	usage(const char *) __dead2;

int
main(
	int argc,
	char *const argv[])
{
	extern int opterr, optopt, optind;
	extern char *optarg;
	char ch;
	const char *const basename = argv[0];
	int debuf, running;
	SDL_Event e;
	time_t t0;
	field_t *field = NULL;
	dim_t dim;

	opterr = 0;
	debuf = running = 1;
	srand((unsigned int)time(&t0));
	dim = DEFAULT_DIM;

	while ((ch = getopt_long(argc, argv, optstring, longopts, NULL)) != -1)
	{
		switch (ch) {
		case 'd':
			dim = (dim_t)abs(atoi(optarg));
			break;;
		case '?':
		default:
			if (isprint(optopt))
				warnx("unknown option `-%c'", optopt);
			else
				warnx("unknown option code %#x", (unsigned int)optopt);
			usage(basename);
		}
	}
	argc -= optind;
	argv += optind;

	if (argc > 0)
		warnx("extraneous arguments passed to program");

	field_generate(dim, &field);

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

void __dead2
usage(
	const char *basename)
{
	fprintf(stderr, "%s [-d dimensions]\n", basename);
	exit(EX_USAGE);
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
