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
              d_sync_word(sync_word),
              d_preamble_shift_reg((preamble_len/2)*8),
              d_preamble_prototype_shift_reg((preamble_len/2)*8),
              d_syncword_shift_reg((sync_word.size()/2)*8),
              d_syncword_prototype_shift_reg((sync_word.size()/2)*8)
    {
      message_port_register_out(pmt::mp("pdu"));

      // Initialize the preamble prototype shift register
      for(int i = 0; i < preamble_len/2; i++){
        for(int j = 0; j < 8; j++){
          d_preamble_prototype_shift_reg.push_back(get_indexed_bit(preamble, j));
        }
      }

      // Initialize the sync word prototype shift register  
      for(int i = 0; i < sync_word.size(); i++){
        for(int j = 0; j < 8; j++){
          d_syncword_prototype_shift_reg.push_back(get_indexed_bit(sync_word[i], j));
        }
      }
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

    // Take a copy of the input byte
    uint8_t in_byte = *in;

    int i = 0;
    // Implement the FSM in a infinite loop
    while(true){
      // exit the loop if we have processed all the input samples
      if(i >= noutput_items){
        break;
      }

      // extract the next sample from the input stream
      uint8_t in_byte = in[i];
      
      // handle each bit seperately
      for(uint8_t bitcnt=0;bitcnt<8;bitcnt++){
        bool bit = (in_byte & 0x01) == 0x01;
                
        // SEARCH_PREAMBLE state
        if(d_state == SEARCH_PREAMBLE){
          // insert the input sample to the preamble shift register
          printf("Searching for bit: %d\n", bit);
          d_preamble_shift_reg.push_back(bit);

          // compare the preamble shift register with the prototype
          printf("comparing: %d\n", (d_preamble_prototype_shift_reg ^ d_preamble_shift_reg).count());
          if((d_preamble_prototype_shift_reg ^ d_preamble_shift_reg).count() < d_preamble_len/2){
            printf("Found preamble pattern\n");
            // if the number of different bits is more than half of the preamble length
            // then we have a mismatch and we need to reset the shift register
            d_preamble_shift_reg.reset();
            d_state = SEARCH_SYNC_WORD;
            break;
          }else{
            printf("Did not find preamble pattern\n");
          }
         
        
        }else if(d_state == SEARCH_SYNC_WORD){
          printf("Searching for sync word\n");
          // insert the input sample to the sync word shift register
          d_syncword_shift_reg.push_back(bit);

          // compare the sync word shift register with the prototype
          if((d_syncword_prototype_shift_reg ^ d_syncword_shift_reg).count() > d_sync_word.size()/2){
            // if the number of different bits is more than half of the sync word length
            // then we have a mismatch and we need to reset the shift register
            printf("Found sync word pattern\n");
            // print the received sync word
            printf("Received sync word: ");
            for(int i = 0; i < d_sync_word.size(); i++){
              printf("%d", d_syncword_shift_reg[i]);
            }
            d_syncword_shift_reg.reset();
            d_state = READ_LENGTH;
          }
        // }else if(d_state == READ_LENGTH){
        //   // insert the input sample to the length shift register
        //   d_length_shift_reg.push_back(bit);

        //   // if the length shift register is full
        //   if(d_length_shift_reg.is_full()){
        //     // extract the length from the shift register
        //     d_length = d_length_shift_reg.extract();

        //     // reset the shift register
        //     d_length_shift_reg.reset();

        //     // move to the next state
        //     d_state = READ_FRAME;
        //   }
        // }else if(d_state == READ_FRAME){
        //   // insert the input sample to the frame shift register
        //   d_frame_shift_reg.push_back(bit);

        //   // if the frame shift register is full
        //   if(d_frame_shift_reg.is_full()){
        //     // extract the frame from the shift register
        //     d_frame = d_frame_shift_reg.extract();

        //     // reset the shift register
        //     d_frame_shift_reg.reset();

        //     // move to the next state
        //     d_state = SEARCH_PREAMBLE;

        //     // break the loop
        //     break;
        //   }
        }



      }

      // increment the input sample index
      i++;
    } 



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
