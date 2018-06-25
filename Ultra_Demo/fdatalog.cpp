#include "tester.h"
#include "math.h"  




LecEntryArray2 lec_ary;
FILE *fp_dut[Max_Dut];
bool DlogOpen[Max_Dut]; 

CString remove_tags(CString tagged)
{
	CString tagless, fail_line;
	bool vec_fail = false;

	tagless = fail_line = tagged;

	if (tagless.Replace("<COLOR=Red>H</COLOR>", "H"))
	{
		fail_line.Replace("<COLOR=Red>H</COLOR>", "^");
		vec_fail = true;
	}

	if (tagless.Replace("<COLOR=Red>L</COLOR>", "L"))
	{
		fail_line.Replace("<COLOR=Red>L</COLOR>", "^");
		vec_fail = true;
	}

	tagless.Replace("<COLOR=Green>", "");
	tagless.Replace("<COLOR=Red>", "");
	tagless.Replace("</COLOR>", "");

	tagless.Replace("<B>", "");
	tagless.Replace("</B>", "");

	tagless.Replace("<U>", "");
	tagless.Replace("</U>", "");

	tagless.Replace("<H5>", "");
	tagless.Replace("</H5>", "");

	if (vec_fail)
	{
		for (int i = 0; i<fail_line.GetLength(); i++)
		{
			if (fail_line[i] != '^')
			{
				fail_line.SetAt(i, ' ');
			}
		}

		tagless += vFormat("%s\n", fail_line);
	}

	return tagless;
}

BOOL check_dlog_enable(char type, CString dlog_info)
{
	if (type == 'o')
	{
		if (user)
		{
			if (tp_fdlog)
			{
				if (current_test_block() != "tp_ATB")
				{
					DutNumArray duts;

					int cnt = active_duts_get(&duts);

					for (int i = 0; i<cnt; i++)
					{
						DutNum Dut = duts[i];

						if (DlogOpen[Dut])
						{
							fprintf(fp_dut[Dut], "%s: %s", current_test_block(), remove_tags(dlog_info));
						}
					}
				}
			}
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	return TRUE;
}

int dlogfileopen(int Dut, int x_coord, int y_coord)
{
	remote_fetch(DLOG_FILE_PATH, 0, FALSE);

	CString FullName = DLOG_FILE_PATH;
	char LogFileName[256];

	if (oDriverType == "prober")
	{
		sprintf(LogFileName, "\\\\\\%s_%s_%s_Site%d_Dut%d_X%dY%d.txt", LOT_NUM, WFR_SLOT_ID, FLOW_NAME, site_num(), Dut + 1, x_coord, y_coord);
	}
	else
	{
		sprintf(LogFileName, "\\\\\\%s_%s_Site%d_Dut%d.txt", LOT_NUM, FLOW_NAME, site_num(), Dut + 1);
	}
	FullName += LogFileName;

	if ((fp_dut[Dut] = fopen(FullName, "a")) == NULL)
	{
		output("Problem opening (dut %d) file %s", Dut + 1, FullName);
		return(1);
	}

	return(0);
}


void dlogclose(int Dut)
{
	if (fclose(fp_dut[Dut]) != 0)
	{
		output("*************ERROR closing file***************");
	};
}

void dlogheader(int Dut)
{
	int x, y;

	TPEGetCurrentXY(Dut, &x, &y);

	fprintf(fp_dut[Dut], "$  Test Station: Magnum II                        $ Wafer Lot: %s\n", LOT_NUM);
	fprintf(fp_dut[Dut], "$ X=%d, Y=%d, Site=%d \n", x, y, site_num());
}

void dlogfileopenallactive(void)
{
	int x, y;

	remote_fetch(tp_fdlog, 0, FALSE);

	if (tp_fdlog == FALSE)
	{
		return;
	}

	for (int cntr = 0; cntr <= max_dut(); cntr++)
	{
		DlogOpen[cntr] = false;
	}

	SoftwareOnlyActiveDutIterator ActiveList;
	while (ActiveList.More())
	{
		DutNum Dut = active_dut_get();

		TPEGetCurrentXY((int)Dut, &x, &y);

		DlogOpen[Dut] = true;
		dlogfileopen(Dut, x, y);
	}

}

void dlogcloseallopen(void)
{
	float time = (float)stopseqcntr();

	output("Overall Test Time = %f Seconds\n", time);

	if (tp_fdlog == FALSE)
	{
		return;
	}

	for (int cntr = 0; cntr <= max_dut(); cntr++)
	{
		if (DlogOpen[cntr])
		{
			fprintf(fp_dut[cntr], "Overall Test Time = %f Seconds", time);
			fclose(fp_dut[cntr]);
			DlogOpen[cntr] = false;
		}
	}
}

void dlogheaderallopen(void)
{

	if (tp_fdlog == FALSE)
	{
		return;
	}

	for (int DutCntr = 0; DutCntr <= max_dut(); DutCntr++)
	{
		if (DlogOpen[DutCntr])
			dlogheader(DutCntr);
	}
}

void dlogtblkheaderallactive(CString TblkName)
{
	int x, y;

	SoftwareOnlyActiveDutIterator ActiveList;
	while (ActiveList.More())
	{
		DutNum Dut = active_dut_get();

		TPEGetCurrentXY((int)Dut, &x, &y);

		if (user&&tp_fdlog) fprintf(fp_dut[Dut], "+=================================================================================+\n");
		if (user&&tp_fdlog) fprintf(fp_dut[Dut], "| %s  X %d, Y %d \n", TblkName, x, y);
		if (user&&tp_fdlog) fprintf(fp_dut[Dut], "+=================================================================================+\n");
	}

}

void dlogtestresults()
{
	//if (dlog) output("Test %s, time = %f Seconds", current_test_block(), stopcntr());
}

