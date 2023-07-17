#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

// wrapc file define:
#define AUTOTB_TVIN_valid "../tv/cdatafile/c.gen4.autotvin_valid.dat"
#define AUTOTB_TVOUT_valid "../tv/cdatafile/c.gen4.autotvout_valid.dat"
// wrapc file define:
#define AUTOTB_TVIN_set "../tv/cdatafile/c.gen4.autotvin_set.dat"
#define AUTOTB_TVOUT_set "../tv/cdatafile/c.gen4.autotvout_set.dat"
// wrapc file define:
#define AUTOTB_TVIN_p_idxs_0 "../tv/cdatafile/c.gen4.autotvin_p_idxs_0.dat"
#define AUTOTB_TVOUT_p_idxs_0 "../tv/cdatafile/c.gen4.autotvout_p_idxs_0.dat"
// wrapc file define:
#define AUTOTB_TVIN_p_idxs_1 "../tv/cdatafile/c.gen4.autotvin_p_idxs_1.dat"
#define AUTOTB_TVOUT_p_idxs_1 "../tv/cdatafile/c.gen4.autotvout_p_idxs_1.dat"
// wrapc file define:
#define AUTOTB_TVIN_p_idxs_2 "../tv/cdatafile/c.gen4.autotvin_p_idxs_2.dat"
#define AUTOTB_TVOUT_p_idxs_2 "../tv/cdatafile/c.gen4.autotvout_p_idxs_2.dat"
// wrapc file define:
#define AUTOTB_TVIN_p_idxs_3 "../tv/cdatafile/c.gen4.autotvin_p_idxs_3.dat"
#define AUTOTB_TVOUT_p_idxs_3 "../tv/cdatafile/c.gen4.autotvout_p_idxs_3.dat"
// wrapc file define:
#define AUTOTB_TVIN_data_out_0 "../tv/cdatafile/c.gen4.autotvin_data_out_0.dat"
#define AUTOTB_TVOUT_data_out_0 "../tv/cdatafile/c.gen4.autotvout_data_out_0.dat"
// wrapc file define:
#define AUTOTB_TVIN_data_out_1 "../tv/cdatafile/c.gen4.autotvin_data_out_1.dat"
#define AUTOTB_TVOUT_data_out_1 "../tv/cdatafile/c.gen4.autotvout_data_out_1.dat"
// wrapc file define:
#define AUTOTB_TVIN_data_out_2 "../tv/cdatafile/c.gen4.autotvin_data_out_2.dat"
#define AUTOTB_TVOUT_data_out_2 "../tv/cdatafile/c.gen4.autotvout_data_out_2.dat"
// wrapc file define:
#define AUTOTB_TVIN_data_out_3 "../tv/cdatafile/c.gen4.autotvin_data_out_3.dat"
#define AUTOTB_TVOUT_data_out_3 "../tv/cdatafile/c.gen4.autotvout_data_out_3.dat"
// wrapc file define:
#define AUTOTB_TVIN_orbit_out_0 "../tv/cdatafile/c.gen4.autotvin_orbit_out_0.dat"
#define AUTOTB_TVOUT_orbit_out_0 "../tv/cdatafile/c.gen4.autotvout_orbit_out_0.dat"
// wrapc file define:
#define AUTOTB_TVIN_orbit_out_1 "../tv/cdatafile/c.gen4.autotvin_orbit_out_1.dat"
#define AUTOTB_TVOUT_orbit_out_1 "../tv/cdatafile/c.gen4.autotvout_orbit_out_1.dat"
// wrapc file define:
#define AUTOTB_TVIN_orbit_out_2 "../tv/cdatafile/c.gen4.autotvin_orbit_out_2.dat"
#define AUTOTB_TVOUT_orbit_out_2 "../tv/cdatafile/c.gen4.autotvout_orbit_out_2.dat"
// wrapc file define:
#define AUTOTB_TVIN_orbit_out_3 "../tv/cdatafile/c.gen4.autotvin_orbit_out_3.dat"
#define AUTOTB_TVOUT_orbit_out_3 "../tv/cdatafile/c.gen4.autotvout_orbit_out_3.dat"
// wrapc file define:
#define AUTOTB_TVIN_start_out_0 "../tv/cdatafile/c.gen4.autotvin_start_out_0.dat"
#define AUTOTB_TVOUT_start_out_0 "../tv/cdatafile/c.gen4.autotvout_start_out_0.dat"
// wrapc file define:
#define AUTOTB_TVIN_start_out_1 "../tv/cdatafile/c.gen4.autotvin_start_out_1.dat"
#define AUTOTB_TVOUT_start_out_1 "../tv/cdatafile/c.gen4.autotvout_start_out_1.dat"
// wrapc file define:
#define AUTOTB_TVIN_start_out_2 "../tv/cdatafile/c.gen4.autotvin_start_out_2.dat"
#define AUTOTB_TVOUT_start_out_2 "../tv/cdatafile/c.gen4.autotvout_start_out_2.dat"
// wrapc file define:
#define AUTOTB_TVIN_start_out_3 "../tv/cdatafile/c.gen4.autotvin_start_out_3.dat"
#define AUTOTB_TVOUT_start_out_3 "../tv/cdatafile/c.gen4.autotvout_start_out_3.dat"
// wrapc file define:
#define AUTOTB_TVIN_end_out_0 "../tv/cdatafile/c.gen4.autotvin_end_out_0.dat"
#define AUTOTB_TVOUT_end_out_0 "../tv/cdatafile/c.gen4.autotvout_end_out_0.dat"
// wrapc file define:
#define AUTOTB_TVIN_end_out_1 "../tv/cdatafile/c.gen4.autotvin_end_out_1.dat"
#define AUTOTB_TVOUT_end_out_1 "../tv/cdatafile/c.gen4.autotvout_end_out_1.dat"
// wrapc file define:
#define AUTOTB_TVIN_end_out_2 "../tv/cdatafile/c.gen4.autotvin_end_out_2.dat"
#define AUTOTB_TVOUT_end_out_2 "../tv/cdatafile/c.gen4.autotvout_end_out_2.dat"
// wrapc file define:
#define AUTOTB_TVIN_end_out_3 "../tv/cdatafile/c.gen4.autotvin_end_out_3.dat"
#define AUTOTB_TVOUT_end_out_3 "../tv/cdatafile/c.gen4.autotvout_end_out_3.dat"
// wrapc file define:
#define AUTOTB_TVIN_valid_out_0 "../tv/cdatafile/c.gen4.autotvin_valid_out_0.dat"
#define AUTOTB_TVOUT_valid_out_0 "../tv/cdatafile/c.gen4.autotvout_valid_out_0.dat"
// wrapc file define:
#define AUTOTB_TVIN_valid_out_1 "../tv/cdatafile/c.gen4.autotvin_valid_out_1.dat"
#define AUTOTB_TVOUT_valid_out_1 "../tv/cdatafile/c.gen4.autotvout_valid_out_1.dat"
// wrapc file define:
#define AUTOTB_TVIN_valid_out_2 "../tv/cdatafile/c.gen4.autotvin_valid_out_2.dat"
#define AUTOTB_TVOUT_valid_out_2 "../tv/cdatafile/c.gen4.autotvout_valid_out_2.dat"
// wrapc file define:
#define AUTOTB_TVIN_valid_out_3 "../tv/cdatafile/c.gen4.autotvin_valid_out_3.dat"
#define AUTOTB_TVOUT_valid_out_3 "../tv/cdatafile/c.gen4.autotvout_valid_out_3.dat"
// wrapc file define:
#define AUTOTB_TVIN_CLOCK_RATIO_MINUS_ONE "../tv/cdatafile/c.gen4.autotvin_CLOCK_RATIO_MINUS_ONE.dat"
#define AUTOTB_TVOUT_CLOCK_RATIO_MINUS_ONE "../tv/cdatafile/c.gen4.autotvout_CLOCK_RATIO_MINUS_ONE.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_valid "../tv/rtldatafile/rtl.gen4.autotvout_valid.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_set "../tv/rtldatafile/rtl.gen4.autotvout_set.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_p_idxs_0 "../tv/rtldatafile/rtl.gen4.autotvout_p_idxs_0.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_p_idxs_1 "../tv/rtldatafile/rtl.gen4.autotvout_p_idxs_1.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_p_idxs_2 "../tv/rtldatafile/rtl.gen4.autotvout_p_idxs_2.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_p_idxs_3 "../tv/rtldatafile/rtl.gen4.autotvout_p_idxs_3.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_data_out_0 "../tv/rtldatafile/rtl.gen4.autotvout_data_out_0.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_data_out_1 "../tv/rtldatafile/rtl.gen4.autotvout_data_out_1.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_data_out_2 "../tv/rtldatafile/rtl.gen4.autotvout_data_out_2.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_data_out_3 "../tv/rtldatafile/rtl.gen4.autotvout_data_out_3.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_orbit_out_0 "../tv/rtldatafile/rtl.gen4.autotvout_orbit_out_0.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_orbit_out_1 "../tv/rtldatafile/rtl.gen4.autotvout_orbit_out_1.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_orbit_out_2 "../tv/rtldatafile/rtl.gen4.autotvout_orbit_out_2.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_orbit_out_3 "../tv/rtldatafile/rtl.gen4.autotvout_orbit_out_3.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_start_out_0 "../tv/rtldatafile/rtl.gen4.autotvout_start_out_0.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_start_out_1 "../tv/rtldatafile/rtl.gen4.autotvout_start_out_1.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_start_out_2 "../tv/rtldatafile/rtl.gen4.autotvout_start_out_2.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_start_out_3 "../tv/rtldatafile/rtl.gen4.autotvout_start_out_3.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_end_out_0 "../tv/rtldatafile/rtl.gen4.autotvout_end_out_0.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_end_out_1 "../tv/rtldatafile/rtl.gen4.autotvout_end_out_1.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_end_out_2 "../tv/rtldatafile/rtl.gen4.autotvout_end_out_2.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_end_out_3 "../tv/rtldatafile/rtl.gen4.autotvout_end_out_3.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_valid_out_0 "../tv/rtldatafile/rtl.gen4.autotvout_valid_out_0.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_valid_out_1 "../tv/rtldatafile/rtl.gen4.autotvout_valid_out_1.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_valid_out_2 "../tv/rtldatafile/rtl.gen4.autotvout_valid_out_2.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_valid_out_3 "../tv/rtldatafile/rtl.gen4.autotvout_valid_out_3.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_CLOCK_RATIO_MINUS_ONE "../tv/rtldatafile/rtl.gen4.autotvout_CLOCK_RATIO_MINUS_ONE.dat"


