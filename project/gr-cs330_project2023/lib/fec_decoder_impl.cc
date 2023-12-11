/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/io_signature.h>
#include "fec_decoder_impl.h"

namespace gr {
  namespace cs330_project2023 {

    fec_decoder::sptr
    fec_decoder::make(int type)
    {
      return gnuradio::make_block_sptr<fec_decoder_impl>(
        type);
    }


    /*
     * The private constructor
     */
    fec_decoder_impl::fec_decoder_impl(int type)
      : gr::block("fec_decoder",
                gr::io_signature::make(0, 0, 0),
                gr::io_signature::make(0, 0, 0)),
      d_type(type)

    {
    message_port_register_in(pmt::mp("pdu_in"));
    message_port_register_out(pmt::mp("pdu_out"));

    /* Register the message handler. For every message received in the input
     * message port it will be called automatically.
     */
    set_msg_handler(pmt::mp("pdu_in"),
    [this](pmt::pmt_t msg) {
        this->fec_decoder_impl::decode(msg);
    });

    }

    /*
     * Our virtual destructor.
     */
    fec_decoder_impl::~fec_decoder_impl()
    {
    }

 
void
fec_decoder_impl::decode(pmt::pmt_t m)
{
    switch (d_type) {
    /* No FEC just copy the input message to the output */
    case 0:
        message_port_pub(pmt::mp("pdu_out"), m);
        return;
    case 1:
        /* Do Hamming encoding */
        return;
    case 2:
        /* Do Golay encoding */
        return;
    default:
        throw std::runtime_error("fec_decoder: Invalid FEC");
        return;
    }
}



  } /* namespace cs330_project2023 */
} /* namespace gr */
