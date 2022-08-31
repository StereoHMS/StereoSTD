cmake_minimum_required(VERSION 3.4.1)

project("examples")

set(TARGET_NAME StereoSTD_demo)

message("configure ${TARGET_NAME}")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
 
	message("current platform: Linux ")
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/Linux64)

	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../examples/third-party/opencv-4.4.0/include)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../examples/third-party/opencv-4.4.0/lib/Linux64/shared)
 
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
 
	message("current platform: Windows ")
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/x64)

	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third-party/opencv-4.4.0/include)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/third-party/opencv-4.4.0/lib/x64/shared)
 
else()
 
	message("current platform: unkonw ")
 
endif()





if(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
  set(OpenCV_LIBS 
    opencv_core440
    opencv_imgproc440
    opencv_imgcodecs440
    opencv_highgui440
    opencv_videoio440
    opencv_calib3d440)
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
set(OpenCV_LIBS 
    opencv_core
    opencv_imgproc
    opencv_imgcodecs
    opencv_highgui
    opencv_videoio
    opencv_calib3d)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -fopenmp")


if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
 
	add_executable(depth STD_depth.cpp)
	target_link_libraries(depth  PRIVATE synexens3 ${OpenCV_LIBS})
	set_property(TARGET depth PROPERTY FOLDER Samples)


	add_executable(rgb STD_rgb.cpp)
	target_link_libraries(rgb  PRIVATE synexens3 ${OpenCV_LIBS})
	set_property(TARGET rgb PROPERTY FOLDER Samples)


	add_executable(align STD_align.cpp)
	target_link_libraries(align  PRIVATE synexens3 ${OpenCV_LIBS})
	set_property(TARGET align PROPERTY FOLDER Samples)


	add_executable(pointcloud STD_pointcloud.cpp)
	target_link_libraries(pointcloud  PRIVATE synexens3 ${OpenCV_LIBS})
	set_property(TARGET pointcloud PROPERTY FOLDER Samples)
 
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
 
	add_executable(depth STD_depth.cpp)
	target_link_libraries(depth  PRIVATE libsynexens3 ${OpenCV_LIBS})
	set_property(TARGET depth PROPERTY FOLDER Samples)


	add_executable(rgb STD_rgb.cpp)
	target_link_libraries(rgb  PRIVATE libsynexens3 ${OpenCV_LIBS})
	set_property(TARGET rgb PROPERTY FOLDER Samples)


	add_executable(align STD_align.cpp)
	target_link_libraries(align  PRIVATE libsynexens3 ${OpenCV_LIBS})
	set_property(TARGET align PROPERTY FOLDER Samples)


	add_executable(pointcloud STD_pointcloud.cpp)
	target_link_libraries(pointcloud  PRIVATE libsynexens3 ${OpenCV_LIBS})
	set_property(TARGET pointcloud PROPERTY FOLDER Samples)


	add_executable(STD-AutoDepth STD-AutoDepth.cpp)
	target_link_libraries(STD-AutoDepth  PRIVATE libsynexens3 ${OpenCV_LIBS})
	set_property(TARGET STD-AutoDepth PROPERTY FOLDER Samples)
 
else()
 
	message("current platform: unkonw ")
 
endif()







