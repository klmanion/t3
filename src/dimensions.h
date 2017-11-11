//dimensions.h
//

#ifndef _DIMENSIONS_H_
#define _DIMENSIONS_H_

#define MIN_DIM	((dim_t)2)
#define MAX_DIM ((dim_t)9)
#define DEFAULT_DIM ((dim_t)4)

#define WIDTH	(640)
#define HEIGHT	(480)

//these are actually the minimums
#define SIDE_MARGIN		((double)(WIDTH/8))
#define TOPBOT_MARGIN	((double)(HEIGHT/8))

#define FIELD_WIDTH		((double)(WIDTH - (2 * SIDE_MARGIN)))
#define FIELD_HEIGHT	((double)(HEIGHT - (2 * TOPBOT_MARGIN)))

#define BOARD_ANGLE	((double)60)
#define VERT_GAP	((double)10)

#endif /* !_DIMENSIONS_H_ */

/* vim: set ts=4 sw=4 noexpandtab tw=79: */
