#ifndef LIBSYNEXENS3_PLATFORM_PLATFORM_INTERFACE_H
#define LIBSYNEXENS3_PLATFORM_PLATFORM_INTERFACE_H

#include "macros.h"
#include "common/paraments_calib.pb.h"

namespace SY3_NAMESPACE
{

	namespace platform
	{

		struct request_format
		{
			int width;
			int height;
			int type;
		};

		class SY3_EXPORT onframe_callback
		{
		public:
			virtual void onframe(uint8_t *buffer, long size, void *ptr) = 0;
		};

		class SY3_EXPORT platform_interface
		{

		public:
			uint16_t vid_;
			uint16_t pid_;
			ParamentsCalib paraments_calib_depth_320_240_;
			ParamentsCalib paraments_calib_depth_640_480_;
			onframe_callback *onframe_;
			virtual int open() = 0;
			virtual int start(onframe_callback *onframe) = 0;
			virtual int stop() = 0;
			virtual int set_format(request_format format_raw, request_format format_depth, request_format format_ir, request_format format_rgb) = 0;
			virtual int get_calib_depth_320_240(ParamentsCalib &paraments_calib_depth_320_240) = 0;
			virtual int get_calib_depth_640_480(ParamentsCalib &paraments_calib_depth_640_480) = 0;
			virtual void write_calib_depth_320_240(uint8_t *data, uint16_t size) = 0;
			virtual	void write_calib_depth_640_480(uint8_t *data, uint16_t size)=0;
			virtual int set_exposure(uint16_t value) = 0;
			virtual int get_exposure(uint16_t &value) = 0;
			virtual std::string get_fw_version()=0;
			virtual std::string get_device_sn()=0;

			virtual int set_rgb_image_flip(uint16_t value) = 0;
			virtual int set_rgb_image_mirror(uint16_t value) = 0;
			virtual int set_tof_image_flip(uint16_t value) = 0;
			virtual int set_tof_image_mirror(uint16_t value) = 0;
			virtual int set_depth_image_mirror(uint16_t value) = 0;
			virtual int set_depth_image_flip(uint16_t value) = 0;
			virtual int set_depth_image_filter(uint16_t value) = 0;

		protected:
		};
	};

};

#endif