//tile.c
//

#include "tile.h"

#include <err.h>
#include <math.h>

double __pure
tile_sidelen(
	tile_t *t)
{
	return t->perim.tr.x - t->perim.tl.x;
}

double __pure
tile_height(
	tile_t *t)
{
	return t->perim.bl.y - t->perim.tl.y;
}

/* set tile's content to blank
 * used by field_clear() */
tile_t*
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
	tile_t *t,
	double theta)
{
	double s,ms,b;
	uint32_t sxm,lxm,ym;
	//tile side_len
	//margin parallelogram side
	//base of exterior triangle
	//margin parallelogram width
	//small x margin
	//large x margin
	//y margin

	s = tile_sidelen(t);
	ms = s/4;
	b = ms * sin(M_PI_2 - 2*theta);
	sxm = (uint32_t)lround(ms - b);
	lxm = (uint32_t)lround(ms + b);
	ym = (uint32_t)lround(ms/2 * cos(M_PI_2 - 2*theta));

	SDL_SetRenderDrawColor(R, 0xFF, 0xFF, 0xFF, 0xFF);

	SDL_RenderDrawLine(R,
		t->perim.tl.x + sxm,	t->perim.tl.y + ym,
		t->perim.br.x - sxm,	t->perim.br.y - ym);
	SDL_RenderDrawLine(R,
		t->perim.tr.x - lxm,	t->perim.tr.y + ym,
		t->perim.bl.x + lxm,	t->perim.bl.y - ym);

	return R;
}

static SDL_Renderer* __pure
tile_render_o(
	SDL_Renderer *R,
	tile_t *t,
	double theta)
{
	/* FIXME */
	
	return R;
}

SDL_Renderer* __pure
tile_render_contents(
	SDL_Renderer *R,
	tile_t *t,
	double theta)
{
	switch (t->content)
	{
	case tile_blank:
		return R;
	case tile_x:
		return tile_render_x(R, t, theta);
	case tile_o:
		return tile_render_o(R, t, theta);
	default:
		warnx("attempted to render a tile with undefined contents");
		return R;
	}
}

SDL_Renderer* __pure
tileset_render_contents(
	SDL_Renderer *R,
	tile_t ***ts,
	double theta,
	dim_t dim)
{
	for (size_t i=0; i<dim; ++i)
		for (size_t j=0; j<dim; ++j)
			for (size_t k=0; k<dim; ++k)
				tile_render_contents(R, &ts[i][j][k], theta);

	return R;
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
