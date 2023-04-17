#!/bin/bash
# Create a video from our teams data sources.
# Usage: bash create_video.bash start_time end_time video_length framerate
./frame_maker 1607055843 1607401443 30 3
#ffmpeg -f image2 -framerate 3 -i "%d.png" output.avi
#rm *.png
