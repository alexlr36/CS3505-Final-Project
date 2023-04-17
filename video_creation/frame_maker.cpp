#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "ffmpeg_utils.h"
#include "drawing_utils.h"
#include "data_source.h"

const char *BACKGROUND_PATH = "background/background.png";
const AVFrame *BACKGROUND = read_image_from_file(BACKGROUND_PATH);
const AVPixelFormat PIXEL_FORMAT = AV_PIX_FMT_RGB24;

data_source data_DEVIN("/mnt/efs/fs1/DevinFiles");
data_source data_ALEX("/mnt/efs/fs1/AlexFiles");
data_source data_ALLAN("/mnt/efs/fs1/AllanFiles");
data_source data_JAVIER("/mnt/efs/fs1/JavierFiles");
data_source data_CARTER("/mnt/efs/fs1/xkcd");
data_source data_JINGSHI("/mnt/efs/fs1/JingshiFiles");

/*
 * Retrieve the data, scale it to fit in its given area, and overlay it onto the background.
 */
void overlay_data(AVFrame *bg, std::string fg_path, int x, int y, int max_scale) {
	if (fg_path == "NO DATA")
		return;
	
	AVFrame *foreground = read_image_from_file(fg_path.c_str());
	
	// Scale the foreground image to fit in its given area.
	double height = foreground->height;
	double width = foreground->width;
	if (height > max_scale) {
		double ratio = (double)max_scale / height;
		height *= ratio;
		width *= ratio;
	}
	if (width > max_scale) {
		double ratio = (double)max_scale / width;
		height *= ratio;
		width *= ratio;
	}
	AVFrame *scaled_fg = scale_image(foreground, (int)width, (int)height, PIXEL_FORMAT);
	
	overlay_image(bg, scaled_fg, x, y);
	
	av_frame_free(&scaled_fg);
	av_frame_free(&foreground);
}

/*
 * Generate a frame with data from all of our data sources
 */
void generate_frame(long frame_time, int frame_number) {
	AVFrame *scaled_bg = scale_image(BACKGROUND, 1000, 1000, PIXEL_FORMAT);
	
	overlay_data(scaled_bg, data_ALLAN.find_closest_data_to_timestamp(frame_time), 77, 77, 250);
	overlay_data(scaled_bg, data_ALEX.find_closest_data_to_timestamp(frame_time), 673, 77, 250);
	overlay_data(scaled_bg, data_JAVIER.find_closest_data_to_timestamp(frame_time), 77, 370, 250);
	overlay_data(scaled_bg, data_JINGSHI.find_closest_data_to_timestamp(frame_time), 673, 370, 250);
	overlay_data(scaled_bg, data_CARTER.find_closest_data_to_timestamp(frame_time), 77, 663, 250);
	overlay_data(scaled_bg, data_DEVIN.find_closest_data_to_timestamp(frame_time), 673, 663, 250);

	std::string frame_name = std::to_string(frame_number) + ".png";	
	write_image_to_file(scaled_bg, frame_name.c_str(), "png", PIXEL_FORMAT);
	av_frame_free(&scaled_bg);
	
/*
	char time_string[30];
	if (std::strftime(time_string, 30, "%c", std::gmtime((time_t*)&frame_time)) != 0) {
		std::string command = "ffmpeg -i temp.png -filter drawtext=text=\"" + (time_string + ("\":x=350:y=500 " + frame_name));
		std::cout << command << std::endl;
		std::system(command.c_str());
	}
*/
}

int main(int argc, char * argv[])
{
	//make_frames start_time end_time video_lenth framerate
	if (argc != 5) {
		std::cout << "Usage: frame_maker start_time (unix time)end_time " <<
		"(unix_time) video_lenth (seconds) framerate (fps)" << std::endl;
		return -1;
	}
	
	long start_time = std::strtol(argv[1], NULL, 10);
	long end_time = std::strtol(argv[2], NULL, 10);
	int run_time = (int)std::strtol(argv[3], NULL, 10);
	int framerate = (int)std::strtol(argv[4], NULL, 10);
	
	// The total number of frames to generate
	int number_of_frames = run_time * framerate;
	
	// The time difference between frames
	double time_step = (double)(end_time - start_time) / number_of_frames;

	for (int i = 0; i < number_of_frames; i++) {
		long curr_time = start_time + (long)(time_step*i);
		generate_frame(curr_time, i);
	}
}
