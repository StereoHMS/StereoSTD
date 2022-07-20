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
		//cout << std::endl;
		int average = sum_p1 / pixel_count;
		/*std::cout << "  average : " << average << "  min : " << p1[0]
			<< "  max : " << p1[pixel_count - 1] << "  median  : " << p1[pixel_count / 2 - 1] << " max min diff value  :"
			<< p1[pixel_count - 1] - p1[0] << std::endl;*/
		int centerdepth = depthdata[640 * 480 / 2 + 640 / 2];
		std::string center_depth = "cer : " + std::to_string(centerdepth);
		std::string avg_depth = "avg : " + std::to_string(average);
		std::string log = center_depth + " " + avg_depth + " dif " + std::to_string(centerdepth - average);
	





		std::string msg = std::to_string(frame->get_width())+ "x"+std::to_string(frame->get_height()) + " fps:" + std::to_string(g_fps);
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


		cv::namedWindow("test", cv::WINDOW_NORMAL);
		cv::resizeWindow("test", frame->get_width(), frame->get_height());
		cv::imshow("test", yuvImg);

		 sy3::sy3_intrinsics intrinsics = frame->get_profile()->get_intrinsics();
		 printf("intrinsics: %d x %d \n", intrinsics.width, intrinsics.height);
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

	sy3::pipeline *pline = sy3::sy3_create_pipeline(ctx, e);

	sy3::config *cfg = sy3_create_config(e);
	cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_DEPTH, DEPTH_WIDTH, DEPTH_HEIGHT, e);
	cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_IR, DEPTH_WIDTH, DEPTH_HEIGHT, e);
	pline->start(cfg, e);

	bool quit = false;
	int nIndex = 0;
	int switch_flag = 1;
	g_is_start = true;

	std::thread fpsThread = std::thread(calculate_framerate);

	while (!quit)
	{
		cv::waitKey(1);


		if (nIndex >= 200000) {

			switch (switch_flag) {

			case 0: {

				printf("=============> 	pline->stop(e) \n");
				pline->stop(e);
				cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_DEPTH, 640, 480, e);
				cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_IR, 640, 480, e);
				printf("=============> 	pline->start(cfg, e) \n");
				pline->start(cfg, e);
				printf("=============>  switch 640x480   %d \n", index_time++);
				switch_flag = !switch_flag;
				nIndex = 1;
			}break;

			case 1:
			{
				pline->stop(e);
				cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_DEPTH, 320, 240, e);
				cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_IR, 320, 240, e);
				pline->start(cfg, e);
				printf("=============>  switch 320x240   %d \n", index_time++);
				switch_flag = !switch_flag;
				nIndex = 0;
			}break;

			default:
				break;
			}
		}

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
		nIndex++;
	}
	system("pause");

	return 0;
}
