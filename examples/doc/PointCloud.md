# PointCloud Sample

## Overview

本コードサンプルはインスタンスの一部です。このサンプルではSDKのコードスニペットでカメラにアクセスし、デプスデータを処理することで、点群データを取得する方法について紹介します。
ここではRGBとToFがマッピングされたデータで保存を行います。その中、PCDはxyzフォーマット、PLYはRGB付きのxyz点群データです。

## Expected Output
RGBDインターフェイスで取得したToFデータとRGBデータ、および位置合わせ後の画像は、「p」キーを押すことで現在のディレクリで保存されます。
<p align="center"><img src="doc/img/PointCloud.png" width="100%" /><br><br></p>
<p align="center"><img src="doc/img/PointCloud1.png" width="100%" /><br><br></p>
pcdとplyファイルを保存する時、メモリの使用率は高いので、時間がかかります。
<p align="center"><img src="doc/img/PointCloud2.png" width="100%" /><br><br></p>
保存したファイルはmeshlabまたは pcl_viewerで確認することができます。
<p align="center"><img src="doc/img/PointCloud3.png" width="100%" /><br><br></p>
<p align="center"><img src="doc/img/PointCloud4.png" width="100%" /><br><br></p>

## Code Overview

初めに、SDKのヘッダーファイルとOpenCVを参照する必要があります。
```cpp
#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <chrono>
#include <fstream>
#include <thread>
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
Step 4：デプスデータとRGBDデータを取得して表示します。
```cpp
while (!quit)
	{
		sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);
		sy3::depth_frame *depth_frame = frameset->get_depth_frame();
		sy3::rgb_frame *rgb_frame = frameset->get_rgb_frame();
	    show_align_rgbd(depth_frame, rgb_frame, 			 pline->get_process_engin(e),&isSavePCDXYZ);
        delete frameset;
		cv::waitKey(1);	
	}
点群を取得する方法
```cpp
    sy3::sy3_error e2;
	sy3::points* points = engine->comptute_points(set->get_depth_frame(), e2);
```
PCDを保存する方法 
```cpp
    void SavePointCloudToPCD_xyz(float* coord3_, int width, int height)
    {
	    int m_width = width;
	    int m_height = height;
	    int points_len = m_width* m_height;
	    std::string pc_name = "./pointcloud_xyz" + std::to_string(getTimestamp()) + ".pcd";
	    std::ofstream fout_pc_name(pc_name);
	    fout_pc_name << "# .PCD v0.7 - Point Cloud Data file format" << std::endl;
	    fout_pc_name << "VERSION 0.7" << std::endl;
	    fout_pc_name << "FIELDS x y z" << std::endl;
	    fout_pc_name << "SIZE 4 4 4" << std::endl;
	    fout_pc_name << "TYPE F F F" << std::endl;
	    fout_pc_name << "COUNT 1 1 1" << std::endl;
	    fout_pc_name << "WIDTH " << points_len << std::endl;
	    fout_pc_name << "HEIGHT 1" << std::endl;
	    fout_pc_name << "VIEWPOINT 0 0 0 1 0 0 0" << std::endl;
	    fout_pc_name << "POINTS " << points_len << std::endl;
	    fout_pc_name << "DATA ascii" << std::endl;
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
		    fout_pc_name << -x << " " << -y << " " << z << std::endl;
    	}
	    std::cout << "Save succ" << std::endl;
    }
```
PLY点群を保存する方法
```cpp
    void SavePointCloudToPLY_rgbxyz(float* coord3_, sy3::rgb_frame *rgb, int width, int height)
    {
    	int m_width = width;
    	int m_height = height;
    	int points_len = m_width * m_height;
    	std::string pc_name = "./ply_xyzrgb" + std::to_string(getTimestamp()) + ".ply";
    	std::ofstream fout_pc_name(pc_name);
    	uint8_t* piexle_rgb = (uint8_t*)rgb->get_data();
    	cv::Mat rgb_img(height, width, CV_8UC3, piexle_rgb);
    	fout_pc_name << "ply" << std::endl;
    	fout_pc_name << "format ascii 1.0" << std::endl;
    	fout_pc_name << "element vertex " << points_len << std::endl;
    	fout_pc_name << "property float x" << std::endl;
    	fout_pc_name << "property float y" << std::endl;
    	fout_pc_name << "property float z" << std::endl;
    	fout_pc_name << "property uchar red" << std::endl;
    	fout_pc_name << "property uchar green" << std::endl;
    	fout_pc_name << "property uchar blue" << std::endl;
    	fout_pc_name << "element face 0" << std::endl;
    	fout_pc_name << "property list uchar int vertex_index" << std::endl;
    	fout_pc_name << "end_header" << std::endl;
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
    		/*pcl::PointXYZRGB p;
    		p.x = -x;
    		p.y = -y;
    		p.z = z;
    		p.b = rgb_img.ptr<uchar>(i / m_width)[i%m_width * 3 + 0];
    		p.g = rgb_img.ptr<uchar>(i / m_width)[i%m_width * 3 + 1];
    		p.r = rgb_img.ptr<uchar>(i / m_width)[i%m_width * 3 + 2];*/
    		fout_pc_name << -x << " " << -y << " " << z <<" "<< 		 (float)rgb_img.ptr<uchar>(i / m_width)[i%m_width * 3 + 2]<<" "<< (float)rgb_img.ptr<uchar>(i / m_width)[i%m_width * 3 + 1]<<" "<< (float)rgb_img.ptr<uchar>(i / m_width)[i%m_width * 3 + 0] << std::endl;
    	}
    	std::cout << "Save succ" << std::endl;
    }
```
