/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CS330_PROJECT2023_DEINTERLEAVER_IMPL_H
#define INCLUDED_CS330_PROJECT2023_DEINTERLEAVER_IMPL_H

#include <gnuradio/cs330_project2023/deinterleaver.h>

namespace gr {
  namespace cs330_project2023 {

    class deinterleaver_impl : public deinterleaver
    {
     private:
    void deinterleave(pmt::pmt_t m);

     public:
      deinterleaver_impl(size_t block_size);
      ~deinterleaver_impl();

    };

  } // namespace cs330_project2023
} // namespace gr

#endif /* INCLUDED_CS330_PROJECT2023_DEINTERLEAVER_IMPL_H */
