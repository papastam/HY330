/* -*- c++ -*- */
/*
 * Copyright 2023 gr-chris_module author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/io_signature.h>
#include "constellation_mapping_4569_impl.h"

namespace gr {
  namespace chris_module {

    using input_type = char;
    using output_type = gr_complex;
    constellation_mapping_4569::sptr
    constellation_mapping_4569::make(int mod_bits_cnt)
    {
      return gnuradio::make_block_sptr<constellation_mapping_4569_impl>(
        mod_bits_cnt);
    }


    /*
     * The private constructor
     */
    constellation_mapping_4569_impl::constellation_mapping_4569_impl(int mod_bits_cnt)
      : gr::sync_block("constellation_mapping_4569",
              gr::io_signature::make(1, 1, sizeof(input_type)),
              gr::io_signature::make(1, 1, sizeof(output_type)))
    {
      _mod_bits_cnt = mod_bits_cnt;
    }
    
    gr_complex const_BPSK(char input_bit){
      if(input_bit == 0){
        return gr_complex(1,0);
      }else if(input_bit == 1){
        return gr_complex(-1,0);
      }else{
        return gr_complex(0,0);
      }
    }

    gr_complex const_QPSK(char input_bit){
      if(input_bit == 0){
        return gr_complex(1,1);
      }else if(input_bit == 1){
        return gr_complex(-1,1);
      }else if(input_bit == 2){
        return gr_complex(1,-1);
      }else if(input_bit == 3){
        return gr_complex(-1,-1);
      }else{
        return gr_complex(0,0);
      }
    }

    gr_complex const_16QAM(char input_bit){
      if(input_bit == 0){
        return gr_complex(3,3);
      }else if(input_bit == 1){
        return gr_complex(1,3);
      }else if(input_bit == 2){
        return gr_complex(-1,3);
      }else if(input_bit == 3){
        return gr_complex(-3,3);
      }else if(input_bit == 4){
        return gr_complex(3,1);
      }else if(input_bit == 5){
        return gr_complex(1,1);
      }else if(input_bit == 6){
        return gr_complex(-1,1);
      }else if(input_bit == 7){
        return gr_complex(-3,1);
      }else if(input_bit == 8){
        return gr_complex(3,-1);
      }else if(input_bit == 9){
        return gr_complex(1,-1);
      }else if(input_bit == 10){
        return gr_complex(-1,-1);
      }else if(input_bit == 11){
        return gr_complex(-3,-1);
      }else if(input_bit == 12){
        return gr_complex(3,-3);
      }else if(input_bit == 13){
        return gr_complex(1,-3);
      }else if(input_bit == 14){
        return gr_complex(-1,-3);
      }else if(input_bit == 15){
        return gr_complex(-3,-3);
      }else{
        return gr_complex(0,0);
      }
    }

    /*
     * Our virtual destructor.
     */
    constellation_mapping_4569_impl::~constellation_mapping_4569_impl()
    {
    }

        int
    constellation_mapping_4569_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      auto in = static_cast<const input_type*>(input_items[0]);
      auto out = static_cast<output_type*>(output_items[0]);

      // constellation function dispatcher
      gr_complex (*constellation_func[])(char) = {NULL, const_BPSK, const_QPSK, NULL, const_16QAM};
      
      float normal_factor[] = {0, 1, 1/sqrt(2), 0,  1/sqrt(10)};

      for(int i = 0; i < noutput_items; i++){
        if(_mod_bits_cnt == 1 || _mod_bits_cnt == 2 || _mod_bits_cnt == 4){
          out[i] = normal_factor[_mod_bits_cnt] * constellation_func[_mod_bits_cnt](in[i]);
        }else{
          out[i] = gr_complex(0,0);
        }
      }

      return noutput_items;
    }

  } /* namespace chris_module */
} /* namespace gr */
