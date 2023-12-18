/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/io_signature.h>
#include "interleaver_impl.h"

namespace gr {
  namespace cs330_project2023 {

    interleaver::sptr
    interleaver::make(size_t block_size)
    {
      return gnuradio::make_block_sptr<interleaver_impl>(
        block_size);
    }


    /*
     * The private constructor
     */
    interleaver_impl::interleaver_impl(size_t block_size)
      : gr::block("interleaver",
                gr::io_signature::make(0, 0, 0),
                gr::io_signature::make(0, 0, 0)),
                d_block_size(block_size)
    {
    message_port_register_in(pmt::mp("pdu_in"));
    message_port_register_out(pmt::mp("pdu_out"));

    /* Register the message handler. For every message received in the input
     * message port it will be called automatically.
     */
    set_msg_handler(pmt::mp("pdu_in"),
    [this](pmt::pmt_t msg) {
        this->interleaver_impl::interleave(msg);
    });
    
    }

    /*
     * Our virtual destructor.
     */
    interleaver_impl::~interleaver_impl()
    {
    }


void
interleaver_impl::interleave(pmt::pmt_t m)
{ 
    pmt::pmt_t bytes(pmt::cdr(m));
    size_t pdu_length;
    const uint8_t *bytes_in = pmt::u8vector_elements(bytes, pdu_length);
    
    uint8_t *bytes_out = new uint8_t[pdu_length*3];
    uint8_t *bits_out = new uint8_t[pdu_length*3*8];

    for(int byteindex = 0; byteindex < pdu_length; byteindex++){
      for(int bitindex = 0; bitindex < 8; bitindex++){
        bits_out[byteindex*3]   = (bytes_in[byteindex] & (0x01 << bitindex)) >> bitindex;
        bits_out[byteindex*3+1] = (bytes_in[byteindex] & (0x01 << bitindex)) >> bitindex;
        bits_out[byteindex*3+2] = (bytes_in[byteindex] & (0x01 << bitindex)) >> bitindex;
      }
    }

    for(int byteindex = 0; byteindex < pdu_length*3; byteindex++){
      for(int bitindex = 0; bitindex < 8; bitindex++){
        bytes_out[byteindex] |= bits_out[byteindex*8+bitindex] << bitindex;
      }
    }

    message_port_pub(pmt::mp("pdu_out"), pmt::init_u8vector(pdu_length*3, bytes_out));
}



  } /* namespace cs330_project2023 */
} /* namespace gr */
