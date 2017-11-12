//tile.c
//

#include "tile.h"

#include <err.h>
#include <math.h>

pt_t* __pure
set_pt(
	pt_t *const pt,
	uint32_t x,
	uint32_t y)
{
	if (!pt)
		errx(1, "unallocated pt_t * sent to set_pt: %s, %d",
			__FILE__, __LINE__);

	pt->x = x;
	pt->y = y;

	return pt;
}

/* set tile's content to blank
 * used by field_clear() */
tile_t* __pure
tile_clear(
	tile_t *const t)
{
	if (t)
		t->content = tile_blank;
	return t;
}

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
