#include "tester.h"
#include "resource.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>

#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>

using std::ifstream;
using std::ofstream;
using std::ios;

CArray<Bin, Bin> dut_bin;
CArray<Die_Crd, Die_Crd> site_map;


IntArray iDutToSite;
void Get_LotNum()
{
	for (int SiteCntr = 1; SiteCntr <= MAX_SITES_NUM; SiteCntr += SITE_PER_CONTROLLER_NUM)
	{
		remote_set(LOT_NUM, LOT_NUM, SiteCntr, FALSE);
		remote_set(WFR_SLOT_ID, WFR_SLOT_ID, SiteCntr, FALSE);
	}
}

BOOL_VARIABLE(FK1, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FK1, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(FK2, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FK2, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(FK3, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FK3, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(FK4, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FK4, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(FK5, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FK5, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(FK6, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FK6, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(FK7, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FK7, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(FK8, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FK8, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(FK9, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FK9, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(FK10, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FK10, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(FK11, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FK11, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(FK12, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FK12, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(FK13, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FK13, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(FK14, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FK14, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(FK15, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FK15, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(FK16, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FK16, isite, FALSE);
		}
	}
};

BOOL_VARIABLE(bProgLoaded, TRUE, ""){};
BOOL_VARIABLE(bWMAP_TOOL, FALSE, "") { }

INT_VARIABLE(OI_SITE_NUM, 1, "") { }
INT_VARIABLE(SITE_PER_CONTROLLER_NUM, 1, "") { };
INT_VARIABLE(MAX_DUT_NUM_PER_SITE, 1, "") { };
INT_VARIABLE(MAX_SITES_NUM, 6, "") { };
INT_VARIABLE(TesterID, 0, "") {};
INT_VARIABLE(SerialNum, 0, "") {};
INT_VARIABLE(BASE_X_COORD, 99, "") { }
INT_VARIABLE(BASE_Y_COORD, 99, "") { }
INT_VARIABLE(Hnd_PositionMinY, 1000, ""){};
INT_VARIABLE(Hnd_PositionMaxY, -1000, ""){};
INT_VARIABLE(Hnd_PositionMinX, 1000, ""){};
INT_VARIABLE(Hnd_PositionMaxX, -1000, ""){};
INT64_VARIABLE(iv_init_dut_mask, 0xff, ""){};
BOOL_VARIABLE(forced_pass, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(forced_pass, isite, TRUE);
		}
	}
	if (forced_pass)
		results_force(1);
	else
		results_force(-1); // return to normal operations

	output("Site%d result_force set based on forced_pass = %d", site_num(), forced_pass);

};
#define HOST	0
BOOL_VARIABLE(para, TRUE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(para, isite, TRUE);
		}
	}
};
BOOL_VARIABLE(func, TRUE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(func, isite, TRUE);
		}
	}
};
BOOL_VARIABLE(lvm, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(lvm, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(user, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(user, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(shmoo, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(shmoo, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(search, FALSE, "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(search, isite, FALSE);
		}
	}
};
BOOL_VARIABLE(tp_fdlog, FALSE, "")
{
	if (OnHost())
	{
		if (tp_fdlog)
		{
			create_datalog_folder();
		}
	}
};
BOOL_VARIABLE(fdlog, FALSE, "")
{
	remote_set(tp_fdlog, fdlog, site_num(), TRUE);
};
CSTRING_VARIABLE(LOT_NUM, "", "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(LOT_NUM, isite, FALSE);
		}
	}
};
CSTRING_VARIABLE(WRF_START_TIME, "", "") { };
CSTRING_VARIABLE(WRF_START_DATE, "", "") { };
CSTRING_VARIABLE(WRF_END_TIME, "", "") { };
CSTRING_VARIABLE(WRF_END_DATE, "", "") { };
CSTRING_VARIABLE(WFR_SLOT_ID, "", "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(WFR_SLOT_ID, isite, FALSE);
		}
	}
};
CSTRING_VARIABLE(WRF_END_TIME_GMT, "XXXXXX", "") {};
CSTRING_VARIABLE(WRF_START_TIME_GMT, "XXXXXX", "") {};
CSTRING_VARIABLE(WRF_START_DATETIME, "XXXXXX", "") {};
CSTRING_VARIABLE(RESULTS_STR, "UNDEFINED", ""){}
CSTRING_VARIABLE(DLOG_FILE_PATH, "D:\\Datalogs", "") {};
CSTRING_VARIABLE(cProbeCardSiteInfo, "", "") { };
CSTRING_VARIABLE(cDutToSiteInfo, "1,2,1,", "") { }
CSTRING_VARIABLE(FLOW_NAME, get_flow_name(), "")
{
	if (OnHost())
	{
		for (int isite = 1; isite <= MAX_SITES_NUM; isite += SITE_PER_CONTROLLER_NUM)
		{
			remote_send(FLOW_NAME, isite, FALSE);
		}
	}
};
CSTRING_VARIABLE(CHUCK_TEMP, "99", "") {};
CSTRING_VARIABLE(OPERATOR_ID, "XXXXXX", ""){};
CSTRING_VARIABLE(DEVICE_NAME, "XXXXXX", "") { };
CSTRING_VARIABLE(COMMENTS, "XXXXXX", "") { };
CSTRING_VARIABLE(USER_C, "XXXXXX", "") { };
CSTRING_VARIABLE(PROGRAM_NAME, "XXXXXX", "") { };
CSTRING_VARIABLE(PROGRAM_PATH, "XXXXXX", "") { };
CSTRING_VARIABLE(PROBE_CARD_ID, "XXXXXX", "") { };



ONEOF_VARIABLE(oDriverType, "prober, handler", "") {};

VOID_VARIABLE(ResetBinTables, "")
{
	for (DutNum dut = t_dut1; dut <= max_dut(); ++dut)
		reset_all_bins(dut);
}

VOID_VARIABLE(ResetBins, "")
{
	for (int i = 0; i < MAX_SITES_NUM; i += SITE_PER_CONTROLLER_NUM)
		remote_send(ResetBinTables, i + 1, TRUE);
}

CSTRING_VARIABLE(cDutDatas, "", "") { }

void after_test_done_process(bool datalog_flag);

void update_wafermap_tool(int x, int y, CString binname)
{
	if (bWMAP_TOOL)
	{
		wmap_die_set(wmap_die_bin, x, y, binname);
	}
}

VOID_VARIABLE(update_wafermap_field, "")
{
	if (bWMAP_TOOL)
	{
		wmap_die_set(wmap_die_field, Hnd_PositionMinX, Hnd_PositionMinY, Hnd_PositionMaxX - Hnd_PositionMinX + 1, Hnd_PositionMaxY - Hnd_PositionMinY + 1, PS_SOLID, RGB(0, 0, 255));
	}
}

VOID_VARIABLE(clear_wafermap_field, "")
{
	static bool first = true;

	if (bWMAP_TOOL)
	{
		if (!first)
		{
			wmap_die_set(wmap_die_field, Hnd_PositionMinX, Hnd_PositionMinY, 0, 0, PS_SOLID, RGB(0, 0, 255));
		}

		first = false;
	}
}

VOID_VARIABLE(DEV_READY_EVENT, "")
{
	if (VERBOSE) output("DEV_READY_EVENT");

	if (OnHost())
	{
		remote_fetch(fdlog, site_num(), TRUE, INFINITE);
		remote_fetch(user, site_num(), TRUE, INFINITE);

		remote_send("ui_StartTest", -1, TRUE); 	// Start testin on all sites
		remote_wait("TestDone", INFINITE); 		// Wait for UI to signal Test Done

		//after_test_done_process();
	}
	else
	{
		ignored_duts_disable(iv_init_dut_mask, FALSE);
		if (VERBOSE) output("DEV_READY_EVENT: iv_init_dut_mask = 0x%I64x", iv_init_dut_mask);
	}
}

VOID_VARIABLE(START_OF_WAFER_EVENT, "")
{
	if (VERBOSE) output("Test Prog: FIRST_DIE_EVENT");

	invoke(ResetBins);

	remote_fetch(LOT_NUM, 0, TRUE);
	remote_fetch(WFR_SLOT_ID, 0, TRUE);


	create_datalog_folder();

	DLOG_FILE_PATH = "D:\\Datalogs\\Lot" + LOT_NUM;
	if (VERBOSE) output("Setting DLOG_FILE_PATH  = %s", DLOG_FILE_PATH);

	char date[12];
	char time1[12];
	//char buff [8];
	char buff[12];// enl mod
	time_t ltime;

	time(&ltime);

	//Get wafer start date
	_strdate(date);
	strncpy(buff, date + 6, 2);
	for (int j = 0; j<6; j++) if (date[j] == '/') date[j] = ':';
	date[6] = '\0';
	sprintf(buff, "%s%d", date, 2000 + (atoi(buff)));
	if (VERBOSE) output("Start Wafer Current Date:%s\n", buff);

	WRF_START_DATE = buff;

	//Get wafer start time 
	_strtime(time1);
	WRF_START_TIME = time1;

	WRF_START_TIME_GMT.Format("%ld", ltime);

	int y = 0;
	for (int j = 0; j<5; j++) { if (date[j] != ':') { buff[y] = date[j]; y++; } }
	for (int j = 0, y = 4; j<5; j++) { if (date[j] != ':') { buff[y] = time1[j]; y++; } }
	buff[8] = '\0';
	WRF_START_DATETIME = buff;

	if (VERBOSE) output("WRF_START_DATETIME:\t%s\n", WRF_START_DATETIME);
}

VOID_VARIABLE(END_OF_WAFER_EVENT, "")
{
	char date[10], buff[32];
	char time1[10];
	time_t ltime;

	if (VERBOSE) output("Test Prog: END_OF_WAFER_EVENT");

	_strdate(date);
	strncpy(buff, date + 6, 2);
	for (int j = 0; j<6; j++) if (date[j] == '/') date[j] = ':';
	date[6] = '\0';
	sprintf(buff, "%s%d", date, 2000 + (atoi(buff)));
	if (VERBOSE) output("END Wafer Current Date:%s\n", buff);

	WRF_END_DATE = buff;

	_strtime(time1);
	if (VERBOSE) output("END Wafer  Time:%s,", time1);
	WRF_END_TIME = time1;

	time(&ltime);
	if (VERBOSE) output("Time in seconds since UTC 1/1/70:\t%ld\n", ltime);

	WRF_END_TIME_GMT.Format("%ld", ltime);
	if (VERBOSE) output("WRF_END_TIME_GMT:\t%s\n", WRF_END_TIME_GMT);
}

VOID_VARIABLE(START_OF_LOT_EVENT, "")
{
	if (VERBOSE) output("Test Prog: FIRST_WAFER_EVENT");

	LOT_NUM = remote_get("LOT_NUM", 0, FALSE);
	WFR_SLOT_ID = remote_get("WFR_SLOT_ID", 0, FALSE);

	create_datalog_folder();
}

VOID_VARIABLE(END_OF_LOT_EVENT, "")
{
	if (VERBOSE) output("Test Prog: LOT_END_EVENT");
}

VOID_VARIABLE(Z_UP_EVENT, "")
{
}

VOID_VARIABLE(FIRST_DIE_EVENT, "")
{
	invoke(START_OF_WAFER_EVENT);
}

VOID_VARIABLE(WAFER_END_EVENT, "")
{
	invoke(END_OF_WAFER_EVENT);
}

VOID_VARIABLE(FIRST_WAFER_EVENT, "")
{
	invoke(START_OF_LOT_EVENT);
}

VOID_VARIABLE(LOT_END_EVENT, "")
{
	invoke(END_OF_LOT_EVENT);
}

VOID_VARIABLE(MASK_SITES, "")
{
	invoke(DEV_READY_EVENT);	//site process
}

VOID_VARIABLE(RUN_TESTS_HOST, "")
{
	invoke(DEV_READY_EVENT);	//host_process
}

// Transform the notification from UI into a signal to
// our HOST_BEGIN_BLOCK, which is waiting for "TestDone"

VOID_VARIABLE(ui_TestDone, ""){
	ASSERT(sender == -1);  // -1 is UI
	Show_All_Site_Info();
	after_test_done_process(FALSE);

	remote_signal("TestDone", site_num());  // should signal the host
}

void after_test_done_process(bool datalog_flag)
{
	CString cData = "";
	CString ResultsFromSite, ResultsFromDut, TmpString, binname;
	int	iDataNum = 0;
	int x_, y_, b_, s_, t_, r_;

	for (int SiteCntr = 1; SiteCntr <= MAX_SITES_NUM; SiteCntr += SITE_PER_CONTROLLER_NUM)
	{
		cDutDatas = vFormat("%d,", SiteCntr);

		ResultsFromSite = remote_get(RESULTS_STR, SiteCntr);
		remote_fetch(iv_init_dut_mask, SiteCntr, FALSE);

		iDataNum = 0;
		cData = "";

		TmpString = ResultsFromSite;

		for (int cntr = 0; cntr < MAX_DUT_NUM_PER_SITE; cntr++)
		{
			int idx = TmpString.Find("X=", 1); //find 2nd occurence of X=

			if (idx>-1)
			{
				ResultsFromDut = TmpString.Left(idx);
				TmpString = TmpString.Right(TmpString.GetLength() - idx);
			}
			else
			{
				ResultsFromDut = TmpString;
			}

			if (ResultsFromDut.Find(",S=") != -1)
			{
				sscanf(ResultsFromDut, "X=%d,Y=%d,S=%d,D=%d,R=%d,T=%d,N=%s", &x_, &y_, &s_, &b_, &r_, &t_, binname.GetBuffer(100)); // enl mod
				binname.ReleaseBuffer();
			}
			else
			{
				sscanf(ResultsFromDut, "X=%d,Y=%d,D=%d,R=%d,T=%d", &x_, &y_, &b_, &r_, &t_);
				s_ = 0;
			}
			if (datalog_flag) output("ResultsFromDut = %s", ResultsFromDut);

			if (((iv_init_dut_mask >> cntr) & 0x1) && (b_ != 0))
			{
				iDataNum++;

				cData = cData + vFormat("%d,%d,%d,%d,%d,%d,%d,",
					x_,
					y_,
					s_,
					b_,
					(((((SiteCntr - 1) / SITE_PER_CONTROLLER_NUM)*MAX_DUT_NUM_PER_SITE)) + (cntr)),
					r_,
					t_
					);

				update_wafermap_tool(x_, y_, binname);
			}
		}

		cDutDatas = cDutDatas + vFormat("%d,%d,%s",
			iDataNum,
			7,
			cData
			);

		remote_set(cDutDatas, cDutDatas, SiteCntr, FALSE);

		if (datalog_flag) output("cDutDatas=%s", cDutDatas);
	}
}

CString GetChrFromLine(CString& cMsg)
{
	CString cRet;

	int i = cMsg.Find(",", 0);
	if (i != -1) {
		cRet = cMsg.Left(i);
		cMsg = cMsg.Right(cMsg.GetLength() - i - 1);
		return cRet;
	}

	cRet = "0";
	return cRet;
}

void load_sitemap_table()
{
	int x, y, SiteCntr, iSiteNum, this_site, if_site;
	int dut;
	CString cTemp;

	site_map.SetSize(max_dut() + 1);
	iDutToSite.SetSize(max_dut() + 1);

	this_site = site_num();

	cTemp = remote_get(cDutToSiteInfo, 0, FALSE);

	iSiteNum = atoi(GetChrFromLine(cTemp));

	//if site > number of sites in cDutToSiteInfo return error
	if (iSiteNum < (SITE_PER_CONTROLLER_NUM == 1 ? this_site : this_site / SITE_PER_CONTROLLER_NUM + 1))
	{
		//output("*********load_sitemap_table: ERROR: iSiteNum(swt)=%d, this_site=%d*********", iSiteNum, this_site);
		return;
	}

	//parse through preceeding sites
	for (SiteCntr = 1; SiteCntr<this_site; SiteCntr += SITE_PER_CONTROLLER_NUM)
	{
		for (dut = 0; dut <= max_dut(); dut++)
		{
			if_site = atoi(GetChrFromLine(cTemp));
		}
	}

	//parse for interface hardware site numbers
	for (dut = 0; dut <= max_dut(); dut++)
	{
		iDutToSite[dut] = atoi(GetChrFromLine(cTemp));
	}


	cTemp = remote_get(cProbeCardSiteInfo, 0, FALSE);

	if (cTemp == "")
	{
		oDriverType = "handler";
		return;
	}

	iSiteNum = atoi(GetChrFromLine(cTemp));

	//if site > number of sites in cProbeCardSiteInfo return error
	if (iSiteNum < (SITE_PER_CONTROLLER_NUM == 1 ? this_site : this_site / SITE_PER_CONTROLLER_NUM + 1))
	{
		//output("*********load_sitemap_table: ERROR: iSiteNum(swt)=%d, this_site=%d*********", iSiteNum, this_site);
		return;
	}

	//parse through preceeding sites
	for (SiteCntr = 1; SiteCntr<this_site; SiteCntr += SITE_PER_CONTROLLER_NUM)
	{
		for (dut = 0; dut <= max_dut(); dut++)
		{
			x = atoi(GetChrFromLine(cTemp));
			y = atoi(GetChrFromLine(cTemp));
		}
	}

	for (dut = 0; dut <= max_dut(); dut++)
	{
		site_map[dut].x = atoi(GetChrFromLine(cTemp));
		site_map[dut].y = atoi(GetChrFromLine(cTemp));
	}
}

void tp_init_bins()
{
	dut_bin.SetSize(max_dut() + 1);

	for (int dut = 0; dut <= max_dut(); dut++)
	{
		dut_bin[dut].name = "NULL";
		dut_bin[dut].hbin = 0;
		dut_bin[dut].sbin = 0;
		dut_bin[dut].result = FAIL;
	}
}

void tp_site_show_bins(void)
{
	if (oDriverType == "prober")
	{
		output("\nTester\tI/F\t   \t   \tSoft\tHard");
		output("Dut   \tDut\t  X\t  Y\tBin\tBin\tP/F\tBin Name");
		output("------\t---\t  -\t  -\t----\t----\t---\t--------");

		{
			SoftwareOnlyActiveDutIterator SwActiveDuts;
			while (SwActiveDuts.More())
			{
				DutNum i = active_dut_get();
				int x, y;

				TPEGetCurrentXY(i, &x, &y);

				// Print header info
				if (tp_fdlog) fprintf(fp_dut[i], "\nTester\tI/F\t   \t   \tSoft\tHard\n");
				if (tp_fdlog) fprintf(fp_dut[i], "Dut   \tDut\t  X\t  Y\tBin\tBin\tP/F\tBin Name\n");
				if (tp_fdlog) fprintf(fp_dut[i], "------\t---\t  -\t  -\t----\t----\t---\t--------\n");

				output("DUT %d\t%3d\t%3d\t%3d\t%4d\t%4d\t%s\t%s", i + 1, iDutToSite[i] + 1, x, y, dut_bin[i].sbin,
					dut_bin[i].hbin, dut_bin[i].result == PASS ? "<COLOR=Green>PASS</COLOR>" : "<COLOR=Red>FAIL</COLOR>", dut_bin[i].name);

				if (tp_fdlog) fprintf(fp_dut[i], "DUT %d\t%3d\t%3d\t%3d\t%4d\t%4d\t%s\t%s\n", i + 1, iDutToSite[i] + 1, x, y, dut_bin[i].sbin,
					dut_bin[i].hbin, dut_bin[i].result == PASS ? "<COLOR=Green>PASS</COLOR>" : "<COLOR=Red>FAIL</COLOR>", dut_bin[i].name);
			}
		}
	}
	else
	{
		output("\nTester\tI/F\tSoft\tHard");
		output("Dut   \tDut\tBin\tBin\tP/F\tBin Name");
		output("------\t---\t----\t----\t---\t--------");

		{
			SoftwareOnlyActiveDutIterator SwActiveDuts;
			while (SwActiveDuts.More())
			{
				DutNum i = active_dut_get();

				// Print header info
				if (tp_fdlog) fprintf(fp_dut[i], "\nTester\tI/F\tSoft\tHard\n");
				if (tp_fdlog) fprintf(fp_dut[i], "Dut   \tDut\tBin\tBin\tP/F\tBin Name\n");
				if (tp_fdlog) fprintf(fp_dut[i], "------\t---\t----\t----\t---\t--------\n");

				output("DUT %d\t%3d\t%4d\t%4d\t%s\t%s", i + 1, iDutToSite[i] + 1, dut_bin[i].sbin,
					dut_bin[i].hbin, dut_bin[i].result == PASS ? "<COLOR=Green>PASS</COLOR>" : "<COLOR=Red>FAIL</COLOR>", dut_bin[i].name);

				if (tp_fdlog) fprintf(fp_dut[i], "DUT %d\t%3d\t%4d\t%4d\t%s\t%s\n", i + 1, iDutToSite[i] + 1, dut_bin[i].sbin,
					dut_bin[i].hbin, dut_bin[i].result == PASS ? "<COLOR=Green>PASS</COLOR>" : "<COLOR=Red>FAIL</COLOR>", dut_bin[i].name);
			}
		}
	}

	output("\n");
} // end of tp_site_show_bins()

// sbin - soft bin, used for data colection
// hbin - hard bin, used for hardware interface( physcial bins )
// pf - pass/fail state
void process_test_results(TestBin* current_test_bin, int sbin, int hbin, PFState pf)
{
	DutNumArray active_duts;
	CString	bin_string = resource_name(current_test_bin);

	int count = active_duts_get(&active_duts);

	for (int ix = 0; ix<count; ix++) {
		dut_bin[(int)active_duts[ix]].name = bin_string;// Store bin string for DUTs that passed this test
		dut_bin[(int)active_duts[ix]].sbin = sbin; // Store bin number for DUTs that passed this test
		dut_bin[(int)active_duts[ix]].hbin = hbin; // Store interface bin for DUTs that passed this test
		dut_bin[(int)active_duts[ix]].result = pf;
	}
} 

void TPEGetCurrentXY(int dut, int *xcord, int *ycord)
{
	load_sitemap_table();

	*xcord = site_map[dut].x;
	*ycord = site_map[dut].y;
}

CString get_flow_name()
{
	int idx;
	CString flow = resource_all_names(S_SequenceTable);

	if ((idx = flow.Find(',')) != -1)
	{
		flow = flow.Left(idx);
	}

	return flow;
}

BEFORE_TESTING_BLOCK(tp_BTB)
{
	static BOOL first = TRUE;

	startseqcntr();

	tp_init_bins();
	initcntr();

	load_sitemap_table();

	remote_fetch(FK1, 0, FALSE);
	remote_fetch(FK2, 0, FALSE);
	remote_fetch(FK3, 0, FALSE);
	remote_fetch(FK4, 0, FALSE);
	remote_fetch(FK5, 0, FALSE);
	remote_fetch(FK6, 0, FALSE);
	remote_fetch(FK7, 0, FALSE);
	remote_fetch(FK8, 0, FALSE);
	remote_fetch(FK9, 0, FALSE);
	remote_fetch(FK10, 0, FALSE);
	remote_fetch(FK11, 0, FALSE);
	remote_fetch(FK12, 0, FALSE);
	remote_fetch(FK13, 0, FALSE);
	remote_fetch(FK14, 0, FALSE);
	remote_fetch(FK15, 0, FALSE);
	remote_fetch(FK16, 0, FALSE);

	dlogfileopenallactive();

	dlogheaderallopen();

	if (first)
	{
		intercept(check_dlog_enable);
		first = FALSE;
		fumble(check_dlog_enable); // enl debug to show messages in output window
	}
}

EXTERN_TEST_BIN(continuity_bin);
AFTER_TESTING_BLOCK(tp_ATB)
{
	double seqtime;
	int itime, x, y;
	Show_All_Dut_Info();
	set_bin(continuity_bin, t_dut1);
	tp_site_show_bins();

	seqtime = stopseqcntr();
	itime = (int)(seqtime * 1000.0);

	if (MODE == 1)
	{
		CString StrBfr;
		RESULTS_STR = ""; // Empty string
		for (int cntr = 0; cntr <= max_dut(); cntr++)
		{
			TPEGetCurrentXY(cntr, &x, &y);
			StrBfr.Format("\n\t\tX=%d,Y=%d,S=%d,D=%d,R=%d,T=%d,N=%s ", x, y, dut_bin[cntr].sbin, dut_bin[cntr].hbin, dut_bin[cntr].result, itime, dut_bin[cntr].name);
			RESULTS_STR += StrBfr;
		}

		output("RESULTS_STR= %s", RESULTS_STR);
	}


	ignored_duts_disable(((__int64)0x1 << (MAX_DUT_NUM_PER_SITE)) - 1, FALSE);

	dlogcloseallopen();
	
}

CSTRING_VARIABLE(Magnum_OI, "", "")
{
	CString toolpath = "C:\\nextest\\user_tools\\Magnum_OI.exe";

	remote_set("ui_StartTool", toolpath, -1, TRUE, INFINITE);
}

void wmap_callback(int x, int y)
{
	output("clicked on x=%d y=%d", x, y);
	BASE_X_COORD = x;
	BASE_Y_COORD = y;

	remote_send(BASE_X_COORD, OI_SITE_NUM, TRUE);
	remote_send(BASE_Y_COORD, OI_SITE_NUM, TRUE);

	invoke(clear_wafermap_field);
	remote_set("vCalcXYCoordinate", 0, OI_SITE_NUM, TRUE, INFINITE);
	invoke(update_wafermap_field);

	remote_set("vHnd_Move", 0, OI_SITE_NUM, TRUE);
}

CSTRING_VARIABLE(WMAP_TOOL_CFG, "", "")
{
	wmap_set(wmap_config_load, WMAP_TOOL_CFG);
	wmap_onclick_set(wmap_callback);

	bWMAP_TOOL = TRUE;
}

INITIALIZATION_HOOK(init_vars)
{
	SITE_PER_CONTROLLER_NUM = sites_per_controller();
	MAX_DUT_NUM_PER_SITE = max_dut() + 1;

	if (OnHost())
	{
		CFileFind finder;

		if (finder.FindFile("C:\\nextest\\user_tools\\Magnum_OI.exe"))
		{
			menu_add("&User/Magnum_OI", Magnum_OI);
		}
	}
	if (OnSite())
	{
		//initialize default iDutToSite
		iDutToSite.SetSize(MAX_DUT_NUM_PER_SITE);

		for (int dut = 0; dut<MAX_DUT_NUM_PER_SITE; dut++)
		{
			iDutToSite[dut] = dut + 1 + ((site_num() - 1) / SITE_PER_CONTROLLER_NUM)*MAX_DUT_NUM_PER_SITE;
		}
	}
}

void create_datalog_folder()
{
	if (tp_fdlog)
	{
		CString CMDLine = "D:\\Datalogs";
		CFileFind finder;

		if (finder.FindFile(CMDLine) == false)
		{
			if (!CreateDirectory(CMDLine, NULL))
			{
				output("Creating Directory failed %s", CMDLine);
				tp_fdlog = false;
				return;
			}
			else
			{
				output("Directory %s created  Successfully!", CMDLine);
			}
		}

		CMDLine += vFormat("\\Lot%s", LOT_NUM);

		if (finder.FindFile(CMDLine) == false)
		{
			if (!CreateDirectory(CMDLine, NULL))
			{
				output("Creating Directory failed %s", CMDLine);
				tp_fdlog = false;
				return;
			}
			else
			{
				output("Directory %s created  Successfully!", CMDLine);
			}
		}

		DLOG_FILE_PATH = CMDLine;
		output("DLOG_FILE_PATH  = %s", DLOG_FILE_PATH);
	}
}

VOID_VARIABLE(ui_ProgLoaded, "")
{
	invoke(Max_Site);
}