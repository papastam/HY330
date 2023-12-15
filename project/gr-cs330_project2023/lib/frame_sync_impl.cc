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
              d_preamble(preamble),
              d_preamble_len(preamble_len),
              d_sync_word(sync_word),
              d_mod((mod_t)mod),
              d_state(SEARCH_PREAMBLE),
              d_preamble_shift_reg(           new shift_reg((preamble_len/2)*8)),
              d_preamble_prototype_shift_reg( new shift_reg((preamble_len/2)*8)),
              d_syncword_shift_reg(           new shift_reg((sync_word.size()/2)*8)),
              d_syncword_prototype_shift_reg( new shift_reg((sync_word.size()/2)*8)),
              d_preamble_sr_len((preamble_len/2)*8),
              d_syncword_sr_len((sync_word.size()/2)*8)
    {
      message_port_register_out(pmt::mp("pdu"));

      // Initialize the preamble prototype shift register
      for(int i = 0; i < preamble_len/2; i++){
        for(int j = 0; j < 8; j++){
          d_preamble_prototype_shift_reg->push_back(get_indexed_bit(preamble, j));
        }
      }

      // Initialize the sync word prototype shift register  
      for(long unsigned int i = 0; i < sync_word.size(); i++){
        for(int j = 0; j < 8; j++){
          d_syncword_prototype_shift_reg->push_back(get_indexed_bit(sync_word[i], j));
        }
      }
    }

    /*
      * Our virtual destructor.
     */
    frame_sync_impl::~frame_sync_impl()
    {
      delete d_preamble_shift_reg;
      delete d_preamble_prototype_shift_reg;
      delete d_syncword_shift_reg;
      delete d_syncword_prototype_shift_reg;
    }

    int
    frame_sync_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const uint8_t *in = (const uint8_t *) input_items[0];
      pmt::pmt_t pair = pmt::cons(pmt::PMT_NIL, pmt::PMT_NIL);

      int bit_count = 0;

      
      for(int count = 0; count < noutput_items; count++){
        std::cout << "Input: " << " ";
        for(int i = 0; i < 8; i++){
          std::cout << ((in[0] >> i) & 0x01) << " "; 
        }
        std::cout << std::endl;
        if(d_state==SEARCH_PREAMBLE){
          d_preamble_shift_reg->push_back(in[count]);
          // Fill up the shift register
          if(bit_count < d_preamble_sr_len){
            bit_count++;
            continue;
          }
          // And then compare it to the prototype
          if((*d_preamble_shift_reg ^ *d_preamble_prototype_shift_reg).count() <= d_preamble_sr_len/2){
            d_state = SEARCH_SYNC_WORD;
            std::cout << "Found preamble\n" << std::endl;
            std::cout << "Detected Preamble:\n" << std::endl;
            std::cout << d_preamble_shift_reg[0];
          }
        }else if(d_state==SEARCH_SYNC_WORD){
          break;
          d_syncword_shift_reg->push_back(in[count]);
          // Fill up the shift register
          if(bit_count < d_syncword_sr_len){
            bit_count++;
            continue;
          }
          // And then compare it to the prototype
          if((*d_syncword_shift_reg ^ *d_syncword_prototype_shift_reg).count() <= d_syncword_sr_len/2){
            d_state = READ_LENGTH;
            std::cout << "Found sync word\n" << std::endl;
            std::cout << "Detected Sync Word:\n" << std::endl;
            for(long unsigned int i = 0; i < d_sync_word.size(); i++){
              for(int j = 0; j < 8; j++){
                std::cout << d_syncword_shift_reg[i*8+j];
              }
              std::cout << std::endl;
            }         
          }
        }else if(d_state==READ_LENGTH){
          d_state = READ_FRAME;
          std::cout << "Reading length\n" << std::endl;
        }else if(d_state==READ_FRAME){
          std::cout << "Reading frame\n" << std::endl;
        }
      }


      pmt::pmt_t bytes_out_pmt = pmt::init_u8vector((size_t) 1, (const uint8_t*)1);
      

      message_port_pub(pmt::mp("pdu"), pmt::cons(pmt::PMT_NIL, bytes_out_pmt));

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace cs330_project2023 */
} /* namespace gr */
