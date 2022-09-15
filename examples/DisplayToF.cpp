#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<thread>

#define DEPTH_WINDOW_NAME "DEPTH IR"

#if 1
#define DEPTH_WIDTH 640
#define DEPTH_HEIGHT 480
#else 
#define DEPTH_WIDTH 320
#define DEPTH_HEIGHT 240
#endif


volatile bool g_is_start = false;
volatile int g_fps = 0;
volatile unsigned long g_last_time = 0;
volatile int g_frame_count = 0;

std::thread fpsThread;

#include <stdlib.h>
#include <stdio.h>

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

int  index_time = 1;
void show_ir_frame(sy3::ir_frame *frame, const char* name)
{
	if (frame) {

		cv::Mat gray16(frame->get_height(), frame->get_width(), CV_16UC1, frame->get_data());
		cv::Mat tmp;
		cv::Mat gray8 = cv::Mat::zeros(gray16.size(), CV_8U);
		cv::normalize(gray16, tmp, 0, 255, cv::NORM_MINMAX);
		cv::convertScaleAbs(tmp, gray8);
		cv::namedWindow(name, cv::WINDOW_NORMAL);
		cv::imshow(name, gray8);
	}

}

void show_depth_frame(sy3::depth_frame *frame, const char* name)
{
	if (frame) {

		g_frame_count++;

		cv::Mat gray16(frame->get_height(), frame->get_width(), CV_16UC1, frame->get_data());
		cv::Mat tmp;
		cv::Mat gray8 = cv::Mat::zeros(gray16.size(), CV_8U);
		cv::normalize(gray16, tmp, 0, 255, cv::NORM_MINMAX);
		cv::convertScaleAbs(tmp, gray8);
		cv::namedWindow(name, cv::WINDOW_NORMAL);
		cv::imshow(name, gray8);

		uint8_t* depth_color = frame->apply_colormap();
		cv::Mat yuvImg(frame->get_height(), frame->get_width(), CV_8UC3, depth_color);

		
		cv::namedWindow("depth", cv::WINDOW_NORMAL);
		cv::resizeWindow("depth", frame->get_width(), frame->get_height());
		cv::imshow("depth", yuvImg);

	
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
			std::cerr << "Enter code" << std::endl;
			std::cout << "---------------------------" << std::endl;
			std::cout << "| a     Turn 640*480      |" << std::endl;
			std::cout << "| s     Turn 320*240      |" << std::endl;
			std::cout << "| d     FILTER on         |" << std::endl;
			std::cout << "| f     FILTER off        |" << std::endl;
			std::cout << "| g  TOF_IMAGE_FLIP off   |" << std::endl;
			std::cout << "| h  TOF_IMAGE_FLIP on    |" << std::endl;
			std::cout << "| j  TOF_IMAGE_MIRROR on  |" << std::endl;
			std::cout << "| k  TOF_IMAGE_MIRROR off |" << std::endl;
			std::cout << "| l  Set _EXPOSURE   300  |" << std::endl;
			std::cout << "| w  Set _EXPOSURE   1000 |" << std::endl;
			std::cout << "| e  Set _EXPOSURE   000  |" << std::endl;
			std::cout << "| q        -Quit-         |" << std::endl;
			std::cout << "---------------------------" << std::endl;
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
	sy3::sy3_error e;
	printf("version:%s \n", sy3::sy3_get_version(e));
	sy3::context *ctx = sy3::sy3_create_context(e);
	sy3::device *dev = ctx->query_device(e);
	if (e != sy3::sy3_error::SUCCESS) {
		printf("error:%s \n", sy3::sy3_error_to_string(e));
		return 0;
	}

	printf("    Firmware version: %s   sn: %s   %s\n\n", sy3::sy3_get_device_info(dev, sy3::SY3_CAMERA_INFO_FIRMWARE_VERSION, e), sy3::sy3_get_device_info(dev, sy3::SY3_CAMERA_INFO_SERIAL_NUMBER, e), sy3::sy3_get_device_info(dev, sy3::SY3_CAMERA_INFO_RECOMMENDED_FIRMWARE_VERSION, e));
	print_support_format(dev, e);
	print_device_info(dev);


	sy3::pipeline *pline = sy3::sy3_create_pipeline(ctx, e);

	sy3::config *cfg = sy3_create_config(e);
	cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_DEPTH, DEPTH_WIDTH, DEPTH_HEIGHT, e);
	cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_IR, DEPTH_WIDTH, DEPTH_HEIGHT, e);
	pline->start(cfg, e);

	bool quit = false;
	int nIndex = 0;
	
	g_is_start = true;

	std::thread fpsThread = std::thread(calculate_framerate);

	uint16_t filter_on = 1;
	uint16_t filter_off = 0;
	std::thread t(GetkeyThread);

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
			//show_ir_frame(ir_frame, "IR");

		}

		delete frameset;
		cv::waitKey(1);
		switch (keyCode)
		{

		case 'a':
		{
			std::cout << "code " << keyCode << " | -----Turn 640*480----- |"<< std::endl;
			pline->stop(e);
			cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_DEPTH, 640, 480, e);
			cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_IR, 640, 480, e);
			pline->start(cfg, e);
			
			
			printf("%s  %d   switch 640x480\n", __FILE__, __LINE__);
		}
		break;

		case 's':
		{	
			std::cout << "code " << keyCode << " | -----Turn 320*240----- |" << std::endl;
			pline->stop(e);
			cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_DEPTH, 320, 240, e);
			cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_IR, 320, 240, e);
			pline->start(cfg, e);			
			
			printf("%s  %d   switch 320x240\n", __FILE__, __LINE__);
		}
		break;

		case 'd':
		{
			std::cout << "code " << keyCode << " | -----Turn SY3_OPTION_DEPTH_IMAGE_FILTER---ON-- |" << std::endl;

			dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_DEPTH_IMAGE_FILTER, filter_on, e);
			
		}
		break;

		case 'f':
		{
			std::cout << "code " << keyCode << " | -----Turn SY3_OPTION_DEPTH_IMAGE_FILTER--OFF--- |" << std::endl;

			dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_DEPTH_IMAGE_FILTER, filter_off, e);
			
		}
		break;

		case 'g':
		{
			std::cout << "code " << keyCode << " | -----Turn SY3_OPTION_TOF_IMAGE_FLIP off----- |" << std::endl;

			dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_TOF_IMAGE_FLIP, 0, e);
		}
		break;

		case 'h':
		{
			std::cout << "code " << keyCode << " | -----Turn SY3_OPTION_TOF_IMAGE_FLIP on----- |" << std::endl;

			dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_TOF_IMAGE_FLIP, 1, e);
		}
		break;

		case 'j':
		{
			std::cout << "code " << keyCode << " | -----Turn SY3_OPTION_TOF_IMAGE_MIRROR on----- |" << std::endl;

			dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_TOF_IMAGE_MIRROR, 1, e);
		}
		break;

		case 'k':
		{
			std::cout << "code " << keyCode << " | -----Turn SY3_OPTION_TOF_IMAGE_MIRROR off----- |" << std::endl;

			dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_TOF_IMAGE_MIRROR, 0, e);
		}
		break;

		case 'l': {
			std::cout << "code " << keyCode << " | -----set SY3_OPTION_EXPOSURE   300----- |" << std::endl;

			dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_EXPOSURE, 300, e);
		} break;

		case 'w': {
			std::cout << "code " << keyCode << " | -----set SY3_OPTION_EXPOSURE   1000----- |" << std::endl;

			dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_EXPOSURE, 1000, e);
		} break;

		case 'e': {
			std::cout << "code " << keyCode << " | -----set SY3_OPTION_EXPOSURE   0----- |" << std::endl;

			uint16_t exposure = 0;
			dev->get_sensor(e)->get_option(sy3::sy3_option::SY3_OPTION_EXPOSURE, exposure, e);

		} break;

		case 'q': {
			std::cout << "code " << keyCode << " | -----Quit----- |" << std::endl;

			g_is_start = false;
			pline->stop(e);
			delete ctx;
			cv::destroyAllWindows();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			quit = true;
			break;

		}
		default: {

			
		}
		break;


		
		}
		keyCode = -1;

	}
	system("pause");

	return 0;
}
