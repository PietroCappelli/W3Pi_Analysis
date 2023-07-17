; ModuleID = '/home/pcappell/hls/gen_project/proj_gen4/solution/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"struct.ap_uint<64>" = type { %"struct.ap_int_base<64, false>" }
%"struct.ap_int_base<64, false>" = type { %"struct.ssdm_int<64, false>" }
%"struct.ssdm_int<64, false>" = type { i64 }
%"struct.ap_uint<4>" = type { %"struct.ap_int_base<4, false>" }
%"struct.ap_int_base<4, false>" = type { %"struct.ssdm_int<4, false>" }
%"struct.ssdm_int<4, false>" = type { i4 }

; Function Attrs: noinline
define void @apatb_gen4_ir(i1 %valid, i1 %set, %"struct.ap_uint<64>"* %p_idxs, %"struct.ap_uint<64>"* %data_out, i1* %orbit_out, i1* %start_out, i1* %end_out, i1* %valid_out, %"struct.ap_uint<4>"* nocapture readonly %CLOCK_RATIO_MINUS_ONE) local_unnamed_addr #0 {
entry:
  %p_idxs_copy_0 = alloca i64, align 512
  %p_idxs_copy_1 = alloca i64, align 512
  %p_idxs_copy_2 = alloca i64, align 512
  %p_idxs_copy_3 = alloca i64, align 512
  %data_out_copy_0 = alloca i64, align 512
  %data_out_copy_1 = alloca i64, align 512
  %data_out_copy_2 = alloca i64, align 512
  %data_out_copy_3 = alloca i64, align 512
  %orbit_out_copy_0 = alloca i1, align 512
  %orbit_out_copy_1 = alloca i1, align 512
  %orbit_out_copy_2 = alloca i1, align 512
  %orbit_out_copy_3 = alloca i1, align 512
  %start_out_copy_0 = alloca i1, align 512
  %start_out_copy_1 = alloca i1, align 512
  %start_out_copy_2 = alloca i1, align 512
  %start_out_copy_3 = alloca i1, align 512
  %end_out_copy_0 = alloca i1, align 512
  %end_out_copy_1 = alloca i1, align 512
  %end_out_copy_2 = alloca i1, align 512
  %end_out_copy_3 = alloca i1, align 512
  %valid_out_copy_0 = alloca i1, align 512
  %valid_out_copy_1 = alloca i1, align 512
  %valid_out_copy_2 = alloca i1, align 512
  %valid_out_copy_3 = alloca i1, align 512
  %0 = bitcast %"struct.ap_uint<64>"* %p_idxs to [4 x %"struct.ap_uint<64>"]*
  %1 = bitcast %"struct.ap_uint<64>"* %data_out to [4 x %"struct.ap_uint<64>"]*
  %2 = bitcast i1* %orbit_out to [4 x i1]*
  %3 = bitcast i1* %start_out to [4 x i1]*
  %4 = bitcast i1* %end_out to [4 x i1]*
  %5 = bitcast i1* %valid_out to [4 x i1]*
  call void @copy_in([4 x %"struct.ap_uint<64>"]* %0, i64* nonnull align 512 %p_idxs_copy_0, i64* nonnull align 512 %p_idxs_copy_1, i64* nonnull align 512 %p_idxs_copy_2, i64* nonnull align 512 %p_idxs_copy_3, [4 x %"struct.ap_uint<64>"]* %1, i64* nonnull align 512 %data_out_copy_0, i64* nonnull align 512 %data_out_copy_1, i64* nonnull align 512 %data_out_copy_2, i64* nonnull align 512 %data_out_copy_3, [4 x i1]* %2, i1* nonnull align 512 %orbit_out_copy_0, i1* nonnull align 512 %orbit_out_copy_1, i1* nonnull align 512 %orbit_out_copy_2, i1* nonnull align 512 %orbit_out_copy_3, [4 x i1]* %3, i1* nonnull align 512 %start_out_copy_0, i1* nonnull align 512 %start_out_copy_1, i1* nonnull align 512 %start_out_copy_2, i1* nonnull align 512 %start_out_copy_3, [4 x i1]* %4, i1* nonnull align 512 %end_out_copy_0, i1* nonnull align 512 %end_out_copy_1, i1* nonnull align 512 %end_out_copy_2, i1* nonnull align 512 %end_out_copy_3, [4 x i1]* %5, i1* nonnull align 512 %valid_out_copy_0, i1* nonnull align 512 %valid_out_copy_1, i1* nonnull align 512 %valid_out_copy_2, i1* nonnull align 512 %valid_out_copy_3)
  call void @apatb_gen4_hw(i1 %valid, i1 %set, i64* %p_idxs_copy_0, i64* %p_idxs_copy_1, i64* %p_idxs_copy_2, i64* %p_idxs_copy_3, i64* %data_out_copy_0, i64* %data_out_copy_1, i64* %data_out_copy_2, i64* %data_out_copy_3, i1* %orbit_out_copy_0, i1* %orbit_out_copy_1, i1* %orbit_out_copy_2, i1* %orbit_out_copy_3, i1* %start_out_copy_0, i1* %start_out_copy_1, i1* %start_out_copy_2, i1* %start_out_copy_3, i1* %end_out_copy_0, i1* %end_out_copy_1, i1* %end_out_copy_2, i1* %end_out_copy_3, i1* %valid_out_copy_0, i1* %valid_out_copy_1, i1* %valid_out_copy_2, i1* %valid_out_copy_3, %"struct.ap_uint<4>"* %CLOCK_RATIO_MINUS_ONE)
  call void @copy_out([4 x %"struct.ap_uint<64>"]* %0, i64* nonnull align 512 %p_idxs_copy_0, i64* nonnull align 512 %p_idxs_copy_1, i64* nonnull align 512 %p_idxs_copy_2, i64* nonnull align 512 %p_idxs_copy_3, [4 x %"struct.ap_uint<64>"]* %1, i64* nonnull align 512 %data_out_copy_0, i64* nonnull align 512 %data_out_copy_1, i64* nonnull align 512 %data_out_copy_2, i64* nonnull align 512 %data_out_copy_3, [4 x i1]* %2, i1* nonnull align 512 %orbit_out_copy_0, i1* nonnull align 512 %orbit_out_copy_1, i1* nonnull align 512 %orbit_out_copy_2, i1* nonnull align 512 %orbit_out_copy_3, [4 x i1]* %3, i1* nonnull align 512 %start_out_copy_0, i1* nonnull align 512 %start_out_copy_1, i1* nonnull align 512 %start_out_copy_2, i1* nonnull align 512 %start_out_copy_3, [4 x i1]* %4, i1* nonnull align 512 %end_out_copy_0, i1* nonnull align 512 %end_out_copy_1, i1* nonnull align 512 %end_out_copy_2, i1* nonnull align 512 %end_out_copy_3, [4 x i1]* %5, i1* nonnull align 512 %valid_out_copy_0, i1* nonnull align 512 %valid_out_copy_1, i1* nonnull align 512 %valid_out_copy_2, i1* nonnull align 512 %valid_out_copy_3)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal void @onebyonecpy_hls.p0a4i1.80.81(i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="0" %_0, i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="0" %_1, i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="0" %_2, i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="0" %_3, [4 x i1]* noalias readonly "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1") #1 {
