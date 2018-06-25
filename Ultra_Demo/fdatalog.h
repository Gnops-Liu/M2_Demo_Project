extern FILE *fp_dut[];

extern void dlogfileopenallactive(void);					// Put in BTB, after IgnoreDutsEnable
extern void dlogcloseallopen(void);							// Put in ATB
extern void dlogheaderallopen(void);						// Put in BTB, just after DlogFileOpenAllActive
extern void dlogtblkheaderallactive(CString TblkName);		// Put at the start of each test block
extern void dlogtestresults();
extern void create_datalog_folder();

extern BOOL check_dlog_enable( char type, CString dlog_info);
