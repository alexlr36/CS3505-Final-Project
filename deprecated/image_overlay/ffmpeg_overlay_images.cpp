/*
Courtesy of Peter Jensen
The videos on the creation and explanation of this code are in Media Gallery on Canvas
*/

#include<iostream>
#include<fstream>

extern "C" {
  #include <libavformat/avformat.h>
  #include <libavcodec/avcodec.h>
  #include <libavutil/imgutils.h>
  #include <libswscale/swscale.h>
  //#include <libavfilter/drawutils.h>
};

#include"ffmpeg_utils.h"

int main(int argc, char * argv[]) {

  if (argc != 6) {
    std::cout<< "Usage: Overlays the second image atop the first, with the given x and y offset, into an output file of png format with the given name such as:" << std::endl;
		std::cout<< "./frame_maker_program back.jpg front.png 100 200 output.png" << std::endl;
    return 2;
  }
  
  AVFrame *frame;

  frame = read_image_from_file(argv[1]);

  if (frame == NULL) {
    std::cout << "MAIN: Could not open file, bailing..." <<std::endl;
    return 1;
  }

	
	// This is all manipulation of the image
  /////////////////////
  AVFrame* topFrame = read_image_from_file(argv[2]);
	
	// Scale the image to 750x750
	topFrame = scale_image(topFrame, 750, 750, topFrame->format);
  
  int xOffset = std::stoi(argv[3]), yOffset = std::stoi(argv[4]), b;

  for (int x = xOffset; x < topFrame->width+xOffset; x++)
    for (int y = yOffset; y < topFrame->height+yOffset; y++)
      for (b = 0; b < 3; b++) {
	frame->data[0][y*frame->linesize[0]+x*3 + b] = topFrame->data[0][y*topFrame->linesize[0]-yOffset*topFrame->linesize[0]+x*3-xOffset*3 + b];  
  }
  
  /////////////////////

	write_image_to_file(frame, argv[5]);
}
