//tile.h
//

#ifndef _TILE_H_
#define _TILE_H_

#include <stdlib.h>
#include <SDL2/SDL.h>

typedef
enum __attribute__((packed)) _mark {
	tile_blank = 0,
	tile_x,
	tile_o
} mark_t;

typedef
struct _box {
	uint32_t x1;
	uint32_t y1;
	uint32_t x2;
	uint32_t y2;
} box_t;

typedef
struct _tile {
	mark_t content;
	box_t box;
} tile_t;
#define tile_sz (sizeof(tile_t))

__BEGIN_DECLS
SDL_Rect*	box_to_rect __P((box_t *,SDL_Rect *)) __pure;
SDL_Rect*	tile_to_rect __P((tile_t *,SDL_Rect *)) __pure;
__END_DECLS

#endif /* !_TILE_H_ */

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
