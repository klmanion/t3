//field.h
//

#ifndef _FIELD_H_
#define _FIELD_H_

#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>

typedef
enum __attribute__((packed)) _mark_t {
	tile_blank = 0,
	tile_x,
	tile_o
} mark_t;

typedef
struct _box_t {
	uint32_t x1;
	uint32_t y1;
	uint32_t x2;
	uint32_t y2;
} box_t;

typedef
struct _tile_t {
	mark_t content;
	box_t box;
} tile_t;
#define tile_sz (sizeof(tile_t))

typedef uint32_t dim_t;
#define dim_sz (sizeof(dim_t))

typedef
struct _field_t {
	tile_t ***tileset;
	dim_t dim;
	double tile_width;
} field_t;
#define field_sz (sizeof(field_t))

#define USE_FIELD_DIMS (0)

__BEGIN_DECLS
field_t*	field_generate __P((dim_t,field_t **));
field_t*	field_free __P((field_t *));

SDL_Rect*	box_to_rect __P((box_t *,SDL_Rect *)) __pure;
SDL_Rect*	tile_to_rect __P((tile_t *,SDL_Rect *)) __pure;

SDL_Renderer*	field_render __P((SDL_Renderer *,field_t *));
__END_DECLS


#endif /* !_FIELD_H_ */
