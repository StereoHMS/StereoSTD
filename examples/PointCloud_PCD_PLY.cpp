#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <chrono>

#include <fstream>

#define DEPTH_WIDTH 640
#define DEPTH_HEIGHT 480


#define RGB_WIDTH 1920
#define RGB_HEIGHT 1080

#define RGBD_WINDOW_NAME "RGBD"
#define RGB_WINDOW_NAME "RGB"
#define TOF_WINDOW_NAME "TOF"



unsigned long getTimestamp()
{
	return std::chrono::system_clock::now().time_since_epoch().count() /std::chrono::system_clock::period::den;
}

void Render(uint8_t* piexls_depth, uint8_t* piexls_rgb, int width, int height)
{
	cv::Mat gray16_img(height, width, CV_16UC1, piexls_depth);
	cv::Mat normalize_img;
	cv::Mat depth_color_img;
	cv::Mat gray8_img = cv::Mat::zeros(gray16_img.size(), CV_8U);
	cv::normalize(gray16_img, normalize_img, 0, 255, cv::NORM_MINMAX);
	cv::convertScaleAbs(normalize_img, gray8_img);
	cv::cvtColor(gray8_img, depth_color_img, cv::COLOR_GRAY2BGR);

	cv::Mat rgb_img(height, width, CV_8UC3, piexls_rgb);
	//cv::cvtColor(rgb_img, rgb_img, cv::COLOR_BGR2RGB);



	//RGBD�ϳ�ͼ
	cv::Mat rgbd_img(height, width, CV_8UC3, cv::Scalar(0));// rgb_img;
	for (int row = 0; row < rgb_img.rows; row++)
		for (int col = 0; col < rgb_img.cols; col++)
		{
			if (gray16_img.ptr<uint16_t>(row)[col] > 10)
			{
				rgbd_img.ptr<uchar>(row)[col * 3] = rgb_img.ptr<uchar>(row)[col * 3];
				rgbd_img.ptr<uchar>(row)[col * 3 + 1] = rgb_img.ptr<uchar>(row)[col * 3 + 1];
				rgbd_img.ptr<uchar>(row)[col * 3 + 2] = rgb_img.ptr<uchar>(row)[col * 3 + 2];
			}
		}

	cv::namedWindow(RGBD_WINDOW_NAME, cv::WINDOW_NORMAL);
	cv::resizeWindow(RGBD_WINDOW_NAME, width,height);
	cv::imshow(RGBD_WINDOW_NAME, rgbd_img);

}


void show_depth_frame(sy3::depth_frame *frame, const char *name)
{
	if (frame)
	{

		cv::Mat gray16(frame->get_height(), frame->get_width(), CV_16UC1, frame->get_data());
		cv::Mat tmp;
		cv::Mat gray8 = cv::Mat::zeros(gray16.size(), CV_8U);
		cv::normalize(gray16, tmp, 0, 255, cv::NORM_MINMAX);
		cv::convertScaleAbs(tmp, gray8);
		cv::namedWindow(name, cv::WINDOW_NORMAL);
		cv::imshow(name, gray8);
	}
}

void show_rgb_rgb_frame(sy3::frame *frame, const char *name)
{
	if (frame)
	{

		cv::Mat yuvImg(frame->get_height(), frame->get_width(), CV_8UC3, frame->get_data());
		//cv::Mat rgbImg(frame->get_height(), frame->get_width(), CV_8UC3);
		//	cv::cvtColor(yuvImg, rgbImg, cv::ColorConversionCodes::COLOR_BGR2BGR);
		cv::namedWindow(name, cv::WINDOW_NORMAL);
		cv::imshow(name, yuvImg);
		const sy3::stream_profile *rgb_profile = frame->get_profile();
		sy3::sy3_intrinsics rgb_inteinics = rgb_profile->get_intrinsics();
	}
}

void SavePointCloudToPCD_xyz(float* coord3_, int width, int height)
{
	int m_width = width;
	int m_height = height;

	int points_len = m_width* m_height;
	std::string pc_name = "./pointcloud_xyz" + std::to_string(getTimestamp()) + ".pcd";
	std::ofstream fout_pc_name(pc_name);

	fout_pc_name << "# .PCD v0.7 - Point Cloud Data file format" << std::endl;
	fout_pc_name << "VERSION 0.7" << std::endl;
	fout_pc_name << "FIELDS x y z" << std::endl;
	fout_pc_name << "SIZE 4 4 4" << std::endl;
	fout_pc_name << "TYPE F F F" << std::endl;
	fout_pc_name << "COUNT 1 1 1" << std::endl;
	fout_pc_name << "WIDTH " << points_len << std::endl;
	fout_pc_name << "HEIGHT 1" << std::endl;
	fout_pc_name << "VIEWPOINT 0 0 0 1 0 0 0" << std::endl;
	fout_pc_name << "POINTS " << points_len << std::endl;
	fout_pc_name << "DATA ascii" << std::endl;


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
		fout_pc_name << -x << " " << -y << " " << z << std::endl;
	}
	std::cout << "Save succ" << std::endl;

}

