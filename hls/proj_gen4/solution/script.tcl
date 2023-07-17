############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
open_project proj_gen4
set_top gen4
add_files gen4.cc -cflags "-std=c++11"
add_files gen4.h
add_files -tb gen4_test.cpp -cflags "-std=c++11 -Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution" -flow_target vivado
set_part {xcku15p-ffva1760-2-e}
create_clock -period 2.5 -name default
source "./proj_gen4/solution/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
