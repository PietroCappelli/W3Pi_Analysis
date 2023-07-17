#include <systemc>
#include <vector>
#include <iostream>
#include "hls_stream.h"
#include "ap_int.h"
#include "ap_fixed.h"
using namespace std;
using namespace sc_dt;
class AESL_RUNTIME_BC {
  public:
    AESL_RUNTIME_BC(const char* name) {
      file_token.open( name);
      if (!file_token.good()) {
        cout << "Failed to open tv file " << name << endl;
        exit (1);
      }
      file_token >> mName;//[[[runtime]]]
    }
    ~AESL_RUNTIME_BC() {
      file_token.close();
    }
    int read_size () {
      int size = 0;
      file_token >> mName;//[[transaction]]
      file_token >> mName;//transaction number
      file_token >> mName;//pop_size
      size = atoi(mName.c_str());
      file_token >> mName;//[[/transaction]]
      return size;
    }
  public:
    fstream file_token;
    string mName;
};
struct __cosim_s1__ { char data[1]; };
extern "C" void gen4(char, char, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, __cosim_s1__);
extern "C" void apatb_gen4_hw(char __xlx_apatb_param_valid, char __xlx_apatb_param_set, volatile void * __xlx_apatb_param_p_idxs_0, volatile void * __xlx_apatb_param_p_idxs_1, volatile void * __xlx_apatb_param_p_idxs_2, volatile void * __xlx_apatb_param_p_idxs_3, volatile void * __xlx_apatb_param_data_out_0, volatile void * __xlx_apatb_param_data_out_1, volatile void * __xlx_apatb_param_data_out_2, volatile void * __xlx_apatb_param_data_out_3, volatile void * __xlx_apatb_param_orbit_out_0, volatile void * __xlx_apatb_param_orbit_out_1, volatile void * __xlx_apatb_param_orbit_out_2, volatile void * __xlx_apatb_param_orbit_out_3, volatile void * __xlx_apatb_param_start_out_0, volatile void * __xlx_apatb_param_start_out_1, volatile void * __xlx_apatb_param_start_out_2, volatile void * __xlx_apatb_param_start_out_3, volatile void * __xlx_apatb_param_end_out_0, volatile void * __xlx_apatb_param_end_out_1, volatile void * __xlx_apatb_param_end_out_2, volatile void * __xlx_apatb_param_end_out_3, volatile void * __xlx_apatb_param_valid_out_0, volatile void * __xlx_apatb_param_valid_out_1, volatile void * __xlx_apatb_param_valid_out_2, volatile void * __xlx_apatb_param_valid_out_3, __cosim_s1__* __xlx_apatb_param_CLOCK_RATIO_MINUS_ONE) {
  // DUT call
  gen4(__xlx_apatb_param_valid, __xlx_apatb_param_set, __xlx_apatb_param_p_idxs_0, __xlx_apatb_param_p_idxs_1, __xlx_apatb_param_p_idxs_2, __xlx_apatb_param_p_idxs_3, __xlx_apatb_param_data_out_0, __xlx_apatb_param_data_out_1, __xlx_apatb_param_data_out_2, __xlx_apatb_param_data_out_3, __xlx_apatb_param_orbit_out_0, __xlx_apatb_param_orbit_out_1, __xlx_apatb_param_orbit_out_2, __xlx_apatb_param_orbit_out_3, __xlx_apatb_param_start_out_0, __xlx_apatb_param_start_out_1, __xlx_apatb_param_start_out_2, __xlx_apatb_param_start_out_3, __xlx_apatb_param_end_out_0, __xlx_apatb_param_end_out_1, __xlx_apatb_param_end_out_2, __xlx_apatb_param_end_out_3, __xlx_apatb_param_valid_out_0, __xlx_apatb_param_valid_out_1, __xlx_apatb_param_valid_out_2, __xlx_apatb_param_valid_out_3, *__xlx_apatb_param_CLOCK_RATIO_MINUS_ONE);
}
