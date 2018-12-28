#ifndef DIPS_H_INCLUDED_
#define DIPS_H_INCLUDED_

#include "Constants.h"
#include "Image.h"
/* change color image to black & white */
//void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* edge detection */
/* Shuffle the image */
IMAGE *BlackNWhite(IMAGE *image);
IMAGE *Edge(IMAGE *image);
IMAGE *Shuffle(IMAGE *image);









#endif /* DIPS_H_INCLUDED_ */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
