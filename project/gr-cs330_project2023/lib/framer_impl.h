/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CS330_PROJECT2023_FRAMER_IMPL_H
#define INCLUDED_CS330_PROJECT2023_FRAMER_IMPL_H

#include <gnuradio/cs330_project2023/framer.h>

namespace gr {
  namespace cs330_project2023 {

    class framer_impl : public framer
    {
     private:
      void
      construct(pmt::pmt_t m);


     public:
      framer_impl(uint8_t preamble, size_t preamble_len,const std::vector<uint8_t> &sync_word);
      ~framer_impl();

    };

  } // namespace cs330_project2023
} // namespace gr

#endif /* INCLUDED_CS330_PROJECT2023_FRAMER_IMPL_H */
