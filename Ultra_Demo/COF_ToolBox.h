//COF FUNC
//#define COF_CONTROL

TEST_BIN(_NEXT){}

#ifdef 	COF_CONTROL	
#define SINO_TEST(block, pass, fail)						\
	CALL(block);											\
	tblk_list.Add(resource_name(block));					\
if (resource_name(fail) != "_NEXT")							\
{															\
	fail_index[block] = resource_name(fail);				\
}															\
if (resource_name(pass) != "_NEXT")							\
{															\
	fail_index[block] = resource_name(pass);				\
}

	
#define COF_SWITCH_BOARD()			BIN(cof_bin, STOP);	
#else		
#define _NEXT NEXT
#define SINO_TEST(block, pass, fail)		\
	TEST(block, pass, exit_##fail);			\
	tblk_list.Add(resource_name(block))		\

#define COF_SWITCH_BOARD()			BIN(pass_bin, STOP);
#endif

#define PASS_BIN(bin_name, hbin, sbin)			\
	TEST_BIN(bin_name)		{ process_test_results(current_test_bin, sbin, hbin, PASS); }

#define FAIL_BIN(bin_name, hbin, sbin)			\
	TEST_BIN(bin_name)		{ process_test_results(current_test_bin, sbin, hbin, FAIL); }

#define LINK_TO_BIN(bin_name)\
	BINL(exit_##bin_name, bin_name, STOP);
