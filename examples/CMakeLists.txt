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
 
	
 
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
 
	add_executable(Hello-StereoSTD Hello-StereoSTD.cpp)
	target_link_libraries(Hello-StereoSTD  PRIVATE libsynexens3 ${OpenCV_LIBS})
	set_property(TARGET Hello-StereoSTD PROPERTY FOLDER Samples)


	add_executable(Distance Distance.cpp)
	target_link_libraries(Distance  PRIVATE libsynexens3 ${OpenCV_LIBS})
	set_property(TARGET Distance PROPERTY FOLDER Samples)


	add_executable(DisplayRGB DisplayRGB.cpp)
	target_link_libraries(DisplayRGB  PRIVATE libsynexens3 ${OpenCV_LIBS})
	set_property(TARGET DisplayRGB PROPERTY FOLDER Samples)


	add_executable(DisplayToF DisplayToF.cpp)
	target_link_libraries(DisplayToF  PRIVATE libsynexens3 ${OpenCV_LIBS})
	set_property(TARGET DisplayToF PROPERTY FOLDER Samples)


	add_executable(Capture_Save Capture_Save.cpp)
	target_link_libraries(Capture_Save  PRIVATE libsynexens3 ${OpenCV_LIBS})
	set_property(TARGET Capture_Save PROPERTY FOLDER Samples)
 
	add_executable(PointCloud_PCD_PLY PointCloud_PCD_PLY.cpp)
	target_link_libraries(PointCloud_PCD_PLY  PRIVATE libsynexens3 ${OpenCV_LIBS})
	set_property(TARGET PointCloud_PCD_PLY PROPERTY FOLDER Samples)
 
	add_executable(SpatialAlignment Spatial_Alignment.cpp)
	target_link_libraries(SpatialAlignment  PRIVATE libsynexens3 ${OpenCV_LIBS})
	set_property(TARGET SpatialAlignment PROPERTY FOLDER Samples)
 
	add_executable(PostProcessing PostProcessing.cpp)
	target_link_libraries(PostProcessing  PRIVATE libsynexens3 ${OpenCV_LIBS})
	set_property(TARGET PostProcessing PROPERTY FOLDER Samples)
 

	add_executable(StreamRecording StreamRecording.cpp)
	target_link_libraries(StreamRecording  PRIVATE libsynexens3 ${OpenCV_LIBS})
	set_property(TARGET StreamRecording PROPERTY FOLDER Samples)
 



	add_executable(3DSpatialAlignment Spatial_Alignment3D.cpp)
	target_link_libraries(3DSpatialAlignment  PRIVATE libsynexens3 ${OpenCV_LIBS})
	target_link_libraries(3DSpatialAlignment  PRIVATE libsynexens3 ${PCL_LIBS})
	set_property(TARGET 3DSpatialAlignment PROPERTY FOLDER Samples)
	
	
else()
 
	message("current platform: unkonw ")
 
endif()