inline void rev_endian(char* p, size_t nbytes)
{
  std::reverse(p, p+nbytes);
}

template<size_t bit_width>
struct transaction {
  typedef uint64_t depth_t;
  static const size_t wbytes = (bit_width+7)>>3;
  static const size_t dbytes = sizeof(depth_t);
  const depth_t depth;
  const size_t vbytes;
  const size_t tbytes;
  char * const p;
  typedef char (*p_dat)[wbytes];
  p_dat vp;

  void reorder() {
    rev_endian(p, dbytes);
    p_dat vp = (p_dat) (p+dbytes);
    for (depth_t i = 0; i < depth; ++i) {
      rev_endian(vp[i], wbytes);
    }
  }

  transaction(depth_t depth)
    : depth(depth), vbytes(wbytes*depth), tbytes(dbytes+vbytes),
      p(new char[tbytes]) {
    *(depth_t*)p = depth;
    vp = (p_dat) (p+dbytes);
  }

  template<size_t psize>
  void import(char* param, depth_t num, int64_t offset) {
    param -= offset*psize;
    for (depth_t i = 0; i < num; ++i) {
      memcpy(vp[i], param, wbytes);
      param += psize;
    }
    vp += num;
  }

  template<size_t psize>
  void send(char* param, depth_t num) {
    for (depth_t i = 0; i < num; ++i) {
      memcpy(param, vp[i], wbytes);
      param += psize;
    }
    vp += num;
  }

