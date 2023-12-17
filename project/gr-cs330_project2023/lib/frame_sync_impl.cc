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
              d_syncword_shift_reg(           new shift_reg((sync_word.size())*8)),
              d_syncword_prototype_shift_reg( new shift_reg((sync_word.size())*8)),
              d_syncword_sr_len((sync_word.size())*8),
              read_length_index(0),
              d_payload_len(0)
    {
      message_port_register_out(pmt::mp("pdu"));

      // Initialize the preamble prototype shift register
      for(int i = 0; i < preamble_len / 2; i++){
        for(int j = 0; j < 8; j++){
            *d_preamble_prototype_shift_reg >>= ((d_preamble & (1 << j)) >> j);
        }
      }


      // Initialize the sync word prototype shift register  
      for(long unsigned int i = 0; i < sync_word.size(); i++){
        for(int j = 0; j < 8; j++){
            *d_syncword_prototype_shift_reg >>= ((sync_word[sync_word.size() - i - 1] & (1 << j)) >> j);
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
      uint plcount = 0;
      uint plbitcount = 0;

      noutput_items += 25;
      
      for(int count = 0; count < noutput_items; count++){
        if(d_state==DONE){
          break;
        }
        if((d_state == SEARCH_PREAMBLE || d_state == SEARCH_SYNC_WORD) && (long unsigned int) count > ((d_preamble_len+d_sync_word.size()+2)*8) ){
          std::cout << "Preamble and sync word found in the first " << ((d_preamble_len+d_sync_word.size())*8)+16 << " bits" << std::endl;
          std::cout << "Exiting" << std::endl;
          break;
        }
        if(d_state==SEARCH_PREAMBLE){
          d_preamble_shift_reg->push_back(in[count]);
          // Fill up the shift register
          if(bit_count < d_preamble_len*4){
            bit_count++;
            continue;
          }
          // And then compare it to the prototype
          if((*d_preamble_shift_reg ^ *d_preamble_prototype_shift_reg).count() <= (d_preamble_len*2)){
            std::cout << "Found preamble\n" << std::endl;
            std::cout << "Detected Preamble:\n" << std::endl;
            std::cout << d_preamble_shift_reg[0] << std::endl << std::endl;
            std::cout << "Transitioning to search for sync word\n" << std::endl;
            d_state = SEARCH_SYNC_WORD;
          }
        }else if(d_state==SEARCH_SYNC_WORD){
          d_syncword_shift_reg->push_back(in[count]);
          // Fill up the shift register
          if(bit_count < d_syncword_sr_len){
            bit_count++;
            continue;
          }
          // And then compare it to the prototype
          if((*d_syncword_shift_reg ^ *d_syncword_prototype_shift_reg).count() <= d_syncword_sr_len/4){
            std::cout << "Detected Sync Word:\n" << std::endl;
            std::cout << d_syncword_shift_reg[0] << std::endl << std::endl;
            std::cout << "Transitioning to read length\n" << std::endl;      
            d_state = READ_LENGTH;
          }
        }else if(d_state==READ_LENGTH){
          read_length[read_length_index]=(bool) in[count];
          read_length_index++;

          if (read_length_index==16){
            // turn read_length array into a number
            std::cout << "Read length array:\n" << std::endl;
            d_payload_len=0;
            for(int i=0;i<16;i++){
              d_payload_len+=read_length[i]<<(15-i);
            }
            std::cout << "Payload length: " << d_payload_len << std::endl;
            std::cout << "Transitioning to read frame\n" << std::endl;
            d_state=READ_FRAME;
          }
        }else if(d_state==READ_FRAME){
          if(plcount == 0){
            d_payload = new uint8_t[d_payload_len];
          }
          std::cout << "count: " << count << " | noutput_items: " << noutput_items << std::endl;

          if(plcount < d_payload_len){
            if(plbitcount < 8){
              d_payload[plcount] |= (in[count] << (7-plbitcount));
              plbitcount++;
              std::cout << "Payload bit read\n" << std::endl;
              continue; 
            }
            std::cout << "Payload byte read\n" << std::endl;
            plbitcount = 0;
            plcount++;
            continue;
          }
          
          std::cout << "Payload read\n" << std::endl;
          std::cout << "Transitioning to done\n" << std::endl;
          d_state=DONE;
          break;
        }
      }

      if (d_state==DONE){
        std::cout << "Done" << std::endl;
        std::cout << "Payload:\n" << std::endl;
        for(int i=0;i<d_payload_len;i++){
          std::cout << d_payload[i] << std::endl;
        }
        std::cout << std::endl;

        pmt::pmt_t bytes_out_pmt = pmt::init_u8vector(d_payload_len, d_payload);
        message_port_pub(pmt::mp("pdu"), pmt::cons(pmt::PMT_NIL, bytes_out_pmt));
      }
      
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace cs330_project2023 */
} /* namespace gr */