entry:
  %1 = icmp eq i1* %_0, null
  %2 = icmp eq [4 x i1]* %0, null
  %3 = or i1 %1, %2
  br i1 %3, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %dst.addr.exit, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %dst.addr.exit ]
  %src.addr = getelementptr [4 x i1], [4 x i1]* %0, i64 0, i64 %for.loop.idx1
  %4 = bitcast i1* %src.addr to i8*
  %5 = load i8, i8* %4
  %6 = trunc i8 %5 to i1
  %7 = trunc i64 %for.loop.idx1 to i2
  switch i2 %7, label %dst.addr.case.3 [
    i2 0, label %dst.addr.case.0
    i2 1, label %dst.addr.case.1
    i2 -2, label %dst.addr.case.2
  ]

dst.addr.case.0:                                  ; preds = %for.loop
  store i1 %6, i1* %_0, align 512
  br label %dst.addr.exit

dst.addr.case.1:                                  ; preds = %for.loop
  store i1 %6, i1* %_1, align 512
  br label %dst.addr.exit

dst.addr.case.2:                                  ; preds = %for.loop
  store i1 %6, i1* %_2, align 512
  br label %dst.addr.exit

dst.addr.case.3:                                  ; preds = %for.loop
  store i1 %6, i1* %_3, align 512
  br label %dst.addr.exit

