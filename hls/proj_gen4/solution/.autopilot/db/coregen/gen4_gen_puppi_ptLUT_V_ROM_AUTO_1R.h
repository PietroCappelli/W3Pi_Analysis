// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.2 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __gen4_gen_puppi_ptLUT_V_ROM_AUTO_1R_H__
#define __gen4_gen_puppi_ptLUT_V_ROM_AUTO_1R_H__


#include <systemc>
using namespace sc_core;
using namespace sc_dt;




#include <iostream>
#include <fstream>

struct gen4_gen_puppi_ptLUT_V_ROM_AUTO_1R_ram : public sc_core::sc_module {

  static const unsigned DataWidth = 8;
  static const unsigned AddressRange = 1023;
  static const unsigned AddressWidth = 10;

//latency = 1
//input_reg = 1
//output_reg = 0
sc_core::sc_in <sc_lv<AddressWidth> > address0;
sc_core::sc_in <sc_logic> ce0;
sc_core::sc_out <sc_lv<DataWidth> > q0;
sc_core::sc_in<sc_logic> reset;
sc_core::sc_in<bool> clk;


sc_lv<DataWidth> ram[AddressRange];


   SC_CTOR(gen4_gen_puppi_ptLUT_V_ROM_AUTO_1R_ram) {
        for (unsigned i = 0; i < 182 ; i = i + 1) {
            ram[i] = "0b00001000";
        }
        for (unsigned i = 182; i < 379 ; i = i + 1) {
            ram[i] = "0b00001001";
        }
        for (unsigned i = 379; i < 518 ; i = i + 1) {
            ram[i] = "0b00001010";
        }
        for (unsigned i = 518; i < 618 ; i = i + 1) {
            ram[i] = "0b00001011";
        }
        for (unsigned i = 618; i < 689 ; i = i + 1) {
            ram[i] = "0b00001100";
        }
        for (unsigned i = 689; i < 742 ; i = i + 1) {
            ram[i] = "0b00001101";
        }
        for (unsigned i = 742; i < 781 ; i = i + 1) {
            ram[i] = "0b00001110";
        }
        for (unsigned i = 781; i < 811 ; i = i + 1) {
            ram[i] = "0b00001111";
        }
        for (unsigned i = 811; i < 834 ; i = i + 1) {
            ram[i] = "0b00010000";
        }
        for (unsigned i = 834; i < 852 ; i = i + 1) {
            ram[i] = "0b00010001";
        }
        for (unsigned i = 852; i < 866 ; i = i + 1) {
            ram[i] = "0b00010010";
        }
        for (unsigned i = 866; i < 878 ; i = i + 1) {
            ram[i] = "0b00010011";
        }
        for (unsigned i = 878; i < 887 ; i = i + 1) {
            ram[i] = "0b00010100";
        }
        for (unsigned i = 887; i < 895 ; i = i + 1) {
            ram[i] = "0b00010101";
        }
        for (unsigned i = 895; i < 902 ; i = i + 1) {
            ram[i] = "0b00010110";
        }
        for (unsigned i = 902; i < 907 ; i = i + 1) {
            ram[i] = "0b00010111";
        }
        for (unsigned i = 907; i < 912 ; i = i + 1) {
            ram[i] = "0b00011000";
        }
        for (unsigned i = 912; i < 917 ; i = i + 1) {
            ram[i] = "0b00011001";
        }
        ram[917] = "0b00011010";
        ram[918] = "0b00011010";
        ram[919] = "0b00011010";
        ram[920] = "0b00011011";
        ram[921] = "0b00011011";
        ram[922] = "0b00011011";
        ram[923] = "0b00011011";
        ram[924] = "0b00011100";
        ram[925] = "0b00011100";
        ram[926] = "0b00011100";
        ram[927] = "0b00011101";
        ram[928] = "0b00011101";
        ram[929] = "0b00011110";
        ram[930] = "0b00011110";
        ram[931] = "0b00011110";
        ram[932] = "0b00011111";
        ram[933] = "0b00011111";
        ram[934] = "0b00100000";
        ram[935] = "0b00100000";
        ram[936] = "0b00100001";
        ram[937] = "0b00100001";
        ram[938] = "0b00100010";
        ram[939] = "0b00100010";
        ram[940] = "0b00100011";
        ram[941] = "0b00100011";
        ram[942] = "0b00100100";
        ram[943] = "0b00100101";
        ram[944] = "0b00100101";
        ram[945] = "0b00100110";
        ram[946] = "0b00100111";
        ram[947] = "0b00101000";
        ram[948] = "0b00101000";
        ram[949] = "0b00101001";
        ram[950] = "0b00101010";
        ram[951] = "0b00101011";
        ram[952] = "0b00101011";
        ram[953] = "0b00101100";
        ram[954] = "0b00101101";
        ram[955] = "0b00101110";
        ram[956] = "0b00101111";
        ram[957] = "0b00110000";
        ram[958] = "0b00110001";
        ram[959] = "0b00110001";
        ram[960] = "0b00110011";
        ram[961] = "0b00110100";
        ram[962] = "0b00110101";
        ram[963] = "0b00110110";
        ram[964] = "0b00110111";
        ram[965] = "0b00111000";
        ram[966] = "0b00111001";
        ram[967] = "0b00111010";
        ram[968] = "0b00111011";
        ram[969] = "0b00111100";
        ram[970] = "0b00111110";
        ram[971] = "0b00111111";
        ram[972] = "0b01000000";
        ram[973] = "0b01000001";
        ram[974] = "0b01000011";
        ram[975] = "0b01000100";
        ram[976] = "0b01000101";
        ram[977] = "0b01000111";
        ram[978] = "0b01001000";
        ram[979] = "0b01001010";
        ram[980] = "0b01001011";
        ram[981] = "0b01001101";
        ram[982] = "0b01001110";
        ram[983] = "0b01010000";
        ram[984] = "0b01010001";
        ram[985] = "0b01010011";
        ram[986] = "0b01010101";
        ram[987] = "0b01010110";
        ram[988] = "0b01011000";
        ram[989] = "0b01011010";
        ram[990] = "0b01011011";
        ram[991] = "0b01011101";
        ram[992] = "0b01011111";
        ram[993] = "0b01100001";
        ram[994] = "0b01100011";
        ram[995] = "0b01100101";
        ram[996] = "0b01100110";
        ram[997] = "0b01101000";
        ram[998] = "0b01101010";
        ram[999] = "0b01101100";
        ram[1000] = "0b01101110";
        ram[1001] = "0b01110001";
        ram[1002] = "0b01110011";
        ram[1003] = "0b01110101";
        ram[1004] = "0b01110111";
        ram[1005] = "0b01111001";
        ram[1006] = "0b01111011";
        ram[1007] = "0b01111110";
        ram[1008] = "0b10000000";
        ram[1009] = "0b10000011";
        ram[1010] = "0b10000110";
        ram[1011] = "0b10001000";
        ram[1012] = "0b10001100";
        ram[1013] = "0b10001110";
        ram[1014] = "0b10010010";
        ram[1015] = "0b10010101";
        ram[1016] = "0b10011010";
        ram[1017] = "0b10011110";
        ram[1018] = "0b10100011";
        ram[1019] = "0b10101001";
        ram[1020] = "0b10110001";
        ram[1021] = "0b10111010";
        ram[1022] = "0b11000100";


SC_METHOD(prc_write_0);
  sensitive<<clk.pos();
   }


void prc_write_0()
{
    if (ce0.read() == sc_dt::Log_1) 
    {
            if(address0.read().is_01() && address0.read().to_uint()<AddressRange)
              q0 = ram[address0.read().to_uint()];
            else
              q0 = sc_lv<DataWidth>();
    }
}


}; //endmodule


SC_MODULE(gen4_gen_puppi_ptLUT_V_ROM_AUTO_1R) {


static const unsigned DataWidth = 8;
static const unsigned AddressRange = 1023;
static const unsigned AddressWidth = 10;

sc_core::sc_in <sc_lv<AddressWidth> > address0;
sc_core::sc_in<sc_logic> ce0;
sc_core::sc_out <sc_lv<DataWidth> > q0;
sc_core::sc_in<sc_logic> reset;
sc_core::sc_in<bool> clk;


gen4_gen_puppi_ptLUT_V_ROM_AUTO_1R_ram* meminst;


SC_CTOR(gen4_gen_puppi_ptLUT_V_ROM_AUTO_1R) {
meminst = new gen4_gen_puppi_ptLUT_V_ROM_AUTO_1R_ram("gen4_gen_puppi_ptLUT_V_ROM_AUTO_1R_ram");
meminst->address0(address0);
meminst->ce0(ce0);
meminst->q0(q0);

meminst->reset(reset);
meminst->clk(clk);
}
~gen4_gen_puppi_ptLUT_V_ROM_AUTO_1R() {
    delete meminst;
}


};//endmodule
#endif
