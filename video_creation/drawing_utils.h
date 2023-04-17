/*
 * Utilities for drawing on AVFrames.
 *
 * Carter Morgan
 * 11/30/2020
 */

#ifndef DRAWING_UTILS
#define DRAWING_UTILS

#include "ffmpeg_utils.h"

/*
 * Represents an RGB color value.
 */
typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb24_color;

/* ***WARNING***
 * This is a bit buggy and may change. Use with caution.
 *
 * Map an integer value from the source range to the destination range.
 * eg. mapping 6 from 0-10 to 0-100 yields 60.
 */
int map(int val, int src_lower, int src_size, int dest_lower, int dest_size);

/*
 * Overlay the foreground image over the background image. x and y represent the
 * coordinates of the top left corner of the foreground image.
 */
void overlay_image(AVFrame *bg, AVFrame *fg, int x, int y);

/*
 * Attempt to set the color of the pixel at the given coordinates to the given color.
 * If the given coordinates are outside the bounds of the frame, nothing is done.
 */
void try_write_pixel(AVFrame *frame, int x, int y, rgb24_color color);

/*
 * Draw a rectangle of the given size and color with its top left corner at the given
 * coordinates.
 */
void rectangle(AVFrame *frame, int x, int y, int width, int height, rgb24_color color);

/*
 * Draw a line of the given color from (x1,y1) to (x2,y2). x1 must be less than or
 * equal to x2.
 */
void line(AVFrame *frame, int x1, int y1, int x2, int y2, rgb24_color color);

#endif