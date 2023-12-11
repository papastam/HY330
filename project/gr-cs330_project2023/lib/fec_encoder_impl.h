/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CS330_PROJECT2023_FEC_ENCODER_IMPL_H
#define INCLUDED_CS330_PROJECT2023_FEC_ENCODER_IMPL_H

#include <gnuradio/cs330_project2023/fec_encoder.h>

namespace gr {
  namespace cs330_project2023 {

    class fec_encoder_impl : public fec_encoder
    {
     private:
    const int d_type;

    void encode(pmt::pmt_t m);

     public:
      fec_encoder_impl(int type);
      ~fec_encoder_impl();

    };

  } // namespace cs330_project2023
} // namespace gr

#endif /* INCLUDED_CS330_PROJECT2023_FEC_ENCODER_IMPL_H */
