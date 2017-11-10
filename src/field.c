//field.c
//

#include <err.h>
#include <math.h>
#include "dimensions.h"
#include "field.h"

field_t*
field_generate(
	dim_t dim,
	field_t **field)
{
	double a,b,fwp,tw,th;
	// height of each board
	// base of the paralellogram's complementary triangle
	// field width proper
	// tile width
	// tile height
	tile_t ***ts = NULL;
	field_t *f = NULL;

	/*
	if (dim == USE_FIELD_DIMS) {
		if (field && *field)
			dim = (*field)->dim;
		else
			errx(1, "No dimensions set");
	}
	*/

	f = (field_t *)malloc(field_sz);
	if (!f) errx(1, "Malloc failure");

	if (field)
		*field = f;

	if (dim < MIN_DIM) {
		warnx("Dimensions raised to minimum");
		dim = MIN_DIM;
	}
	if (dim > MAX_DIM) {
		warnx("Dimensions floored to maximum");
		dim = MAX_DIM;
	}

	uint32_t fpx[dim+1][dim+1]; //field points x-coordinates

	a = (FIELD_HEIGHT - (VERT_GAP * (dim - 1))) / dim;
	b = a / tan(BOARD_ANGLE);
	fwp = FIELD_WIDTH - b;
	tw = fwp / dim;

	for (size_t i=0; i<dim+1; ++i) {
		double ai = a - (a * ((double)i / (double)dim));
		for (size_t j=0; j<dim+1; ++j)
			fpx[i][j] = (uint32_t)floor(SIDE_MARGIN + ai + tw * j);
	}

	uint32_t fpy[dim][dim+1];

	th = a / dim;

	for (size_t i=0; i<dim; ++i) {
		fpy[i][0] = (uint32_t)floor(TOPBOT_MARGIN + (a + VERT_GAP) * i);
		for (size_t j=1; j<dim+1; ++j)
			fpy[i][j] = (uint32_t)floor(fpy[i][j-1] + th);
	}

	ts = (tile_t ***)malloc(sizeof(tile_t **) * dim); //z-axis
	if (!ts) errx(1, "Malloc failure");
	for (size_t i=0; i<dim; ++i) {
		ts[i] = (tile_t **)malloc(sizeof(tile_t *) * dim); //y-axis
		if (!ts[i]) errx(1, "Malloc failure");
		for (size_t j=0; j<dim; ++j) {
			ts[i][j] = (tile_t *)malloc(tile_sz * dim); //x-axis
			if (!ts[i][j]) errx(1, "Malloc failure");
			for (size_t k=0; k<dim; ++k) {
				ts[i][j][k].content = tile_blank;
				ts[i][j][k].box.x1 = fpx[j][k];
				ts[i][j][k].box.y1 = fpy[i][j];
				ts[i][j][k].box.x2 = fpx[j][k+1];
				ts[i][j][k].box.y2 = fpy[i][j+1];
			}
		}
	}

	f->tileset = ts;
	f->dim = dim;
	f->tile_width = tw;
	return f;
}

field_t*
field_free(
	field_t *f)
{
	if (f) {
		if (f->tileset) {
			for (size_t i=0; i<f->dim; ++i) {
				for (size_t j=0; j<f->dim; ++j)
					free(f->tileset[i][j]);
				free(f->tileset[i]);
			}
			free(f->tileset);
		}
		free(f);
	}
	return f = NULL;
}

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

SDL_Renderer*
field_render(
	SDL_Renderer *R,
	field_t *f)
{
	tile_t ***ts = NULL;

	ts = f->tileset;

	SDL_SetRenderDrawColor(R, 0xFF, 0xFF, 0xFF, 0xFF);

	//vertical lines
	for (size_t i=0; i<f->dim; ++i)
		for (size_t j=0; j<f->dim-1; ++j)
			SDL_RenderDrawLine(R,
				ts[i][0][j].box.x2,	ts[i][0][j].box.y1,
				ts[i][f->dim-1][j].box.x2,	ts[i][f->dim-1][j].box.y2);

	//horizontal lines
	for (size_t i=0; i<f->dim; ++i)
		for (size_t j=0; j<f->dim-1; ++j)
			SDL_RenderDrawLine(R,
				ts[i][j][0].box.x1,	ts[i][j][0].box.y2,
				ts[i][j][f->dim-1].box.x2,	ts[i][j][f->dim-1].box.y2);
	
	return R;
}
