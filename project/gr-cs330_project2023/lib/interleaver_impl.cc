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
                gr::io_signature::make(0, 0, 0))

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
    /* TODO: Add your code here */

    /*
     * FIXME: This just copies the input to the output. Even you do not
     * implement the interleaver, it will forward the input message to the next
     * block and everything should work fine
     */
    message_port_pub(pmt::mp("pdu_out"), m);
}



  } /* namespace cs330_project2023 */
} /* namespace gr */
