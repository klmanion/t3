//field.c
//

#include <err.h>
#include "field.h"

field_t*
field_generate(
	dim_t dim,
	field_t *f)
{
	tile_t ***ts = NULL;

	if (dim == USE_FIELD_DIMS) {
		if (f)
			dim = f->dim;
		else
			errx(1, "No dimensions set");
	}

	if (!f)
		f = (field_t *)malloc(field_sz);
	else if (!f->tileset)
		errx(1, "This field has already been initiallized");

	ts = (tile_t ***)malloc(sizeof(tile_t **) * dim); //z-axis
	if (!ts) errx(1, "Malloc failure");
	for (size_t i=0; i<dim; ++i) {
		ts[i] = (tile_t **)malloc(sizeof(tile_t *) * dim); //y-axis
		if (!ts[i]) errx(1, "Malloc failure");
		for (size_t j=0; j<dim; ++j) {
			ts[i][j] = (tile_t *)malloc(tile_sz * dim); //x-axis
			if (!ts[i][j]) errx(1, "Malloc failure");
			for (size_t k=0; k<dim; ++k)
				ts[i][j][k] = tile_blank; //indiv. tile
		}
	}

	f->dim = dim;
	f->tileset = ts;
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
