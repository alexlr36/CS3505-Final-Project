overlay_images: ffmpeg_overlay_images.cpp
utils: ffmpeg_utils.cpp
	g++ -o create_frame ffmpeg_overlay_images.cpp ffmpeg_utils.cpp  `pkg-config --cflags --libs libavformat libavcodec libswscale libavutil libavfilter`
