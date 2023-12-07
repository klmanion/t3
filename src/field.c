//field.c
//

#include "field.h"

#include <err.h>
#include <math.h>
#include "dimensions.h"

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
		// With n increments, at increment i the length will be
		// i/(n-1), where i is zero-indexed.
		// Here, n=dim+1.
		double si = s * ((double)(dim-i) / (double)(dim));
		double bi = si * sin(M_PI_2 - 2 * BOARD_ANGLE);
		fpx[i][0] = (smp - tw/2) + bi;
		for (size_t j=1; j<dim+1; ++j)
			fpx[i][j] = fpx[i][j-1] + tw;
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
				tile_t *t = &ts[i][j][k];
				t->content = tile_blank;
				t->is_win = false;
				set_pt(&t->perim.tl,	fpx[j][k],		fpy[i][j]);
				set_pt(&t->perim.tr,	fpx[j][k+1],	fpy[i][j]);
				set_pt(&t->perim.bl,	fpx[j+1][k],	fpy[i][j+1]);
				set_pt(&t->perim.br,	fpx[j+1][k+1],	fpy[i][j+1]);
			}
		}
	}

	f->tileset = ts;
	f->dim = dim;
	f->height = h;
	f->side_len = s;
	f->theta = BOARD_ANGLE;
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
field_tile_width(
	const field_t *const f)
{
	return f->side_len / f->dim;
}

double __pure2
field_diameter(
	const field_t *const f)
{
	return f->side_len / cos(f->theta);
}

double __pure2
field_tile_diameter(
	const field_t *const f)
{
	return field_tile_width(f) / cos(f->theta);
}

/** check_line()
 * 		Given a starting position, and increments for each dimension,
 * 		determine whether all traversed tiles have the same mark.
 */
static	bool
check_line(
	tile_t			***ts,
	uint32_t		   x0,
	uint32_t		   y0,
	uint32_t		   z0,
	uint32_t		   xd,
	uint32_t		   yd,
	uint32_t		   zd,
	uint32_t		   len)
{
	uint32_t x,y,z;
	mark_t mark;

	x = x0;
	y = y0;
	z = z0;
	mark = ts[z][y][x].content;

	if (mark == tile_blank)
		return false;

	for (size_t ct=1; ct<len; ++ct)
		{
			x += xd;
			y += yd;
			z += zd;

			if (ts[z][y][x].content != mark)
				return false;
		}

	return true;
}

static	bool
win_line(
	tile_t			***ts,
	uint32_t		   x0,
	uint32_t		   y0,
	uint32_t		   z0,
	uint32_t		   xd,
	uint32_t		   yd,
	uint32_t		   zd,
	uint32_t		   len)
{
	bool retv;

	if ((retv=check_line(ts, x0,y0,z0, xd,yd,zd, len)))
		{
			uint32_t x,y,z;

			x = x0;
			y = y0;
			z = z0;

			for (size_t ct=0; ct<len; ++ct, x+=xd,y+=yd,z+=zd)
				ts[z][y][x].is_win = true;		
		}	
	return retv;
}

/** field_checkwin()
 * 		Checks if given field contains a winning line.
 * 		Shall update tile's is_win member variable accordingly.
 */
bool
field_checkwin(
	field_t *const	f)
{
	for (size_t i=0; i<f->dim; ++i)	/* z-grid */
		{
			for (size_t j=0; j<f->dim; ++j)	/* y-axis */
				{
					if (win_line(f->tileset, 0,j,i, 1,0,0, f->dim))
						return true;
				}

			for (size_t j=0; j<f->dim; ++j)
				{
					if (win_line(f->tileset, j,0,i, 0,1,0, f->dim))
						return true;
				}
		}

	if (win_line(f->tileset, 0,0,0, 1,1,1, f->dim))
		return true;

	if (win_line(f->tileset, f->dim-1,0,0, -1,1,1, f->dim))
		return true;

	if (win_line(f->tileset, 0,f->dim-1,0, 1,-1,1, f->dim))
		return true;

	if (win_line(f->tileset, f->dim-1,f->dim-1,0, -1,-1,1, f->dim))
		return true;

	return false;
}

tile_t*
field_tile_at(
	const field_t *const	f,
	const uint32_t			x,
	const uint32_t			y)
{
	pt_t pt;

	pt.x = x;
	pt.y = y;

	for (size_t i=0; i<f->dim; ++i)
		for (size_t j=0; j<f->dim; ++j)
			for (size_t k=0; k<f->dim; ++k)
				if (tile_has_pt(&f->tileset[i][j][k], &pt))
					return &f->tileset[i][j][k];

	return (tile_t *)NULL;
}

SDL_Renderer*
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
				ts[i][0][j].perim.tr.x,
				ts[i][0][j].perim.tr.y,
				ts[i][f->dim-1][j].perim.br.x,
				ts[i][f->dim-1][j].perim.br.y);

	//horizontal lines
	for (size_t i=0; i<f->dim; ++i)
		for (size_t j=0; j<f->dim-1; ++j)
			SDL_RenderDrawLine(R,
				ts[i][j][0].perim.bl.x,
				ts[i][j][0].perim.bl.y,
				ts[i][j][f->dim-1].perim.br.x,
				ts[i][j][f->dim-1].perim.br.y);
/*
	//DEBUG: redline
	SDL_SetRenderDrawColor(R, 0xFF, 0x0, 0x0, 0xFF);
	for (size_t i=0; i<f->dim; ++i) {
		SDL_RenderDrawLine(R,
			ts[i][0][0].perim.tl.x,
			ts[i][0][0].perim.tl.y,
			ts[i][f->dim-1][0].perim.bl.x,
			ts[i][f->dim-1][0].perim.bl.y);
	}

	//DEBUG: blueline
	SDL_SetRenderDrawColor(R, 0x00, 0x00, 0xFF, 0xFF);
	for (size_t i=0; i<f->dim; ++i) {
		for (size_t j=0; j<f->dim; ++j) {
			SDL_RenderDrawLine(R,
				ts[i][j][0].perim.tl.x,
				ts[i][j][0].perim.tl.y,
				ts[i][j][0].perim.bl.x,
				ts[i][j][0].perim.bl.y);
		}
	}
*/

	//tile contents
	tileset_render_contents(R, ts, f->theta, f->dim);

	return R;
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
