set moduleName gen4
set isTopModule 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set pipeline_type function
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {gen4}
set C_modelType { void 0 }
set C_modelArgList {
	{ valid uint 1 regular  }
	{ set uint 1 regular  }
	{ p_idxs_0 int 64 regular {pointer 0}  }
	{ p_idxs_1 int 64 regular {pointer 0}  }
	{ p_idxs_2 int 64 regular {pointer 0}  }
	{ p_idxs_3 int 64 regular {pointer 0}  }
	{ data_out_0 int 64 regular {pointer 1}  }
	{ data_out_1 int 64 regular {pointer 1}  }
	{ data_out_2 int 64 regular {pointer 1}  }
	{ data_out_3 int 64 regular {pointer 1}  }
	{ orbit_out_0 int 1 regular {pointer 1}  }
	{ orbit_out_1 int 1 regular {pointer 1}  }
	{ orbit_out_2 int 1 regular {pointer 1}  }
	{ orbit_out_3 int 1 regular {pointer 1}  }
	{ start_out_0 int 1 regular {pointer 1}  }
	{ start_out_1 int 1 regular {pointer 1}  }
	{ start_out_2 int 1 regular {pointer 1}  }
	{ start_out_3 int 1 regular {pointer 1}  }
	{ end_out_0 int 1 regular {pointer 1}  }
	{ end_out_1 int 1 regular {pointer 1}  }
	{ end_out_2 int 1 regular {pointer 1}  }
	{ end_out_3 int 1 regular {pointer 1}  }
	{ valid_out_0 int 1 regular {pointer 1}  }
	{ valid_out_1 int 1 regular {pointer 1}  }
	{ valid_out_2 int 1 regular {pointer 1}  }
	{ valid_out_3 int 1 regular {pointer 1}  }
	{ CLOCK_RATIO_MINUS_ONE int 4 unused  }
}
set C_modelArgMapList {[ 
	{ "Name" : "valid", "interface" : "wire", "bitwidth" : 1, "direction" : "READONLY"} , 
 	{ "Name" : "set", "interface" : "wire", "bitwidth" : 1, "direction" : "READONLY"} , 
 	{ "Name" : "p_idxs_0", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "p_idxs_1", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "p_idxs_2", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "p_idxs_3", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "data_out_0", "interface" : "wire", "bitwidth" : 64, "direction" : "WRITEONLY"} , 
 	{ "Name" : "data_out_1", "interface" : "wire", "bitwidth" : 64, "direction" : "WRITEONLY"} , 
 	{ "Name" : "data_out_2", "interface" : "wire", "bitwidth" : 64, "direction" : "WRITEONLY"} , 
 	{ "Name" : "data_out_3", "interface" : "wire", "bitwidth" : 64, "direction" : "WRITEONLY"} , 
 	{ "Name" : "orbit_out_0", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "orbit_out_1", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "orbit_out_2", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "orbit_out_3", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "start_out_0", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "start_out_1", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "start_out_2", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "start_out_3", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "end_out_0", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "end_out_1", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "end_out_2", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "end_out_3", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "valid_out_0", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "valid_out_1", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "valid_out_2", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "valid_out_3", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "CLOCK_RATIO_MINUS_ONE", "interface" : "wire", "bitwidth" : 4, "direction" : "READONLY"} ]}
