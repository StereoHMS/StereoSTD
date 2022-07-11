/**
 * @file context.h
 * @author HMS
 * @brief
 * @version 0.0.4
 * @date 2022-04-24
 *
 * Copyright(c) 2022 HMS.Co.Ltd. All rights reserved
 *
 */
#ifndef LIBSYNEXENS3_CONTEXT_H
#define LIBSYNEXENS3_CONTEXT_H

#include <memory>
#include "macros.h"
#include "device-info.h"

namespace SY3_NAMESPACE
{

	class SY3_EXPORT context
	{

	public:

		/**
		 * \brief デバイス情報を取得する
		 * \return
		 */
		virtual const device_info *get_device_info(sy3_error &error) const = 0;

		/**
		 * \brief デバイスを探す
		 * \return
		 */
		virtual device *query_device(sy3_error &error) const = 0;
	};

};

#endif