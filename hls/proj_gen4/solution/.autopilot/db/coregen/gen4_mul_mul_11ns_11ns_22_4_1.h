// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.2 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __gen4_mul_mul_11ns_11ns_22_4_1__HH__
#define __gen4_mul_mul_11ns_11ns_22_4_1__HH__
#include "gen4_mul_mul_11ns_11ns_22_4_1_DSP48_2.h"
#include <systemc>

template<
    int ID,
    int NUM_STAGE,
    int din0_WIDTH,
    int din1_WIDTH,
    int dout_WIDTH>
SC_MODULE(gen4_mul_mul_11ns_11ns_22_4_1) {
    sc_core::sc_in_clk clk;
    sc_core::sc_in<sc_dt::sc_logic> reset;
    sc_core::sc_in<sc_dt::sc_logic> ce;
    sc_core::sc_in< sc_dt::sc_lv<din0_WIDTH> >   din0;
    sc_core::sc_in< sc_dt::sc_lv<din1_WIDTH> >   din1;
    sc_core::sc_out< sc_dt::sc_lv<dout_WIDTH> >   dout;



    gen4_mul_mul_11ns_11ns_22_4_1_DSP48_2 gen4_mul_mul_11ns_11ns_22_4_1_DSP48_2_U;

    SC_CTOR(gen4_mul_mul_11ns_11ns_22_4_1):  gen4_mul_mul_11ns_11ns_22_4_1_DSP48_2_U ("gen4_mul_mul_11ns_11ns_22_4_1_DSP48_2_U") {
        gen4_mul_mul_11ns_11ns_22_4_1_DSP48_2_U.clk(clk);
        gen4_mul_mul_11ns_11ns_22_4_1_DSP48_2_U.rst(reset);
        gen4_mul_mul_11ns_11ns_22_4_1_DSP48_2_U.ce(ce);
        gen4_mul_mul_11ns_11ns_22_4_1_DSP48_2_U.a(din0);
        gen4_mul_mul_11ns_11ns_22_4_1_DSP48_2_U.b(din1);
        gen4_mul_mul_11ns_11ns_22_4_1_DSP48_2_U.p(dout);

    }

};

#endif //