dst.addr.exit:                                    ; preds = %dst.addr.case.3, %dst.addr.case.2, %dst.addr.case.1, %dst.addr.case.0
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 4
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %dst.addr.exit, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal void @copy_in([4 x %"struct.ap_uint<64>"]* readonly "orig.arg.no"="0", i64* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1" %_0, i64* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1" %_1, i64* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1" %_2, i64* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1" %_3, [4 x %"struct.ap_uint<64>"]* readonly "orig.arg.no"="2", i64* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="3" %_01, i64* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="3" %_12, i64* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="3" %_23, i64* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="3" %_34, [4 x i1]* readonly "orig.arg.no"="4", i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="5" %_05, i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="5" %_16, i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="5" %_27, i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="5" %_38, [4 x i1]* readonly "orig.arg.no"="6", i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="7" %_09, i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="7" %_110, i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="7" %_211, i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="7" %_312, [4 x i1]* readonly "orig.arg.no"="8", i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="9" %_013, i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="9" %_114, i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="9" %_215, i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="9" %_316, [4 x i1]* readonly "orig.arg.no"="10", i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="11" %_017, i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="11" %_118, i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="11" %_219, i1* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="11" %_320) #2 {
entry:
  call void @"onebyonecpy_hls.p0a4struct.ap_uint<64>.78.79"(i64* align 512 %_0, i64* align 512 %_1, i64* align 512 %_2, i64* align 512 %_3, [4 x %"struct.ap_uint<64>"]* %0)
  call void @"onebyonecpy_hls.p0a4struct.ap_uint<64>.78.79"(i64* align 512 %_01, i64* align 512 %_12, i64* align 512 %_23, i64* align 512 %_34, [4 x %"struct.ap_uint<64>"]* %1)
  call void @onebyonecpy_hls.p0a4i1.80.81(i1* align 512 %_05, i1* align 512 %_16, i1* align 512 %_27, i1* align 512 %_38, [4 x i1]* %2)
  call void @onebyonecpy_hls.p0a4i1.80.81(i1* align 512 %_09, i1* align 512 %_110, i1* align 512 %_211, i1* align 512 %_312, [4 x i1]* %3)
  call void @onebyonecpy_hls.p0a4i1.80.81(i1* align 512 %_013, i1* align 512 %_114, i1* align 512 %_215, i1* align 512 %_316, [4 x i1]* %4)
  call void @onebyonecpy_hls.p0a4i1.80.81(i1* align 512 %_017, i1* align 512 %_118, i1* align 512 %_219, i1* align 512 %_320, [4 x i1]* %5)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal void @onebyonecpy_hls.p0a4i1.88.89([4 x i1]* noalias "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="0", i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1" %_0, i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1" %_1, i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1" %_2, i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1" %_3) #1 {
entry:
  %1 = icmp eq [4 x i1]* %0, null
  %2 = icmp eq i1* %_0, null
  %3 = or i1 %1, %2
  br i1 %3, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %src.addr.exit, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %src.addr.exit ]
  %dst.addr = getelementptr [4 x i1], [4 x i1]* %0, i64 0, i64 %for.loop.idx1
  %4 = trunc i64 %for.loop.idx1 to i2
  switch i2 %4, label %src.addr.case.3 [
    i2 0, label %src.addr.case.0
    i2 1, label %src.addr.case.1
    i2 -2, label %src.addr.case.2
  ]

