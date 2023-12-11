//field.h
//

#ifndef _FIELD_H_
#define _FIELD_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "tile.h"
#include "defs.h"

typedef
struct _field {
	tile_t	***tileset;
	dim_t	dim;
	double	height;
	double	side_len;
	double	theta;	//board_angle
} field_t;
#define field_sz (sizeof(field_t))

__BEGIN_DECLS
field_t*	field_generate (dim_t,field_t **);
field_t*	field_free (field_t *);

field_t*	field_clear (field_t *const) __pure;

double	field_tile_height (const field_t *const) __pure2;
double	field_tile_width (const field_t *const) __pure2;
double	field_diameter (const field_t *const) __pure2;
double	field_tile_diameter (const field_t *const) __pure2;

tile_t*	field_tile_at (const field_t *const,const uint32_t,const uint32_t);
bool	field_checkwin (field_t *const);

SDL_Renderer*	field_render (SDL_Renderer *const,const field_t *const);
__END_DECLS

#endif /* !_FIELD_H_ */

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
