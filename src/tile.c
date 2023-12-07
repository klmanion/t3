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

/* TODO
 * placeholder to test clicking
 * does not faithfully compute whether a point falls within given tile
 */
bool
tile_has_pt(
	const tile_t *const	t,
	const pt_t *const	pt)
{
	return (pt->y >= t->perim.tl.y && pt->y <= t->perim.br.y)
		&& (pt->x <= t->perim.tr.x && pt->x >= t->perim.bl.x);
}

static SDL_Renderer*
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

	SDL_RenderDrawLine(R,
		t->perim.tl.x + sxm,	t->perim.tl.y + ym,
		t->perim.br.x - sxm,	t->perim.br.y - ym);
	SDL_RenderDrawLine(R,
		t->perim.tr.x - lxm,	t->perim.tr.y + ym,
		t->perim.bl.x + lxm,	t->perim.bl.y - ym);

	return R;
}

static SDL_Renderer*
tile_render_o(
	SDL_Renderer *R,
	tile_t *t)
{
	double tw,th,A,B;
	uint32_t cuts,h,k;
	parl_t *p;
	pt_t *tl,*tr,*br,*bl;
	//tile width and height
	//major and minor axii
	//cuts for one quadrant of the ellipse
	//x and y translations

	p = &t->perim;

	tw = tile_sidelen(t);
	th = tile_height(t);

	A = tw/4; //A controls width
	B = th/4;

	cuts = floor(A);

	pt_t circum[cuts*4];
	tl = &circum[0];
	tr = &circum[cuts];
	br = &circum[cuts*2];
	bl = &circum[cuts*3];

	h = lround((p->bl.x + (p->tl.x - p->bl.x)/2) + tw/2);
	k = lround(p->tl.y + th/2);

	for (int32_t x=0; x<=cuts; ++x) {
		int32_t y = lround(sqrt(pow(B,2) * (1 - pow(x,2)/pow(A,2))));
		set_pt(&tl[cuts-x],	h-x,	k-y);
		set_pt(&tr[x],		h+x,	k-y);
		set_pt(&br[cuts-x],	h+x,	k+y);
		set_pt(&bl[x],		h-x,	k+y);
	}

	for (size_t i=0; i<cuts*4; ++i)
		SDL_RenderDrawLine(R,
			circum[i].x,	circum[i].y,
			circum[i+1].x,	circum[i+1].y);
	SDL_RenderDrawLine(R,
		circum[cuts*4].x,	circum[cuts*4].y,
		circum[0].x,		circum[0].y);

	return R;
}

SDL_Renderer*
tile_render_contents(
	SDL_Renderer *R,
	tile_t *t,
	double theta)
{
	if (!t->is_win)
		SDL_SetRenderDrawColor(R, 0xFF, 0xFF, 0xFF, 0xFF);
	else
		SDL_SetRenderDrawColor(R, 0xFF, 0x0, 0x0, 0xFF);

	switch (t->content)
	{
	case tile_blank:
		return R;
	case tile_x:
		return tile_render_x(R, t, theta);
	case tile_o:
		return tile_render_o(R, t);
	default:
		warnx("attempted to render a tile with undefined contents");
		return R;
	}
}

SDL_Renderer*
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