src.addr.case.0:                                  ; preds = %for.loop
  %5 = bitcast i1* %_0 to i8*
  %6 = load i8, i8* %5
  %7 = trunc i8 %6 to i1
  br label %src.addr.exit

src.addr.case.1:                                  ; preds = %for.loop
  %8 = bitcast i1* %_1 to i8*
  %9 = load i8, i8* %8
  %10 = trunc i8 %9 to i1
  br label %src.addr.exit

src.addr.case.2:                                  ; preds = %for.loop
  %11 = bitcast i1* %_2 to i8*
  %12 = load i8, i8* %11
  %13 = trunc i8 %12 to i1
  br label %src.addr.exit

src.addr.case.3:                                  ; preds = %for.loop
  %14 = bitcast i1* %_3 to i8*
  %15 = load i8, i8* %14
  %16 = trunc i8 %15 to i1
  br label %src.addr.exit

src.addr.exit:                                    ; preds = %src.addr.case.3, %src.addr.case.2, %src.addr.case.1, %src.addr.case.0
  %17 = phi i1 [ %7, %src.addr.case.0 ], [ %10, %src.addr.case.1 ], [ %13, %src.addr.case.2 ], [ %16, %src.addr.case.3 ]
  store i1 %17, i1* %dst.addr, align 1
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 4
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %src.addr.exit, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal void @copy_out([4 x %"struct.ap_uint<64>"]* "orig.arg.no"="0", i64* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1" %_0, i64* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1" %_1, i64* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1" %_2, i64* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1" %_3, [4 x %"struct.ap_uint<64>"]* "orig.arg.no"="2", i64* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="3" %_01, i64* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="3" %_12, i64* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="3" %_23, i64* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="3" %_34, [4 x i1]* "orig.arg.no"="4", i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="5" %_05, i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="5" %_16, i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="5" %_27, i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="5" %_38, [4 x i1]* "orig.arg.no"="6", i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="7" %_09, i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="7" %_110, i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="7" %_211, i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="7" %_312, [4 x i1]* "orig.arg.no"="8", i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="9" %_013, i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="9" %_114, i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="9" %_215, i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="9" %_316, [4 x i1]* "orig.arg.no"="10", i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="11" %_017, i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="11" %_118, i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="11" %_219, i1* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="11" %_320) #3 {
entry:
  call void @"onebyonecpy_hls.p0a4struct.ap_uint<64>.86.87"([4 x %"struct.ap_uint<64>"]* %0, i64* align 512 %_0, i64* align 512 %_1, i64* align 512 %_2, i64* align 512 %_3)
  call void @"onebyonecpy_hls.p0a4struct.ap_uint<64>.86.87"([4 x %"struct.ap_uint<64>"]* %1, i64* align 512 %_01, i64* align 512 %_12, i64* align 512 %_23, i64* align 512 %_34)
  call void @onebyonecpy_hls.p0a4i1.88.89([4 x i1]* %2, i1* align 512 %_05, i1* align 512 %_16, i1* align 512 %_27, i1* align 512 %_38)
  call void @onebyonecpy_hls.p0a4i1.88.89([4 x i1]* %3, i1* align 512 %_09, i1* align 512 %_110, i1* align 512 %_211, i1* align 512 %_312)
  call void @onebyonecpy_hls.p0a4i1.88.89([4 x i1]* %4, i1* align 512 %_013, i1* align 512 %_114, i1* align 512 %_215, i1* align 512 %_316)
  call void @onebyonecpy_hls.p0a4i1.88.89([4 x i1]* %5, i1* align 512 %_017, i1* align 512 %_118, i1* align 512 %_219, i1* align 512 %_320)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal void @"onebyonecpy_hls.p0a4struct.ap_uint<64>.78.79"(i64* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="0" %_0, i64* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="0" %_1, i64* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="0" %_2, i64* noalias align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="0" %_3, [4 x %"struct.ap_uint<64>"]* noalias readonly "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1") #1 {
