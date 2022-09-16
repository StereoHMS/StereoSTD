cmake_minimum_required(VERSION 3.4.1)
project("examples")

set(TARGET_NAME StereoSTD demo)


message("configure ${TARGET_NAME}")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/ubuntu20.04_x64)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third-party/opencv-4.4.0/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third-party/opencv-4.4.0/lib/x64/shared)


if(WIN32)
  set(OpenCV_LIBS 
    opencv_core440
    opencv_imgproc440
    opencv_imgcodecs440
    opencv_highgui440
    opencv_videoio440
    opencv_calib3d440)
set(LIBSYNEXENS3 libsynexens3)

elseif(UNIX)
set(OpenCV_LIBS 
    opencv_core
    opencv_imgproc
    opencv_imgcodecs
    opencv_highgui
    opencv_videoio
    opencv_calib3d)

set(LIBSYNEXENS3 synexens3)

endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -fopenmp")

add_executable(Capture_Save Capture_Save.cpp)
target_link_libraries(Capture_Save  PRIVATE ${LIBSYNEXENS3} ${OpenCV_LIBS})
set_property(TARGET Capture_Save PROPERTY FOLDER Samples)


add_executable(DisplayRGB DisplayRGB.cpp)
target_link_libraries(DisplayRGB  PRIVATE ${LIBSYNEXENS3} ${OpenCV_LIBS})
set_property(TARGET DisplayRGB PROPERTY FOLDER Samples)


add_executable(DisplayToF DisplayToF.cpp)
target_link_libraries(DisplayToF  PRIVATE ${LIBSYNEXENS3} ${OpenCV_LIBS})
set_property(TARGET DisplayToF PROPERTY FOLDER Samples)


add_executable(Distance Distance.cpp)
target_link_libraries(Distance  PRIVATE ${LIBSYNEXENS3} ${OpenCV_LIBS})
set_property(TARGET Distance PROPERTY FOLDER Samples)

add_executable(Hello-StereoSTD Hello-StereoSTD.cpp)
target_link_libraries(Hello-StereoSTD  PRIVATE ${LIBSYNEXENS3} ${OpenCV_LIBS})
set_property(TARGET Hello-StereoSTD PROPERTY FOLDER Samples)

add_executable(PointCloud_PCD_PLY PointCloud_PCD_PLY.cpp)
target_link_libraries(PointCloud_PCD_PLY  PRIVATE ${LIBSYNEXENS3} ${OpenCV_LIBS})
set_property(TARGET PointCloud_PCD_PLY PROPERTY FOLDER Samples)

add_executable(Spatial_Alignment Spatial_Alignment.cpp)
target_link_libraries(Spatial_Alignment  PRIVATE ${LIBSYNEXENS3} ${OpenCV_LIBS})
set_property(TARGET Spatial_Alignment PROPERTY FOLDER Samples)

add_executable(StreamRecording StreamRecording.cpp)
target_link_libraries(StreamRecording  PRIVATE ${LIBSYNEXENS3} ${OpenCV_LIBS})
set_property(TARGET StreamRecording PROPERTY FOLDER Samples)
