#include<iostream>
#include<fstream>
#include<math.h>
#include <experimental/filesystem>
#include <chrono>
#include <algorithm>

#include"data_source.h"

namespace filesystem = std::experimental::filesystem;

data_source::data_source() { // Default constructor
	folderPath = "..";
	build_data_points();
}

data_source::data_source(std::string foldPath) { // Constructor with filepath
	folderPath = foldPath;
	build_data_points();
}

// Follow the folder path and add every image file in the folder of the specific format 
// to the data points vector (using the data_point struct.) Then sort the vector.
void data_source::build_data_points() {
	
	for(const filesystem::directory_entry& p: filesystem::directory_iterator(this->folderPath)) {
		bool is_image = exists(p.status())
			&& p.path().string().find(".png") != std::string::npos
			||  p.path().string().find(".jpg") != std::string::npos;
		if ( is_image ) {
			struct data_point POINT;
			POINT.filePath = p.path().string();
			// We'll have to convert the time before putting it into the struct
			filesystem::file_time_type TIME = last_write_time(p.path());
			std::time_t point_time = decltype(TIME)::clock::to_time_t(TIME);
			POINT.unixTime = (long)point_time;
			this->dataPoints.push_back(POINT);
		}
	}
	
	// Sort the vector
	std::sort(this->dataPoints.begin(), this->dataPoints.end(), [](const data_point& lhs, const data_point& rhs) {
      return lhs.unixTime < rhs.unixTime;
   });
}


std::string data_source::find_closest_data_to_timestamp(long time){
	if (dataPoints.empty())
		return "NO DATA";

	// Binary Search
	int lower = 0;
	int upper = dataPoints.size();
	while (upper > lower) {
		int middle = (upper + lower) / 2;
		if (dataPoints.at(middle).unixTime == time)
			return dataPoints.at(middle).filePath;
		else if (dataPoints.at(middle).unixTime > time)
			upper = middle;
		else
			lower = middle + 1;
	}

	// If the search fails lower will be positioned at the
	// first list element greater than the requested value
	if (lower > 0)
		lower--;
	return dataPoints.at(lower).filePath;
}