entry:
  %1 = icmp eq i64* %_0, null
  %2 = icmp eq [4 x %"struct.ap_uint<64>"]* %0, null
  %3 = or i1 %1, %2
  br i1 %3, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %dst.addr.0.0.06.exit, %copy
  %for.loop.idx7 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %dst.addr.0.0.06.exit ]
  %src.addr.0.0.05 = getelementptr [4 x %"struct.ap_uint<64>"], [4 x %"struct.ap_uint<64>"]* %0, i64 0, i64 %for.loop.idx7, i32 0, i32 0, i32 0
  %4 = load i64, i64* %src.addr.0.0.05, align 8
  %5 = trunc i64 %for.loop.idx7 to i2
  switch i2 %5, label %dst.addr.0.0.06.case.3 [
    i2 0, label %dst.addr.0.0.06.case.0
    i2 1, label %dst.addr.0.0.06.case.1
    i2 -2, label %dst.addr.0.0.06.case.2
  ]

dst.addr.0.0.06.case.0:                           ; preds = %for.loop
  store i64 %4, i64* %_0, align 512
  br label %dst.addr.0.0.06.exit

dst.addr.0.0.06.case.1:                           ; preds = %for.loop
  store i64 %4, i64* %_1, align 512
  br label %dst.addr.0.0.06.exit

dst.addr.0.0.06.case.2:                           ; preds = %for.loop
  store i64 %4, i64* %_2, align 512
  br label %dst.addr.0.0.06.exit

dst.addr.0.0.06.case.3:                           ; preds = %for.loop
  store i64 %4, i64* %_3, align 512
  br label %dst.addr.0.0.06.exit

dst.addr.0.0.06.exit:                             ; preds = %dst.addr.0.0.06.case.3, %dst.addr.0.0.06.case.2, %dst.addr.0.0.06.case.1, %dst.addr.0.0.06.case.0
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx7, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 4
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %dst.addr.0.0.06.exit, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal void @"onebyonecpy_hls.p0a4struct.ap_uint<64>.86.87"([4 x %"struct.ap_uint<64>"]* noalias "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="0", i64* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1" %_0, i64* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1" %_1, i64* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1" %_2, i64* noalias readonly align 512 "fpga.caller.interfaces"="layout_transformed" "orig.arg.no"="1" %_3) #1 {
entry:
  %1 = icmp eq [4 x %"struct.ap_uint<64>"]* %0, null
  %2 = icmp eq i64* %_0, null
  %3 = or i1 %1, %2
  br i1 %3, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %src.addr.0.0.05.exit, %copy
  %for.loop.idx7 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %src.addr.0.0.05.exit ]
  %dst.addr.0.0.06 = getelementptr [4 x %"struct.ap_uint<64>"], [4 x %"struct.ap_uint<64>"]* %0, i64 0, i64 %for.loop.idx7, i32 0, i32 0, i32 0
  %4 = trunc i64 %for.loop.idx7 to i2
  switch i2 %4, label %src.addr.0.0.05.case.3 [
    i2 0, label %src.addr.0.0.05.case.0
    i2 1, label %src.addr.0.0.05.case.1
    i2 -2, label %src.addr.0.0.05.case.2
  ]

src.addr.0.0.05.case.0:                           ; preds = %for.loop
  %5 = load i64, i64* %_0, align 512
  br label %src.addr.0.0.05.exit

src.addr.0.0.05.case.1:                           ; preds = %for.loop
  %6 = load i64, i64* %_1, align 512
  br label %src.addr.0.0.05.exit

