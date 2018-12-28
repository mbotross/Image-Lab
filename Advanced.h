#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_

#include "Constants.h"
#include "Image.h"
/* Adjust the brightness of an image */
/* Mirror an image horizontally */

IMAGE *Brightness(IMAGE *image, int brightness);
IMAGE *HMirror(IMAGE *image);
IMAGE *HueRotate(IMAGE *image, float angle);
IMAGE *Resize(IMAGE *image, int percentage);
IMAGE *Rotate(IMAGE *image, int option);
IMAGE *Saturate(IMAGE *image, float percent);

#endif /* ADVANCED_H_INCLUDED_ */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
