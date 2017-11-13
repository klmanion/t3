//tile.h
//

#ifndef _TILE_H_
#define _TILE_H_

#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#include "defs.h"

typedef
enum __attribute__((packed)) _mark {
	tile_blank = 0,
	tile_x,
	tile_o
} mark_t;
#define mark_sz (sizeof(mark_t))

typedef
struct _parallelogram {
	pt_t	tl;
	pt_t	tr;
	pt_t	bl;
	pt_t	br;
} parl_t;
#define parl_sz (sizeof(parl_t))

typedef
struct _tile {
	mark_t	content;
	parl_t	perim;
} tile_t;
#define tile_sz (sizeof(tile_t))

__BEGIN_DECLS
double	tile_tilewidth __P((tile_t *t)) __pure;
double	tile_tileheight __P((tile_t *t)) __pure;

tile_t*	tile_clear __P((tile_t *const)) __pure;

SDL_Renderer*	tile_render_contents __P((SDL_Renderer *,tile_t *)) __pure;
SDL_Renderer*	tileset_render_contents __P((SDL_Renderer *,tile_t ***,dim_t)) __pure;
__END_DECLS

#endif /* !_TILE_H_ */

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
