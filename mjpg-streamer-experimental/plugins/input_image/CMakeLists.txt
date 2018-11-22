find_package(OpenCV COMPONENTS core imgproc highgui videoio)

MJPG_STREAMER_PLUGIN_OPTION(input_image "Image input plugin"
        ONLYIF OpenCV_FOUND)

enable_language(CXX)
include_directories(${OpenCV_INCLUDE_DIRS})

MJPG_STREAMER_PLUGIN_COMPILE(input_image input_image.cpp)

target_link_libraries(input_image ${OpenCV_LIBS})



