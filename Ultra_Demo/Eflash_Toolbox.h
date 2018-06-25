#ifndef EFLASH_TOOLBAX_H_
#define EFLASH_TOOLBAX_H_
#include "user_define.h"
/*******************Brief Introduction************************/
//Developer: Colin Liu
//Log:Version	|	Date		|	Description
//		V1.0	|	June.9	2017|	Foundational STB module Design
//		V1.1	|	June.16	2017|	Foundational SPI module Design
//		V1.2	|	June.30	2017|	Fixed after debug, function Verified
//		V1.3	|	July.6	2017|	Updated label, loop and link module
//		V2.0	|	JUly.21 2017|	Improve the tools, abandon the way to send address by ps, 
//				|				|	and control the data bit with address ALU
/*************************************************************/
//Developed Area



#define address_shifter(labelname,gap,state)		\
%	pinfunc	tset1,PS_DEF						\n	\
	chips	state								\n	\
	count	count60,countudata					\n	\
	udata	gap									\n	\
%	USERRAM	SET,URAM2,COUNT						\n	\
	count	count60								\n	\
	pinfunc	tset1,PS_DEF						\n	\
	chips	state								\n	\
cycle_delay(labelname##_delay1,0x4,state)		\n	\
%	USERRAM		Mod,Uram1,ADD,URAM2				\n	\
	pinfunc	    tset1,PS_DEF					\n	\
	chips		state							\n	\
cycle_delay(labelname##_delay2,0x4,state)		\n

#define X8_address_shifter(labelname,state)			\
%	pinfunc	tset1,PS_DEF						\n	\
	chips	state								\n	\
	count	count60,countudata					\n	\
	udata	0x08								\n	\
%	USERRAM	SET,URAM2,COUNT						\n	\
	count	count60								\n	\
	pinfunc	tset1,PS_DEF						\n	\
	chips	state								\n	\
cycle_delay(labelname##_delay1,0x4,state)		\n	\
%	USERRAM		Mod,Uram1,ADD,URAM2				\n	\
	pinfunc	    tset1,PS_DEF					\n	\
	chips		state							\n	\
cycle_delay(labelname##_delay2,0x4,state)		\n

#define X1_address_shifter(labelname,state)			\
%	pinfunc	tset1,PS_DEF						\n	\
	chips	state								\n	\
	count	count60,countudata					\n	\
	udata	0x01								\n	\
%	USERRAM	SET,URAM2,COUNT						\n	\
	count	count60								\n	\
	pinfunc	tset1,PS_DEF						\n	\
	chips	state								\n	\
cycle_delay(labelname##_delay1,0x4,state)		\n	\
%	USERRAM		Mod,Uram1,ADD,URAM2				\n	\
	pinfunc	    tset1,PS_DEF					\n	\
	chips		state							\n	\
cycle_delay(labelname##_delay2,0x4,state)		\n



#define usr_addr_loadin(labelname,state)			\
%	USERRAM		Set,Uram1,dmain2				\n	\
	pinfunc	    tset1,PS_DEF					\n	\
	chips		state							\n	\
cycle_delay(labelname##_delay1,0x4,state)		\n	

#define usr_addr_loadout(labelname,state)			\
%	USERRAM		Get,Uram1,dmain2				\n	\
	pinfunc	    tset1,PS_DEF					\n	\
	chips		state							\n	\
cycle_delay(labelname##_delay,0x0,state)		\n

#define ecr_addr_increment(state)								\
% xalu		xmain, xcare, con, increment, dxmain,oxmain		\n	\
yalu		ymain, xcare, cmeqmax, increment, dymain,oymain	\n	\
pinfunc		tset1, PS_DEF									\n	\
chips		state											\n
//EBM AREA
/****************************************************************
Macro name: send_EBM_data
Usage:send_EBM_data(labelname,state)
Action:Send the data which is saved in the EBM, and output from the
designed pin
Total cycle count:controlled by count12
Working state:
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
labelname:	used create a label for the inside loop
state:		The statement in which ebm is sended
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>WARNING<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Can not be used in the first three cycle of pattern
*****************************************************************/
#define send_EBM_data(labelname,state,PS)			\
%labelname##_EBM:							\n	\
	chips	state							\n	\
	count	EBM_COUNTER,decr,aon			\n  \
	pinfunc PS,EBM_PS1,tset1,ebm_enable,ebm_inc	\n	\
	mar		cjmpnz,labelname##_EBM			\n

#define compare_with_EBM_data(labelname,state,PS)					\
%labelname##_EBM:											\n	\
	chips	state											\n	\
	count	EBM_COUNTER,decr,aon							\n  \
	pinfunc PS,EBM_PS1,tset1,adhiz,ebm_enable,ebm_inc			\n	\
	mar		cjmpnz,labelname##_EBM,read						\n
/****************************************************************
Macro name: set_counter
Usage:set_counter(count,num,state)
Action:Set the content of the count you want
Total cycle count:1
Working state: dummy state
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
count: The count you want to modified
num: the content you want to save in the count
*****************************************************************/
#define set_counter(counter,num,state)			\
%	pinfunc	tset1, PS_DEF					\n	\
	chips	state							\n	\
	count	counter, countudata				\n	\
	udata	num								\n	

//LOOP AND JUMP
/****************************************************************
Macro name: loop_start
Usage:loop_start(loop_name,counter,num_subtract_1)
Action:make a new loop
Total cycle count:2
Working state: dummy_state
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
loop_name: used create a label for the loop
counter:select the count which is used to control the loop
num_subtract_1:input the number of loop remember -1
*****************************************************************/
#define loop_start(loop_name,counter,num_subtract_1,state)		\
%	pinfunc	tset1, PS_DEF									\n	\
	chips	state											\n	\
	count	counter, countudata								\n	\
	udata	num_subtract_1									\n	\
%loop_name##:												\n	\
	pinfunc tset1, PS_DEF									\n	\
	chips	state											\n	\
	mar		inc												\n

/****************************************************************
Macro name: loop_end
Usage:loop_end(loop_name,counter)
Action:loop's end, have two action, jump back to the loop label
or just jump out
Total cycle count:1
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
loop_name: used create a label for the loop
counter:select the count which is used to control the loop
num_subtract_1:input the number of loop£¬ remember -1
*****************************************************************/
#define loop_end(loop_name,counter,state)		\
%	chips		state						\n	\
	pinfunc		tset1, PS_DEF				\n	\
	count		counter, decr, aoff			\n	\
	mar			cjmpnz, loop_name			\n

/****************************************************************
Macro name: label
Usage:label(labelname)
Action:make a new label
Total cycle count:1
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
labelname: used create a label,for other place jump
>>>>>>>>>>>>>>>>>>>Improve action<<<<<<<<<<<<<<<<<<<
programer can use count,mar,datgen,xalu,yalu follow this macro
,To improve the function of this cycle
*****************************************************************/
#define label(labelname,state)		\
%labelname:						\n	\
	pinfunc tset1, PS_DEF		\n	\
	chips	state				\n

/***************************************************
Macro name: just_jump_to
Usage:just_jump_to(labelname,condition)
Action:jump to the label or pattern according to the
jump condition, affected only by count9
Total cycle count:1
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
labelname:	which pattern or label you wanna jump
counter: which counter you are using to control the jump function
condition:	The condition that this macro can take effect.
SEE mar instruction
>>>>>>>>>>>>>>>>>>>Improve action<<<<<<<<<<<<<<<<<<<
programer can use mar,datgen,xalu,yalu, improve
the function of this cycle
****************************************************/
#define just_jump_to(labelname,counter,condition,state)		\
%	mar		condition,labelname							\n	\
	count	counter										\n	\
	pinfunc tset1, PS_DEF								\n	\
	chips	state										\n 

//BASIC FUNCTION 

/***************************************************
Macro name: stb_set_all
Usage:stb_set_all(cmd,addr,dataH,dataL)
Action:All parameter setup at every begining of stb
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
keyin all parameter in hex
****************************************************/
#define stb_set_all(cmd,addr,datah, datal,state)		\
	stb_set_command(cmd,state)							\n	\
	stb_set_address(addr,state)							\n	\
	stb_set_data(datah,datal,state)					\n

/***********************************************************
Macro name: stb_set_command
Usage:stb_set_command(hexdata)
Action:save cmd data in dmain register
Total cycle count:1
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
cmd: please input the cmd in Hex as you want
************************************************************/
#define stb_set_command(cmd,state)				\
%	chips	state							\n	\
	pinfunc tset1, PS_DEF					\n	\
	DATGEN	sudata,dmain,udatadr			\n	\
	UDATA	cmd								\n

/***********************************************************
Macro name: stb_send_command
Usage:stb_send_command()
Action:get cmd data in dmain register and output
Total cycle count:count6+2
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
please use it after using stb_set_command or stb_set_all
label_name: used for incide loop, pay attention not to be repeated
***********************************************************/
#define stb_send_command(labelname,state)			\
%	chips	state								\n	\
	pinfunc tset1, PS_STB_CMD					\n	\
	DATGEN  mainmain							\n	\
%labelname##_cmd:								\n	\
	datgen	sdmain, dmain, SHLDR, mainmain		\n	\
	chips	state								\n	\
	pinfunc tset1, PS_STB_CMD					\n	\
	count	count6, decr, aon					\n	\
	mar		cjmpnz, labelname##_cmd				\n

/***************************************************
Macro name: stb_set_address
Usage:stb_send_address(hexdata)
Action:save address in dmain2
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
xaddr: X address in Hex
yaddr: Y address in Hex
***************************************************/
#define stb_set_address(addr,state)				    \
%	pinfunc		tset1, PS_DEF				\n	\
	chips		state						\n	\
	datgen		sudata,dmain2,udatadr		\n	\
	udata		addr						\n

/***************************************************
Macro name: stb_set_start_address
Usage:stb_send__start_address(hexdata)
Action:save address in dmain2
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
xaddr: X address in Hex
yaddr: Y address in Hex
***************************************************/
#define stb_set_start_address(addr,state)	    \
%	pinfunc		tset1, PS_DEF				\n	\
	chips		state						\n	\
	datgen		sudata,dmain2,udatadr		\n	\
	udata		addr						\n

/***********************************************************
Macro name: stb_send_address
Usage:stb_send_address(labelname)
Action:get address in dmain2 register and output
Total cycle count:count7+2
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
please use it after using stb_set_address or stb_set_all
label_name: used for incide loop, pay attention not to be repeated
***********************************************************/
#define stb_send_address(labelname,state)				\
%	chips	state									\n	\
	pinfunc tset1, PS_STB_ADDR						\n	\
	DATGEN  main2main2								\n	\
%labelname##_address:								\n	\
	datgen	sdmain2, dmain2, shldr,main2main2		\n	\
	chips	state									\n	\
	pinfunc tset1, PS_STB_ADDR						\n	\
	count	count7, decr, aon						\n	\
	mar		cjmpnz, labelname##_address				\n

/***************************************************
Macro name: stb_set_data
Usage:stb_set_data(hexdata)
Action:save data in dbase register
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
data: please input the data in Hex as you want
****************************************************/
#define stb_set_data(dataH,dataL,state)			\
%	chips	state							\n	\
	pinfunc tset1, PS_DEF					\n	\
	DATGEN	sudata, dbase2,udatadr			\n	\
	UDATA	dataL							\n	\
%	chips	state							\n	\
	pinfunc tset1, PS_DEF					\n	\
	DATGEN	sudata, dbase,udatadr			\n	\
	UDATA	dataH							\n	

#define set_blank_data(Hdata,Ldata,state)		\
%	chips	state							\n	\
	pinfunc tset1, PS_DEF					\n	\
	DATGEN	sudata, dbase2,udatadr			\n	\
	UDATA	Ldata							\n	\
%	chips	state							\n	\
	pinfunc tset1, PS_DEF					\n	\
	DATGEN	sudata, dbase,udatadr			\n	\
	UDATA	Hdata							\n	
/***************************************************
Macro name: stb_send_data
Usage:stb_send_data(labelname)
Action:get data in dbase register and output all on sio_in
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
please use it after using stb_set_data or set_all
label_name: used for incide loop,  pay attention not to be repeated
****************************************************/
#define stb_send_data(labelname,state)			\
%	chips	state							\n	\
	pinfunc tset1, PS_STB_DIN				\n	\
	DATGEN	basebase						\n	\
%labelname##_datal:							\n	\
	datgen	sdbase,dbase,SHLDR,basebase		\n	\
	chips	state							\n	\
	pinfunc tset1, PS_STB_DIN				\n	\
	count	count4, decr, aon				\n	\
	mar		cjmpnz, labelname##_datal		\n	\
%	chips	state							\n	\
	pinfunc tset1, PS_STB_DIN				\n	\
	DATGEN	base2base2						\n	\
%labelname##_datah:							\n	\
	datgen	sdbase2,dbase2,SHLDR,base2base2	\n	\
	chips	state							\n	\
	pinfunc tset1, PS_STB_DIN				\n	\
	count	count4, decr, aon				\n	\
	mar		cjmpnz, labelname##_datah		\n

/***********************************************************
Macro name: E1_stb_read_data
Usage:E1_stb_read_data()
Action:get data in dbase register and compared with
Eflash1 output
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
please use it after using stb_set_command or set_all
label_name: used for incide loop, pay attention not to be repeated
*************************************************************/
#define E1_stb_read_data(label_name,state)		\
%	chips	state							\n	\
	pinfunc tset1, PS_STB_DOUT1, adhiz		\n	\
	DATGEN	basebase						\n	\
	mar		inc, read						\n	\
%label_name##_datal:						\n	\
	datgen	sdbase,dbase,SHLDR,basebase		\n	\
	chips	state							\n	\
	pinfunc tset1, PS_STB_DOUT1, adhiz		\n	\
	count	count4, decr, aon				\n	\
	mar		cjmpnz, label_name##_datal, read\n	\
%	chips	state							\n	\
	pinfunc tset1, PS_STB_DOUT1, adhiz		\n	\
	DATGEN	base2base2						\n	\
	mar		inc, read						\n	\
%label_name##_datah:						\n	\
	datgen	sdbase2,dbase2,SHLDR,base2base2	\n	\
	chips	state							\n	\
	pinfunc tset1, PS_STB_DOUT1, adhiz		\n	\
	count	count4, decr, aon				\n	\
	mar		cjmpnz, label_name##_datah, read\n

/***************************************************
Macro name: E2_stb_read_data
Usage:E2_stb_read_data(label_name)
Action:get data in dbase register and compared with
Eflash2 output
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
please use it after using stb_set_command or set_all
label_name: used for incide loop, pay attention not to be repeated
****************************************************/
#define E2_stb_read_data(label_name,state)		\
%	chips	state							\n	\
	pinfunc tset1, PS_STB_DOUT2, adhiz		\n	\
	DATGEN	basebase						\n	\
	mar		inc, read						\n	\
%label_name##_datal:						\n	\
	datgen	sdbase,dbase,SHLDR,basebase		\n	\
	chips	state							\n	\
	pinfunc tset1, PS_STB_DOUT2, adhiz		\n	\
	count	count4, decr, aon				\n	\
	mar		cjmpnz, label_name##_datal, read\n	\
%	chips	state							\n	\
	pinfunc tset1, PS_STB_DOUT2, adhiz		\n	\
	DATGEN	base2base2						\n	\
	mar		inc, read						\n	\
%label_name##_datah:						\n	\
	datgen	sdbase2,dbase2,SHLDR,base2base2	\n	\
	chips	state							\n	\
	pinfunc tset1, PS_STB_DOUT2, adhiz		\n	\
	count	count4, decr, aon				\n	\
	mar		cjmpnz, label_name##_datah, read\n

/***********************************************************
Macro name: cycle_delay
Usage:		cycle_delay(labelname,hex_num, ps)
Action:		set the cycle number and state of delay
Total cycle count:count8 + 2
Limit:      3 -->(2^32 + 1)[cycle range]
1 -->(2^32 - 1)[input range]
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
label_name: used for incide loop, pay attention not to be repeated
num_substract_2 : please input [num(delay cycle) - 2] in hex
state :	please input chip select state which has been defined
*************************************************************/
#define cycle_delay(labelname,num_subtract_2, state)			\
%	pinfunc	tset1, PS_DEF									\n	\
	chips	state											\n	\
	count	count8, countudata								\n	\
	udata	num_subtract_2									\n	\
	mar		noread											\n	\
%labelname##_start:											\n	\
	pinfunc	tset1, PS_DEF									\n	\
	chips	state											\n	\
	count	count8, decr, aoff								\n	\
	mar		cjmpnz, labelname##_start,noread				\n

/***************************************************
Macro name: spi_set_address
Usage:spi_set_address(address)
Action:save spi address in dmain
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
keyin all parameter in hex
****************************************************/
#define spi_set_address(address,state)			\
%	chips	state							\n	\
	pinfunc tset1, PS_DEF					\n	\
	DATGEN	sudata,dmain,udatadr			\n	\
	UDATA	address							\n


/***************************************************
Macro name: spi_set_data
Usage:spi_set_data(data)
Action:send spi data in dbase
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
keyin all parameter in hex
****************************************************/
#define spi_set_data(data,state)				\
%	chips	state							\n	\
	pinfunc tset1, PS_DEF					\n	\
	DATGEN	sudata,dbase,udatadr			\n	\
	UDATA	data							\n

/***************************************************
Macro name: spi_input_setup
Usage:spi_input_setup(address,data)
Action:save spi address in dmain and save spi data in
dbase and initialize the spi transmission protocol
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
keyin all parameter in hex
****************************************************/
#define spi_input_setup(address, data,dummy_state,active_state)	\
	spi_set_address(address,dummy_state)					\n	\
	spi_set_data(data,dummy_state)							\n	\
%	chips	dummy_state										\n	\
	pinfunc	tset1, PS_DEF									\n	\
	DATGEN	sudata,dmain2,udatadr							\n	\
	UDATA	0x3												\n	\
%	chips	active_state									\n	\
	pinfunc tset1, PS_SPI_DIN								\n	\
	datgen	main2main2										\n	\
%	chips	active_state									\n	\
	datgen	sdmain2,dmain2,SHRDR,main2main2					\n	\
	pinfunc tset1, PS_SPI_DIN								\n

/***************************************************
Macro name: spi_output_setup
Usage:spi_output_setup(address,data)
Action:save spi address in dmain and save spi data in
dbase and initialize the spi transmission protocol
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
keyin all parameter in hex
****************************************************/
#define spi_output_setup(address, data,dummy_state,active_state)\
	spi_set_address(address,dummy_state)					\n	\
	spi_set_data(data,dummy_state)							\n	\
%	chips	dummy_state										\n	\
	pinfunc	tset1, PS_DEF									\n	\
	DATGEN	sudata,dmain2,udatadr							\n	\
	UDATA	0x0												\n	\
%	chips	active_state									\n	\
	datgen	main2main2										\n	\
	pinfunc tset1, PS_SPI_DIN								\n	\
%	chips	active_state									\n	\
	datgen	sdmain2,dmain2,SHRDR,main2main2					\n	\
	pinfunc tset1, PS_SPI_DIN								\n

/***************************************************
Macro name: spi_send_address
Usage:spi_send_address(labelname)
Action:get spi address in dmain and send to device
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
PLZ use it after spi_input(output)_setup or spi_set_address
label_name: used for incide loop, pay attention not to be repeated
****************************************************/
#define spi_send_address(labelname,state)			\
%	chips	state								\n	\
	pinfunc tset1, PS_SPI_DIN_ADDR				\n	\
	DATGEN  mainmain							\n	\
%labelname##_addr:								\n	\
	datgen	sdmain,dmain,SHLDR,mainmain			\n	\
	chips	state								\n	\
	pinfunc tset1, PS_SPI_DIN_ADDR				\n	\
	count	count2, decr, aon					\n	\
	mar		cjmpnz, labelname##_addr			\n

/***************************************************
Macro name: spi_send_data
Usage:spi_send_data(labelname)
Action:get spi data in dbase and send to device
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
PLZ use it after spi_set_data or spi_input_setup
label_name: used for incide loop, pay attention not to be repeated
****************************************************/
#define spi_send_data(labelname,state)			\
%	chips	state							\n	\
	pinfunc tset1, PS_SPI_DIN_DATA			\n	\
	DATGEN  basebase						\n	\
%labelname##_data:							\n	\
	datgen	sdbase, dbase, SHLDR, basebase	\n	\
	chips	state							\n	\
	pinfunc tset1, PS_SPI_DIN_DATA			\n	\
	count	count3, decr, aon				\n	\
	mar		cjmpnz, labelname##_data		\n

/***************************************************
Macro name: spi_read_data
Usage:spi_read_data(labelname)
Action:get spi data in dbase and compare with the spi_txd
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
PLZ use it after spi_set_data or spi_input_setup
label_name: used for incide loop, pay attention not to be repeated
****************************************************/
#define spi_read_data(labelname,state)			\
%	chips	state							\n	\
	pinfunc tset1, PS_SPI_DOUT_DATA, adhiz	\n	\
	DATGEN  basebase						\n	\
	mar		inc, read						\n	\
%labelname##_start:							\n	\
	datgen	basebase, SHLDR					\n	\
	chips	state							\n	\
	pinfunc tset1, PS_SPI_DOUT_DATA, adhiz	\n	\
	count	count3, decr, aon				\n	\
	mar		cjmpnz, labelname##_start, read	\n

/***********************************************************
Macro name: E1_stb_read_data
Usage:E1_stb_read_data()
Action:get data in dbase register and compared with
Eflash1 output
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
please use it after using stb_set_command or set_all
label_name: used for incide loop, pay attention not to be repeated
*************************************************************/
#define E1_stb_read_data_AIA(label_name,state)		\
%	xalu	xmain, xcare, con, increment, dxmain,oxmain		\n	\
	yalu	ymain, xcare, cmeqmax, increment, dymain,oymain	\n	\
	chips	state							\n	\
	pinfunc tset1, PS_STB_DOUT1, adhiz		\n	\
	DATGEN	basebase						\n	\
	mar		inc, read						\n	\
%label_name##_datal:						\n	\
	xalu	xmain, xcare, con, increment, dxmain,oxmain		\n	\
	yalu	ymain, xcare, cmeqmax, increment, dymain,oymain	\n	\
	datgen	sdbase,dbase,SHLDR,basebase		\n	\
	chips	state							\n	\
	pinfunc tset1, PS_STB_DOUT1, adhiz		\n	\
	count	count4, decr, aon				\n	\
	mar		cjmpnz, label_name##_datal, read\n	\
%	xalu	xmain, xcare, con, increment, dxmain,oxmain		\n	\
	yalu	ymain, xcare, cmeqmax, increment, dymain,oymain	\n	\
	chips	state							\n	\
	pinfunc tset1, PS_STB_DOUT1, adhiz		\n	\
	DATGEN	base2base2						\n	\
	mar		inc, read						\n	\
%label_name##_datah:						\n	\
	xalu	xmain, xcare, con, increment, dxmain,oxmain		\n	\
	yalu	ymain, xcare, cmeqmax, increment, dymain,oymain	\n	\
	datgen	sdbase2,dbase2,SHLDR,base2base2	\n	\
	chips	state							\n	\
	pinfunc tset1, PS_STB_DOUT1, adhiz		\n	\
	count	count4, decr, aon				\n	\
	mar		cjmpnz, label_name##_datah, read\n

/***************************************************
Macro name: E2_stb_read_data_AI
Usage:E2_stb_read_data(label_name)
Action:get data in dbase register and compared with
Eflash2 output
>>>>>>>>>>>>>>>>>>>>>>>>GUIDE<<<<<<<<<<<<<<<<<<<<<<<
please use it after using stb_set_command or set_all
label_name: used for incide loop, pay attention not to be repeated
****************************************************/
#define E2_stb_read_data_AIA(label_name,state)		\
%	xalu	xmain, xcare, con, increment, dxmain,oxmain		\n	\
	yalu	ymain, xcare, cmeqmax, increment, dymain,oymain	\n	\
	chips	state							\n	\
	pinfunc tset1, PS_STB_DOUT2, adhiz		\n	\
	DATGEN	basebase						\n	\
	mar		inc, read						\n	\
%label_name##_datal:						\n	\
	xalu	xmain, xcare, con, increment, dxmain,oxmain		\n	\
	yalu	ymain, xcare, cmeqmax, increment, dymain,oymain	\n	\
	datgen	sdbase,dbase,SHLDR,basebase		\n	\
	chips	state							\n	\
	pinfunc tset1, PS_STB_DOUT2, adhiz		\n	\
	count	count4, decr, aon				\n	\
	mar		cjmpnz, label_name##_datal, read\n	\
%	xalu	xmain, xcare, con, increment, dxmain,oxmain		\n	\
	yalu	ymain, xcare, cmeqmax, increment, dymain,oymain	\n	\
	chips	state							\n	\
	pinfunc tset1, PS_STB_DOUT2, adhiz		\n	\
	DATGEN	base2base2						\n	\
	mar		inc, read						\n	\
%label_name##_datah:						\n	\
	xalu	xmain, xcare, con, increment, dxmain,oxmain		\n	\
	yalu	ymain, xcare, cmeqmax, increment, dymain,oymain	\n	\
	datgen	sdbase2,dbase2,SHLDR,base2base2	\n	\
	chips	state							\n	\
	pinfunc tset1, PS_STB_DOUT2, adhiz		\n	\
	count	count4, decr, aon				\n	\
	mar		cjmpnz, label_name##_datah, read\n



#endif