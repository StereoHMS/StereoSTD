#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#define DEPTH_WINDOW_NAME "DEPTH"

#if 1
#define DEPTH_WIDTH 640
#define DEPTH_HEIGHT 480
#else 
#define DEPTH_WIDTH 320
#define DEPTH_HEIGHT 240
#endif

int  raw_index = 0;

void show_raw_frame(sy3::raw_frame *frame, const char* name)
{
	if (frame) {

		std::string  file_name = "D://test//" + std::to_string(raw_index++) + ".raw";
		frame->dump(file_name.c_str());
		cv::Mat gray16(frame->get_height(), frame->get_width(), CV_16UC1, frame->get_data());
		cv::Mat tmp;
		cv::Mat gray8 = cv::Mat::zeros(gray16.size(), CV_8U);
		cv::normalize(gray16, tmp, 0, 255, cv::NORM_MINMAX);
		cv::convertScaleAbs(tmp, gray8);
		cv::namedWindow(name, cv::WINDOW_NORMAL);
		cv::imshow(name, gray8);
	}

}

int main(int argc, char **argv)
{
	sy3::sy3_error e;
	printf("version:%s \n", sy3::sy3_get_version(e));
	sy3::context *ctx = sy3::sy3_create_context(e);
	sy3::device *dev = ctx->query_device(e);

	sy3::pipeline *pline = sy3::sy3_create_pipeline(ctx, e);

	sy3::config *cfg = sy3_create_config(e);
	cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_RAW, DEPTH_WIDTH, DEPTH_HEIGHT, e);
	pline->start(cfg, e);

	bool quit = false;
	while (!quit)
	{

		sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);
		sy3::raw_frame *raw_frame = frameset->get_raw_frame();
		show_raw_frame(raw_frame, DEPTH_WINDOW_NAME);

		delete frameset;
		cv::waitKey(1);
	}
	system("pause");

	return 0;
}
