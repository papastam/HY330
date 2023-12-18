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

bool calculate_ham(bool bit1, bool bit2, bool bit3){
  // Calculate the average of the 3 bits
  int sum = ((int) bit1 + (int) bit2 + (int) bit3);
  if (sum >= 2){
    return true;
  }
  return false;
}
 
void
fec_decoder_impl::decode(pmt::pmt_t m)
{
    pmt::pmt_t bytes(pmt::cdr(m));
    size_t pdu_len;
    const uint8_t *bytes_in = pmt::u8vector_elements(bytes, pdu_len);

    uint8_t *bytes_out = nullptr;
    uint8_t *bits_out = nullptr;

    uint bitcnt = 0;

    bool bit1 = false;
    bool bit2 = false;
    bool bit3 = false;

    switch (d_type) {
    /* No FEC just copy the input message to the output */
    case 0:
        message_port_pub(pmt::mp("pdu_out"), m);
        return;
    case 1:
        /* Do Hamming encoding */
        bytes_out = new uint8_t[pdu_len/3];
        bits_out = new uint8_t[(pdu_len*8)/3];
        
        for(uint byteindex; byteindex < pdu_len/3; byteindex++){
          for(uint bitindex; bitindex < 8; bitindex++){
            // 3 cases for each index of the bit
            if(bitcnt == 0 ){
              bit1 = (bytes_in[byteindex] & (0x01 << bitindex)) >> bitindex;
              bitcnt++;
            }else if(bitcnt == 1){
              bit2 = (bytes_in[byteindex] & (0x01 << bitindex)) >> bitindex;
              bitcnt++;
            }else if(bitcnt == 2){
              bit3 = (bytes_in[byteindex] & (0x01 << bitindex)) >> bitindex;
              bitcnt=0;
              bits_out[(byteindex*8)+bitindex] = calculate_ham(bit1, bit2, bit3);
            }
          }
        }

        for(uint byteindex; byteindex < pdu_len/3; byteindex++){
          for(uint bitindex; bitindex < 8; bitindex++){
            bytes_out[byteindex] |= bits_out[(byteindex*8)+bitindex] << bitindex;
          }
        }

        message_port_pub(pmt::mp("pdu_out"), pmt::init_u8vector(pdu_len/3, bytes_out));
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
