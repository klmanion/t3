//pt.c
//

#include "pt.h"

#include <err.h>

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