# RTL Port declarations: 
set portNum 55
set portList { 
	{ ap_local_block sc_out sc_logic 1 signal -1 } 
	{ ap_local_deadlock sc_out sc_logic 1 signal -1 } 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ valid sc_in sc_logic 1 signal 0 } 
	{ set sc_in sc_logic 1 signal 1 } 
	{ p_idxs_0 sc_in sc_lv 64 signal 2 } 
	{ p_idxs_1 sc_in sc_lv 64 signal 3 } 
	{ p_idxs_2 sc_in sc_lv 64 signal 4 } 
	{ p_idxs_3 sc_in sc_lv 64 signal 5 } 
	{ data_out_0 sc_out sc_lv 64 signal 6 } 
	{ data_out_0_ap_vld sc_out sc_logic 1 outvld 6 } 
	{ data_out_1 sc_out sc_lv 64 signal 7 } 
	{ data_out_1_ap_vld sc_out sc_logic 1 outvld 7 } 
	{ data_out_2 sc_out sc_lv 64 signal 8 } 
	{ data_out_2_ap_vld sc_out sc_logic 1 outvld 8 } 
	{ data_out_3 sc_out sc_lv 64 signal 9 } 
	{ data_out_3_ap_vld sc_out sc_logic 1 outvld 9 } 
	{ orbit_out_0 sc_out sc_logic 1 signal 10 } 
	{ orbit_out_0_ap_vld sc_out sc_logic 1 outvld 10 } 
	{ orbit_out_1 sc_out sc_logic 1 signal 11 } 
	{ orbit_out_1_ap_vld sc_out sc_logic 1 outvld 11 } 
	{ orbit_out_2 sc_out sc_logic 1 signal 12 } 
	{ orbit_out_2_ap_vld sc_out sc_logic 1 outvld 12 } 
	{ orbit_out_3 sc_out sc_logic 1 signal 13 } 
	{ orbit_out_3_ap_vld sc_out sc_logic 1 outvld 13 } 
	{ start_out_0 sc_out sc_logic 1 signal 14 } 
	{ start_out_0_ap_vld sc_out sc_logic 1 outvld 14 } 
	{ start_out_1 sc_out sc_logic 1 signal 15 } 
	{ start_out_1_ap_vld sc_out sc_logic 1 outvld 15 } 
	{ start_out_2 sc_out sc_logic 1 signal 16 } 
	{ start_out_2_ap_vld sc_out sc_logic 1 outvld 16 } 
	{ start_out_3 sc_out sc_logic 1 signal 17 } 
	{ start_out_3_ap_vld sc_out sc_logic 1 outvld 17 } 
	{ end_out_0 sc_out sc_logic 1 signal 18 } 
	{ end_out_0_ap_vld sc_out sc_logic 1 outvld 18 } 
	{ end_out_1 sc_out sc_logic 1 signal 19 } 
	{ end_out_1_ap_vld sc_out sc_logic 1 outvld 19 } 
	{ end_out_2 sc_out sc_logic 1 signal 20 } 
	{ end_out_2_ap_vld sc_out sc_logic 1 outvld 20 } 
	{ end_out_3 sc_out sc_logic 1 signal 21 } 
	{ end_out_3_ap_vld sc_out sc_logic 1 outvld 21 } 
	{ valid_out_0 sc_out sc_logic 1 signal 22 } 
	{ valid_out_0_ap_vld sc_out sc_logic 1 outvld 22 } 
	{ valid_out_1 sc_out sc_logic 1 signal 23 } 
	{ valid_out_1_ap_vld sc_out sc_logic 1 outvld 23 } 
	{ valid_out_2 sc_out sc_logic 1 signal 24 } 
	{ valid_out_2_ap_vld sc_out sc_logic 1 outvld 24 } 
	{ valid_out_3 sc_out sc_logic 1 signal 25 } 
	{ valid_out_3_ap_vld sc_out sc_logic 1 outvld 25 } 
	{ CLOCK_RATIO_MINUS_ONE sc_in sc_lv 4 signal 26 } 
}
set NewPortList {[ 
	{ "name": "ap_local_block", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "ap_local_block", "role": "default" }} , 
 	{ "name": "ap_local_deadlock", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "ap_local_deadlock", "role": "default" }} , 
 	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "valid", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "valid", "role": "default" }} , 
 	{ "name": "set", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "set", "role": "default" }} , 
 	{ "name": "p_idxs_0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "p_idxs_0", "role": "default" }} , 
 	{ "name": "p_idxs_1", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "p_idxs_1", "role": "default" }} , 
 	{ "name": "p_idxs_2", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "p_idxs_2", "role": "default" }} , 
 	{ "name": "p_idxs_3", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "p_idxs_3", "role": "default" }} , 
 	{ "name": "data_out_0", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "data_out_0", "role": "default" }} , 
 	{ "name": "data_out_0_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "data_out_0", "role": "ap_vld" }} , 
 	{ "name": "data_out_1", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "data_out_1", "role": "default" }} , 
 	{ "name": "data_out_1_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "data_out_1", "role": "ap_vld" }} , 
 	{ "name": "data_out_2", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "data_out_2", "role": "default" }} , 
 	{ "name": "data_out_2_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "data_out_2", "role": "ap_vld" }} , 
 	{ "name": "data_out_3", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "data_out_3", "role": "default" }} , 
 	{ "name": "data_out_3_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "data_out_3", "role": "ap_vld" }} , 
 	{ "name": "orbit_out_0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "orbit_out_0", "role": "default" }} , 
 	{ "name": "orbit_out_0_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "orbit_out_0", "role": "ap_vld" }} , 
 	{ "name": "orbit_out_1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "orbit_out_1", "role": "default" }} , 
 	{ "name": "orbit_out_1_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "orbit_out_1", "role": "ap_vld" }} , 
 	{ "name": "orbit_out_2", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "orbit_out_2", "role": "default" }} , 
 	{ "name": "orbit_out_2_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "orbit_out_2", "role": "ap_vld" }} , 
 	{ "name": "orbit_out_3", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "orbit_out_3", "role": "default" }} , 
 	{ "name": "orbit_out_3_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "orbit_out_3", "role": "ap_vld" }} , 
 	{ "name": "start_out_0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "start_out_0", "role": "default" }} , 
 	{ "name": "start_out_0_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "start_out_0", "role": "ap_vld" }} , 
 	{ "name": "start_out_1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "start_out_1", "role": "default" }} , 
 	{ "name": "start_out_1_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "start_out_1", "role": "ap_vld" }} , 
 	{ "name": "start_out_2", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "start_out_2", "role": "default" }} , 
 	{ "name": "start_out_2_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "start_out_2", "role": "ap_vld" }} , 
 	{ "name": "start_out_3", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "start_out_3", "role": "default" }} , 
 	{ "name": "start_out_3_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "start_out_3", "role": "ap_vld" }} , 
 	{ "name": "end_out_0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "end_out_0", "role": "default" }} , 
 	{ "name": "end_out_0_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "end_out_0", "role": "ap_vld" }} , 
 	{ "name": "end_out_1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "end_out_1", "role": "default" }} , 
 	{ "name": "end_out_1_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "end_out_1", "role": "ap_vld" }} , 
 	{ "name": "end_out_2", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "end_out_2", "role": "default" }} , 
 	{ "name": "end_out_2_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "end_out_2", "role": "ap_vld" }} , 
 	{ "name": "end_out_3", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "end_out_3", "role": "default" }} , 
 	{ "name": "end_out_3_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "end_out_3", "role": "ap_vld" }} , 
 	{ "name": "valid_out_0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "valid_out_0", "role": "default" }} , 
 	{ "name": "valid_out_0_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "valid_out_0", "role": "ap_vld" }} , 
 	{ "name": "valid_out_1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "valid_out_1", "role": "default" }} , 
 	{ "name": "valid_out_1_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "valid_out_1", "role": "ap_vld" }} , 
 	{ "name": "valid_out_2", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "valid_out_2", "role": "default" }} , 
 	{ "name": "valid_out_2_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "valid_out_2", "role": "ap_vld" }} , 
 	{ "name": "valid_out_3", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "valid_out_3", "role": "default" }} , 
 	{ "name": "valid_out_3_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "valid_out_3", "role": "ap_vld" }} , 
 	{ "name": "CLOCK_RATIO_MINUS_ONE", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "CLOCK_RATIO_MINUS_ONE", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "7", "12", "17", "22", "23"],
		"CDFG" : "gen4",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "Aligned", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "11", "EstimateLatencyMin" : "11", "EstimateLatencyMax" : "11",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "valid", "Type" : "None", "Direction" : "I"},
			{"Name" : "set", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_idxs_0", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_idxs_1", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_idxs_2", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_idxs_3", "Type" : "None", "Direction" : "I"},
			{"Name" : "data_out_0", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "data_out_1", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "data_out_2", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "data_out_3", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "orbit_out_0", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "orbit_out_1", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "orbit_out_2", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "orbit_out_3", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "start_out_0", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "start_out_1", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "start_out_2", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "start_out_3", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "end_out_0", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "end_out_1", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "end_out_2", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "end_out_3", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "valid_out_0", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "valid_out_1", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "valid_out_2", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "valid_out_3", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "CLOCK_RATIO_MINUS_ONE", "Type" : "None", "Direction" : "I"},
			{"Name" : "npuppi_V", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "irow_V", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "running", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "orbit", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "NLUT_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "nremaining_V", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "wptr", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "ptLUT_V", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "7", "SubInstance" : "grp_gen_puppi_fu_792", "Port" : "ptLUT_V"},
					{"ID" : "12", "SubInstance" : "grp_gen_puppi_fu_799", "Port" : "ptLUT_V"},
					{"ID" : "17", "SubInstance" : "grp_gen_puppi_fu_806", "Port" : "ptLUT_V"},
					{"ID" : "2", "SubInstance" : "grp_gen_puppi_fu_785", "Port" : "ptLUT_V"}]},
			{"Name" : "rptr", "Type" : "OVld", "Direction" : "IO"}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.NLUT_V_U", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_785", "Parent" : "0", "Child" : ["3", "4", "5", "6"],
		"CDFG" : "gen_puppi",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "Aligned", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "4", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "1",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "rnd", "Type" : "None", "Direction" : "I"},
			{"Name" : "ptLUT_V", "Type" : "Memory", "Direction" : "I"}]},
	{"ID" : "3", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_785.ptLUT_V_U", "Parent" : "2"},
	{"ID" : "4", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_785.mul_mul_12ns_11ns_23_4_1_U1", "Parent" : "2"},
	{"ID" : "5", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_785.mul_mul_10ns_10ns_20_4_1_U2", "Parent" : "2"},
	{"ID" : "6", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_785.mul_mul_11ns_11ns_22_4_1_U3", "Parent" : "2"},
	{"ID" : "7", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_792", "Parent" : "0", "Child" : ["8", "9", "10", "11"],
		"CDFG" : "gen_puppi",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "Aligned", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "4", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "1",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "rnd", "Type" : "None", "Direction" : "I"},
			{"Name" : "ptLUT_V", "Type" : "Memory", "Direction" : "I"}]},
	{"ID" : "8", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_792.ptLUT_V_U", "Parent" : "7"},
	{"ID" : "9", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_792.mul_mul_12ns_11ns_23_4_1_U1", "Parent" : "7"},
	{"ID" : "10", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_792.mul_mul_10ns_10ns_20_4_1_U2", "Parent" : "7"},
	{"ID" : "11", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_792.mul_mul_11ns_11ns_22_4_1_U3", "Parent" : "7"},
	{"ID" : "12", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_799", "Parent" : "0", "Child" : ["13", "14", "15", "16"],
		"CDFG" : "gen_puppi",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "Aligned", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "4", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "1",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "rnd", "Type" : "None", "Direction" : "I"},
			{"Name" : "ptLUT_V", "Type" : "Memory", "Direction" : "I"}]},
	{"ID" : "13", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_799.ptLUT_V_U", "Parent" : "12"},
	{"ID" : "14", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_799.mul_mul_12ns_11ns_23_4_1_U1", "Parent" : "12"},
	{"ID" : "15", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_799.mul_mul_10ns_10ns_20_4_1_U2", "Parent" : "12"},
	{"ID" : "16", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_799.mul_mul_11ns_11ns_22_4_1_U3", "Parent" : "12"},
	{"ID" : "17", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_806", "Parent" : "0", "Child" : ["18", "19", "20", "21"],
		"CDFG" : "gen_puppi",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "Aligned", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "4", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "1",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "rnd", "Type" : "None", "Direction" : "I"},
			{"Name" : "ptLUT_V", "Type" : "Memory", "Direction" : "I"}]},
	{"ID" : "18", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_806.ptLUT_V_U", "Parent" : "17"},
	{"ID" : "19", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_806.mul_mul_12ns_11ns_23_4_1_U1", "Parent" : "17"},
	{"ID" : "20", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_806.mul_mul_10ns_10ns_20_4_1_U2", "Parent" : "17"},
	{"ID" : "21", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_gen_puppi_fu_806.mul_mul_11ns_11ns_22_4_1_U3", "Parent" : "17"},
	{"ID" : "22", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_mul_11ns_7ns_18_4_1_U9", "Parent" : "0"},
	{"ID" : "23", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_mul_11ns_7ns_18_4_1_U10", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	gen4 {
		valid {Type I LastRead 0 FirstWrite -1}
		set {Type I LastRead 0 FirstWrite -1}
		p_idxs_0 {Type I LastRead 0 FirstWrite -1}
		p_idxs_1 {Type I LastRead 0 FirstWrite -1}
		p_idxs_2 {Type I LastRead 0 FirstWrite -1}
		p_idxs_3 {Type I LastRead 0 FirstWrite -1}
		data_out_0 {Type O LastRead -1 FirstWrite 11}
		data_out_1 {Type O LastRead -1 FirstWrite 11}
		data_out_2 {Type O LastRead -1 FirstWrite 11}
		data_out_3 {Type O LastRead -1 FirstWrite 11}
		orbit_out_0 {Type O LastRead -1 FirstWrite 11}
		orbit_out_1 {Type O LastRead -1 FirstWrite 11}
		orbit_out_2 {Type O LastRead -1 FirstWrite 11}
		orbit_out_3 {Type O LastRead -1 FirstWrite 11}
		start_out_0 {Type O LastRead -1 FirstWrite 11}
		start_out_1 {Type O LastRead -1 FirstWrite 11}
		start_out_2 {Type O LastRead -1 FirstWrite 11}
		start_out_3 {Type O LastRead -1 FirstWrite 11}
		end_out_0 {Type O LastRead -1 FirstWrite 11}
		end_out_1 {Type O LastRead -1 FirstWrite 11}
		end_out_2 {Type O LastRead -1 FirstWrite 11}
		end_out_3 {Type O LastRead -1 FirstWrite 11}
		valid_out_0 {Type O LastRead -1 FirstWrite 11}
		valid_out_1 {Type O LastRead -1 FirstWrite 11}
		valid_out_2 {Type O LastRead -1 FirstWrite 11}
		valid_out_3 {Type O LastRead -1 FirstWrite 11}
		CLOCK_RATIO_MINUS_ONE {Type I LastRead -1 FirstWrite -1}
		npuppi_V {Type IO LastRead -1 FirstWrite -1}
		irow_V {Type IO LastRead -1 FirstWrite -1}
		running {Type IO LastRead -1 FirstWrite -1}
		orbit {Type IO LastRead -1 FirstWrite -1}
		NLUT_V {Type I LastRead -1 FirstWrite -1}
		nremaining_V {Type IO LastRead -1 FirstWrite -1}
		wptr {Type IO LastRead -1 FirstWrite -1}
		ptLUT_V {Type I LastRead -1 FirstWrite -1}
		rptr {Type IO LastRead -1 FirstWrite -1}}
	gen_puppi {
		rnd {Type I LastRead 0 FirstWrite -1}
		ptLUT_V {Type I LastRead -1 FirstWrite -1}}
	gen_puppi {
		rnd {Type I LastRead 0 FirstWrite -1}
		ptLUT_V {Type I LastRead -1 FirstWrite -1}}
	gen_puppi {
		rnd {Type I LastRead 0 FirstWrite -1}
		ptLUT_V {Type I LastRead -1 FirstWrite -1}}
	gen_puppi {
		rnd {Type I LastRead 0 FirstWrite -1}
		ptLUT_V {Type I LastRead -1 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "11", "Max" : "11"}
	, {"Name" : "Interval", "Min" : "1", "Max" : "1"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	valid { ap_none {  { valid in_data 0 1 } } }
	set { ap_none {  { set in_data 0 1 } } }
	p_idxs_0 { ap_none {  { p_idxs_0 in_data 0 64 } } }
	p_idxs_1 { ap_none {  { p_idxs_1 in_data 0 64 } } }
	p_idxs_2 { ap_none {  { p_idxs_2 in_data 0 64 } } }
	p_idxs_3 { ap_none {  { p_idxs_3 in_data 0 64 } } }
	data_out_0 { ap_vld {  { data_out_0 out_data 1 64 }  { data_out_0_ap_vld out_vld 1 1 } } }
	data_out_1 { ap_vld {  { data_out_1 out_data 1 64 }  { data_out_1_ap_vld out_vld 1 1 } } }
	data_out_2 { ap_vld {  { data_out_2 out_data 1 64 }  { data_out_2_ap_vld out_vld 1 1 } } }
	data_out_3 { ap_vld {  { data_out_3 out_data 1 64 }  { data_out_3_ap_vld out_vld 1 1 } } }
	orbit_out_0 { ap_vld {  { orbit_out_0 out_data 1 1 }  { orbit_out_0_ap_vld out_vld 1 1 } } }
	orbit_out_1 { ap_vld {  { orbit_out_1 out_data 1 1 }  { orbit_out_1_ap_vld out_vld 1 1 } } }
	orbit_out_2 { ap_vld {  { orbit_out_2 out_data 1 1 }  { orbit_out_2_ap_vld out_vld 1 1 } } }
	orbit_out_3 { ap_vld {  { orbit_out_3 out_data 1 1 }  { orbit_out_3_ap_vld out_vld 1 1 } } }
	start_out_0 { ap_vld {  { start_out_0 out_data 1 1 }  { start_out_0_ap_vld out_vld 1 1 } } }
	start_out_1 { ap_vld {  { start_out_1 out_data 1 1 }  { start_out_1_ap_vld out_vld 1 1 } } }
	start_out_2 { ap_vld {  { start_out_2 out_data 1 1 }  { start_out_2_ap_vld out_vld 1 1 } } }
	start_out_3 { ap_vld {  { start_out_3 out_data 1 1 }  { start_out_3_ap_vld out_vld 1 1 } } }
	end_out_0 { ap_vld {  { end_out_0 out_data 1 1 }  { end_out_0_ap_vld out_vld 1 1 } } }
	end_out_1 { ap_vld {  { end_out_1 out_data 1 1 }  { end_out_1_ap_vld out_vld 1 1 } } }
	end_out_2 { ap_vld {  { end_out_2 out_data 1 1 }  { end_out_2_ap_vld out_vld 1 1 } } }
	end_out_3 { ap_vld {  { end_out_3 out_data 1 1 }  { end_out_3_ap_vld out_vld 1 1 } } }
	valid_out_0 { ap_vld {  { valid_out_0 out_data 1 1 }  { valid_out_0_ap_vld out_vld 1 1 } } }
	valid_out_1 { ap_vld {  { valid_out_1 out_data 1 1 }  { valid_out_1_ap_vld out_vld 1 1 } } }
	valid_out_2 { ap_vld {  { valid_out_2 out_data 1 1 }  { valid_out_2_ap_vld out_vld 1 1 } } }
	valid_out_3 { ap_vld {  { valid_out_3 out_data 1 1 }  { valid_out_3_ap_vld out_vld 1 1 } } }
	CLOCK_RATIO_MINUS_ONE { ap_none {  { CLOCK_RATIO_MINUS_ONE in_data 0 4 } } }
}

set busDeadlockParameterList { 
}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
