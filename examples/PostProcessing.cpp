#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<thread>

#define DEPTH_WINDOW_NAME "DEPTH"

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
		cv::Mat srcOpencvMean, srcOpencvmidanBlur,srcOpencvGaussian;
		uint8_t* depth_color = frame->apply_colormap();
		cv::Mat src(frame->get_height(), frame->get_width(), CV_8UC3, depth_color);

		cv::namedWindow(name, cv::WINDOW_NORMAL);
		cv::resizeWindow(name, frame->get_width(), frame->get_height());
		cv::imshow(name, src);


		cv::blur(src, srcOpencvMean,cv::Size(5, 5));
		cv::namedWindow("Mean filtering", cv::WINDOW_NORMAL);
		cv::resizeWindow("Mean filtering", frame->get_width(), frame->get_height());
		cv::imshow("Mean filtering", srcOpencvMean);

		cv::medianBlur(src, srcOpencvmidanBlur, 5);
		cv::namedWindow("medianblur ksize=5", cv::WINDOW_NORMAL);
		cv::resizeWindow("medianblur ksize=5", frame->get_width(), frame->get_height());
		cv::imshow("medianblur ksize=5", srcOpencvmidanBlur);

		cv::GaussianBlur(src, srcOpencvGaussian, cv::Size(9,9),10,20);
		cv::namedWindow("srcOpencvGaussian ksize=9", cv::WINDOW_NORMAL);
		cv::resizeWindow("srcOpencvGaussian ksize=9", frame->get_width(), frame->get_height());
		cv::imshow("srcOpencvGaussian ksize=9", srcOpencvGaussian);

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

	uint16_t filter_value = 0;
	dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_TOF_IMAGE_FLIP, 0, e);

	while (!quit)
	{
		sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);
		sy3::depth_frame *depth_frame = frameset->get_depth_frame();
	
		if (depth_frame == nullptr)
		{
		}
		else 
		{
			show_depth_frame(depth_frame, DEPTH_WINDOW_NAME);
		}

		delete frameset;
		cv::waitKey(1);

	}
	system("pause");

	return 0;
}