  template<size_t psize>
  void send(char* param, depth_t num, int64_t skip) {
    for (depth_t i = 0; i < num; ++i) {
      memcpy(param, vp[skip+i], wbytes);
      param += psize;
    }
  }

  ~transaction() { if (p) { delete[] p; } }
};
      

inline const std::string begin_str(int num)
{
  return std::string("[[transaction]] ")
         .append(std::to_string(num))
         .append("\n");
}

inline const std::string end_str()
{
  return std::string("[[/transaction]] \n");
}
      
class INTER_TCL_FILE {
  public:
INTER_TCL_FILE(const char* name) {
  mName = name; 
  valid_depth = 0;
  set_depth = 0;
  p_idxs_0_depth = 0;
  p_idxs_1_depth = 0;
  p_idxs_2_depth = 0;
  p_idxs_3_depth = 0;
  data_out_0_depth = 0;
  data_out_1_depth = 0;
  data_out_2_depth = 0;
  data_out_3_depth = 0;
  orbit_out_0_depth = 0;
  orbit_out_1_depth = 0;
  orbit_out_2_depth = 0;
  orbit_out_3_depth = 0;
  start_out_0_depth = 0;
  start_out_1_depth = 0;
  start_out_2_depth = 0;
  start_out_3_depth = 0;
  end_out_0_depth = 0;
  end_out_1_depth = 0;
  end_out_2_depth = 0;
  end_out_3_depth = 0;
  valid_out_0_depth = 0;
  valid_out_1_depth = 0;
  valid_out_2_depth = 0;
  valid_out_3_depth = 0;
  CLOCK_RATIO_MINUS_ONE_depth = 0;
  trans_num =0;
}
~INTER_TCL_FILE() {
  mFile.open(mName);
  if (!mFile.good()) {
    cout << "Failed to open file ref.tcl" << endl;
    exit (1); 
  }
  string total_list = get_depth_list();
  mFile << "set depth_list {\n";
  mFile << total_list;
  mFile << "}\n";
  mFile << "set trans_num "<<trans_num<<endl;
  mFile.close();
}
string get_depth_list () {
  stringstream total_list;
  total_list << "{valid " << valid_depth << "}\n";
  total_list << "{set " << set_depth << "}\n";
  total_list << "{p_idxs_0 " << p_idxs_0_depth << "}\n";
  total_list << "{p_idxs_1 " << p_idxs_1_depth << "}\n";
  total_list << "{p_idxs_2 " << p_idxs_2_depth << "}\n";
  total_list << "{p_idxs_3 " << p_idxs_3_depth << "}\n";
  total_list << "{data_out_0 " << data_out_0_depth << "}\n";
  total_list << "{data_out_1 " << data_out_1_depth << "}\n";
  total_list << "{data_out_2 " << data_out_2_depth << "}\n";
  total_list << "{data_out_3 " << data_out_3_depth << "}\n";
  total_list << "{orbit_out_0 " << orbit_out_0_depth << "}\n";
  total_list << "{orbit_out_1 " << orbit_out_1_depth << "}\n";
  total_list << "{orbit_out_2 " << orbit_out_2_depth << "}\n";
  total_list << "{orbit_out_3 " << orbit_out_3_depth << "}\n";
  total_list << "{start_out_0 " << start_out_0_depth << "}\n";
  total_list << "{start_out_1 " << start_out_1_depth << "}\n";
  total_list << "{start_out_2 " << start_out_2_depth << "}\n";
  total_list << "{start_out_3 " << start_out_3_depth << "}\n";
  total_list << "{end_out_0 " << end_out_0_depth << "}\n";
  total_list << "{end_out_1 " << end_out_1_depth << "}\n";
  total_list << "{end_out_2 " << end_out_2_depth << "}\n";
  total_list << "{end_out_3 " << end_out_3_depth << "}\n";
  total_list << "{valid_out_0 " << valid_out_0_depth << "}\n";
  total_list << "{valid_out_1 " << valid_out_1_depth << "}\n";
  total_list << "{valid_out_2 " << valid_out_2_depth << "}\n";
  total_list << "{valid_out_3 " << valid_out_3_depth << "}\n";
  total_list << "{CLOCK_RATIO_MINUS_ONE " << CLOCK_RATIO_MINUS_ONE_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int valid_depth;
    int set_depth;
    int p_idxs_0_depth;
    int p_idxs_1_depth;
    int p_idxs_2_depth;
    int p_idxs_3_depth;
    int data_out_0_depth;
    int data_out_1_depth;
    int data_out_2_depth;
    int data_out_3_depth;
    int orbit_out_0_depth;
    int orbit_out_1_depth;
    int orbit_out_2_depth;
    int orbit_out_3_depth;
    int start_out_0_depth;
    int start_out_1_depth;
    int start_out_2_depth;
    int start_out_3_depth;
    int end_out_0_depth;
    int end_out_1_depth;
    int end_out_2_depth;
    int end_out_3_depth;
    int valid_out_0_depth;
    int valid_out_1_depth;
    int valid_out_2_depth;
    int valid_out_3_depth;
    int CLOCK_RATIO_MINUS_ONE_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};

static bool RTLOutputCheckAndReplacement(std::string &AESL_token, std::string PortName) {
  bool err = false;
  size_t x_found;

  // search and replace 'X' with '0' from the 3rd char of token
  while ((x_found = AESL_token.find('X', 0)) != string::npos)
    err = true, AESL_token.replace(x_found, 1, "0");
  
  // search and replace 'x' with '0' from the 3rd char of token
  while ((x_found = AESL_token.find('x', 2)) != string::npos)
    err = true, AESL_token.replace(x_found, 1, "0");
  
  return err;}
struct __cosim_s1__ { char data[1]; };
extern "C" void gen4_hw_stub_wrapper(char, char, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, __cosim_s1__*);

extern "C" void apatb_gen4_hw(char __xlx_apatb_param_valid, char __xlx_apatb_param_set, volatile void * __xlx_apatb_param_p_idxs_0, volatile void * __xlx_apatb_param_p_idxs_1, volatile void * __xlx_apatb_param_p_idxs_2, volatile void * __xlx_apatb_param_p_idxs_3, volatile void * __xlx_apatb_param_data_out_0, volatile void * __xlx_apatb_param_data_out_1, volatile void * __xlx_apatb_param_data_out_2, volatile void * __xlx_apatb_param_data_out_3, volatile void * __xlx_apatb_param_orbit_out_0, volatile void * __xlx_apatb_param_orbit_out_1, volatile void * __xlx_apatb_param_orbit_out_2, volatile void * __xlx_apatb_param_orbit_out_3, volatile void * __xlx_apatb_param_start_out_0, volatile void * __xlx_apatb_param_start_out_1, volatile void * __xlx_apatb_param_start_out_2, volatile void * __xlx_apatb_param_start_out_3, volatile void * __xlx_apatb_param_end_out_0, volatile void * __xlx_apatb_param_end_out_1, volatile void * __xlx_apatb_param_end_out_2, volatile void * __xlx_apatb_param_end_out_3, volatile void * __xlx_apatb_param_valid_out_0, volatile void * __xlx_apatb_param_valid_out_1, volatile void * __xlx_apatb_param_valid_out_2, volatile void * __xlx_apatb_param_valid_out_3, __cosim_s1__* __xlx_apatb_param_CLOCK_RATIO_MINUS_ONE) {
  refine_signal_handler();
  fstream wrapc_switch_file_token;
  wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
static AESL_FILE_HANDLER aesl_fh;
  int AESL_i;
  if (wrapc_switch_file_token.good())
  {

    CodeState = ENTER_WRAPC_PC;
    static unsigned AESL_transaction_pc = 0;
    string AESL_token;
    string AESL_num;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_data_out_0);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<64> > data_out_0_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "data_out_0");
  