src.addr.0.0.05.case.2:                           ; preds = %for.loop
  %7 = load i64, i64* %_2, align 512
  br label %src.addr.0.0.05.exit

src.addr.0.0.05.case.3:                           ; preds = %for.loop
  %8 = load i64, i64* %_3, align 512
  br label %src.addr.0.0.05.exit

src.addr.0.0.05.exit:                             ; preds = %src.addr.0.0.05.case.3, %src.addr.0.0.05.case.2, %src.addr.0.0.05.case.1, %src.addr.0.0.05.case.0
  %9 = phi i64 [ %5, %src.addr.0.0.05.case.0 ], [ %6, %src.addr.0.0.05.case.1 ], [ %7, %src.addr.0.0.05.case.2 ], [ %8, %src.addr.0.0.05.case.3 ]
  store i64 %9, i64* %dst.addr.0.0.06, align 8
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx7, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 4
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %src.addr.0.0.05.exit, %entry
  ret void
}

declare void @apatb_gen4_hw(i1, i1, i64*, i64*, i64*, i64*, i64*, i64*, i64*, i64*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, %"struct.ap_uint<4>"*)

define void @gen4_hw_stub_wrapper(i1, i1, i64*, i64*, i64*, i64*, i64*, i64*, i64*, i64*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, i1*, %"struct.ap_uint<4>"*) #4 {
entry:
  %27 = alloca [4 x %"struct.ap_uint<64>"]
  %28 = alloca [4 x %"struct.ap_uint<64>"]
  %29 = alloca [4 x i1]
  %30 = alloca [4 x i1]
  %31 = alloca [4 x i1]
  %32 = alloca [4 x i1]
  call void @copy_out([4 x %"struct.ap_uint<64>"]* %27, i64* %2, i64* %3, i64* %4, i64* %5, [4 x %"struct.ap_uint<64>"]* %28, i64* %6, i64* %7, i64* %8, i64* %9, [4 x i1]* %29, i1* %10, i1* %11, i1* %12, i1* %13, [4 x i1]* %30, i1* %14, i1* %15, i1* %16, i1* %17, [4 x i1]* %31, i1* %18, i1* %19, i1* %20, i1* %21, [4 x i1]* %32, i1* %22, i1* %23, i1* %24, i1* %25)
  %33 = bitcast [4 x %"struct.ap_uint<64>"]* %27 to %"struct.ap_uint<64>"*
  %34 = bitcast [4 x %"struct.ap_uint<64>"]* %28 to %"struct.ap_uint<64>"*
  %35 = bitcast [4 x i1]* %29 to i1*
  %36 = bitcast [4 x i1]* %30 to i1*
  %37 = bitcast [4 x i1]* %31 to i1*
  %38 = bitcast [4 x i1]* %32 to i1*
  call void @gen4_hw_stub(i1 %0, i1 %1, %"struct.ap_uint<64>"* %33, %"struct.ap_uint<64>"* %34, i1* %35, i1* %36, i1* %37, i1* %38, %"struct.ap_uint<4>"* %26)
  call void @copy_in([4 x %"struct.ap_uint<64>"]* %27, i64* %2, i64* %3, i64* %4, i64* %5, [4 x %"struct.ap_uint<64>"]* %28, i64* %6, i64* %7, i64* %8, i64* %9, [4 x i1]* %29, i1* %10, i1* %11, i1* %12, i1* %13, [4 x i1]* %30, i1* %14, i1* %15, i1* %16, i1* %17, [4 x i1]* %31, i1* %18, i1* %19, i1* %20, i1* %21, [4 x i1]* %32, i1* %22, i1* %23, i1* %24, i1* %25)
  ret void
}

declare void @gen4_hw_stub(i1, i1, %"struct.ap_uint<64>"*, %"struct.ap_uint<64>"*, i1*, i1*, i1*, i1*, %"struct.ap_uint<4>"*)

attributes #0 = { noinline "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline norecurse "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #2 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyin" }
attributes #3 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyout" }
attributes #4 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
