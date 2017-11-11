//field.h
//

#ifndef _FIELD_H_
#define _FIELD_H_

#include "tile.h"

#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>

typedef uint32_t dim_t;
#define dim_sz (sizeof(dim_t))

typedef
struct _field {
	tile_t	***tileset;
	dim_t	dim;
	double	height;
	double	side_len;
} field_t;
#define field_sz (sizeof(field_t))

#define USE_FIELD_DIMS (0)

__BEGIN_DECLS
field_t*	field_generate __P((dim_t,field_t **));
field_t*	field_free __P((field_t *));

double	field_tile_height __P((field_t *)) __pure2;
double	field_tile_length __P((field_t *)) __pure2;

SDL_Renderer*	field_render __P((SDL_Renderer *,field_t *));
__END_DECLS


#endif /* !_FIELD_H_ */

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
