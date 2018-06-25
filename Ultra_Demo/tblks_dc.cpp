#include "tester.h"
// ******************************
// *****  Test Blocks file  *****
// ******************************

//TEST_BLOCK(tb_continuity)
//{
//	TB.header();
//	power_down();
//	partime(10 MS);
//	back_voltage(0 V);
//	back_voltage_enable(true);
//	vclamp(7 V, -2 V);
//	ipar_force(-100 UA);
//	vpar_high(-200 MV);
//	vpar_low(-1 V);
//	partest(pass_nivl, pl_all_pins);
//	TB.Pdatalog(pl_all_pins, ForceIMeasureV);
//	back_voltage_enable(false);
//	return TB.end();
//}
//
//TEST_BLOCK(tb_continuity_dps)
//{
//	TB.header();
//	power_down();
//	partime(10 MS);
//	back_voltage_enable(false);
//	vclamp(7 V, -2 V);
//	ipar_force(100 UA);
//	vpar_high(1 V);
//	vpar_low(100 MV);
//	partest(pass_nivl, pl_dps);
//	TB.Pdatalog(pl_dps, ForceIMeasureV);
//	partime(0 MS);
//	SoftwareOnlyActiveDutIterator DLoop;
//	while (DLoop.More(TRUE))
//	{
//		DutNum dut = active_dut_get();
//		if (dut<t_dut5)
//			result_set(dut, PASS);
//	}
//	return TB.end();
//}
//
//TEST_BLOCK(tb_continuity_hv)
//{
//	TB.header();
//	power_down();
//	partime(10 MS);
//	back_voltage_enable(false);
//	vclamp(7 V, -1 V);
//	ipar_force(100 UA);
//	vpar_high(1 V);
//	vpar_low(100 MV);
//	partest(pass_nivl, pl_hv);
//	TB.Pdatalog(pl_hv, ForceIMeasureV);
//	partime(0 MS);
//
//	return TB.end();
//}
//
//TEST_BLOCK(tb_continuity_dpo)
//{
//	TB.header();
//	power_down();
//	partime(10 MS);
//	dpo_pmu_vclamp_set(7 V, -2 V);
//	dpo_ipar_force_set(100 UA);
//	dpo_vpar_high_set(1 V);
//	dpo_vpar_low_set(200 MV);
//	dpo_partest(pass_nivl, pl_dpo);
//	TB.Pdatalog(pl_dpo, ForceIMeasureV);
//	partime(0 MS);
//
//	return TB.end();
//}
//
//TEST_BLOCK(tb_continuity_dpohv)
//{
//	TB.header();
//	power_down();
//	partime(10 MS);
//	dpo_hv_vclamp_set(10 V, -1 V, pl_dpohv);
//	dpo_hv_ipar_force_set(100 UA, pl_dpohv);
//	dpo_hv_vpar_high_set(1 V, pl_dpohv);
//	dpo_hv_vpar_low_set(200 MV, pl_dpohv);
//	dpo_hv_partest(pass_nivl, pl_dpohv);
//	TB.Pdatalog(pl_dpohv, ForceIMeasureV);
//	partime(0 MS);
//	dpo_hv_ipar_force_set(0 UA, pl_dpohv);
//	power_down();
//	return TB.end();
//}
//
//TEST_BLOCK(tb_leakage)
//{
//	//	IntArray  r1,r2;
//	TB.header();
//	vs_loose();
//	vpar_force(1.8 V);
//	back_voltage(0 V);
//	back_voltage_enable(true);
//	ipar_high(1 UA);
//	ipar_low(-1 UA);
//	partime(0 S);
//	pmu_comp_cap(0);
//	partest(pass_nicl, pl_all_pins);
//	//	pdatalog(pl_all_pins);
//	TB.Pdatalog(pl_all_pins, ForceVMeasureI);
//
//	vpar_force(0 V);
//	back_voltage(1.8 V);
//	back_voltage_enable(true);
//	partest(pass_nicl, pl_all_pins);
//	//	pdatalog(pl_all_pins);
//	TB.Pdatalog(pl_all_pins, ForceVMeasureI);
//	back_voltage_enable(false);
//	return TB.end();
//}
//
//TEST_BLOCK(tb_IDD2S_dps)
//{
//	//	IntArray  r1,r2;
//	TB.header();
//	vs_loose();
//	vpar_force(5 V, pl_vbat);
//	ipar_high(2 UA, pl_vbat);
//	ipar_low(0 UA, pl_vbat);
//
//	vpar_force(1.8 V, pl_vdd_buck);
//	ipar_high(3 UA, pl_vdd_buck);
//	ipar_low(0 UA, pl_vdd_buck);
//	partime(10 MS);
//	dps_comp_cap(0);
//	//iacc_count_set(10);
//	partest(pass_nicl, pl_dps);
//	partime(0 MS);
//	//	pdatalog(pl_vcc);
//	TB.Pdatalog(pl_dps, ForceVMeasureI);
//
//	return TB.end();
//}
//
//TEST_BLOCK(tb_IDD2S_dpo)
//{
//	//	IntArray  r1,r2;
//	TB.header();
//	vs_loose();
//	dpo_vpar_force_set(1.8 V);
//	dpo_ipar_high_set(3 UA);
//	dpo_ipar_low_set(0 UA);
//	partime(10 MS);
//	//iacc_count_set(10);
//	dpo_comp_cap_set(1);
//	dpo_partest(pass_nicl, pl_dpo);
//	partime(0 MS);
//	//	pdatalog(pl_vcc);
//	TB.Pdatalog(pl_dpo, ForceVMeasureI);
//
//	return TB.end();
//}