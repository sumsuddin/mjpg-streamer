uvcdynctrl -v -d video0 --set='Focus, Auto' 0
LD_LIBRARY_PATH=/usr/local/lib mjpg_streamer -i "input_file.so -f /mnt/ramdisk -n img_logout.jpg" -o "output_http.so -w /usr/local/www -p 8889"
