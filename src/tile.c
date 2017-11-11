//tile.c
//

#include "tile.h"

#include <err.h>

SDL_Rect* __pure
box_to_rect(
	box_t *box,
	SDL_Rect *rect)
{
	if (!box) {
		warnx("uninitiallized box passed to box_to_rect: %s, %d",
			__FILE__, __LINE__);
		return NULL;
	}

	if (!rect)
		rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));

	rect->x = box->x1;
	rect->y = box->y1;
	rect->w = rect->h = box->x2 - box->x1;

	return rect;
}

SDL_Rect* __pure
tile_to_rect(
	tile_t *tile,
	SDL_Rect *rect)
{
	return box_to_rect(&tile->box, rect);
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
