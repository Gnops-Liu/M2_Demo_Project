#include "pat_macro.h"
//subroutine layer
PATTERN(SUB_GPIB5_send_A_Byte)
%	GPIB5_send_bit(6)
%	GPIB5_send_bit(5)
%	GPIB5_send_bit(4)
%	GPIB5_send_bit(3)
%	GPIB5_send_bit(2)
%	GPIB5_send_bit(1)
%	GPIB5_send_bit(0)
	mar return
%mar done
pinfunc adhiz

PATTERN(SUB_GPIB5_read_A_Byte)
%	GPIB5_read_bit(6)
	mar read
%	GPIB5_read_bit(5)
	mar read
%	GPIB5_read_bit(4)
	mar read
%	GPIB5_read_bit(3)
	mar read
%	GPIB5_read_bit(2)
	mar read
%	GPIB5_read_bit(1)
	mar read
%	GPIB5_read_bit(0)
	mar return, read




PATTERN(SUB_WaitFor_CRC)
@{
	dmain(0);
@}
%label1:
	DATGEN	DATDAT
	UDATA	0x0
	PINFUNC	tset1,PS_GPIB5_D0,ADHIZ
	count	CRC_Count,decr,aoff
	MAR		cjmpe, label2, READUDATA, reset
%	DATGEN	DATDAT
	UDATA	0x0
	count	CRC_Count,decr,aoff
	PINFUNC	tset1,PS_GPIB5_D0,ADHIZ
	MAR		cjmpnz, label1, READUDATA
%label2:
	read_CRC_bit(0)
%	read_CRC_bit(1)
%	read_CRC_bit(2)
%	read_CRC_bit(3)
%	read_CRC_bit(4)
%	read_CRC_bit(5)
%	read_CRC_bit(6)
%	read_CRC_bit(7)
%	mar return 


PATTERN(SUB_read_CRC)//description layer
%	read_CRC_bit(6)
	mar read
%	read_CRC_bit(5)
	mar read
%	read_CRC_bit(4)
	mar read
%	read_CRC_bit(3)
	mar read
%	read_CRC_bit(2)
	mar read
%	read_CRC_bit(1)
	mar read
%	read_CRC_bit(0)
	mar return,read
