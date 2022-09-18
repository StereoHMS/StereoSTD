# Spatial Alignment Sample

## Overview

本コードサンプルはインスタンスの一部です。このサンプルではSDKのコードスニペットでカメラにアクセスし、デプスデータを処理することで、点群データを取得し、RGB、ToFデータを表示する方法、そしてRGBDデータにフュージョンする方法について紹介します。

## Expected Output
実行成功すると、RGBDインターフェイスで取得したToFデータとRGBデータ、および位置合わせ後の画像は、「p」キーを押すことで現在のディレクリで保存されます。
<p align="center"><img src="/examples/doc/img/Spatial Alignment.png" width="100%" /><br><br></p>
<p align="center"><img src="/examples/doc/img/Spatial Alignment1.png" width="100%" /><br><br></p>

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
RGBDを取得する方法
```cpp
   sy3::frameset *set = engine->align_to_rgb(depth, rgb, e);
```

