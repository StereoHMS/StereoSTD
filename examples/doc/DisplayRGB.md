# DisplayRGB Sample

## Overview

本コードサンプルはインスタンスの一部です。このサンプルではSDKのコードスニペットでカメラにアクセスし、RGBのソースデータを取得する方法について説明します。DisplayRGBはカラーデータストリームを読み取ることでカメラのカラーフレームデータ情報をプリントします。
			  
## Expected Output
実行するとRGBの画面（1920*1080）が表示されます。
<p align="center"><img src="/examples/doc/img/DisplayRGB.png" width="100%" /><br><br></p>

## Code Overview

初めに、SDKのヘッダーファイルとOpenCVを参照する必要があります。
```cpp
#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
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
Step 4：RGBデータを取得して表示します。
```cpp
while (!quit)
	{
		sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);
		sy3::rgb_frame *rgb_frame = frameset->get_rgb_frame();
		show_rgb_nv12_frame(rgb_frame, RGB_WINDOW_NAME);
		delete frameset;
		cv::waitKey(1);
	}
```
フレームレートを計算する方法
```cpp
void calculate_framerate()
{
	while (g_is_start)
	{
		double cur_time = cv::getTickCount() / cv::getTickFrequency() * 1000;
		if (cur_time - g_last_time > 1000)
		{
			g_fps = g_frame_count;
			g_frame_count = 0;
			g_last_time = cur_time;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
```
RGB画像を表示する方法
```cpp
        cv::Mat yuvImg(frame->get_height() * 3 / 2, frame->get_width(), CV_8UC1, frame->get_data());
		cv::Mat rgbImg(frame->get_height(), frame->get_width(), CV_8UC3);
		cv::cvtColor(yuvImg, rgbImg, cv::ColorConversionCodes::COLOR_YUV2BGR_NV12);
		cv::namedWindow(name, cv::WINDOW_NORMAL);
		cv::imshow(name, rgbImg);
```