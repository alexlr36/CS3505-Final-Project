a.out: ffmpeg_utils.cpp ffmpeg_utils.h drawing_utils.cpp drawing_utils.h data_source.cpp data_source.h frame_maker.cpp
	g++ $(shell pkg-config --cflags libavutil) -std=c++17 frame_maker.cpp data_source.cpp drawing_utils.cpp ffmpeg_utils.cpp  $(shell pkg-config --libs libavcodec libavformat libswscale) -lstdc++fs -o frame_maker
