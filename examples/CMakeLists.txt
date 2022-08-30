cmake_minimum_required(VERSION 3.4.1)

project("StereoSTD_demo")

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

	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third-party/pcl/3rdParty/Qhull/include)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/third-party/pcl/3rdParty/Qhull/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third-party/pcl/include/pcl-1.11)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/third-party/pcl/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third-party/pcl/3rdParty/FLANN/include)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/third-party/pcl/3rdParty/FLANN/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third-party/pcl/3rdParty/VTK/include/vtk-8.2)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/third-party/pcl/3rdParty/VTK/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third-party/pcl/3rdParty/Eigen/eigen3)
	#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/third-party/opencv-4.4.0/lib/x64/shared)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third-party/pcl/3rdParty/Boost/include/boost-1_74)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/third-party/pcl/3rdParty/Boost/lib)

 
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
 set(PCL_LIBS 
    pcl_common.lib
pcl_io.lib
pcl_filters.lib
pcl_visualization.lib
vtkChartsCore-8.2.lib
vtkCommonComputationalGeometry-8.2.lib
vtkCommonColor-8.2.lib
vtkCommonCore-8.2.lib
vtkCommonDataModel-8.2.lib
vtkCommonMath-8.2.lib
vtkCommonSystem-8.2.lib
vtkFiltersCore-8.2.lib
vtkFiltersGeneral-8.2.lib
vtkglew-8.2.lib
vtkRenderingContext2D-8.2.lib
vtkRenderingContextOpenGL2-8.2.lib
vtkRenderingCore-8.2.lib
vtkRenderingOpenGL2-8.2.lib
vtkInteractionStyle-8.2.lib
vtkViewsCore-8.2.lib
vtkIOGeometry-8.2.lib
vtkIOPLY-8.2.lib
vtkGeovisCore-8.2.lib)
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
 

	add_executable(ShowPointcloud ShowPointcloud.cpp)
	target_link_libraries(ShowPointcloud  PRIVATE libsynexens3 ${OpenCV_LIBS})
	target_link_libraries(ShowPointcloud  PRIVATE libsynexens3 ${PCL_LIBS})
	set_property(TARGET ShowPointcloud PROPERTY FOLDER Samples)
	
	
else()
 
	message("current platform: unkonw ")
 
endif()







