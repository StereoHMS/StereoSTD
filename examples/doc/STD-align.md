# STD-align Sample

## Overview

本コードサンプルはインスタンスの一部です。このサンプルではSDKコードスニペットでカメラにアクセスする方法について説明します。STD-alignはデプスストリームデータとRGBデータを読み取ることでマッピングを行います。解像度1920*1080のRGBDデータと画像を出力します。RGBDを使用する場合は、RGBセンサーとTOFセンサーの両方をオンにする必要があります。
			  
## Expected Output

実行すると、デプス疑似カラー画像、RGBカラー画像および位置合わせを行った後RGBDの画像が表示されます。
<p align="center"><img src="doc/img/rgbd.png" width="100%" /><br><br></p>

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
Step 3：TOFデータストリームとRGBデータストリームをコンフィグします
```cpp
    sy3::config *cfg = sy3_create_config(e);
    cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_DEPTH, DEPTH_WIDTH, DEPTH_HEIGHT, e);
    cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_RGB, RGB_WIDTH, RGB_HEIGHT, e);
```
Step 4 : pipelineを起動します 
```cpp
    pline->start(cfg, e);
```
Step 5: rgb、tofフレームデータを取得します
```cpp
    sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);
    sy3::depth_frame *depth_frame = frameset->get_depth_frame();
```
Step 6：rgb、tofフレームデータの位置合わせを行います。
```cpp
    sy3::frameset *set = pline->get_process_engin(e)->align_to_rgb(depth, rgb, e);
    //位置合わせ後のtofデータ
    set->get_depth_frame();
    //位置合わせ後のrgbデータ
    set->get_rgb_frame();
    //両方の解像度とも1920*1080です
```
Step 7:ToF画像をレンダリングします。
```cpp
    cv::Mat gray16(piexls_depth->get_height(), piexls_depth->get_width(), CV_16UC1, 	piexls_depth->get_data());
	cv::Mat tmp;
	cv::Mat gray8 = cv::Mat::zeros(gray16.size(), CV_8U);
	cv::normalize(gray16, tmp, 0, 255, cv::NORM_MINMAX);
```
Step 8:RGB画像をレンダリングします。
```cpp
   cv::Mat yuvImg(piexls_rgb->get_height(), piexls_rgb->get_width(), CV_8UC3, piexls_rgb->get_data());
```
Step 9：RGBD画像を合成します
```cpp
  cv::Mat rgbd_img(height, width, CV_8UC3, cv::Scalar(0));// rgb_img;
	for (int row = 0; row < yuvImg.rows; row++){
		for (int col = 0; col < yuvImg.cols; col++)
		{
			if (gray16.ptr<uint16_t>(row)[col] > 10)
			{
				rgbd_img.ptr<uchar>(row)[col * 3] = yuvImg.ptr<uchar>(row)[col * 3];
				rgbd_img.ptr<uchar>(row)[col * 3 + 1] = yuvImg.ptr<uchar>(row)[col * 3 + 1];
				rgbd_img.ptr<uchar>(row)[col * 3 + 2] = yuvImg.ptr<uchar>(row)[col * 3 + 2];
			}
		}
	}
```
