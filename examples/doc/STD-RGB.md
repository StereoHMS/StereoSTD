# STD-DisplayRGB Sample

## Overview

本コードサンプルはインスタンスの一部です。このサンプルではSDKのコードスニペットでカメラにアクセスし、RGBのソースデータを取得する方法について説明します。
STD-rgbがカラーデータストリームを読み取ることでカメラのカラーフレームデータ情報をプリントします。 
			  
## Expected Output

実行するとウインドウでRGBの画面が表示されます。
<p align="center"><img src="doc/img/rgb.png" width="100%" /><br><br></p>

## Code Overview

初めに、SDKのヘッダーファイルとOpenCV依存ライブラリを参照する必要があります。
```cpp
#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
```

Step 1: データの出力の設定とデバイスの取得。
```cpp
    sy3::sy3_error e;
	printf("version:%s \n", sy3::sy3_get_version(e));
    //コンテキストの作成
	sy3::context *ctx = sy3::sy3_create_context(e);
    //デバイスの取得
	sy3::device *dev = ctx->query_device(e);
	if (e != sy3::sy3_error::SUCCESS) {
		printf("error:%s \n", sy3::sy3_error_to_string(e));
		return 0;
	}
```
Step 2：pipelineを作成します。
```cpp
    sy3::pipeline *pline = sy3::sy3_create_pipeline(ctx, e);
```
Step 3：データストリームをコンフィグします。
```cpp
    sy3::config *cfg = sy3_create_config(e);
    cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_RGB, RGB_WIDTH, RGB_HEIGHT, e);
```
Step 4 : pipelineを起動します 
```cpp
    pline->start(cfg, e);
```
Step 5: RGBフレームデータを取得します。
```cpp
    sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);
	sy3::rgb_frame *rgb_frame = frameset->get_rgb_frame();
```
Step 6：RGB画面をレンダリングします。
```cpp
    void show_rgb_nv12_frame(sy3::frame *frame, const char *name)
    {
	    if (frame)
    	{
	    	cv::Mat yuvImg(frame->get_height() * 3 / 2, frame->get_width(), CV_8UC1, frame->get_data());
		    cv::Mat rgbImg(frame->get_height(), frame->get_width(), CV_8UC3);
		    cv::cvtColor(yuvImg, rgbImg, cv::ColorConversionCodes::COLOR_YUV2BGR_NV12);
		    cv::namedWindow(name, cv::WINDOW_NORMAL);
	    	cv::imshow(name, rgbImg);
	    	const sy3::stream_profile *rgb_profile = frame->get_profile();
	    	sy3::sy3_intrinsics rgb_inteinics = rgb_profile->get_intrinsics();
    	}
    }
```
