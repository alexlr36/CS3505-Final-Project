/* Utilities for reading, scaling, and writing images using FFmpeg.
 * 
 * Carter Morgan
 * 11/25/2020
 */
 
#include "ffmpeg_utils.h"
#include <iostream>
#include <fstream>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

AVFrame *read_image_from_file(const char *filename) {
  AVFormatContext *format_context = NULL;
  if (avformat_open_input(&format_context, filename, NULL, NULL) < 0) {
    std::cout << "Failed to open file: " << filename << std::endl;
    return NULL;
  }

  AVCodecParameters *codec_params = format_context->streams[0]->codecpar;

  AVCodec *codec = avcodec_find_decoder(codec_params->codec_id);
  if (codec == NULL) {
    std::cout << "Couldn't find codec" << std::endl;
    return NULL;
  }

  AVCodecContext *codec_context = avcodec_alloc_context3(codec);
  if (avcodec_open2(codec_context, codec, NULL) < 0) {
    std::cout << "Failed to open codec context" << std::endl;
    return NULL;
  }

  AVPacket *packet = av_packet_alloc();
  AVFrame *frame = av_frame_alloc();
  if (packet == NULL || frame == NULL) {
    std::cout << "Failed to allocate packet/frame" << std::endl;
    return NULL;
  }

  if (av_read_frame(format_context, packet) < 0) {
    std::cout << "Failed to read packet from file" << std::endl;
    return NULL;
  }
  if (avcodec_send_packet(codec_context, packet) < 0) {
    std::cout << "Failed to send packet" << std::endl;
    return NULL;
  }
  if (avcodec_receive_frame(codec_context, frame) < 0) {
    std::cout << "Failed to receive frame" << std::endl;
    return NULL;
  }

  av_packet_free(&packet);
  avcodec_free_context(&codec_context);
  avformat_close_input(&format_context);
  
  return frame;
}

AVFrame *scale_image(const AVFrame *frame, int width, int height, AVPixelFormat pix_fmt) {
  AVFrame *output_frame = av_frame_alloc();
  if (output_frame == NULL) {
    std::cout << "Failed to allocate output frame" << std::endl;
    return NULL;
  }
  
  output_frame->width = width;
  output_frame->height = height;
  output_frame->format = pix_fmt;
  if (av_frame_get_buffer(output_frame, 0) < 0) {
    std::cout << "Failed to allocate output frame buffer" << std::endl;
    return NULL;
  }
  
  SwsContext *scale_context =
    sws_getContext(frame->width, frame->height, (AVPixelFormat)frame->format,
		   width, height, pix_fmt,
		   SWS_BICUBIC, NULL, NULL, NULL);
  if (scale_context == NULL) {
    std::cout << "Failed to allocate scaling context" << std::endl;
    return NULL;
  }
  
  sws_scale(scale_context,
	    frame->data, frame->linesize, 0, frame->height,
	    output_frame->data, output_frame->linesize);

  sws_freeContext(scale_context);
  return output_frame;
}

void write_image_to_file(const AVFrame *frame,  const char *filename,
			 const char * encoder_name, AVPixelFormat pix_fmt) {
  AVCodec *codec = avcodec_find_encoder_by_name(encoder_name);
  if (codec == NULL) {
    std::cout << "Failed to find encoder" << std::endl;
    return;
  }

  AVCodecContext *codec_context = avcodec_alloc_context3(codec);
  if (codec_context == NULL) {
    std::cout << "Failed to allocate codec context" << std::endl;
    return;
  }

  codec_context->pix_fmt = pix_fmt;
  codec_context->width = frame->width;
  codec_context->height = frame->height;
  codec_context->time_base.num = 1;
  codec_context->time_base.den = 1;

  if (avcodec_open2(codec_context, codec, NULL) < 0) {
    std::cout << "Failed to open codec context" << std::endl;
    return;
  }

  AVPacket *packet = av_packet_alloc();
  if (packet == NULL) {
    std::cout << "Failed to allocate packet" << std::endl;
    return;
  }

  if (avcodec_send_frame(codec_context, frame) < 0) {
    std::cout << "Failed to send frame to encoder" << std::endl;
    return;
  }
  if (avcodec_receive_packet(codec_context, packet) < 0 ) {
    std::cout << "Failed to receive packet from encoder" << std::endl;
    return;
  }

  std::ofstream output_file(filename);
  output_file.write((const char *)packet->data, packet->size);
  output_file.close();

  avcodec_free_context(&codec_context);
  av_packet_free(&packet);
}