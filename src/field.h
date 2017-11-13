//field.h
//

#ifndef _FIELD_H_
#define _FIELD_H_

#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#include "tile.h"
#include "defs.h"

typedef
struct _field {
	tile_t	***tileset;
	dim_t	dim;
	double	height;
	double	side_len;
} field_t;
#define field_sz (sizeof(field_t))

__BEGIN_DECLS
field_t*	field_generate __P((dim_t,field_t **));
field_t*	field_free __P((field_t *));

field_t*	field_clear __P((field_t *const)) __pure;

double	field_tile_height __P((const field_t *const)) __pure2;
double	field_tile_length __P((const field_t *const)) __pure2;

SDL_Renderer*	field_render __P((SDL_Renderer *const,const field_t *const)) __pure;
__END_DECLS

#endif /* !_FIELD_H_ */

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
