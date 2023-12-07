//tile.h
//

#ifndef _TILE_H_
#define _TILE_H_

#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>

typedef
enum __attribute__((packed)) _mark {
	tile_blank = 0,
	tile_x,
	tile_o
} mark_t;

typedef
struct _pt {
	uint32_t	x;
	uint32_t	y;
} pt_t;

typedef
struct _parallelogram {
	pt_t	tl;
	pt_t	tr;
	pt_t	bl;
	pt_t	br;
} parl_t;

typedef
struct _tile {
	mark_t	content;
	parl_t	perim;
} tile_t;
#define tile_sz (sizeof(tile_t))

__BEGIN_DECLS
pt_t*	set_pt __P((pt_t *const,uint32_t,uint32_t));

tile_t*	tile_clear __P((tile_t *const));
__END_DECLS

#endif /* !_TILE_H_ */

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
