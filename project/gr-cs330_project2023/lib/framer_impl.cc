/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/io_signature.h>
#include "framer_impl.h"

namespace gr {
  namespace cs330_project2023 {

    framer::sptr
    framer::make(uint8_t preamble, size_t preamble_len,const std::vector<uint8_t> &sync_word)
    {
      return gnuradio::make_block_sptr<framer_impl>(
        preamble, preamble_len, sync_word);
    }


    /*
     * The private constructor
     */
    framer_impl::framer_impl(uint8_t preamble, size_t preamble_len,const std::vector<uint8_t> &sync_word)
      : gr::block("framer",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(0,0,0))
    {
    message_port_register_in(pmt::mp("pdu"));
    message_port_register_out(pmt::mp("frame"));

    /*
     * Register the message handler. For every message received in the input
     * message port it will be called automatically.
     */
    set_msg_handler(pmt::mp("pdu"),
    [this](pmt::pmt_t msg) {
        this->framer_impl::construct(msg);
    });

    }
    
    
    void
framer_impl::construct(pmt::pmt_t m)
{
    /* Extract the bytes of the PDU. GNU Radio handles PDUs in pairs.
     * The first element of the pair contains metadata associated with  the
     * PDU, whereas the second element of the pair is a pmt with a u8 vector
     * containing the raw bytes. Below there is an example how to get the
     * PDU raw pointer and the length of the frame in bytes that points to
     */
    pmt::pmt_t meta(pmt::car(m));
    pmt::pmt_t bytes(pmt::cdr(m));
    /* Access the raw bytes of the PDU */
    size_t pdu_len;
    const uint8_t *bytes_in = pmt::u8vector_elements(bytes, pdu_len);

    /*
     * TODO: Do processing
     */
    /*
     * FIXME: This just copies the input to the output. It is just for testing
     * purposes.
     * NOTE: Obey the pair scheme that GNU Radio uses otherwise following
     * blocks will not work. In your case if you do not have any associated
     * metadata, place just pmt::PMT_NIL on the first element of the pair
     */
    message_port_pub(pmt::mp("frame"), pmt::cons(pmt::PMT_NIL, bytes));
}


    /*
     * Our virtual destructor.
     */
    framer_impl::~framer_impl()
    {
    }



  } /* namespace cs330_project2023 */
} /* namespace gr */
