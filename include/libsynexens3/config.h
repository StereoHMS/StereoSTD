/**
 * @file config.h
 * @author HMS
 * @brief 
 * @version 0.0.4
 * @date 2022-04-24
 * 
 * Copyright(c) 2022 HMS.Co.Ltd. All rights reserved
 * 
 */

#ifndef LIBSYNEXENS3_CONFIG_H
#define LIBSYNEXENS3_CONFIG_H

#include <string>
#include "macros.h"
#include "libsynexens3/types.h"

namespace SY3_NAMESPACE
{

	class SY3_EXPORT config
	{
	public:
		config(){};

		/**
		 * \brief 指定された解像度でデータストリームを開きます
		 * \param[in] stream 開くデータストリームのタイプ
		 * \param[in] width  データストリーム画像の幅
		 * \param[in] height データストリーム画像の高さ
		 * \return
		 */
		virtual void enable_stream(sy3_stream stream, uint16_t width, uint16_t height,sy3_error &error) = 0;

		/**
		 * \brief 指定されたデータストリームを閉じる
		 * \param[in] stream 閉じるデータストリームのタイプ
		 * \return
		 */
		virtual void disable_stream(sy3_stream stream,sy3_error &error) = 0;
		
		/**
			 * \brief すべてのデータストリームを閉じる
			 * \return
			 */
		virtual void disable_all_streams(sy3_error &error) = 0;

		/**
		 * \brief 指定されたデータストリームのコンフィグを取得する
		 * \param[in] stream 指定されたデータストリーム
		 * \return
		 */
		//virtual const stream_profile *get_stream_profile(sy3::sy3_stream stream,sy3_error &error) = 0;

	};
}

#endif