# W3Pi_Analysis

This repository contains the main code which I developed during my work at Cern for my master thesis.

- **hls folder**: gen4.cc is the code to generate the output of the correlator layer, emulating the puppi candidates of the W3pi signal events.
    - to create the hls project you need the run_hls_gen4.tcl file
    - proj_gen4: contains all the files generated by vitis
      - syn: files generated after run the synthesis on vitis, to include in the top file for the bitfile
    - ***gen_seed*** us the latest version for the puppi generator, where the orbits are different from each other (in accordance with the LUT). It also includes the payloads with the Ethernet connections.
- **gen4**: to exctract the bitfile from the hls code, you need the infrastructure contained in this folder, i.e. two folder called hdl and cfg
  - hdl: contains the payloads, i.e. the port connections
  - cfg: contains the top file which summarizes the file to import to compile the project
- **gen4_vhdl**: contains the file generated by vitis for the gen4.cc code
- **read**: useful code used to develope an unpacker of the files coming from the correlator and to plot the unpacked features
- **unpack_select**: algorithm used for the online unpacker and analyzer
- **Live_analysis**: all the files to unpack and analyze online from the DTH
- **w3pi_analysis**: contains the studies of the features for the generator, the selection algorithm for the estimates and the bkg study (for the compine usage)
