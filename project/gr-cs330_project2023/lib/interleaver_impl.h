/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CS330_PROJECT2023_INTERLEAVER_IMPL_H
#define INCLUDED_CS330_PROJECT2023_INTERLEAVER_IMPL_H

#include <gnuradio/cs330_project2023/interleaver.h>

namespace gr {
  namespace cs330_project2023 {

    class interleaver_impl : public interleaver
    {
     private:
    void
    interleave(pmt::pmt_t m);


     public:
      interleaver_impl(size_t block_size);
      ~interleaver_impl();

    };

  } // namespace cs330_project2023
} // namespace gr

#endif /* INCLUDED_CS330_PROJECT2023_INTERLEAVER_IMPL_H */
