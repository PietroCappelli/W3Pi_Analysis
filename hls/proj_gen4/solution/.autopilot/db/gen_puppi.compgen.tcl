# This script segment is generated automatically by AutoPilot

set id 1
set name gen4_mul_mul_12ns_11ns_23_4_1
set corename simcore_mul
set op mul
set stage_num 4
set clk_width 1
set clk_signed 0
set reset_width 1
set reset_signed 0
set in0_width 12
set in0_signed 0
set in1_width 11
set in1_signed 0
set ce_width 1
set ce_signed 0
set out_width 23
set arg_lists {i0 {12 0 +} i1 {11 0 +} p {23 1 +} acc {0} }
set TrueReset 0
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {op} TYPE {mul} IMPL {dsp} LATENCY 3 ALLOW_PRAGMA 1
}


set op mul
set corename DSP48
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_dsp48] == "::AESL_LIB_VIRTEX::xil_gen_dsp48"} {
eval "::AESL_LIB_VIRTEX::xil_gen_dsp48 { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    true_reset ${TrueReset} \
    stage_num ${stage_num} \
    clk_width ${clk_width} \
    clk_signed ${clk_signed} \
    reset_width ${reset_width} \
    reset_signed ${reset_signed} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    ce_width ${ce_width} \
    ce_signed ${ce_signed} \
    out_width ${out_width} \
    arg_lists {${arg_lists}} \
}"
} else {
puts "@W \[IMPL-101\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_dsp48, check your platform lib"
}
}


set id 2
set name gen4_mul_mul_10ns_10ns_20_4_1
set corename simcore_mul
set op mul
set stage_num 4
set clk_width 1
set clk_signed 0
set reset_width 1
set reset_signed 0
set in0_width 10
set in0_signed 0
set in1_width 10
set in1_signed 0
set ce_width 1
set ce_signed 0
set out_width 20
set arg_lists {i0 {10 0 +} i1 {10 0 +} p {20 1 +} acc {0} }
set TrueReset 0
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {op} TYPE {mul} IMPL {dsp} LATENCY 3 ALLOW_PRAGMA 1
}


set op mul
set corename DSP48
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_dsp48] == "::AESL_LIB_VIRTEX::xil_gen_dsp48"} {
eval "::AESL_LIB_VIRTEX::xil_gen_dsp48 { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    true_reset ${TrueReset} \
    stage_num ${stage_num} \
    clk_width ${clk_width} \
    clk_signed ${clk_signed} \
    reset_width ${reset_width} \
    reset_signed ${reset_signed} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    ce_width ${ce_width} \
    ce_signed ${ce_signed} \
    out_width ${out_width} \
    arg_lists {${arg_lists}} \
}"
} else {
puts "@W \[IMPL-101\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_dsp48, check your platform lib"
}
}


set id 3
set name gen4_mul_mul_11ns_11ns_22_4_1
set corename simcore_mul
set op mul
set stage_num 4
set clk_width 1
set clk_signed 0
set reset_width 1
set reset_signed 0
set in0_width 11
set in0_signed 0
set in1_width 11
set in1_signed 0
set ce_width 1
set ce_signed 0
set out_width 22
set arg_lists {i0 {11 0 +} i1 {11 0 +} p {22 1 +} acc {0} }
set TrueReset 0
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {op} TYPE {mul} IMPL {dsp} LATENCY 3 ALLOW_PRAGMA 1
}


set op mul
set corename DSP48
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_dsp48] == "::AESL_LIB_VIRTEX::xil_gen_dsp48"} {
eval "::AESL_LIB_VIRTEX::xil_gen_dsp48 { \
    id ${id} \
    name ${name} \
    corename ${corename} \
    op ${op} \
    reset_level 1 \
    sync_rst true \
    true_reset ${TrueReset} \
    stage_num ${stage_num} \
    clk_width ${clk_width} \
    clk_signed ${clk_signed} \
    reset_width ${reset_width} \
    reset_signed ${reset_signed} \
    in0_width ${in0_width} \
    in0_signed ${in0_signed} \
    in1_width ${in1_width} \
    in1_signed ${in1_signed} \
    ce_width ${ce_width} \
    ce_signed ${ce_signed} \
    out_width ${out_width} \
    arg_lists {${arg_lists}} \
}"
} else {
puts "@W \[IMPL-101\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_dsp48, check your platform lib"
}
}


