#include "tester.h"


// ******************************
// *****  Test Blocks file  *****
// ******************************
// 

TEST_BLOCK(tb_demo2)
{
	TB.header();
	int Cad[12];
	for (int i = 0; i < 12; i++)
	{
		Cad[i] = 521;
	}
	CString label1 = "Cad";
	CString label2 = "Cad2";
	TB.value(label1, Cad);
	TB.value(label2, Cad);
	results_set(PASS);
	return TB.end();
}

TEST_BLOCK(tb_demo1)
{
	TB.header();
	char *  Cad[12];
	static char * time[12];
	for (int i = 0; i < 12; i++)
	{
		Cad[i] = "hello";
	}
	SoftwareOnlyActiveDutIterator loop;
	int demo[12];
	CString buffer12[12];
	CString buffer = CTime::GetCurrentTime().Format("%y.%m.%d_%H.%M.%S");
// example 1
	//while (loop.More(TRUE))
	//{
	//	DutNum dut = active_dut_get();
	//	CString buffer = CTime::GetCurrentTime().Format("%y.%m.%d_%H.%M.%S");
	//	time[dut] = CString2Char(buffer);
	//}
// example 2
	
	//for (int i = 0; i < 12; i++)
	//{
	//	time[i] = CString2Char(buffer);
	//}

//example 3
	//while (loop.More(TRUE))
	//{
	//	DutNum dut = active_dut_get();
	//	demo[dut] = dut;
	//}
	//for (int i = 0; i < 12; i++)
	//{
	//	buffer12[i] = (buffer + Int2CString(demo[i]));
	//	time[i] = CString2Char(buffer12[i]);
	//}
// example 4
	while (loop.More(TRUE))
	{
		DutNum dut = active_dut_get();
		buffer12[dut] = CTime::GetCurrentTime().Format("%y.%m.%d_%H.%M.%S");
		time[dut] = CString2Char(buffer12[dut]);
	}

//end
	output(time[0]);

	CString hello = "hello";
	CString label1 = "Ca";
	CString label2 = "time";
	TB.value(label1, Cad);
	TB.value(label2, time);
	
	results_set(PASS);
	return TB.end();
}

