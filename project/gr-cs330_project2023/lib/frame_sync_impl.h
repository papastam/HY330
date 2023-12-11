/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CS330_PROJECT2023_FRAME_SYNC_IMPL_H
#define INCLUDED_CS330_PROJECT2023_FRAME_SYNC_IMPL_H

#include <gnuradio/cs330_project2023/frame_sync.h>

namespace gr {
  namespace cs330_project2023 {

    class frame_sync_impl : public frame_sync
    {
     private:
    typedef enum {
        BPSK,
        QPSK
    } mod_t;

    const mod_t d_mod;


     public:
      frame_sync_impl(uint8_t preamble, uint8_t preamble_len,const std::vector<uint8_t> &sync_word, int mod);
      ~frame_sync_impl();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace cs330_project2023
} // namespace gr

#endif /* INCLUDED_CS330_PROJECT2023_FRAME_SYNC_IMPL_H */
