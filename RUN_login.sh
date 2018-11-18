uvcdynctrl -v -d video0 --set='Focus, Auto' 0
LD_LIBRARY_PATH=/usr/local/lib mjpg_streamer -i "input_opencv.so -d 0" -o "output_http.so -w /usr/local/www -p 8877"
