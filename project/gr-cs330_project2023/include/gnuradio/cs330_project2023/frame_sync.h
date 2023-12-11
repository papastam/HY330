/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CS330_PROJECT2023_FRAME_SYNC_H
#define INCLUDED_CS330_PROJECT2023_FRAME_SYNC_H

#include <gnuradio/cs330_project2023/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace cs330_project2023 {

    /*!
     * \brief <+description of block+>
     * \ingroup cs330_project2023
     *
     */
    class CS330_PROJECT2023_API frame_sync : virtual public gr::sync_block
    {
     public:
      typedef std::shared_ptr<frame_sync> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of cs330_project2023::frame_sync.
       *
       * To avoid accidental use of raw pointers, cs330_project2023::frame_sync's
       * constructor is in a private implementation
       * class. cs330_project2023::frame_sync::make is the public interface for
       * creating new instances.
       */
      static sptr make(uint8_t preamble, uint8_t preamble_len,const std::vector<uint8_t> &sync_word, int mod);
    };

  } // namespace cs330_project2023
} // namespace gr

#endif /* INCLUDED_CS330_PROJECT2023_FRAME_SYNC_H */
