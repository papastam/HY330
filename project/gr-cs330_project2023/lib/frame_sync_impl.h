/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CS330_PROJECT2023_FRAME_SYNC_IMPL_H
#define INCLUDED_CS330_PROJECT2023_FRAME_SYNC_IMPL_H

#include <gnuradio/cs330_project2023/frame_sync.h>
#include "../include/gnuradio/cs330_project2023/shift_reg.h"

namespace gr {
  namespace cs330_project2023 {

    class frame_sync_impl : public frame_sync
    {
     private:
    typedef enum {
        BPSK,
        QPSK
    } mod_t;

    typedef enum {
        SEARCH_PREAMBLE,
        SEARCH_SYNC_WORD,
        READ_LENGTH,
        READ_FRAME,
    } state_t;

    uint8_t d_preamble;
    uint8_t d_preamble_len;
    std::vector<uint8_t> d_sync_word;

    const mod_t d_mod;
    state_t d_state;

    shift_reg *d_preamble_shift_reg;
    shift_reg *d_preamble_prototype_shift_reg;
    shift_reg *d_syncword_shift_reg;
    shift_reg *d_syncword_prototype_shift_reg;

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