            // push token into output port buffer
            if (AESL_token != "") {
              data_out_0_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "data_out_0" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_data_out_0)[0*8+0] = data_out_0_pc_buffer[0].range(7, 0).to_int64();
((char*)__xlx_apatb_param_data_out_0)[0*8+1] = data_out_0_pc_buffer[0].range(15, 8).to_int64();
((char*)__xlx_apatb_param_data_out_0)[0*8+2] = data_out_0_pc_buffer[0].range(23, 16).to_int64();
((char*)__xlx_apatb_param_data_out_0)[0*8+3] = data_out_0_pc_buffer[0].range(31, 24).to_int64();
((char*)__xlx_apatb_param_data_out_0)[0*8+4] = data_out_0_pc_buffer[0].range(39, 32).to_int64();
((char*)__xlx_apatb_param_data_out_0)[0*8+5] = data_out_0_pc_buffer[0].range(47, 40).to_int64();
((char*)__xlx_apatb_param_data_out_0)[0*8+6] = data_out_0_pc_buffer[0].range(55, 48).to_int64();
((char*)__xlx_apatb_param_data_out_0)[0*8+7] = data_out_0_pc_buffer[0].range(63, 56).to_int64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_data_out_1);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<64> > data_out_1_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "data_out_1");
  
            // push token into output port buffer
            if (AESL_token != "") {
              data_out_1_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "data_out_1" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_data_out_1)[0*8+0] = data_out_1_pc_buffer[0].range(7, 0).to_int64();
((char*)__xlx_apatb_param_data_out_1)[0*8+1] = data_out_1_pc_buffer[0].range(15, 8).to_int64();
((char*)__xlx_apatb_param_data_out_1)[0*8+2] = data_out_1_pc_buffer[0].range(23, 16).to_int64();
((char*)__xlx_apatb_param_data_out_1)[0*8+3] = data_out_1_pc_buffer[0].range(31, 24).to_int64();
((char*)__xlx_apatb_param_data_out_1)[0*8+4] = data_out_1_pc_buffer[0].range(39, 32).to_int64();
((char*)__xlx_apatb_param_data_out_1)[0*8+5] = data_out_1_pc_buffer[0].range(47, 40).to_int64();
((char*)__xlx_apatb_param_data_out_1)[0*8+6] = data_out_1_pc_buffer[0].range(55, 48).to_int64();
((char*)__xlx_apatb_param_data_out_1)[0*8+7] = data_out_1_pc_buffer[0].range(63, 56).to_int64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_data_out_2);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<64> > data_out_2_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "data_out_2");
  
            // push token into output port buffer
            if (AESL_token != "") {
              data_out_2_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "data_out_2" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_data_out_2)[0*8+0] = data_out_2_pc_buffer[0].range(7, 0).to_int64();
((char*)__xlx_apatb_param_data_out_2)[0*8+1] = data_out_2_pc_buffer[0].range(15, 8).to_int64();
((char*)__xlx_apatb_param_data_out_2)[0*8+2] = data_out_2_pc_buffer[0].range(23, 16).to_int64();
((char*)__xlx_apatb_param_data_out_2)[0*8+3] = data_out_2_pc_buffer[0].range(31, 24).to_int64();
((char*)__xlx_apatb_param_data_out_2)[0*8+4] = data_out_2_pc_buffer[0].range(39, 32).to_int64();
((char*)__xlx_apatb_param_data_out_2)[0*8+5] = data_out_2_pc_buffer[0].range(47, 40).to_int64();
((char*)__xlx_apatb_param_data_out_2)[0*8+6] = data_out_2_pc_buffer[0].range(55, 48).to_int64();
((char*)__xlx_apatb_param_data_out_2)[0*8+7] = data_out_2_pc_buffer[0].range(63, 56).to_int64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_data_out_3);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<64> > data_out_3_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "data_out_3");
  
            // push token into output port buffer
            if (AESL_token != "") {
              data_out_3_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "data_out_3" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_data_out_3)[0*8+0] = data_out_3_pc_buffer[0].range(7, 0).to_int64();
