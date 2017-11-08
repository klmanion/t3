//dimensions.h
//

#ifndef _DIMENSIONS_H_
#define _DIMENSIONS_H_

#define MIN_DIM	(2)
#define MAX_DIM (9)

#define WIDTH	(640)
#define HEIGHT	(480)

#define SIDE_MARGIN		((double)(WIDTH/8))
#define TOPBOT_MARGIN	((double)(HEIGHT/8))

#define FIELD_WIDTH		((double)(WIDTH - (2 * SIDE_MARGIN)))
#define FIELD_HEIGHT	((double)(HEIGHT - (2 * TOPBOT_MARGIN)))

#define BOARD_ANGLE	((double)60)
#define VERT_GAP	((double)10)

#endif /* !_DIMENSIONS_H_ */
