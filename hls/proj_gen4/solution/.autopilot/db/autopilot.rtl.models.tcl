set SynModuleInfo {
  {SRCNAME gen_puppi MODELNAME gen_puppi RTLNAME gen4_gen_puppi
    SUBMODULES {
      {MODELNAME gen4_mul_mul_12ns_11ns_23_4_1 RTLNAME gen4_mul_mul_12ns_11ns_23_4_1 BINDTYPE op TYPE mul IMPL dsp LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME gen4_mul_mul_10ns_10ns_20_4_1 RTLNAME gen4_mul_mul_10ns_10ns_20_4_1 BINDTYPE op TYPE mul IMPL dsp LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME gen4_mul_mul_11ns_11ns_22_4_1 RTLNAME gen4_mul_mul_11ns_11ns_22_4_1 BINDTYPE op TYPE mul IMPL dsp LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME gen4_gen_puppi_ptLUT_V_ROM_AUTO_1R RTLNAME gen4_gen_puppi_ptLUT_V_ROM_AUTO_1R BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME gen4 MODELNAME gen4 RTLNAME gen4 IS_TOP 1
    SUBMODULES {
      {MODELNAME gen4_mul_mul_11ns_7ns_18_4_1 RTLNAME gen4_mul_mul_11ns_7ns_18_4_1 BINDTYPE op TYPE mul IMPL dsp LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME gen4_NLUT_V_ROM_AUTO_1R RTLNAME gen4_NLUT_V_ROM_AUTO_1R BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
    }
  }
}
