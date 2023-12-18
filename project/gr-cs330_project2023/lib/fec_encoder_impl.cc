/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/io_signature.h>
#include "fec_encoder_impl.h"

namespace gr {
  namespace cs330_project2023 {


    fec_encoder::sptr
    fec_encoder::make(int type)
    {
      return gnuradio::make_block_sptr<fec_encoder_impl>(
        type);
    }


    /*
     * The private constructor
     */
    fec_encoder_impl::fec_encoder_impl(int type)
      : gr::block("fec_encoder",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(0,0,0)),
              d_type(type)
    {
        message_port_register_in(pmt::mp("pdu_in"));
    message_port_register_out(pmt::mp("pdu_out"));

    /*
     * Register the message handler. For every message received in the input
     * message port it will be called automatically.
     */
    set_msg_handler(pmt::mp("pdu_in"),
    [this](pmt::pmt_t msg) {
        this->fec_encoder_impl::encode(msg);
    });

}

    /*
     * Our virtual destructor.
     */
    fec_encoder_impl::~fec_encoder_impl()
    {
    }

void
fec_encoder_impl::encode(pmt::pmt_t m)
{
    uint8_t *bytes_out = nullptr;
    uint8_t *bits_out = nullptr;
    pmt::pmt_t bytes(pmt::cdr(m));

    switch (d_type) {
        /* No FEC just copy the input message to the output */
        case 0:
            message_port_pub(pmt::mp("pdu_out"), m);
            return;
        case 1:
            size_t pdu_length;
            const uint8_t *bytes_in = pmt::u8vector_elements(bytes, pdu_length);
            
            bytes_out = new uint8_t[pdu_length*3];
            bits_out = new uint8_t[(pdu_length*3)*8];

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
            return;
        case 2:
            /* Do Golay encoding */
            return;
        default:
            throw std::runtime_error("fec_encoder: Invalid FEC");
            return;
    }
}



  } /* namespace cs330_project2023 */
} /* namespace gr */
