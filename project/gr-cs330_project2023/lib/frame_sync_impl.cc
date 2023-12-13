/* -*- c++ -*- */
/*
 * Copyright 2023 no.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/io_signature.h>
#include "frame_sync_impl.h"
#include "../include/gnuradio/cs330_project2023/shift_reg.h"

namespace gr {
  namespace cs330_project2023 {

    bool get_indexed_bit(uint8_t input, unsigned index){
      return (input >> index) & 0x01;
    }

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
              d_mod((mod_t)mod),
              d_state(SEARCH_PREAMBLE),
              d_preamble(preamble),
              d_preamble_len(preamble_len),
              d_sync_word(sync_word)
    {
      message_port_register_out(pmt::mp("pdu"));
      // d_preamble_shift_reg            = shift_reg((preamble_len/2)*8);
      // d_preamble_prototype_shift_reg  = &shift_reg((preamble_len/2)*8);
      // d_syncword_shift_reg            = &shift_reg((sync_word.size()/2)*8);
      // d_syncword_prototype_shift_reg  = &shift_reg((sync_word.size()/2)*8);

      // // Initialize the preamble prototype shift register
      // for(int i = 0; i < preamble_len/2; i++){
      //   d_preamble_prototype_shift_reg->push_back(get_indexed_bit(preamble, 0));
      //   d_preamble_prototype_shift_reg->push_back(get_indexed_bit(preamble, 1));
      //   d_preamble_prototype_shift_reg->push_back(get_indexed_bit(preamble, 2));
      //   d_preamble_prototype_shift_reg->push_back(get_indexed_bit(preamble, 3));
      //   d_preamble_prototype_shift_reg->push_back(get_indexed_bit(preamble, 4));
      //   d_preamble_prototype_shift_reg->push_back(get_indexed_bit(preamble, 5));
      //   d_preamble_prototype_shift_reg->push_back(get_indexed_bit(preamble, 6));
      //   d_preamble_prototype_shift_reg->push_back(get_indexed_bit(preamble, 7));
      // }

      // // Initialize the sync word prototype shift register  
      // for(int i = 0; i < sync_word.size(); i++){
      //   d_syncword_prototype_shift_reg->push_back(get_indexed_bit(sync_word[i], 0));
      //   d_syncword_prototype_shift_reg->push_back(get_indexed_bit(sync_word[i], 1));
      //   d_syncword_prototype_shift_reg->push_back(get_indexed_bit(sync_word[i], 2));
      //   d_syncword_prototype_shift_reg->push_back(get_indexed_bit(sync_word[i], 3));
      //   d_syncword_prototype_shift_reg->push_back(get_indexed_bit(sync_word[i], 4));
      //   d_syncword_prototype_shift_reg->push_back(get_indexed_bit(sync_word[i], 5));
      //   d_syncword_prototype_shift_reg->push_back(get_indexed_bit(sync_word[i], 6));
      //   d_syncword_prototype_shift_reg->push_back(get_indexed_bit(sync_word[i], 7));
      // }
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

    // Print all bytes of the input in hex
    int i=0;
    while(*in != '\0'){
      printf("%02x ", in[i]);
      i++;
    }

    // // Take a copy of the input byte
    // uint8_t in_byte = *in;

    // // Implement the FSM in a infinite loop
    // while(true){
    //   // extract the next sample from the input stream
    //   bool sample = (in_byte & 0x01) == 0x01;
    //   in_byte >>= 1;

    //   // SEARCH_PREAMBLE state
    //   if(d_state == SEARCH_PREAMBLE){
    //     // insert the input sample to the preamble shift register
    //     d_preamble_shift_reg->push_back(sample);


        
      
      // }



    // }
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
