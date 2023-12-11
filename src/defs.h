//defs.h
//

#ifndef _DEFS_H_
#define _DEFS_H_

#include <sys/cdefs.h>

/* TODO this should be coming from sys/cdefs.h */
#ifndef __pure
#define __pure __attribute__((pure))
#endif /* !__pure */

#include "pt.h"

typedef uint32_t dim_t;
#define dim_sz (sizeof(dim_t))

#endif /* !_DEFS_H_ */