((char*)__xlx_apatb_param_data_out_3)[0*8+1] = data_out_3_pc_buffer[0].range(15, 8).to_int64();
((char*)__xlx_apatb_param_data_out_3)[0*8+2] = data_out_3_pc_buffer[0].range(23, 16).to_int64();
((char*)__xlx_apatb_param_data_out_3)[0*8+3] = data_out_3_pc_buffer[0].range(31, 24).to_int64();
((char*)__xlx_apatb_param_data_out_3)[0*8+4] = data_out_3_pc_buffer[0].range(39, 32).to_int64();
((char*)__xlx_apatb_param_data_out_3)[0*8+5] = data_out_3_pc_buffer[0].range(47, 40).to_int64();
((char*)__xlx_apatb_param_data_out_3)[0*8+6] = data_out_3_pc_buffer[0].range(55, 48).to_int64();
((char*)__xlx_apatb_param_data_out_3)[0*8+7] = data_out_3_pc_buffer[0].range(63, 56).to_int64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_orbit_out_0);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > orbit_out_0_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "orbit_out_0");
  
            // push token into output port buffer
            if (AESL_token != "") {
              orbit_out_0_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "orbit_out_0" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_orbit_out_0)[0*1+0] = orbit_out_0_pc_buffer[0].range(0, 0).to_uint64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_orbit_out_1);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > orbit_out_1_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "orbit_out_1");
  
            // push token into output port buffer
            if (AESL_token != "") {
              orbit_out_1_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "orbit_out_1" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_orbit_out_1)[0*1+0] = orbit_out_1_pc_buffer[0].range(0, 0).to_uint64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_orbit_out_2);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > orbit_out_2_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "orbit_out_2");
  
            // push token into output port buffer
            if (AESL_token != "") {
              orbit_out_2_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "orbit_out_2" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_orbit_out_2)[0*1+0] = orbit_out_2_pc_buffer[0].range(0, 0).to_uint64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_orbit_out_3);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > orbit_out_3_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "orbit_out_3");
  
            // push token into output port buffer
            if (AESL_token != "") {
              orbit_out_3_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "orbit_out_3" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_orbit_out_3)[0*1+0] = orbit_out_3_pc_buffer[0].range(0, 0).to_uint64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_start_out_0);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > start_out_0_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "start_out_0");
  
            // push token into output port buffer
            if (AESL_token != "") {
              start_out_0_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "start_out_0" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_start_out_0)[0*1+0] = start_out_0_pc_buffer[0].range(0, 0).to_uint64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_start_out_1);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > start_out_1_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "start_out_1");
  
            // push token into output port buffer
            if (AESL_token != "") {
              start_out_1_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "start_out_1" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_start_out_1)[0*1+0] = start_out_1_pc_buffer[0].range(0, 0).to_uint64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_start_out_2);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > start_out_2_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "start_out_2");
  
            // push token into output port buffer
            if (AESL_token != "") {
              start_out_2_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "start_out_2" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_start_out_2)[0*1+0] = start_out_2_pc_buffer[0].range(0, 0).to_uint64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_start_out_3);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > start_out_3_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "start_out_3");
  
            // push token into output port buffer
            if (AESL_token != "") {
              start_out_3_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "start_out_3" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_start_out_3)[0*1+0] = start_out_3_pc_buffer[0].range(0, 0).to_uint64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_end_out_0);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > end_out_0_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "end_out_0");
  
            // push token into output port buffer
            if (AESL_token != "") {
              end_out_0_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "end_out_0" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_end_out_0)[0*1+0] = end_out_0_pc_buffer[0].range(0, 0).to_uint64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_end_out_1);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > end_out_1_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "end_out_1");
  
            // push token into output port buffer
            if (AESL_token != "") {
              end_out_1_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "end_out_1" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_end_out_1)[0*1+0] = end_out_1_pc_buffer[0].range(0, 0).to_uint64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_end_out_2);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > end_out_2_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "end_out_2");
  
            // push token into output port buffer
            if (AESL_token != "") {
              end_out_2_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "end_out_2" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_end_out_2)[0*1+0] = end_out_2_pc_buffer[0].range(0, 0).to_uint64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_end_out_3);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > end_out_3_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "end_out_3");
  
            // push token into output port buffer
            if (AESL_token != "") {
              end_out_3_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "end_out_3" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_end_out_3)[0*1+0] = end_out_3_pc_buffer[0].range(0, 0).to_uint64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_valid_out_0);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > valid_out_0_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "valid_out_0");
  
            // push token into output port buffer
            if (AESL_token != "") {
              valid_out_0_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "valid_out_0" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_valid_out_0)[0*1+0] = valid_out_0_pc_buffer[0].range(0, 0).to_uint64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_valid_out_1);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > valid_out_1_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "valid_out_1");
  
            // push token into output port buffer
            if (AESL_token != "") {
              valid_out_1_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "valid_out_1" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_valid_out_1)[0*1+0] = valid_out_1_pc_buffer[0].range(0, 0).to_uint64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_valid_out_2);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > valid_out_2_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "valid_out_2");
  
            // push token into output port buffer
            if (AESL_token != "") {
              valid_out_2_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "valid_out_2" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_valid_out_2)[0*1+0] = valid_out_2_pc_buffer[0].range(0, 0).to_uint64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_valid_out_3);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > valid_out_3_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token, "valid_out_3");
  
            // push token into output port buffer
            if (AESL_token != "") {
              valid_out_3_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "valid_out_3" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_valid_out_3)[0*1+0] = valid_out_3_pc_buffer[0].range(0, 0).to_uint64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
    AESL_transaction_pc++;
    return ;
  }
