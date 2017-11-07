//SDL_err_ext.c

#include <SDL2/SDL.h>
#include <string.h>
#include "SDL_err_ext.h"

void __dead2
SDL_errx(
	int eval,
	const char *fmt,
	...)
{
	va_list ap;
	va_start(ap, fmt);

	SDL_LogMessageV(SDL_LOG_CATEGORY_ERROR,
		SDL_LOG_PRIORITY_ERROR, fmt, ap);

	va_end(ap);
	exit(eval);
}

void __dead2
SDL_err(
	int eval,
	const char *fmt,
	...)
{
	va_list ap;
	char b[1024];

	va_start(ap, fmt);
	vsprintf(b, "%s", ap);
	va_end(ap);
	SDL_errx(eval, "%s%s%s", SDL_GetError(), (strlen(b)==0)?"":": ", b);
}

void __dead2
SDL_die(void)
{
	SDL_err(1, NULL);
}