# Memory (RAM/ROM)  definition:
set ID 7
set hasByteEnable 0
set MemName gen4_gen_puppi_ptLUT_V_ROM_AUTO_1R
set CoreName ap_simcore_mem
set PortList { 1 }
set DataWd 8
set AddrRange 1023
set AddrWd 10
set impl_style auto
set TrueReset 0
set IsROM 1
set ROMData { "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001000" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001001" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001010" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001011" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001100" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001101" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001110" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00001111" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010000" "00010001" "00010001" "00010001" "00010001" "00010001" "00010001" "00010001" "00010001" "00010001" "00010001" "00010001" "00010001" "00010001" "00010001" "00010001" "00010001" "00010001" "00010001" "00010010" "00010010" "00010010" "00010010" "00010010" "00010010" "00010010" "00010010" "00010010" "00010010" "00010010" "00010010" "00010010" "00010010" "00010011" "00010011" "00010011" "00010011" "00010011" "00010011" "00010011" "00010011" "00010011" "00010011" "00010011" "00010011" "00010100" "00010100" "00010100" "00010100" "00010100" "00010100" "00010100" "00010100" "00010100" "00010101" "00010101" "00010101" "00010101" "00010101" "00010101" "00010101" "00010101" "00010110" "00010110" "00010110" "00010110" "00010110" "00010110" "00010110" "00010111" "00010111" "00010111" "00010111" "00010111" "00011000" "00011000" "00011000" "00011000" "00011000" "00011001" "00011001" "00011001" "00011001" "00011001" "00011010" "00011010" "00011010" "00011011" "00011011" "00011011" "00011011" "00011100" "00011100" "00011100" "00011101" "00011101" "00011110" "00011110" "00011110" "00011111" "00011111" "00100000" "00100000" "00100001" "00100001" "00100010" "00100010" "00100011" "00100011" "00100100" "00100101" "00100101" "00100110" "00100111" "00101000" "00101000" "00101001" "00101010" "00101011" "00101011" "00101100" "00101101" "00101110" "00101111" "00110000" "00110001" "00110001" "00110011" "00110100" "00110101" "00110110" "00110111" "00111000" "00111001" "00111010" "00111011" "00111100" "00111110" "00111111" "01000000" "01000001" "01000011" "01000100" "01000101" "01000111" "01001000" "01001010" "01001011" "01001101" "01001110" "01010000" "01010001" "01010011" "01010101" "01010110" "01011000" "01011010" "01011011" "01011101" "01011111" "01100001" "01100011" "01100101" "01100110" "01101000" "01101010" "01101100" "01101110" "01110001" "01110011" "01110101" "01110111" "01111001" "01111011" "01111110" "10000000" "10000011" "10000110" "10001000" "10001100" "10001110" "10010010" "10010101" "10011010" "10011110" "10100011" "10101001" "10110001" "10111010" "11000100" }
set HasInitializer 1
set Initializer $ROMData
set NumOfStage 2
set DelayBudget 1.237
set ClkPeriod 2.5
if {${::AESL::PGuard_simmodel_gen}} {
if {[info proc ap_gen_simcore_mem] == "ap_gen_simcore_mem"} {
    eval "ap_gen_simcore_mem { \
    id ${ID} \
    name ${MemName} \
    corename ${CoreName}  \
    op mem  \
    hasByteEnable ${hasByteEnable} \
    reset_level 1 \
    sync_rst true \
    stage_num ${NumOfStage}  \
    port_num 1 \
    port_list \{${PortList}\} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    addr_range ${AddrRange} \
    style ${impl_style} \
    true_reset ${TrueReset} \
    delay_budget ${DelayBudget} \
    clk_period ${ClkPeriod} \
    HasInitializer ${HasInitializer} \
    rom_data \{${ROMData}\} \
 } "
} else {
    puts "@W \[IMPL-102\] Cannot find ap_gen_simcore_mem, check your platform lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $MemName BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


set CoreName ROM
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_ROM] == "::AESL_LIB_VIRTEX::xil_gen_ROM"} {
    eval "::AESL_LIB_VIRTEX::xil_gen_ROM { \
    id ${ID} \
    name ${MemName} \
    corename ${CoreName}  \
    op mem  \
    hasByteEnable ${hasByteEnable} \
    reset_level 1 \
    sync_rst true \
    stage_num ${NumOfStage}  \
    port_num 1 \
    port_list \{${PortList}\} \
    data_wd ${DataWd} \
    addr_wd ${AddrWd} \
    addr_range ${AddrRange} \
    style ${impl_style} \
    true_reset ${TrueReset} \
    delay_budget ${DelayBudget} \
    clk_period ${ClkPeriod} \
    HasInitializer ${HasInitializer} \
    rom_data \{${ROMData}\} \
 } "
  } else {
    puts "@W \[IMPL-104\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_ROM, check your platform lib"
  }
}


# clear list
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_begin
    cg_default_interface_gen_bundle_begin
    AESL_LIB_XILADAPTER::native_axis_begin
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 8 \
    name rnd \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_rnd \
    op interface \
    ports { rnd { I 34 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id -1 \
    name ap_ctrl \
    type ap_ctrl \
    reset_level 1 \
    sync_rst true \
    corename ap_ctrl \
    op interface \
    ports { ap_start { I 1 bit } ap_ready { O 1 bit } ap_done { O 1 bit } ap_idle { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id -2 \
    name ap_return \
    type ap_return \
    reset_level 1 \
    sync_rst true \
    corename ap_return \
    op interface \
    ports { ap_return { O 64 vector } } \
} "
}


# Adapter definition:
set PortName ap_clk
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_clock] == "cg_default_interface_gen_clock"} {
eval "cg_default_interface_gen_clock { \
    id -3 \
    name ${PortName} \
    reset_level 1 \
    sync_rst true \
    corename apif_ap_clk \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-113\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}


# Adapter definition:
set PortName ap_rst
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_reset] == "cg_default_interface_gen_reset"} {
eval "cg_default_interface_gen_reset { \
    id -4 \
    name ${PortName} \
    reset_level 1 \
    sync_rst true \
    corename apif_ap_rst \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-114\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}


# Adapter definition:
set PortName ap_ce
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_ce] == "cg_default_interface_gen_ce"} {
eval "cg_default_interface_gen_ce { \
    id -5 \
    name ${PortName} \
    reset_level 1 \
    sync_rst true \
    corename apif_ap_ce \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-113\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}



# merge
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_end
    cg_default_interface_gen_bundle_end
    AESL_LIB_XILADAPTER::native_axis_end
}


