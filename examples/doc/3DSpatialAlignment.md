# 3D Spatial Alignment Sample

## Overview

本コードサンプルはインスタンスの一部です。このサンプルではSDKのコードスニペットでカメラにアクセスし、デプスデータを処理することで、点群データを取得し、RGB、ToFデータを表示する方法、そしてRGBDデータにフュージョンして表示する方法について紹介します。または、データをpoint（x,y,z,r,g,b）としてPCL画面に出力方法も紹介します。

## Expected Output
実行すると、PCL Viewerで点群データが表示されます。
<p align="center"><img src="/examples/doc/img/3D Spatial Alignment.png" width="100%" /><br><br></p>
<p align="center"><img src="/examples/doc/img/3D Spatial Alignment1.png" width="100%" /><br><br></p>

## Code Overview

初めに、SDKのヘッダーファイル、OpenCVとPCLライブラリを参照する必要があります。
```cpp
#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#ifndef PCL_NO_PRECOMPILE
#define PCL_NO_PRECOMPILE
#endif
#define _CRT_SECURE_NO_WARNINGS
#include <pcl/common/common.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/point_cloud_color_handlers.h>
#define no_init_all_deprecated
```

Step 1:データ出力を設定し、deviceを取得します。
```cpp
   sy3::sy3_error e;
	printf("version:%s \n", sy3::sy3_get_version(e));
	sy3::context *ctx = sy3::sy3_create_context(e);
	sy3::device *dev = ctx->query_device(e);
	if (e != sy3::sy3_error::SUCCESS) {
		printf("error:%d  %s \n", e, sy3::sy3_error_to_string(e));
		return 0;
	}	

```
Step 2：サポートするストリームを取得します。 
```cpp
   void print_support_format(sy3::device *dev, sy3::sy3_error &e)
    {
	std::vector<sy3::sy3_stream> support_stream = dev->get_support_stream(e);
	    for (int i = 0; i < support_stream.size(); i++)
	    {
		    printf("support stream:%s \n", sy3_stream_to_string(support_stream[i]));
		    std::vector<sy3::sy3_format> support_format = dev->get_support_format(support_stream[i], e);
		        for (int j = 0; j < support_format.size(); j++)
		        {
			        printf("\t\t support format:%d x %d \n", support_format[j].width, support_format[j].height);
	        	}
	     }
     }
```
Step 3：カメラモジュールの基本情報を取得します。
```cpp
void print_device_info(sy3::device *dev)
{
	sy3::sy3_error e;
	printf("\nUsing device 0, an %s\n", sy3::sy3_get_device_info(dev, sy3::SY3_CAMERA_INFO_NAME, e));
	printf("    Serial number: %s\n", sy3::sy3_get_device_info(dev, sy3::SY3_CAMERA_INFO_SERIAL_NUMBER, e));
	printf("    Firmware version: %s\n\n", sy3::sy3_get_device_info(dev, sy3::SY3_CAMERA_INFO_FIRMWARE_VERSION, e));
}
```
Step 4：デプスデータとRGBデータを取得して表示します。
```cpp
    while (!quit)
    {
		sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);
		sy3::depth_frame *depth_frame = frameset->get_depth_frame();
		sy3::rgb_frame *rgb_frame = frameset->get_rgb_frame();
		show_align_rgbd(depth_frame, rgb_frame, pline->get_process_engin(e));
        delete frameset;
		cv::waitKey(1);	
	}
```
初始化PCLViewer
```cpp
    viewer = boost::shared_ptr<pcl::visualization::PCLVisualizer>(new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer->initCameraParameters();
	viewer->setBackgroundColor(0, 0, 0);
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
```
RGBD ailgn後のデータを取得します。
```cpp
    sy3::frameset *set = engine->align_to_rgb(depth, rgb, e);
	sy3::depth_frame *align_depth = set->get_depth_frame();
	sy3::rgb_frame *align_rgb = set->get_rgb_frame();
```
PCLを通して点群を表示します。
```cpp
    void showPointCloud(float* coord3_ , sy3::rgb_frame *rgb,int width , int height) 
    {
    	uint8_t* piexle_rgb = (uint8_t*)rgb->get_data();
    	cv::Mat rgb_img(height, width, CV_8UC3, piexle_rgb);
    	//cv::imshow("rgb", rgb_img);
    	int m_width = width;
    	int m_height = height;
    	PointCloud<pcl::PointXYZRGB>::Ptr cloud(new PointCloud<PointXYZRGB>);
    	for (uint32_t i = 0; i < m_width * m_height; ++i) {
    		int x = 0, y = 0, z = 0;
    		if (i < m_width * 2) {
    			x = 0;
    			y = 0;
    			z = 0;
    		}
    		else {
    			x = coord3_[i * 3 + 0];
    			y = coord3_[i * 3 + 1];
    			z = coord3_[i * 3 + 2];
    		}
    		pcl::PointXYZRGB p;
    		p.x = -x;
    		p.y = -y;
    		p.z = z;
    		p.b = rgb_img.ptr<uchar>(i / m_width)[i%m_width * 3+0];
    		p.g = rgb_img.ptr<uchar>(i / m_width)[i%m_width * 3+1];
    		p.r = rgb_img.ptr<uchar>(i / m_width)[i%m_width * 3+2];
    		cloud->points.push_back(p);
    	}
    	cloud->width = cloud->points.size();
    	cloud->height = 1;
    	viewer->removeAllPointClouds();
    	viewer->removeAllShapes();
    	pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> fildColor(cloud);
    	viewer->addPointCloud<pcl::PointXYZRGB>(cloud, fildColor, "sample cloud");
    	viewer->spinOnce(100);
    }
```
