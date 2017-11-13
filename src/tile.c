//tile.c
//

#include "tile.h"

#include <err.h>
#include <math.h>

double __pure
tile_tilewidth(
	tile_t *t)
{
	return t->perim.tr.x - t->perim.tl.x;
}

double __pure
tile_tileheight(
	tile_t *t)
{
	return t->perim.bl.y - t->perim.tl.y;
}

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

static SDL_Renderer* __pure
tile_render_x(
	SDL_Renderer *R,
	tile_t *t)
{
	uint32_t dx, dy;

	dx = (uint32_t)lround(tile_tilewidth(t) / 4);
	dy = (uint32_t)lround(tile_tileheight(t) / 4);

	SDL_RenderDrawLine(R,
		t->perim.tl.x + dx,	t->perim.tl.y - dy,
		t->perim.br.x - dx,	t->perim.br.y + dy);
	SDL_RenderDrawLine(R,
		t->perim.tr.x - dx,	t->perim.tr.y - dy,
		t->perim.bl.x + dx,	t->perim.bl.y + dy);

	return R;
}

static SDL_Renderer* __pure
tile_render_o(
	SDL_Renderer *R,
	tile_t *t)
{
	/* FIXME */
	
	return R;
}

SDL_Renderer* __pure
tile_render_contents(
	SDL_Renderer *R,
	tile_t *t)
{
	switch (t->content)
	{
	case tile_blank:
		return R;
	case tile_x:
		return tile_render_x(R, t);
	case tile_o:
		return tile_render_o(R, t);
	default:
		warnx("attempted to render a tile with undefined contents");
		return R;
	}
}

SDL_Renderer* __pure
tileset_render_contents(
	SDL_Renderer *R,
	tile_t ***ts,
	dim_t dim)
{
	for (size_t i=0; i<dim; ++i)
		for (size_t j=0; j<dim; ++j)
			for (size_t k=0; k<dim; ++k)
				tile_render_contents(R, &ts[i][j][k]);

	return R;
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
