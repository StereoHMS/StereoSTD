#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <fstream>

#define RAW_WIDTH 1280
#define RAW_HEIGHT 960


#define DEPTH_WIDTH 640
#define DEPTH_HEIGHT 480



#define RGB_WIDTH 1920
#define RGB_HEIGHT 1080

void SavePointCloud(float* coord3_, std::string path) {

	int m_width = 640;
	int m_height = 480;

	std::fstream points;

	points.open(path, std::fstream::out);
	points << "ply" << std::endl;
	points << "			format ascii 1.0" << std::endl;
	points << "			element vertex " << m_width * m_height << std::endl;
	points << "			property float x" << std::endl;
	points << "			property float y" << std::endl;
	points << "			property float z" << std::endl;
	points << "			element face 0" << std::endl;
	points << "			property list uchar int vertex_index" << std::endl;
	points << "			end_header" << std::endl;

	std::string writestring;

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

		writestring += std::to_string(x) + " " + std::to_string(y) + " " +
			std::to_string(z) + "\n";
	}
	points << writestring;
	points.close();
}


void show_point_cloud_frame(sy3::depth_frame *frame, const char* name,sy3::process_engine* engine,float index)
{
	if (frame) {

		sy3::sy3_error e;
		sy3::points* points = engine->comptute_points(frame,e);
		std::string path = "./tof_pointcloud_" + std::to_string(index)+".ply";
		//std::cout << points->get_length() << std::endl;
		std::cout <<" write point cloud ...."<< path <<std::endl;
		float* data = points->get_points();		
		SavePointCloud(data,path);
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

int main(int argc, char **argv)
{
	sy3::sy3_error e;
	printf("version:%s \n", sy3::sy3_get_version(e));
	sy3::context *ctx = sy3::sy3_create_context(e);
	sy3::device *dev = ctx->query_device(e);

	print_support_format(dev, e);
	print_device_info(dev);

	sy3::pipeline *pline = sy3::sy3_create_pipeline(ctx, e);

	sy3::config *cfg = sy3_create_config(e);
	cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_DEPTH, DEPTH_WIDTH, DEPTH_HEIGHT, e);

	pline->start(cfg, e);

	
	uint16_t exposure = 0;
	bool quit = false;
	float index = 0;
	while (!quit)
	{
		index+=1.000;
		std::ofstream ofs;
		
		sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);

		sy3::depth_frame *depth_frame = frameset->get_depth_frame();
		show_point_cloud_frame(depth_frame, "POINT_CLOUD", pline->get_process_engin(e),index);

		delete frameset;
		switch (cv::waitKey(1))
		{

		case 'm':
		{
			const sy3::sensor *cs30_sensor = pline->get_device(e)->get_sensor(e);
			cs30_sensor->set_option(sy3::sy3_option::SY3_OPTION_DEPTH_IMAGE_MIRROR, 1, e);
		}
		break;

		case 'M':
		{
			const sy3::sensor *cs30_sensor = pline->get_device(e)->get_sensor(e);
			cs30_sensor->set_option(sy3::sy3_option::SY3_OPTION_DEPTH_IMAGE_MIRROR, 0, e);
		}
		break;

		case 'q':
		{
			pline->stop(e);
			quit = true;
		}
		break;
		}
	}
	system("pause");

	return 0;
}
