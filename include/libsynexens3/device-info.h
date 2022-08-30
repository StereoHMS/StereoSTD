/**
 * @file device-info.h
 * @author HMS
 * @brief 
 * @version 0.0.4
 * @date 2022-04-24
 * 
 * Copyright(c) 2022 HMS.Co.Ltd. All rights reserved
 * 
 */
#ifndef LIBSYNEXENS3_DEVICE_INFO_H
#define LIBSYNEXENS3_DEVICE_INFO_H

#include "macros.h"
#include "device.h"
#include "types.h"

namespace SY3_NAMESPACE
{

	class SY3_EXPORT device_info
	{

	public:
		/**
		 * \brief デバイスタイプを取得する
		 * \return
		 */
		virtual const sy3_device_type get_device_type(sy3_error &error) const = 0;

		/**
		 * \brief デバイスハンドルを取得する
		 * \return
		 */
		virtual const device *get_device(sy3_error &error) const = 0;

		virtual ~device_info() = default;

		
	};

};

#endif