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
void show_depth_frame(sy3::depth_frame *frame, const char* name)
{
	if (frame) {
		g_frame_count++;

		uint8_t* depth_color = frame->apply_colormap();
		cv::Mat yuvImg(frame->get_height(), frame->get_width(), CV_8UC3, depth_color);


		//get 10*10 pixel middle value
		uint16_t* depthdata = (uint16_t*)frame->get_data();
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

		std::sort(p1, p1 + pixel_count);// min 2 max
		int sum_p1 = 0;
		for (int i = 0; i < pixel_count; i++) {
			sum_p1 += p1[i];
		}
		int average = sum_p1 / pixel_count;
		/*std::cout << "  average : " << average << "  min : " << p1[0]
			<< "  max : " << p1[pixel_count - 1] << "  median  : " << p1[pixel_count / 2 - 1] << " max min diff value  :"
			<< p1[pixel_count - 1] - p1[0] << std::endl;*/
		int centerdepth = depthdata[DEPTH_WIDTH * DEPTH_HEIGHT / 2 + DEPTH_WIDTH / 2];
		std::string center_depth = "cer : " + std::to_string(centerdepth);
		std::string avg_depth = "avg : " + std::to_string(average);
		std::string log = center_depth + " " + avg_depth + " dif " + std::to_string(centerdepth - average);

	    std::string msg = std::to_string(frame->get_width()) + "x" + std::to_string(frame->get_height()) + " fps:" + std::to_string(g_fps);
		int font_face = cv::FONT_HERSHEY_COMPLEX;
		double font_scale = 1;
		int thickness = 1;
		int baseline;
		cv::Size text_size = cv::getTextSize(msg, font_face, font_scale, thickness, &baseline);

		cv::Point origin;
		origin.x = yuvImg.cols / 2 - text_size.width / 2;
		origin.y = 0 + text_size.height;
		cv::putText(yuvImg, msg, origin, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 2, 0);


		cv::Point originlog;
		originlog.x = yuvImg.cols / 2 - text_size.width;
		originlog.y = yuvImg.rows;
		cv::putText(yuvImg, log, originlog, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 2, 0);
		cv::rectangle(yuvImg, cv::Point(yuvImg.size().width / 2 - 5, yuvImg.size().height / 2 - 5), cv::Point(yuvImg.size().width / 2 + 5, yuvImg.size().height / 2 + 5), cv::Scalar(0, 255, 255));


		cv::namedWindow(name, cv::WINDOW_NORMAL);
		cv::resizeWindow(name, frame->get_width(), frame->get_height());
		cv::imshow(name, yuvImg);
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

		}

		delete frameset;
		cv::waitKey(1);
	}
	system("pause");

	return 0;
}
