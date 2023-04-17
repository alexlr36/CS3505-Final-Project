#include <cmath>
#include "drawing_utils.h"

int map(int val, int src_lower, int src_size, int dest_lower, int dest_size) {
  val -= src_lower;
  val *= (dest_size);
  val /= (src_size);
  return val + dest_lower;
}

void overlay_image(AVFrame *bg, AVFrame *fg, int x, int y) {
  for (int i = 0; i < fg->width; i++) {
    for (int j = 0; j < fg->height; j++) {
      int pixel_r_index = i*3 + j*fg->linesize[0];
      rgb24_color pixel = {fg->data[0][pixel_r_index],
                           fg->data[0][pixel_r_index + 1],
                           fg->data[0][pixel_r_index + 2]};
      try_write_pixel(bg, x + i, y + j, pixel);
    }
  }
}

void try_write_pixel(AVFrame *frame, int x, int y, rgb24_color color) {
  if (-1 < x && x < frame->width && -1 < y && y < frame->height) {
    int pixel_r_index = x*3 + y*frame->linesize[0];
    frame->data[0][pixel_r_index + 0] = color.r;
    frame->data[0][pixel_r_index + 1] = color.g;
    frame->data[0][pixel_r_index + 2] = color.b;
  }
}

void rectangle (AVFrame *frame, int x, int y, int width, int height, rgb24_color color) {
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++)
      try_write_pixel(frame, x + i, y + j, color);
}

void line(AVFrame *frame, int x1, int y1, int x2, int y2, rgb24_color color) {
  int x_relative = 0; // values of x & y relative to x1 & y1.
  int y_relative = 0;

  int dx = x2 - x1;
  int dy = y2 - y1;
  int slope_sign = dy / std::abs(dy);

  while (x_relative <= dx) {  
    try_write_pixel(frame, x1 + x_relative, y1 + y_relative, color);

    int y_bound = dx == 0 ? dy : dy * x_relative / dx;
    while (std::abs(y_relative) < std::abs(y_bound)) {
      y_relative += slope_sign;
      try_write_pixel(frame, x1 + x_relative, y1 + y_relative, color);
    }

    x_relative++;
  }  
}