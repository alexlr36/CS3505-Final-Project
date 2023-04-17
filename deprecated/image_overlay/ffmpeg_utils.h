/* Utilities for reading, scaling, and writing images using FFmpeg.
 * 
 * Carter Morgan
 * 11/25/2020
 */

#ifndef FFMPEG_UTILS
#define FFMPEG_UTILS

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

/* Read from the given image file and return the decoded frame.
 * Return NULL if the image can't be decoded. Returned frame must
 * be deallocated with av_frame_free.
 */
AVFrame *read_image_from_file(const char *filename);

/* Scale the provided frame to the given width and height, and
 * convert the pixel format of the image to pix_fmt. Return the
 * scaled frame or NULL on failure. Returned frame must be deallocated
 * with av_frame_free.
 */
AVFrame *scale_image(const AVFrame *frame, int width, int height, AVPixelFormat pix_fmt);

/* Encode and write the given frame to a file using the encoder specified.
 */
void write_image_to_file(const AVFrame *frame, const char *filename,
                         const char *encoder_name, AVPixelFormat pix_fmt);

#endif
