/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/io_signature.h>
#include "frame_sync_impl.h"

namespace gr {
  namespace cs330_project2023 {

    frame_sync::sptr
    frame_sync::make(uint8_t preamble, uint8_t preamble_len,const std::vector<uint8_t> &sync_word, int mod)
    {
      return gnuradio::make_block_sptr<frame_sync_impl>(
        preamble, preamble_len, sync_word, mod);
    }


    /*
     * The private constructor
     */
    frame_sync_impl::frame_sync_impl(uint8_t preamble, uint8_t preamble_len,const std::vector<uint8_t> &sync_word, int mod)
      : gr::sync_block("frame_sync",
              gr::io_signature::make(1, 1, sizeof(uint8_t)),
              gr::io_signature::make(0,0,0)),
              d_mod((mod_t)mod)
    {
        message_port_register_out(pmt::mp("pdu"));
    }

    /*
     * Our virtual destructor.
     */
    frame_sync_impl::~frame_sync_impl()
    {
    }

    int
    frame_sync_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
    const uint8_t *in = (const uint8_t *) input_items[0];

    // Do <+signal processing+>
    /*
     * GNU Radio handles PMT messages in a pair structure.
     * The first element corresonds to possible metadata (in our case we do not
     * have assosiated metadata) whereas the second element contains the
     * data in a vector of uint8_t.
     *
     * When the frame is extracted, you will possible hold it in a *uint8_t buffer,
     * To create a PMT pair message you can use:
     * pmt::pmt_t pair = pmt::cons(pmt::PMT_NIL, pmt::init_u8vector(frame_len, buf));
     *
     * Then you can send this message to the port we have registered at the contructpr
     * using:
     *
     * message_port_pub(pmt::mp("pdu"), pair);
     */


      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace cs330_project2023 */
} /* namespace gr */
