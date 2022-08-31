
#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#ifndef PCL_NO_PRECOMPILE
#define PCL_NO_PRECOMPILE
#endif
#define _CRT_SECURE_NO_WARNINGS
#include <pcl/common/common.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/point_cloud_color_handlers.h>
#define no_init_all_deprecated

#define DEPTH_WINDOW_NAME "DEPTH"
#define RAW_WIDTH 1280
#define RAW_HEIGHT 960
#define DEPTH_WIDTH 640
#define DEPTH_HEIGHT 480
#define RGB_WIDTH 1920
#define RGB_HEIGHT 1080
//boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
using namespace pcl;
boost::shared_ptr<pcl::visualization::PCLVisualizer> simpleVis(pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud)
{
	// --------------------------------------------
	// -----Open 3D viewer and add point cloud-----
	// --------------------------------------------
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer->setCameraPosition(0, 0, 0, 0, 0, 0, 0, 0, 1);
	viewer->setBackgroundColor(0, 0, 0);
	viewer->addPointCloud<pcl::PointXYZ>(cloud, "sample cloud");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
	viewer->addCoordinateSystem(1.0);
	viewer->initCameraParameters();
	return (viewer);
}

boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;


void showPointCloud(float* coord3_ , sy3::rgb_frame *rgb,int width , int height) {

	uint8_t* piexle_rgb = (uint8_t*)rgb->get_data();
	cv::Mat rgb_img(height, width, CV_8UC3, piexle_rgb);
	//cv::imshow("rgb", rgb_img);
	int m_width = width;
	int m_height = height;
	PointCloud<pcl::PointXYZRGB>::Ptr cloud(new PointCloud<PointXYZRGB>);

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
		pcl::PointXYZRGB p;
		p.x = -x;
		p.y = -y;
		p.z = z;
		p.b = rgb_img.ptr<uchar>(i / m_width)[i%m_width * 3+0];
		p.g = rgb_img.ptr<uchar>(i / m_width)[i%m_width * 3+1];
		p.r = rgb_img.ptr<uchar>(i / m_width)[i%m_width * 3+2];

		cloud->points.push_back(p);

	}
	cloud->width = cloud->points.size();
	cloud->height = 1;

	viewer->removeAllPointClouds();
	viewer->removeAllShapes();

	pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> fildColor(cloud);
	//pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> fildColor(cloud, "z");
	viewer->addPointCloud<pcl::PointXYZRGB>(cloud, fildColor, "sample cloud");
	viewer->spinOnce(100);
}
void showPointCloud(float* coord3_) {

	int m_width = 640;
	int m_height = 480;
	PointCloud<PointXYZ>::Ptr cloud(new PointCloud<PointXYZ>);

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
		pcl::PointXYZ p;
		p.x = -x;
		p.y = -y;
		p.z = z;


		cloud->points.push_back(p);

	}
	cloud->width = cloud->points.size();
	cloud->height = 1;

	viewer->removeAllPointClouds();
	viewer->removeAllShapes();

	//pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> fildColor(cloud);
	pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> fildColor(cloud, "z");
	viewer->addPointCloud<pcl::PointXYZ>(cloud, fildColor, "sample cloud");
	viewer->spinOnce(100);
}

void show_point_cloud_frame(sy3::depth_frame *frame, const char* name, sy3::process_engine* engine, float index)
{
	if (frame) {

		std::cout << "frame down" << std::endl;
		sy3::sy3_error e;
		sy3::points* points = engine->comptute_points(frame, e);

		float* data = points->get_points();
		showPointCloud(data);
		delete points;
	}

}

void show_point_cloud_frame(sy3::depth_frame *frame, sy3::rgb_frame *rgb, const char* name, sy3::process_engine* engine, float index)
{
	if (frame) {

		sy3::sy3_error e;
		sy3::points* points = engine->comptute_points(frame, e);

		float* data = points->get_points();
		showPointCloud(data);
		delete points;
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


		cv::Mat gray16(frame->get_height(), frame->get_width(), CV_16UC1, frame->get_data());
		cv::Mat tmp;
		cv::Mat gray8 = cv::Mat::zeros(gray16.size(), CV_8U);
		cv::normalize(gray16, tmp, 0, 255, cv::NORM_MINMAX);
		cv::convertScaleAbs(tmp, gray8);
		cv::namedWindow(name, cv::WINDOW_NORMAL);
		cv::imshow(name, gray8);

		uint8_t* depth_color = frame->apply_colormap();
		cv::Mat yuvImg(frame->get_height(), frame->get_width(), CV_8UC3, depth_color);





		cv::namedWindow("test", cv::WINDOW_NORMAL);
		cv::resizeWindow("test", frame->get_width(), frame->get_height());
		cv::imshow("test", yuvImg);

		sy3::sy3_intrinsics intrinsics = frame->get_profile()->get_intrinsics();
		//printf("intrinsics: %d x %d \n", intrinsics.width, intrinsics.height);
	}

}
void show_align_rgbd(sy3::depth_frame *depth, sy3::rgb_frame *rgb, sy3::process_engine *engine)
{
	sy3::sy3_error e;
	if (depth && rgb)
	{

		sy3::frameset *set = engine->align_to_rgb(depth, rgb, e);

		sy3::depth_frame *align_depth = set->get_depth_frame();
		sy3::rgb_frame *align_rgb = set->get_rgb_frame();
		std::cout << "depth " << align_depth->get_height() << std::endl;
		std::cout << "rgb " << align_rgb->get_height() << std::endl;
	

		sy3::sy3_error e2;
		sy3::points* points = engine->comptute_points(align_depth, e2);

		float* data = points->get_points();
		int length = points->get_length();
		std::cout << "point length " << length << std::endl;
		showPointCloud(data,align_rgb,1920,1080);
		delete points;
		delete set;
	}
}

int main(int argc, char **argv)
{
	viewer = boost::shared_ptr<pcl::visualization::PCLVisualizer>(new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer->initCameraParameters();
	viewer->setBackgroundColor(0, 0, 0);
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");


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
	float index = 0;
	while (!quit)
	{
		index += 1.000;

		sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);
		sy3::depth_frame *depth_frame = frameset->get_depth_frame();
		sy3::rgb_frame *rgb_frame = frameset->get_rgb_frame();

		show_align_rgbd(depth_frame, rgb_frame, pline->get_process_engin(e));
		



		//show_point_cloud_frame(depth_frame, "POINT_CLOUD", pline->get_process_engin(e), index);
		//show_depth_frame(depth_frame, DEPTH_WINDOW_NAME);

		delete frameset;

		cv::waitKey(1);
	}
	system("pause");

	return 0;
}
