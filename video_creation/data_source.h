// Safeguard against multiple inclusions of this file
#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H

#include<iostream>
#include<string>
#include<vector>

struct data_point
{
	long unixTime;
	std::string filePath;
};

class data_source
{

	private:
	
	std::vector<data_point> dataPoints;
	std::string folderPath;
	
	// Builds the data points for this data source
	void build_data_points();

  public:
  // Constructors
  data_source();
  data_source(std::string folderPath);

	// Finds the closest data source to the given time (in unix time) and returns the filepath
	std::string find_closest_data_to_timestamp(long time);
	
	
};

#endif
