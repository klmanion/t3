//pt.h
//

#ifndef _PT_H_
#define _PT_H_

#include <stdlib.h>
#include <stdint.h>

typedef
struct _pt {
	uint32_t	x;
	uint32_t	y;
} pt_t;

__BEGIN_DECLS
pt_t*	set_pt (pt_t *const,uint32_t,uint32_t);
__END_DECLS

#endif /* !_PT_H_ */