void SavePointCloudToPLY_rgbxyz(float* coord3_, sy3::rgb_frame *rgb, int width, int height)
{
	int m_width = width;
	int m_height = height;

	int points_len = m_width * m_height;
	std::string pc_name = "./ply_xyzrgb" + std::to_string(getTimestamp()) + ".ply";
	std::ofstream fout_pc_name(pc_name);

	uint8_t* piexle_rgb = (uint8_t*)rgb->get_data();
	cv::Mat rgb_img(height, width, CV_8UC3, piexle_rgb);

	fout_pc_name << "ply" << std::endl;
	fout_pc_name << "format ascii 1.0" << std::endl;
	fout_pc_name << "element vertex " << points_len << std::endl;
	fout_pc_name << "property float x" << std::endl;
	fout_pc_name << "property float y" << std::endl;
	fout_pc_name << "property float z" << std::endl;
	fout_pc_name << "property uchar red" << std::endl;
	fout_pc_name << "property uchar green" << std::endl;
	fout_pc_name << "property uchar blue" << std::endl;
	fout_pc_name << "element face 0" << std::endl;
	fout_pc_name << "property list uchar int vertex_index" << std::endl;
	fout_pc_name << "end_header" << std::endl;
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
	
		fout_pc_name << -x << " " << -y << " " << z <<" "<< (float)rgb_img.ptr<uchar>(i / m_width)[i%m_width * 3 + 2]<<" "<< (float)rgb_img.ptr<uchar>(i / m_width)[i%m_width * 3 + 1]<<" "<< (float)rgb_img.ptr<uchar>(i / m_width)[i%m_width * 3 + 0] << std::endl;
	}
	std::cout << "Save succ" << std::endl;
}


int keyCode = -1;
bool isSavePCDXYZ = false;
bool isSavePCDRGBXYZ = false;
bool isSavePLYXYZ = false;
bool isSavePLYRGBXYZ = false;
void GetkeyThread()
{
	int key = -1;
	try
	{
		while (true)
		{
			std::cerr << "Enter p to Save PointCloudData " << std::endl;

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
void show_align_rgbd(sy3::depth_frame *depth, sy3::rgb_frame *rgb, sy3::process_engine *engine,bool *isSave) 
{
	sy3::sy3_error e;
	if (depth && rgb)
	{

		sy3::frameset *set = engine->align_to_rgb(depth, rgb, e);
		show_depth_frame(set->get_depth_frame(), "algin_depth");
		show_rgb_rgb_frame(set->get_rgb_frame(), "algin_rgb");
		
		Render((uint8_t*)set->get_depth_frame()->get_data(), (uint8_t*)set->get_rgb_frame()->get_data(), set->get_rgb_frame()->get_width(),
			set->get_rgb_frame()->get_height());

		sy3::sy3_error e2;
		sy3::points* points = engine->comptute_points(set->get_depth_frame(), e2);

		float* data = points->get_points();
		
		if (*isSave==true)
		{
			
			//xyz .pcd
			SavePointCloudToPCD_xyz(data, set->get_rgb_frame()->get_width(), set->get_rgb_frame()->get_height());
			
			//xyz rgb .ply
			//SavePointCloudToPLY_rgbxyz(data,set->get_rgb_frame(), set->get_rgb_frame()->get_width(), set->get_rgb_frame()->get_height());
			*isSave = false;
			cv::waitKey(6000);
			
		}
		
		
		
		delete set;

		
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

int main(int argc, char **argv)
{
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
	std::thread t(GetkeyThread);
	while (!quit)
	{

		sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);
		sy3::depth_frame *depth_frame = frameset->get_depth_frame();
		sy3::rgb_frame *rgb_frame = frameset->get_rgb_frame();

		show_align_rgbd(depth_frame, rgb_frame, pline->get_process_engin(e),&isSavePCDXYZ);

		switch (keyCode) {

		case 'p':
			isSavePCDXYZ = true;
			break;
		case 's':
			break;
		}

		keyCode = -1;
		delete frameset;
		
		cv::waitKey(1);
	}
	system("pause");

	return 0;
}
