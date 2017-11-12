//field.c
//

#include "field.h"

#include <err.h>
#include <math.h>
#include "dimensions.h"

//FIXME
#include <stdio.h>

/* used by field_generate() to keep the dimensions in a sane range */
static dim_t
sanitize_dim(
	dim_t *dim)
{
	if (!dim)
		errx(1, "unallocated dim_t * sent to sanitize_dim: %s, %d",
			__FILE__, __LINE__);

	if (*dim < MIN_DIM) {
		warnx("Dimensions raised to minimum");
		*dim = MIN_DIM;
	}

	if (*dim > MAX_DIM) {
		warnx("Dimensions floored to maximum");
		*dim = MAX_DIM;
	}

	return *dim;
}

field_t*
field_generate(
	dim_t dim,
	field_t **field)
{
	double h,th,tw,s,b,smp,tbmp;
	// height of each board
	// tile height
	// tile width
	// both sides of the (square) paralellogram
	// base of the paralellogram's complementary triangle
	// side margin proper - used for centering
	// top-bot margin proper
	tile_t ***ts = NULL;
	field_t *f = NULL;

	f = (field_t *)malloc(field_sz);
	if (!f) errx(1, "Malloc failure");

	if (field)
		*field = f;

	sanitize_dim(&dim);

	double fpx[dim+1][dim+1]; //field points x-coordinates

	h = (FIELD_HEIGHT - (VERT_GAP * (dim - 1))) / dim;
	th = h / dim;
	tw = th / tan(BOARD_ANGLE);
	s = tw * dim;
	b = s * sin(M_PI_2 - 2 * BOARD_ANGLE);
	smp = (WIDTH - (s + b)) / 2;

	for (size_t i=0; i<dim+1; ++i) {
		printf("--->i=%zu\n", i);
		double hi = h * ((double)(dim+1-i) / (double)(dim+1));
		double bi = hi * tan(M_PI_2 - 2 * BOARD_ANGLE);
		fpx[i][0] = (smp - tw/2) + bi;
		printf("%f\n", fpx[i][0]);
		for (size_t j=1; j<dim+1; ++j) {
			fpx[i][j] = fpx[i][j-1] + tw;
			printf("%f\n", fpx[i][j]);
		}
	}

	double fpy[dim][dim+1]; //field points y-coordinates

	tbmp = (HEIGHT - (th * dim * dim + VERT_GAP * (dim-1))) / 2;

	for (size_t i=0; i<dim; ++i) {
		fpy[i][0] = tbmp + (th * dim + VERT_GAP) * i;
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
				ts[i][j][k].box.x1 = (uint32_t)lround(fpx[j][k]);
				ts[i][j][k].box.y1 = (uint32_t)lround(fpy[i][j]);
				ts[i][j][k].box.x2 = (uint32_t)lround(fpx[j][k+1]);
				ts[i][j][k].box.y2 = (uint32_t)lround(fpy[i][j+1]);
			}
		}
	}

	f->tileset = ts;
	f->dim = dim;
	f->height = h;
	f->side_len = s;
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

field_t* __pure
field_clear(
	field_t *const f)
{
	if (!f)
		errx(1, "unallocated field_t sent to field_clear: %s, %d",
			__FILE__, __LINE__);

	for (size_t i=0; i<f->dim; ++i)
		for (size_t j=0; j<f->dim; ++j)
			for (size_t k=0; k<f->dim; ++k)
				tile_clear(&f->tileset[i][j][k]);

	return f;
}

double __pure2
field_tile_height(
	const field_t *const f)
{
	return f->height / f->dim;
}

double __pure2
field_tile_length(
	const field_t *const f)
{
	return f->side_len / f->dim;
}

SDL_Renderer* __pure
field_render(
	SDL_Renderer *const R,
	const field_t *const f)
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

	//FIXME: DEBUG
	SDL_SetRenderDrawColor(R, 0xFF, 0x0, 0x0, 0xFF);
	for (size_t i=0; i<f->dim; ++i) {
		SDL_RenderDrawLine(R,
			ts[i][0][0].box.x1,	ts[i][0][0].box.y1,
			ts[i][f->dim-1][0].box.x1,	ts[i][f->dim-1][0].box.y2);
	}
	
	return R;
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
