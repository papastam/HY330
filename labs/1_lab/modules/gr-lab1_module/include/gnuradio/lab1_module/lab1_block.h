/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_LAB1_MODULE_LAB1_BLOCK_H
#define INCLUDED_LAB1_MODULE_LAB1_BLOCK_H

#include <gnuradio/lab1_module/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace lab1_module {

    /*!
     * \brief <+description of block+>
     * \ingroup lab1_module
     *
     */
    class LAB1_MODULE_API lab1_block : virtual public gr::sync_block
    {
     public:
      typedef std::shared_ptr<lab1_block> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of lab1_module::lab1_block.
       *
       * To avoid accidental use of raw pointers, lab1_module::lab1_block's
       * constructor is in a private implementation
       * class. lab1_module::lab1_block::make is the public interface for
       * creating new instances.
       */
      static sptr make(float max_amplitude = 1.0f);
    };

  } // namespace lab1_module
} // namespace gr

#endif /* INCLUDED_LAB1_MODULE_LAB1_BLOCK_H */
