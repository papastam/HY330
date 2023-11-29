/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/io_signature.h>
#include "lab1_block_impl.h"

namespace gr {
  namespace lab1_module {

    #pragma message("set the following appropriately and remove this warning")
    using input_type = float;
    #pragma message("set the following appropriately and remove this warning")
    using output_type = float;
    lab1_block::sptr
    lab1_block::make(float max_amplitude)
    {
      return gnuradio::make_block_sptr<lab1_block_impl>(
        max_amplitude);
    }


    /*
     * The private constructor
     */
    lab1_block_impl::lab1_block_impl(float max_amplitude)
      : gr::sync_block("lab1_block",
              gr::io_signature::make(1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
              gr::io_signature::make(1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)),
              d_clip(max_amplitude)
              )
    {}

    /*
     * Our virtual destructor.
     */
    lab1_block_impl::~lab1_block_impl()
    {
    }

    int
    lab1_block_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float* in = static_cast<const input_type*>(input_items[0]);
      float* out = static_cast<output_type*>(output_items[0]);

      for(int i=0; i<noutput_items; i++)
      {
        if(in[i] > d_clip)
        {
          out[i] = d_clip;
        }
        else if(in[i] < -d_clip)
        {
          out[i] = -d_clip;
        }
        else
        {
          out[i] = in[i];
        }
      }

      return noutput_items;
    }

  } /* namespace lab1_module */
} /* namespace gr */
