#include <iostream>
#include <stdlib.h>   

#include "../video_creation/ffmpeg_utils.h"
#include "data_source.h"

// Make sure to compile using
// g++ -std=c++17 test.cpp -lstdc++fs

int main(int argc, char * argv[])
{
	// Make a data source for each data source in our set
	data_source* data_DEVIN = new data_source("/mnt/efs/fs1/DevinFiles");
	data_source* data_ALEX = new data_source("/mnt/efs/fs1/AlexFiles");
	data_source* data_ALLAN = new data_source("/mnt/efs/fs1/AllanFiles");
	data_source* data_JAVIER = new data_source("/mnt/efs/fs1/JavierFiles");
	data_source* data_CARTER = new data_source("/mnt/efs/fs1/xkcd");
	data_source* data_JINGSHI = new data_source("/mnt/efs/fs1/JingshiFiles");
	
	int time_unix = std::stoi(argv[1]);

	int time_unix_string = time_unix;
	
	// Find the file paths for the data points at this time
	std::string path_DEVIN = data_DEVIN->find_closest_data_to_timestamp((long)time_unix);
	std::string path_ALEX = data_ALEX->find_closest_data_to_timestamp((long)time_unix);
	std::string path_ALLAN = data_ALLAN->find_closest_data_to_timestamp((long)time_unix);
	std::string path_JAVIER = data_JAVIER->find_closest_data_to_timestamp((long)time_unix);
	std::string path_CARTER = data_CARTER->find_closest_data_to_timestamp((long)time_unix);
	std::string path_JINGSHI = data_JINGSHI->find_closest_data_to_timestamp((long)time_unix);
	
	// Make the background frames for each data point
<<<<<<< HEAD
	system(std::cout << "./frame_maker_program FRAME_CANVAS.png " < path_DEVIN + " 2020 1990 FRAME_" + time_unix + ".png");
	system(std::cout << "./frame_maker_program FRAME_" << time_unix_string << ".png " << path_ALEX << " 2020 230 FRAME_" << time_unix_string << ".png");
	system(std::cout << "./frame_maker_program FRAME_" << time_unix_string << ".png " << path_ALLAN << " 230 230 FRAME_" << time_unix_string << ".png");
	system(std::cout << "./frame_maker_program FRAME_" << time_unix_string << ".png " << path_JAVIER << " 230 1110 FRAME_" << time_unix_string << ".png");
	system(std::cout << "./frame_maker_program FRAME_" << time_unix_string << ".png " << path_CARTER << " 230 1990 FRAME_" << time_unix_string << ".png");
	system(std::cout << "./frame_maker_program FRAME_" << time_unix_string << ".png " << path_JINGSHI << " 2020 1110 FRAME_" << time_unix_string << ".png");
=======
	system("./frame_maker_program FRAME_CANVAS.png " + path_DEVIN + " 2020 1990 FRAME_" + time_unix + ".png");
	system("./frame_maker_program FRAME_" << time_unix << ".png " << path_ALEX << " 2020 230 FRAME_" << time_unix << ".png");
	system("./frame_maker_program FRAME_" << time_unix << ".png " << path_ALLAN << " 230 230 FRAME_" << time_unix << ".png");
	system("./frame_maker_program FRAME_" << time_unix << ".png " << path_JAVIER << " 230 1110 FRAME_" << time_unix << ".png");
	system("./frame_maker_program FRAME_" << time_unix << ".png " << path_CARTER << " 230 1990 FRAME_" << time_unix << ".png");
	system("./frame_maker_program FRAME_" << time_unix << ".png " << path_JINGSHI << " 2020 1110 FRAME_" << time_unix << ".png");
>>>>>>> 37f564260f465382a28b7cd803eff5c7f0135e52
	
}
