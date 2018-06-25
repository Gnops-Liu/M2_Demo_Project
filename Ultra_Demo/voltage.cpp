#include "tester.h"

// voltage sets

//void power_down()
//{
//	dps(0 V, pl_vbat);
//	dpo_voltage_set(0 V, pl_vdd_sby);
//	dpo_voltage_set(0 V, pl_vdd_core);
//	dpo_voltage_set(0 V, pl_vdd_buck);
//	vil(0 V, pl_all_iopins);
//	vih(0 V, pl_all_iopins);
//	vol(0 V, pl_all_iopins);
//	voh(0 V, pl_all_iopins);
//	vz(0 V, pl_all_iopins);
//	iol(0 A, pl_all_iopins);
//	ioh(0 A, pl_all_iopins);
//	partime(0 MS);
//}
//
//void vs_loose() {
//	dps(5 V, pl_vbat);
//	dpo_voltage_set(1.8 V, pl_vdd_sby);
//	dpo_voltage_set(1.2 V, pl_vdd_core);
//	dpo_voltage_set(1.8 V, pl_vdd_buck);
//	vil(0 V);
//	vih(1.8 V);
//	vol(0.9 V);
//	voh(0.9 V);
//	vz(0.9 V, pl_all_iopins);
//	iol(10 MA, pl_all_iopins);
//	ioh(10 MA, pl_all_iopins);
//	partime(0 MS);
//	measure(TRUE);
//}
//void vs_Hv()
//{
//	dps(5.0 V, pl_vbat);
//	dpo_voltage_set(1.98 V, pl_vdd_sby);
//	dpo_voltage_set(1.32 V, pl_vdd_core);
//	dpo_voltage_set(1.98 V, pl_vdd_buck);
//	vil(0 V);
//	vih(1.8 V);
//	vol(0.9 V);
//	voh(0.9 V);
//	vz(0.9 V, pl_all_iopins);
//	iol(10 MA, pl_all_iopins);
//	ioh(10 MA, pl_all_iopins);
//	measure(TRUE);
//}
//
//void vs_Lv() {
//	dps(5 V, pl_vbat);
//	dpo_voltage_set(1.62 V, pl_vdd_sby);
//	dpo_voltage_set(1.08 V, pl_vdd_core);
//	dpo_voltage_set(1.62 V, pl_vdd_buck);
//	vil(0 V);
//	vih(1.62 V);
//	vol(0.9 V);
//	voh(0.9 V);
//	vz(0.9 V, pl_all_iopins);
//	iol(10 MA, pl_all_iopins);
//	ioh(10 MA, pl_all_iopins);
//	measure(TRUE);
//}
//
//void Eflash_Selection(int flash_num)
//{
//	switch (flash_num)
//	{
//	case 1: 
//		hv_voltage_set(1.8 V, pl_eflash1_smtn);
//		dps(0 V, pl_eflash2_smtn1);
//		dpo_voltage_set(0 V, pl_eflash2_smtn2);
//		dpo_hv_voltage_set(0 V, pl_eflash2_smtn3);
//		break;
//	case 2:
//		hv_voltage_set(0 V, pl_eflash1_smtn);
//		dps(1.8 V, pl_eflash2_smtn1);
//		dpo_voltage_set(1.8 V, pl_eflash2_smtn2);
//		dpo_hv_voltage_set(1.8 V, pl_eflash2_smtn3);
//		break;
//	default:
//		fatal("Something wrong in switch Eflash, plz check your program!!!");
//		break;
//	}
//}