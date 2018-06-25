#ifndef USER_DEFINE_H_
#define USER_DEFINE_H_
#include "Eflash_Toolbox.h"

#define USE_foreign		0x0
#define EBM_COUNTER count12

#define SIZE_64K		0xFFFF
#define SIZE_76K		0x12fff
//===========================================================
//sector erase: over 40000 cycle
//
//
//
//
//===========================================================
#define PROG_TMX32	0X7DB
#define PROG_TMX128 0X95E
//====================CS TABLE===============================
//SCRAMBLE(eFlash_sclk, t_cs1)
//SCRAMBLE(eFlash_sce, t_cs2)
//SCRAMBLE(eFlash_porstn, t_cs3)
//SCRAMBLE(pmu_rst, t_cs4)
//SCRAMBLE(pmu_cs, t_cs5)
//SCRAMBLE(eFlash_sio_i, t_cs6)
//SCRAMBLE(eFlash1_smten, t_cs7)
//SCRAMBLE(eFlash2_smten, t_cs8)
//===========================================================

//state all for eFlash2 (32 bit)
#define dummy_stateX32			cs1pt,cs2t,cs3f,cs4f,cs5t,cs6f	//PS_DEF
#define blank_stateX32			cs1f, cs2f,cs3f,cs4f,cs5t,cs6f	//PS_DEF
#define stb_active_stateX32		cs1pt,cs2f,cs3f,cs4f,cs5t	  	//PS_DIN 
#define spi_active_stateX32		cs1pt,cs2t,cs3f,cs4f,cs5f	  	//PS_SPI_DIN & PS_SPI_DOUT
#define read_stateX32			cs1pt,cs2f,cs3f,cs4f,cs5t,cs6f	//PS_DOUT1 & PS_DOUT2
#define PSTeq0_stateX32			cs1pt,cs2t,cs3t,cs4f,cs5t,cs6f	//PS_DEF
#define PSTeq1_stateX32			cs1pt,cs2t,cs3f,cs4f,cs5t,cs6f	//PS_DEF
#define RSTeq0_stateX32			cs1pt,cs2t,cs3f,cs4t,cs5t,cs6f	//PS_DEF
#define RSTeq1_stateX32			cs1pt,cs2t,cs3f,cs4f,cs5t,cs6f	//PS_DEF

//state all for eFlash1 (128 bit)
#define dummy_stateX128			cs1pt,cs2t,cs3f,cs4f,cs5t,cs6f	//PS_DEF
#define blank_stateX128			cs1f, cs2f,cs3f,cs4f,cs5t,cs6f	//PS_DEF
#define stb_active_stateX128	cs1pt,cs2f,cs3f,cs4f,cs5t	  	//PS_DIN 
#define spi_active_stateX128	cs1pt,cs2t,cs3f,cs4f,cs5f	  	//PS_SPI_DIN & PS_SPI_DOUT
#define read_stateX128			cs1pt,cs2f,cs3f,cs4f,cs5t,cs6f	//PS_DOUT1 & PS_DOUT2
#define PSTeq0_stateX128		cs1pt,cs2t,cs3t,cs4f,cs5t,cs6f	//PS_DEF
#define PSTeq1_stateX128		cs1pt,cs2t,cs3f,cs4f,cs5t,cs6f	//PS_DEF
#define RSTeq0_stateX128		cs1pt,cs2t,cs3f,cs4t,cs5t,cs6f	//PS_DEF
#define RSTeq1_stateX128		cs1pt,cs2t,cs3f,cs4f,cs5t,cs6f	//PS_DEF

//PS
#define PS_DEF				PS64
#define PS_STB_CMD			PS1
#define PS_STB_ADDR			PS2
#define PS_STB_DIN			PS3
#define PS_STB_DOUT1		PS4
#define PS_STB_DOUT2		PS5
#define PS_SPI_DIN_ADDR		PS6
#define PS_SPI_DIN_DATA		PS7
#define PS_SPI_DOUT_DATA	PS8
#define PS_SPI_DIN			PS9

#define COMMON_HEADER() \
	count(1, amax());	\
	count(2, 8);		\
	count(3, 16);		\
	count(4, 14);		\
	count(5, 5);		\
	count(6, 6);		\
	count(7, 22);		\
	count(8, 0);		\
	count(12, 0);		\
	xmain(xmax());		\
	ymain(ymax());		\
