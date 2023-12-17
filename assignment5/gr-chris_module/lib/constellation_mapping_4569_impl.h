/* -*- c++ -*- */
/*
 * Copyright 2023 gr-chris_module author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CHRIS_MODULE_CONSTELLATION_MAPPING_4569_IMPL_H
#define INCLUDED_CHRIS_MODULE_CONSTELLATION_MAPPING_4569_IMPL_H

#include <gnuradio/chris_module/constellation_mapping_4569.h>

namespace gr {
  namespace chris_module {

    class constellation_mapping_4569_impl : public constellation_mapping_4569
    {
     private:
      int _mod_bits_cnt;

     public:
      constellation_mapping_4569_impl(int mod_bits_cnt);
      ~constellation_mapping_4569_impl();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace chris_module
} // namespace gr

#endif /* INCLUDED_CHRIS_MODULE_CONSTELLATION_MAPPING_4569_IMPL_H */
