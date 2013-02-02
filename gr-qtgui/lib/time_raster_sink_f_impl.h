/* -*- c++ -*- */
/*
 * Copyright 2012,2013 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_QTGUI_TIME_RASTER_SINK_F_IMPL_H
#define INCLUDED_QTGUI_TIME_RASTER_SINK_F_IMPL_H

#include <qtgui/time_raster_sink_f.h>
#include <filter/firdes.h>
#include <fft/fft.h>
#include <gruel/high_res_timer.h>
#include <gruel/thread.h>
#include <timerasterdisplayform.h>

namespace gr {
  namespace qtgui {

    class QTGUI_API time_raster_sink_f_impl : public time_raster_sink_f
    {
    private:
      void initialize();

      std::string d_name;
      int d_nconnections;

      int d_index;
      std::vector<double*> d_residbufs;

      float *d_tmpflt;

      QWidget *d_parent;
      TimeRasterDisplayForm *d_main_gui;

      int d_icols;
      double d_rows, d_cols;
      std::vector<float> d_mult;
      std::vector<float> d_offset;
      double d_samp_rate;

      gruel::high_res_timer_type d_update_time;
      gruel::high_res_timer_type d_last_time;

    public:
      time_raster_sink_f_impl(double samp_rate,
			      double rows, double cols,
 			      const std::vector<float> &mult,
			      const std::vector<float> &offset,
			      const std::string &name,
			      int nconnections,
			      QWidget *parent=NULL);
      ~time_raster_sink_f_impl();

      bool check_topology(int ninputs, int noutputs);

      void exec_();
      QWidget*  qwidget();
      PyObject* pyqwidget();

      void set_update_time(double t);
      void set_title(const std::string &title);
      void set_line_label(const std::string &label);
      void set_line_color(const std::string &color);
      void set_line_width(int width);
      void set_line_style(Qt::PenStyle style);
      void set_line_marker(QwtSymbol::Style marker);

      void set_size(int width, int height);

      void set_num_rows(double rows);
      void set_num_cols(double cols);

      void set_multiplier(const std::vector<float> &mult);
      void set_offset(const std::vector<float> &offset);

      void set_intensity_range(float min, float max);

      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } /* namespace qtgui */
} /* namespace gr */

#endif /* INCLUDED_QTGUI_TIME_RASTER_SINK_F_IMPL_H */
