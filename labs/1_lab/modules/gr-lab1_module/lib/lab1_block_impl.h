/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_LAB1_MODULE_LAB1_BLOCK_IMPL_H
#define INCLUDED_LAB1_MODULE_LAB1_BLOCK_IMPL_H

#include <gnuradio/lab1_module/lab1_block.h>

namespace gr {
  namespace lab1_module {

    class lab1_block_impl : public lab1_block
    {
     private:
      float d_max_amplitude;

     public:
      lab1_block_impl(float max_amplitude);
      ~lab1_block_impl();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace lab1_module
} // namespace gr

#endif /* INCLUDED_LAB1_MODULE_LAB1_BLOCK_IMPL_H */
