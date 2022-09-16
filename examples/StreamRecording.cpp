#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE


#define DEPTH_WIDTH 640
#define DEPTH_HEIGHT 480


#define RGB_WIDTH 1920
#define RGB_HEIGHT 1080




unsigned long getTimestamp()
{
	return chrono::system_clock::now().time_since_epoch().count() / chrono::system_clock::period::den;
}


string savepathtof = "../tofStream_" + to_string(getTimestamp()) + ".avi";

cv::VideoWriter writertof(savepathtof, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 8, cv::Size(640, 480));

string savepathrgb = "../rgbStream_" + to_string(getTimestamp()) + ".avi";

cv::VideoWriter writerrgb(savepathrgb, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 4, cv::Size(1920, 1080));
void show_depth_frame(sy3::depth_frame *frame, const char *name, int  *isCapture)
{
	if (frame) {



		uint8_t* depth_color = frame->apply_colormap();
		cv::Mat yuvImg(frame->get_height(), frame->get_width(), CV_8UC3, depth_color);
		cv::resizeWindow(name, frame->get_width(), frame->get_height());
		cv::imshow(name, yuvImg);
		if (*isCapture == 1||*isCapture==2)
		{					
			writertof << yuvImg;

			std::cout << "Save TOF Stream.......  : " << getTimestamp() << " " << savepathtof << std::endl;
			*isCapture = 2;
		}
		if (*isCapture==3)
		{
			//stop

			writertof.release();
		}

	}
}

void show_rgb_rgb_frame(sy3::frame *frame, const char *name, int *isCapture)
{
	if (frame)
	{

		cv::Mat yuvImg(frame->get_height() * 3 / 2, frame->get_width(), CV_8UC1, frame->get_data());
		cv::Mat rgbImg(frame->get_height(), frame->get_width(), CV_8UC3);
		cv::cvtColor(yuvImg, rgbImg, cv::ColorConversionCodes::COLOR_YUV2BGR_NV12);
		cv::namedWindow(name, cv::WINDOW_NORMAL);
		cv::resizeWindow(name, frame->get_width(), frame->get_height());
		cv::imshow(name, rgbImg);
		
		//	print_intri(rgb_inteinics);
		if (*isCapture == 1 || *isCapture == 2)
		{
			writerrgb << rgbImg;

			std::cout << "Save rgb Stream.......  : " << getTimestamp() << " " << savepathrgb << std::endl;
			*isCapture = 2;
		}
		if (*isCapture == 3)
		{
			//stop

			writerrgb.release();
		}
	}
}

void print_device_info(sy3::device *dev)
{
	sy3::sy3_error e;
	printf("\nUsing device 0, an %s\n", sy3::sy3_get_device_info(dev, sy3::SY3_CAMERA_INFO_NAME, e));
	printf("    Serial number: %s\n", sy3::sy3_get_device_info(dev, sy3::SY3_CAMERA_INFO_SERIAL_NUMBER, e));
	printf("    Firmware version: %s\n\n", sy3::sy3_get_device_info(dev, sy3::SY3_CAMERA_INFO_FIRMWARE_VERSION, e));
}

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

int keyCode = -1;

void GetkeyThread()
{
	int key = -1;
	try
	{
		while (true)
		{
			std::cerr << "Enter w to Capture&Save rgb、tof Stream" << std::endl;

			//std::cout << "a" << std::endl;
			//std::cin.get();

			key = std::cin.get();
			if (key != 10)
			{
				//std::cout << "your code " << key << std::endl;
				keyCode = key;
			}



		}

	}
	catch (const std::exception&)
	{
		std::cout << "enter error" << std::endl;
	}


}


int main(int argc, char **argv)
{
	cout << "the time " << getTimestamp() << endl;
	sy3::sy3_error e;
	printf("version:%s \n", sy3::sy3_get_version(e));
	sy3::context *ctx = sy3::sy3_create_context(e);
	sy3::device *dev = ctx->query_device(e);

	if (e != sy3::sy3_error::SUCCESS) {
		printf("error:%d  %s \n", e, sy3::sy3_error_to_string(e));
		return 0;
	}

	print_support_format(dev, e);
	print_device_info(dev);

	sy3::pipeline *pline = sy3::sy3_create_pipeline(ctx, e);

	sy3::config *cfg = sy3_create_config(e);
	cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_DEPTH, DEPTH_WIDTH, DEPTH_HEIGHT, e);
	cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_RGB, RGB_WIDTH, RGB_HEIGHT, e);

	pline->start(cfg, e);

	uint16_t exposure = 0;
	bool quit = false;
	int isCaptureRGB = 0;
	int isCaptureTOF = 0;
	std::thread t(GetkeyThread);
	while (!quit)
	{
		sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);
		sy3::depth_frame *depth_frame = frameset->get_depth_frame();

	
		sy3::rgb_frame *rgb_frame = frameset->get_rgb_frame();
		show_depth_frame(depth_frame, "TOFStream", &isCaptureTOF);
		show_rgb_rgb_frame(rgb_frame, "RGBStream", &isCaptureRGB);

		switch (keyCode)
		{

		case 'w':
		{
			isCaptureTOF = 1;
			isCaptureRGB = 1;
			/*std::cout << "code " << keyCode << " | Capture&Save |" << std::endl;
			std::cout << "isCaptureTOF " << isCaptureTOF << " | Capture&Save |" << std::endl;
			std::cout << "isCaptureRGB " << isCaptureRGB << " | Capture&Save |" << std::endl;*/
		}
		break;
		case 's':
		{
			if (isCaptureTOF==2)
			{
				isCaptureTOF = 3;
			}
			if (isCaptureRGB==2)
			{
				isCaptureRGB = 3;
			}
		}
		break;
		case 'q':
		{
			quit = !quit;
		}
		break;
		}

		delete frameset;
		keyCode = -1;
		cv::waitKey(1);
	}
	system("pause");

	return 0;
}