static unsigned AESL_transaction;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
CodeState = DUMP_INPUTS;
// print valid Transactions
{
aesl_fh.write(AUTOTB_TVIN_valid, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)&__xlx_apatb_param_valid);
aesl_fh.write(AUTOTB_TVIN_valid, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.valid_depth);
aesl_fh.write(AUTOTB_TVIN_valid, end_str());
}

// print set Transactions
{
aesl_fh.write(AUTOTB_TVIN_set, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)&__xlx_apatb_param_set);
aesl_fh.write(AUTOTB_TVIN_set, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.set_depth);
aesl_fh.write(AUTOTB_TVIN_set, end_str());
}

// print p_idxs_0 Transactions
{
aesl_fh.write(AUTOTB_TVIN_p_idxs_0, begin_str(AESL_transaction));
{
    sc_bv<64> __xlx_tmp_lv = *((long long*)__xlx_apatb_param_p_idxs_0);
aesl_fh.write(AUTOTB_TVIN_p_idxs_0, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.p_idxs_0_depth);
aesl_fh.write(AUTOTB_TVIN_p_idxs_0, end_str());
}

// print p_idxs_1 Transactions
{
aesl_fh.write(AUTOTB_TVIN_p_idxs_1, begin_str(AESL_transaction));
{
    sc_bv<64> __xlx_tmp_lv = *((long long*)__xlx_apatb_param_p_idxs_1);
aesl_fh.write(AUTOTB_TVIN_p_idxs_1, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.p_idxs_1_depth);
aesl_fh.write(AUTOTB_TVIN_p_idxs_1, end_str());
}

// print p_idxs_2 Transactions
{
aesl_fh.write(AUTOTB_TVIN_p_idxs_2, begin_str(AESL_transaction));
{
    sc_bv<64> __xlx_tmp_lv = *((long long*)__xlx_apatb_param_p_idxs_2);
aesl_fh.write(AUTOTB_TVIN_p_idxs_2, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.p_idxs_2_depth);
aesl_fh.write(AUTOTB_TVIN_p_idxs_2, end_str());
}

// print p_idxs_3 Transactions
{
aesl_fh.write(AUTOTB_TVIN_p_idxs_3, begin_str(AESL_transaction));
{
    sc_bv<64> __xlx_tmp_lv = *((long long*)__xlx_apatb_param_p_idxs_3);
aesl_fh.write(AUTOTB_TVIN_p_idxs_3, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.p_idxs_3_depth);
aesl_fh.write(AUTOTB_TVIN_p_idxs_3, end_str());
}

// print data_out_0 Transactions
{
aesl_fh.write(AUTOTB_TVIN_data_out_0, begin_str(AESL_transaction));
{
    sc_bv<64> __xlx_tmp_lv = *((long long*)__xlx_apatb_param_data_out_0);
aesl_fh.write(AUTOTB_TVIN_data_out_0, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.data_out_0_depth);
aesl_fh.write(AUTOTB_TVIN_data_out_0, end_str());
}

// print data_out_1 Transactions
{
aesl_fh.write(AUTOTB_TVIN_data_out_1, begin_str(AESL_transaction));
{
    sc_bv<64> __xlx_tmp_lv = *((long long*)__xlx_apatb_param_data_out_1);
aesl_fh.write(AUTOTB_TVIN_data_out_1, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.data_out_1_depth);
aesl_fh.write(AUTOTB_TVIN_data_out_1, end_str());
}

// print data_out_2 Transactions
{
aesl_fh.write(AUTOTB_TVIN_data_out_2, begin_str(AESL_transaction));
{
    sc_bv<64> __xlx_tmp_lv = *((long long*)__xlx_apatb_param_data_out_2);
aesl_fh.write(AUTOTB_TVIN_data_out_2, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.data_out_2_depth);
aesl_fh.write(AUTOTB_TVIN_data_out_2, end_str());
}

// print data_out_3 Transactions
{
aesl_fh.write(AUTOTB_TVIN_data_out_3, begin_str(AESL_transaction));
{
    sc_bv<64> __xlx_tmp_lv = *((long long*)__xlx_apatb_param_data_out_3);
aesl_fh.write(AUTOTB_TVIN_data_out_3, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.data_out_3_depth);
aesl_fh.write(AUTOTB_TVIN_data_out_3, end_str());
}

// print orbit_out_0 Transactions
{
aesl_fh.write(AUTOTB_TVIN_orbit_out_0, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_orbit_out_0);
aesl_fh.write(AUTOTB_TVIN_orbit_out_0, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.orbit_out_0_depth);
aesl_fh.write(AUTOTB_TVIN_orbit_out_0, end_str());
}

// print orbit_out_1 Transactions
{
aesl_fh.write(AUTOTB_TVIN_orbit_out_1, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_orbit_out_1);
aesl_fh.write(AUTOTB_TVIN_orbit_out_1, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.orbit_out_1_depth);
aesl_fh.write(AUTOTB_TVIN_orbit_out_1, end_str());
}

// print orbit_out_2 Transactions
{
aesl_fh.write(AUTOTB_TVIN_orbit_out_2, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_orbit_out_2);
aesl_fh.write(AUTOTB_TVIN_orbit_out_2, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.orbit_out_2_depth);
aesl_fh.write(AUTOTB_TVIN_orbit_out_2, end_str());
}

// print orbit_out_3 Transactions
{
aesl_fh.write(AUTOTB_TVIN_orbit_out_3, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_orbit_out_3);
aesl_fh.write(AUTOTB_TVIN_orbit_out_3, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.orbit_out_3_depth);
aesl_fh.write(AUTOTB_TVIN_orbit_out_3, end_str());
}

// print start_out_0 Transactions
{
aesl_fh.write(AUTOTB_TVIN_start_out_0, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_start_out_0);
aesl_fh.write(AUTOTB_TVIN_start_out_0, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.start_out_0_depth);
aesl_fh.write(AUTOTB_TVIN_start_out_0, end_str());
}

// print start_out_1 Transactions
{
aesl_fh.write(AUTOTB_TVIN_start_out_1, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_start_out_1);
aesl_fh.write(AUTOTB_TVIN_start_out_1, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.start_out_1_depth);
aesl_fh.write(AUTOTB_TVIN_start_out_1, end_str());
}

// print start_out_2 Transactions
{
aesl_fh.write(AUTOTB_TVIN_start_out_2, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_start_out_2);
aesl_fh.write(AUTOTB_TVIN_start_out_2, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.start_out_2_depth);
aesl_fh.write(AUTOTB_TVIN_start_out_2, end_str());
}

// print start_out_3 Transactions
{
aesl_fh.write(AUTOTB_TVIN_start_out_3, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_start_out_3);
aesl_fh.write(AUTOTB_TVIN_start_out_3, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.start_out_3_depth);
aesl_fh.write(AUTOTB_TVIN_start_out_3, end_str());
}

// print end_out_0 Transactions
{
aesl_fh.write(AUTOTB_TVIN_end_out_0, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_end_out_0);
aesl_fh.write(AUTOTB_TVIN_end_out_0, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.end_out_0_depth);
aesl_fh.write(AUTOTB_TVIN_end_out_0, end_str());
}

// print end_out_1 Transactions
{
aesl_fh.write(AUTOTB_TVIN_end_out_1, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_end_out_1);
aesl_fh.write(AUTOTB_TVIN_end_out_1, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.end_out_1_depth);
aesl_fh.write(AUTOTB_TVIN_end_out_1, end_str());
}

// print end_out_2 Transactions
{
aesl_fh.write(AUTOTB_TVIN_end_out_2, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_end_out_2);
aesl_fh.write(AUTOTB_TVIN_end_out_2, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.end_out_2_depth);
aesl_fh.write(AUTOTB_TVIN_end_out_2, end_str());
}

// print end_out_3 Transactions
{
aesl_fh.write(AUTOTB_TVIN_end_out_3, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_end_out_3);
aesl_fh.write(AUTOTB_TVIN_end_out_3, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.end_out_3_depth);
aesl_fh.write(AUTOTB_TVIN_end_out_3, end_str());
}

// print valid_out_0 Transactions
{
aesl_fh.write(AUTOTB_TVIN_valid_out_0, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_valid_out_0);
aesl_fh.write(AUTOTB_TVIN_valid_out_0, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.valid_out_0_depth);
aesl_fh.write(AUTOTB_TVIN_valid_out_0, end_str());
}

// print valid_out_1 Transactions
{
aesl_fh.write(AUTOTB_TVIN_valid_out_1, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_valid_out_1);
aesl_fh.write(AUTOTB_TVIN_valid_out_1, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.valid_out_1_depth);
aesl_fh.write(AUTOTB_TVIN_valid_out_1, end_str());
}

// print valid_out_2 Transactions
{
aesl_fh.write(AUTOTB_TVIN_valid_out_2, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_valid_out_2);
aesl_fh.write(AUTOTB_TVIN_valid_out_2, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.valid_out_2_depth);
aesl_fh.write(AUTOTB_TVIN_valid_out_2, end_str());
}

// print valid_out_3 Transactions
{
aesl_fh.write(AUTOTB_TVIN_valid_out_3, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_valid_out_3);
aesl_fh.write(AUTOTB_TVIN_valid_out_3, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.valid_out_3_depth);
aesl_fh.write(AUTOTB_TVIN_valid_out_3, end_str());
}

// print CLOCK_RATIO_MINUS_ONE Transactions
{
aesl_fh.write(AUTOTB_TVIN_CLOCK_RATIO_MINUS_ONE, begin_str(AESL_transaction));
{
    sc_bv<4> __xlx_tmp_lv = *((char*)__xlx_apatb_param_CLOCK_RATIO_MINUS_ONE);
aesl_fh.write(AUTOTB_TVIN_CLOCK_RATIO_MINUS_ONE, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.CLOCK_RATIO_MINUS_ONE_depth);
aesl_fh.write(AUTOTB_TVIN_CLOCK_RATIO_MINUS_ONE, end_str());
}

CodeState = CALL_C_DUT;
gen4_hw_stub_wrapper(__xlx_apatb_param_valid, __xlx_apatb_param_set, __xlx_apatb_param_p_idxs_0, __xlx_apatb_param_p_idxs_1, __xlx_apatb_param_p_idxs_2, __xlx_apatb_param_p_idxs_3, __xlx_apatb_param_data_out_0, __xlx_apatb_param_data_out_1, __xlx_apatb_param_data_out_2, __xlx_apatb_param_data_out_3, __xlx_apatb_param_orbit_out_0, __xlx_apatb_param_orbit_out_1, __xlx_apatb_param_orbit_out_2, __xlx_apatb_param_orbit_out_3, __xlx_apatb_param_start_out_0, __xlx_apatb_param_start_out_1, __xlx_apatb_param_start_out_2, __xlx_apatb_param_start_out_3, __xlx_apatb_param_end_out_0, __xlx_apatb_param_end_out_1, __xlx_apatb_param_end_out_2, __xlx_apatb_param_end_out_3, __xlx_apatb_param_valid_out_0, __xlx_apatb_param_valid_out_1, __xlx_apatb_param_valid_out_2, __xlx_apatb_param_valid_out_3, __xlx_apatb_param_CLOCK_RATIO_MINUS_ONE);
CodeState = DUMP_OUTPUTS;
// print data_out_0 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_data_out_0, begin_str(AESL_transaction));
{
    sc_bv<64> __xlx_tmp_lv = *((long long*)__xlx_apatb_param_data_out_0);
aesl_fh.write(AUTOTB_TVOUT_data_out_0, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.data_out_0_depth);
aesl_fh.write(AUTOTB_TVOUT_data_out_0, end_str());
}

// print data_out_1 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_data_out_1, begin_str(AESL_transaction));
{
    sc_bv<64> __xlx_tmp_lv = *((long long*)__xlx_apatb_param_data_out_1);
aesl_fh.write(AUTOTB_TVOUT_data_out_1, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.data_out_1_depth);
aesl_fh.write(AUTOTB_TVOUT_data_out_1, end_str());
}

// print data_out_2 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_data_out_2, begin_str(AESL_transaction));
{
    sc_bv<64> __xlx_tmp_lv = *((long long*)__xlx_apatb_param_data_out_2);
aesl_fh.write(AUTOTB_TVOUT_data_out_2, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.data_out_2_depth);
aesl_fh.write(AUTOTB_TVOUT_data_out_2, end_str());
}

// print data_out_3 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_data_out_3, begin_str(AESL_transaction));
{
    sc_bv<64> __xlx_tmp_lv = *((long long*)__xlx_apatb_param_data_out_3);
aesl_fh.write(AUTOTB_TVOUT_data_out_3, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.data_out_3_depth);
aesl_fh.write(AUTOTB_TVOUT_data_out_3, end_str());
}

// print orbit_out_0 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_orbit_out_0, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_orbit_out_0);
aesl_fh.write(AUTOTB_TVOUT_orbit_out_0, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.orbit_out_0_depth);
aesl_fh.write(AUTOTB_TVOUT_orbit_out_0, end_str());
}

// print orbit_out_1 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_orbit_out_1, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_orbit_out_1);
aesl_fh.write(AUTOTB_TVOUT_orbit_out_1, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.orbit_out_1_depth);
aesl_fh.write(AUTOTB_TVOUT_orbit_out_1, end_str());
}

// print orbit_out_2 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_orbit_out_2, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_orbit_out_2);
aesl_fh.write(AUTOTB_TVOUT_orbit_out_2, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.orbit_out_2_depth);
aesl_fh.write(AUTOTB_TVOUT_orbit_out_2, end_str());
}

// print orbit_out_3 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_orbit_out_3, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_orbit_out_3);
aesl_fh.write(AUTOTB_TVOUT_orbit_out_3, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.orbit_out_3_depth);
aesl_fh.write(AUTOTB_TVOUT_orbit_out_3, end_str());
}

// print start_out_0 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_start_out_0, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_start_out_0);
aesl_fh.write(AUTOTB_TVOUT_start_out_0, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.start_out_0_depth);
aesl_fh.write(AUTOTB_TVOUT_start_out_0, end_str());
}

// print start_out_1 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_start_out_1, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_start_out_1);
aesl_fh.write(AUTOTB_TVOUT_start_out_1, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.start_out_1_depth);
aesl_fh.write(AUTOTB_TVOUT_start_out_1, end_str());
}

// print start_out_2 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_start_out_2, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_start_out_2);
aesl_fh.write(AUTOTB_TVOUT_start_out_2, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.start_out_2_depth);
aesl_fh.write(AUTOTB_TVOUT_start_out_2, end_str());
}

// print start_out_3 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_start_out_3, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_start_out_3);
aesl_fh.write(AUTOTB_TVOUT_start_out_3, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.start_out_3_depth);
aesl_fh.write(AUTOTB_TVOUT_start_out_3, end_str());
}

// print end_out_0 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_end_out_0, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_end_out_0);
aesl_fh.write(AUTOTB_TVOUT_end_out_0, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.end_out_0_depth);
aesl_fh.write(AUTOTB_TVOUT_end_out_0, end_str());
}

