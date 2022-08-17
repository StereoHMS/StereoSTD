#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<thread>
#include<math.h>
#include <iostream>
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

int show_depth_frame(sy3::depth_frame *frame, const char* name,uint16_t exp,int depthx)
{
	if (frame) {

		g_frame_count++;

		/*cv::Mat gray16(frame->get_height(), frame->get_width(), CV_16UC1, frame->get_data());
		cv::Mat tmp;
		cv::Mat gray8 = cv::Mat::zeros(gray16.size(), CV_8U);
		cv::normalize(gray16, tmp, 0, 255, cv::NORM_MINMAX);
		cv::convertScaleAbs(tmp, gray8);
		cv::namedWindow(name, cv::WINDOW_NORMAL);
		cv::imshow(name, gray8);*/

		uint8_t* depth_color = frame->apply_colormap();
		cv::Mat yuvImg(frame->get_height(), frame->get_width(), CV_8UC3, depth_color);

		std::string msg = std::to_string(frame->get_width()) + "x" + std::to_string(frame->get_height()) + " fps:" + std::to_string(g_fps);
		int font_face = cv::FONT_HERSHEY_SIMPLEX;
		double font_scale = 0.85;
		int thickness = 2;
		int baseline;
		//��ȡ�ı���ĳ���
		cv::Size text_size = cv::getTextSize(msg, font_face, font_scale, thickness, &baseline);

		cv::Point origin;
		origin.x = yuvImg.cols / 2 - text_size.width / 2;
		origin.y = 0 + text_size.height;
		cv::putText(yuvImg, msg, origin, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 2, 0);

		cv::Point originexp;
		originexp.x = 0;
		originexp.y = 0 + text_size.height;
		cv::putText(yuvImg, std::to_string(exp), originexp, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 2, 0);


		cv::Point origin22;
		origin22.x = 100;
		origin22.y = 0 + text_size.height;
		cv::putText(yuvImg, std::to_string(depthx), origin22, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 2, 0);

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
		std::string log = center_depth + " " + avg_depth+" dif "+std::to_string(centerdepth - average);
		cv::Point originlog;
		originlog.x = yuvImg.cols / 2 - text_size.width ;
		originlog.y = yuvImg.rows;
		cv::putText(yuvImg, log, originlog, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 2, 0);

		cv::rectangle(yuvImg,cv::Point(yuvImg.size().width / 2-5, yuvImg.size().height / 2-5), cv::Point(yuvImg.size().width / 2 + 5, yuvImg.size().height / 2 + 5), cv::Scalar(0, 255, 255));




		cv::namedWindow(name, cv::WINDOW_NORMAL);
		cv::resizeWindow(name,  frame->get_width(), frame->get_height());


		cv::imshow(name, yuvImg);

		sy3::sy3_intrinsics intrinsics = frame->get_profile()->get_intrinsics();
		//printf("intrinsics: %d x %d \n", intrinsics.width, intrinsics.height);
		return centerdepth;
	}

}
 double depthRel = 0;
 bool isAuto = false;
 uint16_t expnum = 1500;
 int indexD = 10;
 int indexL = 0;
int main(int argc, char **argv)
{
	
	if (argc==2)
	{
		std::cout << argv[1] << std::endl;
		depthRel = atoi(argv[1]);
		isAuto = true;
	}
	else
	{
		depthRel = 500;
		isAuto = true;
	}
	

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
	int switch_flag =0;
	g_is_start = true;

	std::thread fpsThread = std::thread(calculate_framerate);
	int Eindex = 0;
	std::string key;
	bool isStart = true;
	while (!quit)
	{
		cv::waitKey(1);
		
		sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);
		sy3::depth_frame *depth_frame = frameset->get_depth_frame();
		sy3::ir_frame *ir_frame = frameset->get_ir_frame();
		if (depth_frame == nullptr)
		{
			//	printf("depth_frame:empty \n");
		}
		else
		{
			uint16_t t = 10;
			uint16_t t1 = 10;
			int dep = 0;

			dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_EXPOSURE, expnum, e);
			//dev->get_sensor(e)->get_option(sy3::sy3_option::SY3_OPTION_EXPOSURE, t, e);
			//	printf("depth_frame:%d \n", depth_frame);
			dep=show_depth_frame(depth_frame, DEPTH_WINDOW_NAME,t,depthRel);
			//show_ir_frame(ir_frame, "IR");
			if (isAuto /*&& expnum>20*/)
			{
				
				double diff = std::abs(dep - depthRel);
				if (diff>= indexD)
				{
					int temp = diff / 100;
					if (dep>depthRel)
					{
						expnum -=(2 + 2*temp);
					}
					else
					{
						expnum+= (2 + 2 * temp);

					}
					
					dev->get_sensor(e)->set_option(sy3::sy3_option::SY3_OPTION_EXPOSURE, expnum, e);
					std::cout <<"set exposure " <<expnum<<"  diff "<<std::to_string(diff) << std::endl;
					Eindex = 0;
				}
				else
				{
					Eindex++;
					indexL = 0;
					if (Eindex>=100)
					{
						pline->stop(e);
						if (depthRel >= 2000)
						{
							//std::cout << "\033[0;32m " << "Pass Fished" << "\032[0m" << std::endl;
							std::cout << "\033[0;32m *************** \032[0m" << std::endl;
							std::cout << "\033[0;32m * Pass Fished * \032[0m" << std::endl;
							std::cout << "\033[0;32m *************** \032[0m" << std::endl;
							break;
						}
						else
						{
							std::cout <<"\033[0;33m " << depthRel << " : pass " << "\033[0m"<< std::endl;
							std::cerr << "ENTER 'c' to next" << std::endl;
							std::cin >> key;
							if (key == "c")
							{
								std::cout << "Rstart tof " << key << std::endl;
								pline->start(cfg, e);
								Eindex = 0;
								if (depthRel==500)
								{
									depthRel = 1000;
								}
								else if(depthRel==1000)
								{
									depthRel = 2000;
									indexD = 20;
								}
								expnum = 1500;

							}

						}
						
						
						
					}
				}

			}
			if (expnum<=19||expnum>=2994)
			{
				indexL++;
				std::cout << "Lost..." <<indexL<< std::endl;
				if (indexL>=100)
				{
					std::cout << "\033[0;31m ************ \033[0m" << std::endl;
					std::cout << "\033[0;31m **  fail  ** \033[0m" << std::endl;
					std::cout << "\033[0;31m ************ \033[0m" << std::endl;

					break;
				}
				
			}

		}

		delete frameset;
	}
	system("pause");

	return 0;
}
