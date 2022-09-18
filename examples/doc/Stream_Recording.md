# Stream Recording Sample

## Overview

本コードサンプルはインスタンスの一部です。このサンプルではSDKのコードスニペットでカメラにアクセスし、RGBとTOFデータを保存することで、録画します。保存されたファイルはaviフォーマットです。（demoはサンプルのみ提供します。録画する時、，FPSは固定していないため、動画の長さは異なります。環境によって調整してください。）

## Expected Output
実行成功すると、’w’キーを押すと録画が開始し、‘q’キーを押すことで録画を中止できます。
<p align="center"><img src="/examples/doc/img/Stream Recording.png" width="100%" /><br><br></p>
<p align="center"><img src="/examples/doc/img/Stream Recording1.png" width="100%" /><br><br></p>
<p align="center"><img src="/examples/doc/img/Stream Recording2.png" width="100%" /><br><br></p>
## Code Overview

初めに、SDKのヘッダーファイルとOpenCVを参照する必要があります。
```cpp
#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<thread>
#include <iostream>
#include <chrono>
#include <fstream>
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
Step 4：デプスデータとRGBデータを取得します。
```cpp
    sy3::pipeline *pline = sy3::sy3_create_pipeline(ctx, e);
	sy3::config *cfg = sy3_create_config(e);
	cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_DEPTH, DEPTH_WIDTH, DEPTH_HEIGHT, e);
	cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_RGB, RGB_WIDTH, RGB_HEIGHT, e);
	pline->start(cfg, e);
```
Step 5：デプスデータを対象として録画します。
```cpp
   cv::VideoWriter writertof(savepathtof, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 8, cv::Size(640, 480));
   writertof << yuvImg;
```
Step 6：RGBデータを対象として録画します。
```cpp
    cv::VideoWriter writerrgb(savepathrgb, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 4, cv::Size(1920, 1080));
	writerrgb << rgbImg;
```
