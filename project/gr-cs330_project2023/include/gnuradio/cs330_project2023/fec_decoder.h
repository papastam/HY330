/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CS330_PROJECT2023_FEC_DECODER_H
#define INCLUDED_CS330_PROJECT2023_FEC_DECODER_H

#include <gnuradio/cs330_project2023/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace cs330_project2023 {

    /*!
     * \brief <+description of block+>
     * \ingroup cs330_project2023
     *
     */
    class CS330_PROJECT2023_API fec_decoder : virtual public gr::block
    {
     public:
      typedef std::shared_ptr<fec_decoder> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of cs330_project2023::fec_decoder.
       *
       * To avoid accidental use of raw pointers, cs330_project2023::fec_decoder's
       * constructor is in a private implementation
       * class. cs330_project2023::fec_decoder::make is the public interface for
       * creating new instances.
       */
      static sptr make(int type = 0);
    };

  } // namespace cs330_project2023
} // namespace gr

#endif /* INCLUDED_CS330_PROJECT2023_FEC_DECODER_H */
