# STD-depth Sample

## Overview

本コードサンプルはインスタンスの一部です。このサンプルではSDKコードスニペットを使用してカメラにアクセスする方法について説明します。STD-depthはデプスストリームデータを読み取ることでカメラから画像中心の目標物までの距離とセンターエリアの10*10ピクセルの平均距離をプリントします。（カメラはデフォルトで NO AEになっています。異なる環境と距離で取得されたデータは多少異なりますが、コマンドで変更できます。AEバージョンでは露光時間を自動的に調整します）
			  
## Expected Output

実行成功すると、デプス疑似カラー画像で出力のデータが表示され、ウィンドウ内の10*10ピクセルのデータは常に更新されています。
<p align="center"><img src="doc/img/depth.png" width="100%" /><br><br></p>

## Code Overview

初めに、SDKのヘッダーファイルとOpenCV依存ライブラリを参照する必要があります。
```cpp
#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
```

Step 1: データの出力の設定とデバイスの取得
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
Step 2：pipelineを作成します
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
Step 5: TOFフレームデータを取得します
```cpp
    sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);
	sy3::depth_frame *depth_frame = frameset->get_depth_frame();
	sy3::ir_frame *ir_frame = frameset->get_ir_frame();
```
Step 6：IR画面をレンダリングします
```cpp
   cv::Mat gray16(frame->get_height(), frame->get_width(), CV_16UC1frame->get_data());
	cv::Mat tmp;
	cv::Mat gray8 = cv::Mat::zeros(gray16.size(), CV_8U);
	cv::normalize(gray16, tmp, 0, 255, cv::NORM_MINMAX);
	cv::convertScaleAbs(tmp, gray8);
	cv::namedWindow(name, cv::WINDOW_NORMAL);
	cv::imshow(name, gray8);
	uint8_t* depth_color = frame->apply_colormap();
	cv::Mat yuvImg(frame->get_height(), frame->get_width(), CV_8UC3, depth_color);
```
Step 7:疑似カラー画像をレンダリングします
```cpp
    uint8_t* depth_color = frame->apply_colormap();
	cv::Mat yuvImg(frame->get_height(), frame->get_width(), CV_8UC3, depth_color);
	cv::namedWindow("test", cv::WINDOW_NORMAL);
	cv::resizeWindow("test", frame->get_width(), frame->get_height());
	cv::imshow("test", yuvImg);
```
Step 8：中心点の位置を取得します
```cpp
    uint16_t* depthdata = (uint16_t*)frame->get_data();
	int centerdepth = depthdata[frame->get_width() * frame->get_height() / 2 + frame->get_width() / 2];
```
Step 9：センターエリア10*10ピクセルデータを取得します
```cpp
   const int pixel_count = 100;
	const int radius = 5;
	float p1[pixel_count] = { 0 };
	int index_p1 = 0;
	for (int i = -radius; i < radius; i++)
		for (int j = -radius; j < radius; j++) {
			int row = frame->get_height() / 2 + i;
			int col = frame->get_width() / 2 + j;
			p1[index_p1] = depthdata[row * frame->get_width() + col];
			index_p1++;
		}
```