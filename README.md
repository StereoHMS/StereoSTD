# StereoSTD
<p align="center"><img src="doc/img/STD.jpg" width="70%" /><br><br></p>

-----------------
[![GitHub CI](../../actions/workflows/buildsCI.yaml/badge.svg?branch=development)](../../actions/workflows/buildsCI.yaml)

## 概要
**Stereo STD SDK 2.0.0** はSiNGRAY Stereo STDデプスカメラ (Stereo STD)用クロスプラットフォームライブラリです。

このSDKでは、デプスとカラーのストリーミングを取得する可能で、内部のキャリブレーション情報と外部のキャリブレーション情報を提供します。
また、合成ストリーム（点群データ、デコード画像とカラー画像を合わせたデータ）を提供します。

このライブラリを使用するに必要なハードウェアと開発者キットは、下記のサイトからご購入または入手いただけます。 [https://singray-stereo.com/](https://singray-stereo.com/).
Stereo STD　開発用のSDKなどは下記のサイトにてご確認いただけます。
[https://singray-stereo.com/category/support/stdsoftware/](https://singray-stereo.com/category/support/stdsoftware/)


## ダウンロードとインストール 
* **ダウロード** - Stereo STD SDK、Viewerツールなどの最新版は、次のサイトからダウンロードできます: [**latest releases**](https://singray-stereo.com/category/support/stdsoftware/). 対応できるプラットフォーム、新機能、既知の問題、ファームウェアのアップグレード方法などは [**release notes**](https://singray-stereo.com/category/support/stddocuments/) を確認してください。

* **インストール** - SDKをインストールして、Stereo STDカメラをPCに接続した後、最初のアプリケーションの作成を開始することができます。

> **サポート & 問題解決**: 製品サポート(たとえば、デバイスに関する質問やデバイスに問題がある場合)が必要な場合は、[FAQ]を参照してください。(https://singray-stereo.com/stdfaq/)
> FAQで問題の答案が見つからない場合は公式フォーラム [フォーラム](https://singray-stereo.com/forums/forum/stereo-std-forum/) と [ドキュメント資料](https://singray-stereo.com/category/support/stddocuments/) のページをチェックしてください。
上記の方法で質問の答えが見つからない場合は、 [問合せフォーム](https://singray-stereo.com/inform/)の記入またはお問合せ [メール](info@singray-stereo.com)を送ってください。

## SDKの内容:
| 項目 | 説明 | ダウンロードリンク|
| ------- | ------- | ------- |
| **Stereo STD Viewer** | このアプリでSTDカメラにすばやくアクセスし、デプスとRGBストリームの取得、RGB-dの可視化、カメラ設定の変更、点群の出力、デプスストリームの可視化とフィルター処理などを実現できます。 | [**Stereo STD viewer.exe**](https://singray-stereo.com/category/support/stdsoftware/) |
| **[Code Samples](./examples)** |これらのサンプルは、SDKを使用してカメラにアクセスするコードスニペットをアプリケーションに簡単に入れる方法を紹介しています。 [**C++ examples**](./examples/doc/) | [**Stereo STD  SDK.exe**](https://singray-stereo.com/category/support/stdsoftware/)に含まれています。 |

## Samples List:
| 項目 | 説明 | スクリプトファイル |
| ------- | ------- | ------- |
| **[Hello StereoSTD](./examples/doc/Hello_StereoSTD.md)** | Hello-StereoSTD このサンプルではデバイスへの接続とデバイスの基本情報を獲得する方法を紹介します。（SDKバージョン、SN，firmwareバージョンとサポートするデータストリーム） | [**Hello-StereoSTD.cpp**](./examples/Hello-StereoSTD.cpp) |
| **[Distance](./examples/doc/Distance.md)** |本コードサンプルはインスタンスの一部です。このサンプルではSDKコードスニペットを使用してカメラにアクセスする方法について説明します。Distance.cppはデプスストリームデータを読取り、デプスデータに転換します。（単位：mm）。またはセンターエリアの10*10ピクセルの平均デプス値を取得します。 | [**Distance.cpp**](./examples/Distance.cpp) |
| **[DisplayRGB](./examples/doc/DisplayRGB.md)** |本コードサンプルはインスタンスの一部です。このサンプルではSDKのコードスニペットでカメラにアクセスし、RGBのソースデータを取得する方法について説明します。DisplayRGBはカラーデータストリームを読み取ることでカメラのカラーフレームデータ情報をプリントします。 | [**DisplayRGB.cpp**](./examples/DisplayRGB.cpp) |
| **[DisplayToF](./examples/doc/DisplayToF.md)** |本コードサンプルはインスタンスの一部です。このサンプルではSDKのコードスニペットでカメラにアクセスし、ToF画像を表示する方法とボタンを使用した制御でToFの各モードを設定する方法について説明します。| [**DisplayToF.cpp**](./examples/DisplayToF.cpp)|
| **[Capture&Save](./examples/doc/Capture&Save.md)**|  本コードサンプルはインスタンスの一部です。このサンプルではSDKのコードスニペットでカメラにアクセスし、RGB画像とToF疑似カラー画像を表示する方法や、「ｗ」キーを押すことで、pngフォーマットの画像とrgbのcsvファイルを保存する方法を紹介します。 | [**Capture_Save.cpp**](./examples/Capture_Save.cpp)  |
| **[PointCloud](./examples/doc/PointCloud.md)** |RGBDインターフェイスで取得したToFデータとRGBデータ、および位置合わせ後の画像は、「p」キーを押すことで現在のディレクリで保存されます。 |[**PointCloud_PCD_PLY.cpp**](./examples/PointCloud_PCD_PLY.cpp)  |
| **[Spatial Alignment](./examples/doc/Spatial_Alignment.md)** |本コードサンプルはインスタンスの一部です。このサンプルではSDKのコードスニペットでカメラにアクセスし、デプスデータを処理することで、点群データを取得し、RGB、ToFデータを表示する方法、そしてRGBDデータにフュージョンする方法について紹介します。 |[**Spatial_Alignment.cpp**](./examples/Spatial_Alignment.cpp) |
| **[3D Spatial Alignment](./examples/doc/3DSpatialAlignment.md)** |本コードサンプルはインスタンスの一部です。このサンプルではSDKのコードスニペットでカメラにアクセスし、デプスデータを処理することで、点群データを取得し、RGB、ToFデータを表示する方法、そしてRGBDデータにフュージョンして表示する方法について紹介します。または、データをpoint（x,y,z,r,g,b）としてPCL画面に出力方法も紹介します。 | [**Spatial_Alignment3D.cpp**](./examples/Spatial_Alignment3D.cpp) |
| **[Stream Recording](./examples/doc/Stream_Recording.md)** |本コードサンプルはインスタンスの一部です。このサンプルではSDKのコードスニペットでカメラにアクセスし、RGBとTOFデータを保存することで、録画します。保存されたファイルはaviフォーマットです。（demoはサンプルのみ提供します。録画する時、，FPSは固定していないため、動画の長さは異なります。環境によって調整してください。）|[**StreamRecording.cpp**](./examples/StreamRecording.cpp) |
| **[Post Processing](./examples/doc/Post_Processing.md)** |本コードサンプルはインスタンスの一部です。このサンプルではSDKのコードスニペットでカメラにアクセスし、OpenCVでデプスデータを処理し、“Mean filtering”、"medianblur filtering”、”Gaussian filtering“をする方法も紹介します。 | [**PostProcessing.cpp**](./examples/PostProcessing.cpp) |


## 始めましょう!

当社のライブラリはStereo STDカメラ専用の高レベルのAPIを提供しています。
下記のコードクリップは、フレームの転送を開始し、ピクセルのデプス値を抽出する方法を示しています。

```cpp
//データの出力の設定とデバイスの取得。
#include "libsynexens3/libsynexens3.h" 
int main(int argc, char **argv) 
{ 
    //デバイス情報の登録
　　sy3::sy3_error e; 
　　sy3::context *ctx = sy3::sy3_create_context(e); sy3::device 
　　*dev = ctx->query_device(e); 
　　if (e != sy3::sy3_error::SUCCESS) { 
        return 0; 
　　} 
　　sy3::pipeline *pline = sy3::sy3_create_pipeline(ctx, e); 
　　sy3::config *cfg = sy3_create_config(e); 
　　//ストリーム情報の設定
　　cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_DEPTH, 640, 480, e); 
　　cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_RGB, 1920, 1080, e); 
　　//ストリームの有効化
　　pline->start(cfg, e); 
　　bool quit = false; 
    while (!quit) 
　　{ 
　　　　switch (cv::waitKey(1)) { 
　　　　case 'q': { 
　　　　　　pline->stop(e);
　　　　　　quit = true; 
　　　　}break; 
　　　　case 'e': { 
　　　　// 露光時間を設定します。単位 us 
　　　　dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_EXPOSURE, 10, e); 
　　　　}break; 
　　　　default: break; 
　　　　} 
　　　　sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e); 
　　　　//デプスストリームの取得
　　　　sy3::depth_frame *depth_frame = frameset->get_depth_frame();
　　　　//カラーストリームの取得
        sy3::rgb_frame *rgb_frame = frameset->get_rgb_frame(); 
        sy3::process_engine *engine = pline->get_process_engin(e) ;
        //rgbdの位置合わせ
        if (depth_frame && rgb_frame){
　　　 　sy3::frameset *align_set=engine->align_to_rgb(depth_frame,rgb_frame,e); 　　
　　　　 delete align_set; 
        }
        delete frameset; 
　　} 
　return 0;
}
33
## Contributing
In order to contribute to Stereo STD SDK, please follow our [contribution guidelines](CONTRIBUTING.md).
