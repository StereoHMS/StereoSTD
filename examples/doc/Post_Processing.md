# Post Processingt Sample

## Overview

本コードサンプルはインスタンスの一部です。このサンプルではSDKのコードスニペットでカメラにアクセスし、OpenCVでデプスデータを処理し、“Mean filtering”、"medianblur filtering”、”Gaussian filtering“をする方法も紹介します。

## Expected Output
実行成功するとフィルター効果を加えた結果が見られます。
<p align="center"><img src="doc/img/Post Processing.png" width="100%" /><br><br></p>

## Code Overview

初めに、SDKのヘッダーファイルとOpenCVを参照する必要があります。
```cpp
#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<thread>
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
Step 4：デプスデータを取得します。
```cpp
    sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);
    sy3::depth_frame *depth_frame = frameset->get_depth_frame();
	
	if (depth_frame == nullptr)
	{
	}
	else 
	{
		show_depth_frame(depth_frame, DEPTH_WINDOW_NAME);
	}
```
Step 5：デプスデータにフィルターを加えます。
```cpp
    cv::Mat srcOpencvMean, srcOpencvmidanBlur,srcOpencvGaussian;
	uint8_t* depth_color = frame->apply_colormap();
	cv::Mat src(frame->get_height(), frame->get_width(), CV_8UC3, depth_color);
	cv::namedWindow(name, cv::WINDOW_NORMAL);
	cv::resizeWindow(name, frame->get_width(), frame->get_height());
	cv::imshow(name, src);



	cv::blur(src, srcOpencvMean,cv::Size(5, 5));
	cv::namedWindow("Mean filtering", cv::WINDOW_NORMAL);
	cv::resizeWindow("Mean filtering", frame->get_width(), frame->get_height());
	cv::imshow("Mean filtering", srcOpencvMean);



	cv::medianBlur(src, srcOpencvmidanBlur, 5);
	cv::namedWindow("medianblur ksize=5", cv::WINDOW_NORMAL);
	cv::resizeWindow("medianblur ksize=5", frame->get_width(), frame->get_height());
	cv::imshow("medianblur ksize=5", srcOpencvmidanBlur);




	cv::GaussianBlur(src, srcOpencvGaussian, cv::Size(9,9),10,20);
	cv::namedWindow("srcOpencvGaussian ksize=9", cv::WINDOW_NORMAL);
	cv::resizeWindow("srcOpencvGaussian ksize=9", frame->get_width(), frame->get_height());
	cv::imshow("srcOpencvGaussian ksize=9", srcOpencvGaussian);

```
