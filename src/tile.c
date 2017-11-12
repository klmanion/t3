//tile.c
//

#include "tile.h"

#include <err.h>
#include <math.h>

/* set tile's content to blank
 * used by field_clear() */
tile_t* __pure
tile_clear(
	tile_t *const t)
{
	if (t)
		t->content = tile_blank;
	return t;
}

SDL_Rect* __pure
box_to_rect(
	const box_t *const box,
	SDL_Rect *rect)
{
	if (!box) {
		errx(1, "uninitiallized box passed to box_to_rect: %s, %d",
			__FILE__, __LINE__);
	}

	if (!rect)
		rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));

	rect->x = box->x1;
	rect->y = box->y1;
	rect->w = rect->h = box->x2 - box->x1; 
	//x2 will always be greater than x1,
	//thus it is unnecessary to take the absolute value

	return rect;
}

SDL_Rect* __pure
tile_to_rect(
	const tile_t *const tile,
	SDL_Rect *rect)
{
	return box_to_rect(&tile->box, rect);
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
