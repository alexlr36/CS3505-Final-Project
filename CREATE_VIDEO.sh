./create_frame 1606978740

ffmpeg -i FRAME_1606978740.png -vf "drawtext=text='Data from 11\:59 PM 12/2/2020':x=1047:y=1649:fontsize=64:fontcolor=black:fontfile=ArialCE.ttf" -c:a output_frame_0.png

./create_frame 1607065140

ffmpeg -i FRAME_1607065140.png -vf "drawtext=text='Data from 11\:59 PM 12/3/2020':x=1047:y=1649:fontsize=64:fontcolor=black:fontfile=ArialCE.ttf" -c:a output_frame_1.png

./create_frame 1607151540

ffmpeg -i FRAME_1607151540.png -vf "drawtext=text='Data from 11\:59 PM 12/4/2020':x=1047:y=1649:fontsize=64:fontcolor=black:fontfile=ArialCE.ttf" -c:a output_frame_2.png

./create_frame 1607237940

ffmpeg -i FRAME_1607237940.png -vf "drawtext=text='Data from 11\:59 PM 12/5/2020':x=1047:y=1649:fontsize=64:fontcolor=black:fontfile=ArialCE.ttf" -c:a output_frame_3.png

./create_frame 1607324340

ffmpeg -i FRAME_1607324340.png -vf "drawtext=text='Data from 11\:59 PM 12/6/2020':x=1047:y=1649:fontsize=64:fontcolor=black:fontfile=ArialCE.ttf" -c:a output_frame_4.png

ffmpeg -framerate 1/6 -i FRAME_*.png -r 25 SuperAwesomeTeam_Video.mp4