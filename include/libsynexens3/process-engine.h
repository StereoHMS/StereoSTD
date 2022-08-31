/**
 * @file process-engine.h
 * @author synexens
 * @brief 
 * @version 0.0.4
 * @date 2022-04-24
 * 
 * Copyright(c) 2022 synexens.Co.Ltd. All rights reserved
 * 
 */
#ifndef LIBSYNEXENS3_PROCESSING_ENGINE_H
#define LIBSYNEXENS3_PROCESSING_ENGINE_H

#include "macros.h"
#include "types.h"
#include "frame.h"

namespace SY3_NAMESPACE
{

	class SY3_EXPORT process_engine
	{

	public:
		/**
		 * \brief 点群を計算する
		 * \param[in] depth デプスフレーム
		 * \return points，手動でメモリを解放
		 */
		virtual points *comptute_points(depth_frame *depth,sy3_error &error) const =0;

		/**
		 * \brief rgbd位置合わせ
		 * \param[in] depth depthフレーム
		 * \param[in] rgb  rgbフレーム
		 * \return frameset，手動でメモリを解放
		 */
		virtual sy3::frameset *align_to_rgb(depth_frame *depth, rgb_frame *rgb,sy3_error &error) =0;

	};

};

#endif