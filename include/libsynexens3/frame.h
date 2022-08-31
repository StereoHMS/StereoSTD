/**
 * @file frame.h
 * @author HMS
 * @brief 
 * @version 0.0.4
 * @date 2022-04-24
 * 
 * Copyright(c) 2022 HMS.Co.Ltd. All rights reserved
 * 
 */
#ifndef LIBSYNEXENS3_FRAME_H
#define LIBSYNEXENS3_FRAME_H

#include "macros.h"
#include "types.h"
#include "config.h"

namespace SY3_NAMESPACE
{

	class frame
	{

	public:
		/**
		 * \brief フレーム画像の幅を取得する
		 * \return
		 */
		virtual const int get_width() = 0;

		/**
		 * \brief フレーム画像の高さを取得する
		 * \return
		 */
		virtual const int get_height() = 0;

		/**
		 * \brief フレームタイプを取得する
		 * \return
		 */
		virtual const sy3_stream get_type() = 0;

		/**
		 * \brief フレーム画像の配列を取得する
		 * \return
		 */
		virtual void *get_data() = 0;

		/**
		 * \brief フレームコンフィグを取得する
		 * \return
		 */
		virtual const stream_profile *get_profile() const = 0;

		/**
		 * \brief デバッグに使用するフレーム数をローカルに保存する
		 * \param[in] filenam 保存するファイル名
		 * \return
		 */
		virtual int dump(const char *filenam) = 0;

		virtual ~frame() = default;
	};

	class depth_frame : public frame
	{
	public:
		/**
		 * \brief デバイスがサポートするフォーマットを取得する
		 * \return
		 */
		virtual uint8_t *apply_colormap() = 0;
		virtual ~depth_frame() = default;
	};

	class ir_frame : public frame
	{
	public:
		virtual ~ir_frame() = default;
	};

	class rgb_frame : public frame
	{
	public:
		virtual ~rgb_frame() = default;
	};

	class raw_frame : public frame
	{
	public:
		virtual ~raw_frame() = default;
	};

	class points : public frame
	{
	public:
		points(){};

		/**
		 * \brief 点群配列を取得する
		 * \return
		 */
		virtual float *get_points() = 0;
		/**
		 * \brief 点群の長さを取得する
		 * \return
		 */
		virtual int get_length() = 0;

	private:
		void *get_data() override { return nullptr; }
		const stream_profile *get_profile() const override { return nullptr; }
	};

	class frameset
	{

	public:
		frameset(){};

		/**
		 * \brief デプスフレームを取得する
		 * \return
		 */
		virtual depth_frame *get_depth_frame() = 0;

		/**
		 * \brief rgbフレームを取得する
		 * \return
		 */
		virtual rgb_frame *get_rgb_frame() = 0;

		/**
		 * \brief irフレームを取得する
		 * \return
		 */
		virtual ir_frame *get_ir_frame() = 0;

		/**
		 * \brief rawフレームを取得する
		 * \return
		 */
		virtual raw_frame *get_raw_frame() = 0;

		virtual ~frameset(){};
	};

}
#endif