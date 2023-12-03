/* -*- c++ -*- */
/*
 * Copyright 2023 gr-chris_module author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CHRIS_MODULE_CONSTELLATION_MAPPING_4569_H
#define INCLUDED_CHRIS_MODULE_CONSTELLATION_MAPPING_4569_H

#include <gnuradio/chris_module/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace chris_module {

    /*!
     * \brief <+description of block+>
     * \ingroup chris_module
     *
     */
    class CHRIS_MODULE_API constellation_mapping_4569 : virtual public gr::sync_block
    {
     public:
      typedef std::shared_ptr<constellation_mapping_4569> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of chris_module::constellation_mapping_4569.
       *
       * To avoid accidental use of raw pointers, chris_module::constellation_mapping_4569's
       * constructor is in a private implementation
       * class. chris_module::constellation_mapping_4569::make is the public interface for
       * creating new instances.
       */
      static sptr make(int mod_bits_cnt=1);
    };

  } // namespace chris_module
} // namespace gr

#endif /* INCLUDED_CHRIS_MODULE_CONSTELLATION_MAPPING_4569_H */