// print end_out_1 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_end_out_1, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_end_out_1);
aesl_fh.write(AUTOTB_TVOUT_end_out_1, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.end_out_1_depth);
aesl_fh.write(AUTOTB_TVOUT_end_out_1, end_str());
}

// print end_out_2 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_end_out_2, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_end_out_2);
aesl_fh.write(AUTOTB_TVOUT_end_out_2, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.end_out_2_depth);
aesl_fh.write(AUTOTB_TVOUT_end_out_2, end_str());
}

// print end_out_3 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_end_out_3, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_end_out_3);
aesl_fh.write(AUTOTB_TVOUT_end_out_3, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.end_out_3_depth);
aesl_fh.write(AUTOTB_TVOUT_end_out_3, end_str());
}

// print valid_out_0 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_valid_out_0, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_valid_out_0);
aesl_fh.write(AUTOTB_TVOUT_valid_out_0, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.valid_out_0_depth);
aesl_fh.write(AUTOTB_TVOUT_valid_out_0, end_str());
}

// print valid_out_1 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_valid_out_1, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_valid_out_1);
aesl_fh.write(AUTOTB_TVOUT_valid_out_1, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.valid_out_1_depth);
aesl_fh.write(AUTOTB_TVOUT_valid_out_1, end_str());
}

// print valid_out_2 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_valid_out_2, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_valid_out_2);
aesl_fh.write(AUTOTB_TVOUT_valid_out_2, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.valid_out_2_depth);
aesl_fh.write(AUTOTB_TVOUT_valid_out_2, end_str());
}

// print valid_out_3 Transactions
{
aesl_fh.write(AUTOTB_TVOUT_valid_out_3, begin_str(AESL_transaction));
{
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_valid_out_3);
aesl_fh.write(AUTOTB_TVOUT_valid_out_3, __xlx_tmp_lv.to_string(SC_HEX)+string("\n"));
}
  tcl_file.set_num(1, &tcl_file.valid_out_3_depth);
aesl_fh.write(AUTOTB_TVOUT_valid_out_3, end_str());
}

CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