// user macro	
/***************************************************
Macro name: spi_send_data
Usage:spi_send_data(labelname)
Action:get spi data in dbase and send to device
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
PLZ use it after spi_set_data or spi_input_setup
label_name: used for incide loop, pay attention not to be repeated
****************************************************/
#define spi_send_data_temp(labelname,state)			\
%	chips	state								\n	\
	pinfunc tset1, PS_SPI_DIN_DATA				\n	\
	DATGEN  base2base2							\n	\
%labelname##_data:								\n	\
	datgen	sdbase2, dbase2, SHLDR, base2base2	\n	\
	chips	state								\n	\
	pinfunc tset1, PS_SPI_DIN_DATA				\n	\
	count	count3, decr, aon					\n	\
	mar		cjmpnz, labelname##_data			\n


#define pos_margin_readX32(labelname)					\
stb_set_command(0xA3,dummy_stateX32)				\n	\
stb_send_command(labelname,stb_active_stateX32)			\n	\
cycle_delay(labelname##TMC,0x6,stb_active_stateX32)	\n	

#define pos_margin_readX128(labelname)						\
stb_set_command(0xA3,dummy_stateX128)					\n	\
stb_send_command(labelname,stb_active_stateX128)				\n	\
cycle_delay(labelname##TMC,0x6,stb_active_stateX128)	\n	

#define SG_stress_modeX32(labelname,addr,dataH,dataL)		\
stb_set_all(0x51,addr,dataH,dataL,dummy_stateX32)		\n	\
stb_send_command(labelname,stb_active_stateX32)			\n	\
stb_send_address(labelname,stb_active_stateX32)			\n	\
stb_send_data(labelname,stb_active_stateX32)			\n	\
cycle_delay(labelname##_TMC,0x6,stb_active_stateX32)	\n	\
cycle_delay(labelname##_wait,0x8,stb_active_stateX32)	\n		// Need to be verified

#define SG_stress_modeX128(labelname,addr,dataH,dataL)		\
stb_set_all(0x51,addr,dataH,dataL,dummy_stateX128)		\n	\
stb_send_command(labelname,stb_active_stateX128)		\n	\
stb_send_address(labelname,stb_active_stateX128)		\n	\
stb_send_data(labelname,stb_active_stateX128)			\n	\
cycle_delay(labelname##_TMC,0x6,stb_active_stateX128)	\n	\
cycle_delay(labelname##_wait,0x8,stb_active_stateX128)	\n		// Need to be verified

#define Bit_line_stress_modeX32(labelname,addr,dataH,dataL)		\
stb_set_all(0x52,addr,dataH,dataL,dummy_stateX32)			\n	\
stb_send_command(labelname,stb_active_stateX32)				\n	\
stb_send_address(labelname,stb_active_stateX32)				\n	\
stb_send_data(labelname,stb_active_stateX32)				\n	\
cycle_delay(labelname##_TMC,0x6,stb_active_stateX32)		\n	\
cycle_delay(labelname##_wait,0x8,stb_active_stateX32)		\n		// Need to be verified

#define Bit_line_stress_modeX128(labelname,addr,dataH,dataL)	\
stb_set_all(0x52,addr,dataH,dataL,dummy_stateX128)			\n	\
stb_send_command(labelname,stb_active_stateX128)			\n	\
stb_send_address(labelname,stb_active_stateX128)			\n	\
stb_send_data(labelname,stb_active_stateX128)				\n	\
cycle_delay(labelname##_TMC,0x6,stb_active_stateX128)		\n	\
cycle_delay(labelname##_wait,0x8,stb_active_stateX128)		\n		// Need to be verified

#define exit_test_mode0X32(labelname)								\
stb_set_command(0xB1,dummy_stateX32)							\n	\
stb_send_command(labelname##_1,stb_active_stateX32)				\n	\
cycle_delay(labelname##_config1,0x6,stb_active_stateX32)		\n	

#define exit_test_mode0X128(labelname)								\
stb_set_command(0xB1,dummy_stateX128)							\n	\
stb_send_command(labelname##_1,stb_active_stateX128)			\n	\
cycle_delay(labelname##_config1,0x6,stb_active_stateX128)		\n	

#define gang_programX32(labelname,addr,dataH,dataL)					\
stb_set_all(0xA1,addr,dataH,dataL,dummy_stateX32)				\n	\
stb_send_command(labelname,stb_active_stateX32)					\n	\
stb_send_address(labelname,stb_active_stateX32)					\n	\
stb_send_data(labelname,stb_active_stateX32)					\n	\
cycle_delay(labelname##_dummy, PROG_TMX32, stb_active_stateX32)		\n 

#define gang_programX128(labelname,addr,Hdata4,Ldata4,Hdata3,Ldata3,Hdata2,Ldata2,Hdata1,Ldata1)				\
stb_set_all(0xA1,addr,Hdata4,Ldata4,dummy_stateX128)														\n	\
stb_send_command(labelname,stb_active_stateX128)															\n	\
stb_send_address(labelname,stb_active_stateX128)															\n	\
stb_send_data(labelname##4,stb_active_stateX128)															\n	\
set_blank_data(Hdata3,Ldata3,blank_stateX128)																\n	\
stb_send_data(labelname##3, stb_active_stateX128)															\n	\
set_blank_data(Hdata2,Ldata2,blank_stateX128)																\n	\
stb_send_data(labelname##2, stb_active_stateX128)															\n	\
set_blank_data(Hdata1,Ldata1,blank_stateX128)																\n	\
stb_send_data(labelname##1, stb_active_stateX128)															\n	\
cycle_delay(labelname##_dummy, PROG_TMX128, stb_active_stateX128)												\n 

#define gang_program_formX32(labelname,dataH,dataL)				\
stb_set_command(0xA1,dummy_stateX32)						\n	\
stb_set_data(dataH,dataL,dummy_stateX32)					\n	\
stb_send_command(labelname,stb_active_stateX32)				\n	\
stb_send_address(labelname,stb_active_stateX32)				\n	\
stb_send_data(labelname,stb_active_stateX32)				\n	\
cycle_delay(labelname##_dummy, PROG_TMX32, stb_active_stateX32	\n 

#define gang_program_formX128(labelname,dataH,dataL)			\
stb_set_command(0xA1,dummy_stateX128)						\n	\
stb_set_data(dataH,dataL,dummy_stateX128)					\n	\
stb_send_command(labelname,stb_active_stateX128)			\n	\
stb_send_address(labelname,stb_active_stateX128)			\n	\
stb_send_data(labelname,stb_active_stateX128)				\n	\
cycle_delay(labelname##_dummy, PROG_TMX128, stb_active_stateX128	\n 

#define write_optrimming_bitsX32(labelname,addr)						\
	stb_set_all(0x59,addr,USE_foreign,USE_foreign,dummy_stateX32)	\n	\
	set_counter(EBM_COUNTER,0x1f,dummy_stateX32)					\n	\
	stb_send_command(labelname,stb_active_stateX32)					\n	\
	stb_send_address(labelname,stb_active_stateX32)					\n	\
	send_EBM_data(labelname,stb_active_stateX32,PS_STB_DIN)			\n	\
	cycle_delay(labelname##_dummy, 0x8, stb_active_stateX32)		\n		//ebm_send_ebmdata//10us

#define write_optrimming_bitsX128(labelname,addr)						\
	stb_set_all(0x59,addr,USE_foreign,USE_foreign,dummy_stateX128)	\n	\
	set_counter(EBM_COUNTER,0x1f,dummy_stateX128)					\n	\
	stb_send_command(labelname,stb_active_stateX128)				\n	\
	stb_send_address(labelname,stb_active_stateX128)				\n	\
	cycle_delay(labelname##dummy_code,0x5e,stb_active_stateX128)				\n	\
	send_EBM_data(labelname,stb_active_stateX128,PS_STB_DIN)		\n	\
	cycle_delay(labelname##_dummy, 0x8, stb_active_stateX128)		\n	

//ebm_send_ebmdata//10us
/***************************************************
Macro name: serial_test_mode_entry
Usage:serial_test_mode_entry(labelname)
Action:make chips enter into serial test mode
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
label_name: used for incide loop,  pay attention not to be repeated
//stb_set_data(0x2015, 0x0302)
stb_set_data(0x04A8, 0xC040)
****************************************************/
#define serial_test_mode_entryX32(labelname)					\
stb_set_data(0x2015, 0x0302,dummy_stateX32)					\n	\
stb_send_data(labelname,stb_active_stateX32)				\n	\
cycle_delay(label_name##_dummy,0x1000,stb_active_stateX32)	\n	

#define serial_test_mode_entryX128(labelname)					\
stb_set_data(0x2015, 0x0302,dummy_stateX128)				\n	\
stb_send_data(labelname,stb_active_stateX128)				\n	\
cycle_delay(label_name##_dummy,0x1000,stb_active_stateX128)	\n	
/***************************************************
Macro name: read_register_32bit
Usage:read_register_32bit(labelname,addr,Hdat,Ldat)
Action:used for sending read register command in 32 data bits chips
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
label_name: used for incide loop,  pay attention not to be repeated
adr:  Plz input address here and in Hex
Hdat: Plz input MSB of dasta, ensure not to be more than 18 bits
Ldat: Plz input LSB of data, ensure not to be more than 18 bits
****************************************************/
#define read_registerX32(labelname,addr,Hdat,Ldat)				\
stb_set_all(0x01, addr, Hdat, Ldat,dummy_stateX32)			\n	\
stb_send_command(labelname,stb_active_stateX32)				\n	\
stb_send_address(labelname,stb_active_stateX32)				\n	\
E2_stb_read_data(labelname,read_stateX32)					\n

#define read_register_formX32(labelname,addr,Hdat,Ldat)			\
stb_set_command(0x01,dummy_stateX32)						\n	\
stb_set_data(Hdat,Ldat,dummy_stateX32)						\n	\
stb_send_command(labelname,stb_active_stateX32)				\n	\
stb_send_address(labelname,stb_active_stateX32)				\n	\
E2_stb_read_data(labelname,read_stateX32)					\n

#define read_registerX128(labelname,addr,Hdat4,Ldat4,Hdat3,Ldat3,Hdat2,Ldat2,Hdat1,Ldat1)			\
stb_set_all(0x01, addr, Hdat4, Ldat4, dummy_stateX128)							\n	\
stb_send_command(labelname,stb_active_stateX128)								\n	\
stb_send_address(labelname,stb_active_stateX128)								\n	\
cycle_delay(labelname##_dummy, 0x6, stb_active_stateX128)						\n	\
E1_stb_read_data(labelname##4,read_stateX128)									\n	\
set_blank_data(Hdat3,Ldat3,blank_stateX128)										\n	\
E1_stb_read_data(labelname##3,read_stateX128)									\n	\
set_blank_data(Hdat2,Ldat2,blank_stateX128)										\n	\
E1_stb_read_data(labelname##2,read_stateX128)									\n	\
set_blank_data(Hdat1,Ldat1,blank_stateX128)										\n	\
E1_stb_read_data(labelname##1,read_stateX128)									\n

#define read_register_formX128(labelname,Hdat4,Ldat4,Hdat3,Ldat3,Hdat2,Ldat2,Hdat1,Ldat1)			\
stb_set_command(0x01,dummy_stateX128)															\n	\
stb_set_data(Hdat4,Ldat4,dummy_stateX128)														\n	\
stb_send_command(labelname,stb_active_stateX128)												\n	\
stb_send_address(labelname,stb_active_stateX128)												\n	\
cycle_delay(labelname##_dummy, 0x6, stb_active_stateX128)										\n	\
E1_stb_read_data(labelname##4,read_stateX128)													\n	\
set_blank_data(Hdat3,Ldat3,blank_stateX128)														\n	\
E1_stb_read_data(labelname##3,read_stateX128)													\n	\
set_blank_data(Hdat2,Ldat2,blank_stateX128)														\n	\
E1_stb_read_data(labelname##2,read_stateX128)													\n	\
set_blank_data(Hdat1,Ldat1,blank_stateX128)														\n	\
E1_stb_read_data(labelname##1,read_stateX128)													\n	
/***************************************************
Macro name: read_flash_32bit
Usage:read_flash_32bit(labelname,addr,Hdat,Ldat)
Action:used for sending read flash command in 32 data bits chips
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
label_name: used for incide loop,  pay attention not to be repeated
xadr: Plz input x address here and in Hex
yadr: Plz input y address here and in Hex
Hdat: Plz input MSB of data, ensure not to be more than 18 bits
Ldat: Plz input LSB of data, ensure not to be more than 18 bits
****************************************************/
#define read_flashX32(labelname,addr,Hdat,Ldat)					\
stb_set_all(0x02, addr, Hdat, Ldat, dummy_stateX32)				\n	\
stb_send_command(labelname,stb_active_stateX32)					\n	\
stb_send_address(labelname,stb_active_stateX32)					\n	\
cycle_delay(labelname##_dummy, 0x7, stb_active_stateX32)		\n	\
E2_stb_read_data(labelname,read_stateX32)						\n	

#define read_flash_formX32(labelname,Hdat,Ldat)					\
stb_set_command(0x02,dummy_stateX32)							\n	\
stb_set_data(Hdat,Ldat,dummy_stateX32)							\n	\
stb_send_command(labelname,stb_active_stateX32)					\n	\
stb_send_address(labelname,stb_active_stateX32)					\n	\
cycle_delay(labelname##_dummy, 0x7, stb_active_stateX32)		\n	\
E2_stb_read_data(labelname,read_stateX32)						\n

#define read_flashX128(labelname,addr,Hdat4,Ldat4,Hdat3,Ldat3,Hdat2,Ldat2,Hdat1,Ldat1)			\
stb_set_all(0x02, addr, Hdat4, Ldat4, dummy_stateX128)							\n	\
stb_send_command(labelname,stb_active_stateX128)								\n	\
stb_send_address(labelname,stb_active_stateX128)								\n	\
cycle_delay(labelname##_dummy, 0x7, stb_active_stateX128)						\n	\
E1_stb_read_data(labelname##4,read_stateX128)									\n	\
set_blank_data(Hdat3,Ldat3,blank_stateX128)										\n	\
E1_stb_read_data(labelname##3,read_stateX128)									\n	\
set_blank_data(Hdat2,Ldat2,blank_stateX128)										\n	\
E1_stb_read_data(labelname##2,read_stateX128)									\n	\
set_blank_data(Hdat1,Ldat1,blank_stateX128)										\n	\
E1_stb_read_data(labelname##1,read_stateX128)									\n	

#define read_flash_formX128(labelname,Hdat4,Ldat4,Hdat3,Ldat3,Hdat2,Ldat2,Hdat1,Ldat1)	\
stb_set_command(0x02,dummy_stateX128)												\n	\
stb_set_data(Hdat4,Ldat4,dummy_stateX128)											\n	\
stb_send_command(labelname,stb_active_stateX128)									\n	\
stb_send_address(labelname,stb_active_stateX128)									\n	\
cycle_delay(labelname##_dummy, 0x7, stb_active_stateX128)							\n	\
E1_stb_read_data(labelname##4,read_stateX128)										\n	\
set_blank_data(Hdat3,Ldat3,blank_stateX128)											\n	\
E1_stb_read_data(labelname##3,read_stateX128)										\n	\
set_blank_data(Hdat2,Ldat2,blank_stateX128)											\n	\
E1_stb_read_data(labelname##2,read_stateX128)										\n	\
set_blank_data(Hdat1,Ldat1,blank_stateX128)											\n	\
E1_stb_read_data(labelname##1,read_stateX128)										\n	

#define read_optrimming_bitsX32(labelname,addr,PS)								\
	stb_set_all(0x02, addr, USE_foreign, USE_foreign, dummy_stateX32)	\n	\
	set_counter(EBM_COUNTER,0x1f,dummy_stateX32)						\n	\
	stb_send_command(labelname,stb_active_stateX32)						\n	\
	stb_send_address(labelname,stb_active_stateX32)						\n	\
	cycle_delay(labelname##_dummy, 0x7, stb_active_stateX32)			\n	\
	compare_with_EBM_data(labelname,read_stateX32,PS)						\n	

#define read_optrimming_bitsX128(labelname,addr,PS)						\
stb_set_all(0x02, addr, 0x0, 0x0, dummy_stateX128)					\n	\
set_counter(EBM_COUNTER,0x1f,dummy_stateX32)						\n	\
stb_send_command(labelname,stb_active_stateX128)					\n	\
stb_send_address(labelname,stb_active_stateX128)					\n	\
cycle_delay(labelname##_dummy, 0x7, stb_active_stateX128)			\n	\
E1_stb_read_data(labelname##4,read_stateX128)						\n	\
set_blank_data(0x0,0x0,blank_stateX128)								\n	\
E1_stb_read_data(labelname##3,read_stateX128)						\n	\
set_blank_data(0x0,0x0,blank_stateX128)								\n	\
E1_stb_read_data(labelname##2,read_stateX128)						\n	\
compare_with_EBM_data(labelname,read_stateX128,PS)						\n	
/***************************************************
Macro name: program_32bit
Usage:program_32bit(labelname,addr,Hdat,Ldat)
Action:used for sending program command in 32 data bits chips
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
label_name: used for incide loop,  pay attention not to be repeated
addr: Plz input address here and in Hex
Hdat: Plz input MSB of data, ensure not to be more than 18 bits
Ldat: Plz input LSB of data, ensure not to be more than 18 bits
****************************************************/
#define programX32(labelname,addr,Hdat,Ldat)					\
stb_set_all(0x11, addr, Hdat, Ldat,dummy_stateX32)			\n	\
stb_send_command(labelname,stb_active_stateX32)				\n	\
stb_send_address(labelname,stb_active_stateX32)				\n	\
stb_send_data(labelname,stb_active_stateX32)				\n	\
cycle_delay(labelname##_dummy, PROG_TMX32, stb_active_stateX32)	\n       

#define program_formX32(labelname,Hdat,Ldat)					\
stb_set_command(0x11,dummy_stateX32)							\n	\
stb_set_data(Hdat,Ldat,dummy_stateX32)							\n	\
stb_send_command(labelname,stb_active_stateX32)					\n	\
stb_send_address(labelname,stb_active_stateX32)					\n	\
stb_send_data(labelname,stb_active_stateX32)					\n	\
cycle_delay(labelname##_dummy, PROG_TMX32, stb_active_stateX32)		\n 

#define programX128(labelname,addr,Hdat4,Ldat4,Hdat3,Ldat3,Hdat2,Ldat2,Hdat1,Ldat1)			\
stb_set_all(0x11, addr, Hdat4, Ldat4,dummy_stateX128)			\n	\
stb_send_command(labelname,stb_active_stateX128)				\n	\
stb_send_address(labelname,stb_active_stateX128)				\n	\
stb_send_data(labelname##4,stb_active_stateX128)				\n	\
set_blank_data(Hdat3,Ldat3,blank_stateX128)						\n	\
stb_send_data(labelname##3,stb_active_stateX128)				\n	\
set_blank_data(Hdat2,Ldat2,blank_stateX128)						\n	\
stb_send_data(labelname##2,stb_active_stateX128)				\n	\
set_blank_data(Hdat1,Ldat1,blank_stateX128)						\n	\
stb_send_data(labelname##1,stb_active_stateX128)				\n	\
cycle_delay(labelname##_dummy, PROG_TMX128, stb_active_stateX128)		\n

#define program_formX128(labelname,Hdat4,Ldat4,Hdat3,Ldat3,Hdat2,Ldat2,Hdat1,Ldat1)			\
stb_set_command(0x11,dummy_stateX128)											\n	\
stb_set_data(Hdat4,Ldat4,dummy_stateX128)										\n	\
stb_send_command(labelname,stb_active_stateX128)				\n	\
stb_send_address(labelname,stb_active_stateX128)				\n	\
stb_send_data(labelname##4,stb_active_stateX128)				\n	\
set_blank_data(Hdat3,Ldat3,blank_stateX128)						\n	\
stb_send_data(labelname##3,stb_active_stateX128)				\n	\
set_blank_data(Hdat2,Ldat2,blank_stateX128)						\n	\
stb_send_data(labelname##2,stb_active_stateX128)				\n	\
set_blank_data(Hdat1,Ldat1,blank_stateX128)						\n	\
stb_send_data(labelname##1,stb_active_stateX128)				\n	\
cycle_delay(labelname##_dummy, PROG_TMX128, stb_active_stateX128)		\n

/***************************
Macro: program_trim_code
***************************/
#define program_trim_codeX32(labelname,addr,PS)						\
stb_set_all(0x11, addr, USE_foreign, USE_foreign,dummy_stateX32)\n	\
set_counter(EBM_COUNTER,0x1f,dummy_stateX32)					\n	\
stb_send_command(labelname,stb_active_stateX32)					\n	\
stb_send_address(labelname,stb_active_stateX32)					\n	\
send_EBM_data(labelname,stb_active_stateX32,PS)					\n	\
cycle_delay(labelname##_dummy, PROG_TMX32, stb_active_stateX32)		\n   

#define program_trim_codeX128(labelname,addr,PS)						\
stb_set_all(0x11, addr, 0x0, 0x0,dummy_stateX128)			\n	\
set_counter(EBM_COUNTER,0x1f,dummy_stateX128)					\n	\
stb_send_command(labelname,stb_active_stateX128)				\n	\
stb_send_address(labelname,stb_active_stateX128)				\n	\
stb_send_data(labelname##4,stb_active_stateX128)				\n	\
set_blank_data(0x0,0x0,blank_stateX128)						\n	\
stb_send_data(labelnam##3,stb_active_stateX128)				\n	\
set_blank_data(0x0,0x0,blank_stateX128)						\n	\
stb_send_data(labelname##2,stb_active_stateX128)				\n	\
send_EBM_data(labelname,stb_active_stateX128,PS)					\n	\
cycle_delay(labelname##_dummy, PROG_TMX128, stb_active_stateX128)		\n
/***************************************************
Macro name: sector_erase
Usage:sector_erase(labelname,addr)
Action:used for sector erase command in 32 data bits chips
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
label_name: used for incide loop,  pay attention not to be repeated
addr: Plz input  address here and in Hex
****************************************************/
#define sector_eraseX32(labelname,addr)							\
stb_set_all(0x15, addr, 0x0, 0x0,dummy_stateX32)			\n	\
stb_send_command(labelname,stb_active_stateX32)				\n	\
stb_send_address(labelname,stb_active_stateX32)				\n	\
cycle_delay(labelname##_dummy, 0x9C3E, stb_active_stateX32)	\n		

#define sector_erase_formX32(labelname)							\
stb_set_command(0x15,dummy_stateX32)						\n	\
stb_send_command(labelname,stb_active_stateX32)				\n	\
stb_send_address(labelname,stb_active_stateX32)				\n	\
cycle_delay(labelname##_dummy, 0x9C3E, stb_active_stateX32)	\n

#define sector_eraseX128(labelname,addr)							\
stb_set_all(0x15, addr, 0x0, 0x0,dummy_stateX128)				\n	\
stb_send_command(labelname,stb_active_stateX128)				\n	\
stb_send_address(labelname,stb_active_stateX128)				\n	\
cycle_delay(labelname##_dummy, 0x9C3E, stb_active_stateX128)	\n	

#define sector_erase_formX128(labelname)							\
stb_set_command(0x15,dummy_stateX128)							\n	\
stb_send_command(labelname,stb_active_stateX128)				\n	\
stb_send_address(labelname,stb_active_stateX128)				\n	\
cycle_delay(labelname##_dummy, 0x9C3E, stb_active_stateX128)	\n
/***************************************************
Macro name: chip_erase
Usage:chip_erase(labelname,addr)
Action:used for chip erase command in 32 data bits chips
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
label_name: used for incide loop,  pay attention not to be repeated
xadr: Plz input x address here and in Hex
yadr: Plz input y address here and in Hex
****************************************************/
#define chip_eraseX32(labelname,addr)							\
stb_set_all(0x16, addr, 0x0, 0x0,dummy_stateX32)			\n	\
stb_send_command(labelname,stb_active_stateX32)				\n	\
stb_send_address(labelname,stb_active_stateX32)				\n	\
cycle_delay(labelname##_dummy, 0x30D3E, stb_active_stateX32)\n	

#define chip_eraseX128(labelname,addr)							\
stb_set_all(0x16, addr, 0x0, 0x0,dummy_stateX128)			\n	\
stb_send_command(labelname,stb_active_stateX128)				\n	\
stb_send_address(labelname,stb_active_stateX128)				\n	\
cycle_delay(labelname##_dummy, 0x30D3E, stb_active_stateX128)\n

/***************************************************
Macro name: exit_test_mode
Usage:exit_test_mode(labelname)
Action:make chips exist serial test mode
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
label_name: used for incide loop,  pay attention not to be repeated
****************************************************/
#define exit_test_modeX32(labelname)								\
stb_set_command(0xB1,dummy_stateX32)							\n	\
stb_send_command(labelname##_1,stb_active_stateX32)				\n	\
cycle_delay(labelname##_config1,0x6,stb_active_stateX32)		\n	\
cycle_delay(labelname##_dummy,0x62, stb_active_stateX32)		\n	\
stb_set_command(0xC1,dummy_stateX32)							\n	\
stb_send_command(labelname##_2,stb_active_stateX32)				\n	\
cycle_delay(labelname##_config2, 0x6, stb_active_stateX32)		\n		

#define exit_test_modeX128(labelname)								\
stb_set_command(0xB1,dummy_stateX128)							\n	\
stb_send_command(labelname##_1,stb_active_stateX128)				\n	\
cycle_delay(labelname##_config1,0x6,stb_active_stateX128)		\n	\
cycle_delay(labelname##_dummy,0x62, stb_active_stateX128)		\n	\
stb_set_command(0xC1,dummy_stateX128)							\n	\
stb_send_command(labelname##_2,stb_active_stateX128)				\n	\
cycle_delay(labelname##_config2, 0x6, stb_active_stateX128)		\n	

/***************************************************
Macro name: external_chip_erase
Usage:external_chip_erase(labelname,addr)
Action:make chips exist serial test mode
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
label_name: used for incide loop,  pay attention not to be repeated
****************************************************/
#define external_chip_eraseX32(labelname,addr)						\
	stb_set_command(0xa7,dummy_stateX32)						\n	\
	stb_set_address(addr,dummy_stateX32)						\n	\
	stb_send_command(labelname,stb_active_stateX32)				\n	\
	stb_send_address(labelname,stb_active_stateX32)				\n	\
	cycle_delay(labelname##_TMC,0X6,stb_active_stateX32)		\n	\
	cycle_delay(labelname##_dummy,0x30D3E,stb_active_stateX32)	\n

#define external_chip_eraseX128(labelname,addr)						\
	stb_set_command(0xa7,dummy_stateX128)						\n	\
	stb_set_address(addr,dummy_stateX128)						\n	\
	stb_send_command(labelname,stb_active_stateX128)			\n	\
	stb_send_address(labelname,stb_active_stateX128)			\n	\
	cycle_delay(labelname##_TMC,0X6,stb_active_stateX128)		\n	\
	cycle_delay(labelname##_dummy,0x30D3E,stb_active_stateX128)	\n

#define external_sector_eraseX32(labelname,addr)					\
	stb_set_command(0xa6,dummy_stateX32)						\n	\
	stb_set_address(addr,dummy_stateX32)						\n	\
	stb_send_command(labelname,stb_active_stateX32)				\n	\
	stb_send_address(labelname,stb_active_stateX32)				\n	\
	cycle_delay(labelname##_TMC,0X6,stb_active_stateX32)		\n	\
	cycle_delay(labelname##_delay,0x30D3E, stb_active_stateX32)	\n

#define external_sector_eraseX128(labelname,addr)					\
	stb_set_command(0xa6,dummy_stateX128)						\n	\
	stb_set_address(addr,dummy_stateX128)						\n	\
	stb_send_command(labelname,stb_active_stateX128)			\n	\
	stb_send_address(labelname,stb_active_stateX128)			\n	\
	cycle_delay(labelname##_TMC,0X6,stb_active_stateX128)		\n	\
	cycle_delay(labelname##_delay,0x30D3E, stb_active_stateX128)\n

#define external_programX32(labelname,addr,datah,datal)			\
	stb_set_all(0xA5,addr,datah,datal,dummy_stateX32)			\n	\
	stb_send_command(labelname,stb_active_stateX32)				\n	\
	stb_send_address(labelname,stb_active_stateX32)				\n	\
	stb_send_data(labelname,stb_active_stateX32)				\n	\
	cycle_delay(labelname##_TMC,0x6,stb_active_stateX32)		\n	\
	cycle_delay(labelname##_dummy, PROG_TMX32, stb_active_stateX32)	\n	

#define external_programX128(labelname,addr,datah,datal)			\
	stb_set_all(0xA5,addr,datah,datal,dummy_stateX128)			\n	\
	stb_send_command(labelname,stb_active_stateX128)				\n	\
	stb_send_address(labelname,stb_active_stateX128)				\n	\
	stb_send_data(labelname,stb_active_stateX128)				\n	\
	cycle_delay(labelname##_TMC,0x6,stb_active_stateX128)		\n	\
	cycle_delay(labelname##_dummy, PROG_TMX128, stb_active_stateX128)	\n	

#define spi_write_allX32(labelname, address, data)							\
	spi_input_setup(address, data,dummy_stateX32,spi_active_stateX32)	\n	\
	spi_send_address(labelnameX32,spi_active_stateX32)					\n	\
	spi_send_data(labelname,spi_active_stateX32)						\n	

#define spi_read_allX32(labelname, address, data)							\
	spi_output_setup(address,data,dummy_stateX32,spi_active_stateX32)	\n	\
	spi_send_address(labelname,spi_active_stateX32)						\n	\
	spi_send_data(labelname,spi_active_stateX32)						\n 



#endif