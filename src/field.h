//field.h
//

#ifndef _FIELD_H_
#define _FIELD_H_

#include <stdlib.h>
#include <stdint.h>

typedef
enum __attribute__((packed)) _tile_t {
	tile_blank = 0,
	tile_x,
	tile_o
} tile_t;
#define tile_sz (sizeof(tile_t))

typedef uint32_t dim_t;
#define dim_sz (sizeof(dim_t))

typedef
struct _field_t {
	tile_t ***tileset;
	dim_t dim;
} field_t;
#define field_sz (sizeof(field_t))

#define USE_FIELD_DIMS (0)

__BEGIN_DECLS
field_t*	field_generate __P((dim_t,field_t *));
field_t*	field_free __P((field_t *));
__END_DECLS


#endif /* !_FIELD_H_ */
