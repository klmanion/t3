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
	double a,b,fwp,tw,smp,th,tbmp;
	// height of each board
	// base of the paralellogram's complementary triangle
	// field width proper
	// tile width
	// side margin proper - used for centering
	// tile height
	// top-bot margin proper
	tile_t ***ts = NULL;
	field_t *f = NULL;

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

	double fpx[dim+1][dim+1]; //field points x-coordinates

	a = (FIELD_HEIGHT - (VERT_GAP * (dim - 1))) / dim;
	b = a / tan(BOARD_ANGLE);
	th = a / dim;
	tw = th / tan(BOARD_ANGLE);
	fwp = tw * dim;
	smp = (WIDTH - (b + fwp)) / 2;

	for (size_t i=0; i<dim+1; ++i) {
		//double bi = b - (b * ((double)i / (double)dim));
		double bi = (a * ((double)(dim-i) / (double)dim)) / tan(BOARD_ANGLE);
		fpx[i][0] = (smp - tw/2) + bi;
		for (size_t j=1; j<dim+1; ++j)
			fpx[i][j] = fpx[i][j-1] + tw;
	}

	double fpy[dim][dim+1];

	tbmp = (HEIGHT - (th * dim * dim + VERT_GAP * (dim-1))) / 2;

	for (size_t i=0; i<dim; ++i) {
		fpy[i][0] = tbmp + (a + VERT_GAP) * i;
		for (size_t j=1; j<dim+1; ++j)
			fpy[i][j] = fpy[i][j-1] + th;
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
				ts[i][j][k].box.x1 = (uint32_t)floor(fpx[j][k]);
				ts[i][j][k].box.y1 = (uint32_t)floor(fpy[i][j]);
				ts[i][j][k].box.x2 = (uint32_t)floor(fpx[j][k+1]);
				ts[i][j][k].box.y2 = (uint32_t)floor(fpy[i][j+1]);
			}
		}
	}

	f->tileset = ts;
	f->dim = dim;
	f->tile_width = tw;
	f->tile_height = th;
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

SDL_Renderer*
field_render(
	SDL_Renderer *R,
	field_t *f)
{
	tile_t ***ts = NULL;

	ts = f->tileset;

	SDL_SetRenderDrawColor(R, 0xFF, 0xFF, 0xFF, 0xFF);

	//vertical or diagonal lines
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

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
