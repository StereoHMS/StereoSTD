/**
 * @file pipeline.h
 * @author HMS
 * @brief 
 * @version 0.0.4
 * @date 2022-04-24
 * 
 * Copyright(c) 2022 HMS.Co.Ltd. All rights reserved
 * 
 */
#ifndef LIBSYNEXENS3_PIPELINE_H
#define LIBSYNEXENS3_PIPELINE_H
#include <mutex>

#include "macros.h"
#include "frame.h"
#include "context.h"
#include"process-engine.h"
#include"types.h"

namespace SY3_NAMESPACE
{

	class SY3_EXPORT pipeline
	{

	public:
		/**
		 * \brief pipelineを開く
		 * \param[in] cfg pipelineコンフィグ
		 * \return
		 */
		virtual void start(const config *cfg,sy3_error &error) = 0;


		virtual process_engine* get_process_engin(sy3_error &error)=0;

		/**
		 * \brief pipelineを閉じる
		 * \return
		 */
		virtual void stop(sy3_error &error) = 0;

		/**
		 * \brief pipelinenフレームセットを取得する
		 * \param[in] timeout_ms タイムアウト
		 * \return frameset,メモリを手動で解放する
		 */
		virtual frameset *wait_for_frames(unsigned int timeout_ms,sy3_error &error) = 0;

		/**
		 * \brief 現在のデバイスを取得する
		 * \return
		 */
		virtual const device *get_device(sy3_error &error) = 0;


		virtual ~pipeline() = default;
	};

};

#endif