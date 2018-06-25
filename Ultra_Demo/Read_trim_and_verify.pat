#include "Eflash_Toolbox.h"

PATTERN(p_read_trim_and_verify)
@{
	count(1, 0);		//For common loop
	count(2, 8);		//spi address bits -2
	count(3, 16);		//spi data bits -2
	count(4, 14);		//stb data bits - 2 
	count(5, 5);		//stb data bits - 3
	count(6, 6);		//stb cmd bits -2
	count(7, 22);		//stb cmd bits -1
	count(8, 0);		//common delay
	count(10, 9);
	dmain(0x0);
	@}
//PORSTN = 0, delay = 20cycle 1000ns
cycle_delay(bg_setup1, 0x3E6, PSTeq0_stateX32)
//PORSTN = 1, delay = 401 cycle  20005ns
cycle_delay(bg_setup2, 0x4E23, PSTeq1_stateX32)
serial_test_mode_entryX32(enter_serial_testmode)
cycle_delay(delay2, 0x4e1e, stb_active_stateX32)
%mar done
pinfunc	adhiz
/***********end************/