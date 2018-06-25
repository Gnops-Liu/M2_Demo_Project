// *************************
// ***** tester.h file *****
// *************************

#include "TestProgApp/public.h"  // moved above #include <afxwin.h> for conversion MSDev 6.0 -> MSDev 2013
#include <iostream>
#include <io.h>
#include <iomanip>
#include <string.h>
#include <fstream>
#include <afxwin.h>
#include <hash_map>
#include "TestTimer.h"
using namespace std;
//Dll
#include "./Debug/CL_Improve.h"

//TP header
#include "protos.h"
#include "pin_lists.h"
#include "fdatalog.h"
#include "timer.h"
#include "driver.h"
#include "patcom_generated_includes.h"


#define VERBOSE 1


//vars
static ofstream fileout;
#define need_to_be_delete