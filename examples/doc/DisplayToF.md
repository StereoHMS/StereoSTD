# DisplayToF Sample

## Overview

本コードサンプルはインスタンスの一部です。このサンプルではSDKのコードスニペットでカメラにアクセスし、ToF画像を表示する方法とボタンを使用した制御でToFの各モードを設定する方法について説明します。
a     Turn 640*480      
s     Turn 320*240    
d     FILTER off      
f     FILTER on       
g  TOF_IMAGE_FLIP off  
h  TOF_IMAGE_FLIP on   
j  TOF_IMAGE_MIRROR on 
k  TOF_IMAGE_MIRROR off 
l  Set _EXPOSURE   300 
w  Set _EXPOSURE   1000
e  Set _EXPOSURE   000 
q -Quit-       		  
## Expected Output
実行成功すると、TOFの疑似カラー画面が表示され、と同時に、TOFの基本機能ボタンと説明も表示されます。
<p align="center"><img src="/examples/doc/img/DisplayToF1.png" width="100%" /><br><br></p>
Switch 320*240
<p align="center"><img src="/examples/doc/img/DisplayToF2.png" width="100%" /><br><br></p>
Filter on
<p align="center"><img src="/examples/doc/img/DisplayToF3.png" width="100%" /><br><br></p>
Filter off
<p align="center"><img src="/examples/doc/img/DisplayToF4.png" width="100%" /><br><br></p>
Filp off
<p align="center"><img src="/examples/doc/img/DisplayToF5.png" width="100%" /><br><br></p>
Filp on
<p align="center"><img src="/examples/doc/img/DisplayToF6.png" width="100%" /><br><br></p>
Mirror on 
<p align="center"><img src="/examples/doc/img/DisplayToF7.png" width="100%" /><br><br></p>
Mirror off
<p align="center"><img src="/examples/doc/img/DisplayToF8.png" width="100%" /><br><br></p>
Set exposure 300
<p align="center"><img src="/examples/doc/img/DisplayToF9.png" width="100%" /><br><br></p>
Set exposure 1000
<p align="center"><img src="/examples/doc/img/DisplayToF10.png" width="100%" /><br><br></p>
Set exposure 0
<p align="center"><img src="/examples/doc/img/DisplayToF11.png" width="100%" /><br><br></p>
## Code Overview

初めに、SDKのヘッダーファイルとOpenCVを参照する必要があります。
```cpp
#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<thread>
#include <stdlib.h>
#include <stdio.h>
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
Step 4：デプスデータを取得して表示します。
```cpp
while (!quit)
	{
		sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);
		sy3::depth_frame *depth_frame = frameset->get_depth_frame();
		sy3::ir_frame *ir_frame = frameset->get_ir_frame();
		if (depth_frame == nullptr)
		{
			//	printf("depth_frame:empty \n");
		}
		else
		{
			//	printf("depth_frame:%d \n", depth_frame);
			show_depth_frame(depth_frame, DEPTH_WINDOW_NAME);			
		}
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
デプス疑似カラー画像を表示する方法
```cpp
     uint8_t* depth_color = depth_frame->apply_colormap();
     cv::Mat yuvImg(depth_frame->get_height(), depth_frame->get_width(), CV_8UC3, depth_color);
```
ToF IR画像を表示する方法
```cpp
    cv::Mat gray16(frame->get_height(), frame->get_width(), CV_16UC1, frame->get_data());
	cv::Mat tmp;
	cv::Mat gray8 = cv::Mat::zeros(gray16.size(), CV_8U);
	cv::normalize(gray16, tmp, 0, 255, cv::NORM_MINMAX);
	cv::convertScaleAbs(tmp, gray8);
	cv::namedWindow(name, cv::WINDOW_NORMAL);
	cv::imshow(name, gray8); 
```
解像度を設定する方法
```cpp
    //640*480
        pline->stop(e);
		cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_DEPTH, 640, 480, e);
		cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_IR, 640, 480, e);
		pline->start(cfg, e);
     //320*240
        pline->stop(e);
		cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_DEPTH, 320, 240, e);
		cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_IR, 320, 240, e);
		pline->start(cfg, e);
```
TOF filterを設定する方法 
```cpp
    uint16_t filter_on = 1;
	uint16_t filter_off = 0;
	dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_DEPTH_IMAGE_FILTER, filter_on, e);
    dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_DEPTH_IMAGE_FILTER, filter_off, e);
```
ToF画面とTOF_IMAGE_FLIPを設定する方法
```cpp
    //Off：
    dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_TOF_IMAGE_FLIP, 0, e);
    //On：
    dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_TOF_IMAGE_FLIP, 1, e);
```
ミラーモードを設定する方法
```cpp
    //Off：
    dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_TOF_IMAGE_MIRROR, 0, e);
    //On：
    dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_TOF_IMAGE_MIRROR, 1, e);
```
露光時間を設定する方法（firmware は NO AEのバージョンの場合）
```cpp
    dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_EXPOSURE, 露出値, e);
```