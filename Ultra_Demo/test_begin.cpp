#include "tester.h"


BEFORE_TESTING_BLOCK(tb_init)
{
	invoke(Max_Site);
	FlowTimer.StartTimer();

	reset_error();
	data_strobe(0xfffffffff);
	dps_comp_cap(1);
	dps_output_mode_set(pl_dps, t_dps_independent);
	dps_connect(pl_dps);
	hv_connect(pl_hv);
	//dpo_hv_connect(pl_dpohv);

	measure(TRUE);
	//power_down();
}


BEFORE_TESTING_BLOCK(tb_savedown_datalog)
{
	//initial
	int wafer_id = 0;
	CString lot_folder = "";
	CString compress_cmd = "";
	CString dynamic_folder = "";

	if (LOT_NUM == "" || WFR_SLOT_ID == "")
	{
		lot_folder = "Demo_XX_" + CTime::GetCurrentTime().Format("%y%m%d_%H%M%S");
		dynamic_folder = "D:\\Log\\" + lot_folder;
		CC_Path(dynamic_folder);
	}
	else if (atoi(WFR_SLOT_ID) != wafer_id)
	{
		if (dynamic_folder != "")
		{
			compress_cmd.Format("Wzzip %s.zip %s -r -p", CASE_FOLDER, CASE_FOLDER);
			system(compress_cmd.GetBuffer(compress_cmd.GetLength()));
		}
		lot_folder = LOT_NUM + "_" + WFR_SLOT_ID + "_" + CTime::GetCurrentTime().Format("%y%m%d_%H%M%S");
		dynamic_folder = "D:\\Log\\" + lot_folder;
		CC_Path(dynamic_folder);
	}
	CASE_FOLDER = dynamic_folder;
	for (int SiteCntr = 0; SiteCntr <= Max_Site; SiteCntr += SITE_PER_CONTROLLER_NUM)
	{
		remote_set(CASE_FOLDER, CASE_FOLDER, SiteCntr, FALSE);
	}
	remote_set(UI_CREATE_DATALOG_FILE_FLAG,TRUE,site_num(), TRUE, INFINITE);
	results_set(PASS);
	wafer_id = atoi(WFR_SLOT_ID);
}

BEFORE_TESTING_BLOCK(tb_communicate_CL)
{
	//send info to CL here
	SoftwareOnlyActiveDutIterator DutLoop;
	while (DutLoop.More(TRUE))
	{
		DutNum dut = active_dut_get();
		register int X, Y;
		TPEGetCurrentXY(dut, &X, &Y);
		TB.set_Coordinate(X, Y, dut);
	}
	Get_LotNum();
	TB.set_WaferInfo(LOT_NUM, WFR_SLOT_ID);
}