#define TESTER_H "tester.h"
#include TESTER_H

// *********************************************************
// *****  Pin Assignment Table and Current Share file  *****
// *********************************************************

static CMap < DutPin *, DutPin *, CString, CString > dut_pin_info;

DUT_PIN(GPIO0)		{ }
DUT_PIN(GPIO1)		{ }
DUT_PIN(GPIO2)		{ }
DUT_PIN(GPIO3)		{ }
DUT_PIN(GPIO4)		{ }
DUT_PIN(GPIO5)		{ }
DUT_PIN(VDDH_IO)	{ }
DUT_PIN(VDD)		{ } 
DUT_PIN(VDDH)		{ }
DUT_PIN(VDD_2P4V)	{ }
DUT_PIN(_TEST_)		{ } 
DUT_PIN(VPP)		{ }

HOB_ASSIGNMENTS(ha_eflash){
	//  PMN HSB  MOD_TYPE  INSTANCE
	//ASSIGN_OPTION_MODULE(1, t_hsb1, t_dpo_module, 1)
	//ASSIGN_OPTION_MODULE(2, t_hsb1, t_dpo_module, 2)
	//ASSIGN_OPTION_MODULE(3, t_hsb1, t_dpo_module, 3)
	//ASSIGN_OPTION_MODULE(4, t_hsb1, t_dpo_module, 4)
	//ASSIGN_OPTION_MODULE(5, t_hsb1, t_dpo_module, 5)
	//ASSIGN_OPTION_MODULE(6, t_hsb2, t_dpo_module, 1)
	//ASSIGN_OPTION_MODULE(7, t_hsb2, t_dpo_module, 2)
	//ASSIGN_OPTION_MODULE(8, t_hsb2, t_dpo_module, 3)
	//ASSIGN_OPTION_MODULE(9, t_hsb2, t_dpo_module, 4)
	//ASSIGN_OPTION_MODULE(10, t_hsb2, t_dpo_module, 5)
	//ASSIGN_OPTION_MODULE(11, t_hsb3, t_dpo_module, 1)
	//ASSIGN_OPTION_MODULE(12, t_hsb3, t_dpo_module, 2)
	//ASSIGN_OPTION_MODULE(13, t_hsb3, t_dpo_module, 3)
	//ASSIGN_OPTION_MODULE(14, t_hsb3, t_dpo_module, 4)
	//ASSIGN_OPTION_MODULE(15, t_hsb3, t_dpo_module, 5)

}


PIN_ASSIGNMENTS(pa_eflash) {

	ASSIGN_1DUT(GPIO0,		a_1)
	ASSIGN_1DUT(GPIO1,		a_2)
	ASSIGN_1DUT(GPIO2,		a_3)
	ASSIGN_1DUT(GPIO3,		a_4)
	ASSIGN_1DUT(GPIO4,		a_5)
	ASSIGN_1DUT(GPIO5,		a_6)
	ASSIGN_1DUT(VDDH_IO,	a_7)

	ASSIGN_1DUT(VDD,		a_dps1a)
	ASSIGN_1DUT(VDDH,		a_dps2a)
	ASSIGN_1DUT(VDD_2P4V,	a_dps3a)
	ASSIGN_1DUT(_TEST_,		a_hv1)
	ASSIGN_1DUT(VPP,		a_dps4a)

	// define the package pin numbers - used for datalog

}


// return the package pin number for this dutpin
CString get_dut_pin_number( DutPin * dpin ) {
	return dut_pin_info[ dpin ];
}