# STD-pointcloud Sample

## Overview

本コードサンプルはインスタンスの一部です。このサンプルではSDKコードスニペットを使用してカメラにアクセスする方法について説明します。STD-pointcloudはデプスストリームデータを読み取ることでデプスデータを変換して点群データを取得します（plyファイル）。ここではインターフェースを提供し、直接呼び出すことで結果を取得できます。 
			  
## Expected Output

実行成功すると、コマンドプロンプトで点群データが書き込まれていことが表示されます。plyファイルはmeshlabで直接モデルを読み取る、また表示することができます。
<p align="center"><img src="doc/img/pc1.png" width="100%" /><br><br></p>
<p align="center"><img src="doc/img/pc2.png" width="100%" /><br><br></p>
<p align="center"><img src="doc/img/pc3.png" width="100%" /><br><br></p>

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
Step 3：TOFデータストリームをコンフィグします
```cpp
    sy3::config *cfg = sy3_create_config(e);
    cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_DEPTH, DEPTH_WIDTH, DEPTH_HEIGHT, e);
```
Step 4 : pipelineを起動します 
```cpp
    pline->start(cfg, e);
```
Step 5: TOFフレームデータを取得します
```cpp
    sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);
	sy3::depth_frame *depth_frame = frameset->get_depth_frame();
```
Step 6：点群データを取得します
```cpp
  	sy3::points* points = engine->comptute_points(depth_frame,e);
Step 7：点群データ形式を変換します
```cpp
    float* data = points->get_points();		
```
Step 8：点群データを解析します
```cpp
    int  m_width =640,m_height=480;
    for (uint32_t i = 0; i < m_width * m_height; ++i) {
		int x = 0, y = 0, z = 0;
		if (i < m_width * 2) {
			x = 0;
			y = 0;
			z = 0;
		}
		else {
			x = data [i * 3 + 0];
			y = data [i * 3 + 1];
			z = data [i * 3 + 2];
		}
	}
```
Step 9:PLYファイルを保存します
```cpp
    void SavePointCloud(float* coord3_, std::string path) { //path=”xxxx.ply”

	int m_width = 640;
	int m_height = 480;

	std::fstream points;

	points.open(path, std::fstream::out);
	points << "ply" << std::endl;
	points << "			format ascii 1.0" << std::endl;
	points << "			element vertex " << m_width * m_height << std::endl;
	points << "			property float x" << std::endl;
	points << "			property float y" << std::endl;
	points << "			property float z" << std::endl;
	points << "			element face 0" << std::endl;
	points << "			property list uchar int vertex_index" << std::endl;
	points << "			end_header" << std::endl;

	std::string writestring;

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

		writestring += std::to_string(x) + " " + std::to_string(y) + " " +
			std::to_string(z) + "\n";
	}
	points << writestring;
	points.close();
}

```