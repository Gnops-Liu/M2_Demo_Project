//pin scrambles
#define PS_GPIB5_D0 PS8
#define PS_GPIB5_D1 PS1
#define PS_GPIB5_D2 PS2
#define PS_GPIB5_D3 PS3
#define PS_GPIB5_D4 PS4
#define PS_GPIB5_D5 PS5
#define PS_GPIB5_D6 PS6
#define PS_GPIB5_D7 PS7
#define PS_NONE		PS1
//count
#define CRC_Count count10
//under subroutine layer
#define GPIB5_send_bit(num)				\n \
 datgen		mainmain					\n \
 pinfunc	tset1, PS_GPIB5_D##num		\n \
 chips		cs1pt						\n

#define GPIB5_read_bit(num)				\n \
 datgen		mainmain					\n \
 pinfunc	tset1, PS_GPIB5_D##num,adhiz\n \
 chips		cs1pt						\n \

#define read_CRC_bit(num)				\n \
 datgen		basebase					\n \
 pinfunc    tset1, PS_GPIB5_D##num,adhiz\n \
 chips		cs1pt						\n 


//description layer
#define spi_send_A_Byte(data)						  \n \
%datgen		sudata, dmain, udatadr, mainmain		  \n \
 pinfunc	tset1, PS_GPIB5_D7						  \n \
 udata		data									  \n \
 chips		cs1pt									  \n \
 mar		gosub, SUB_GPIB5_send_A_Byte			  \n 

#define spi_read_A_Byte(data)						  \n \
%datgen		sudata, dmain, udatadr, mainmain		  \n \
 pinfunc	tset1, PS_GPIB5_D7,adhiz				  \n \
 udata		data									  \n \
 chips		cs1pt									  \n \
 mar		gosub, SUB_GPIB5_read_A_Byte,read		  \n 

#define CRC_read(CRC, cycle)					\n \
%pinfunc	tset1, PS_NONE						\n \
 chips		cs1pt								\n \
 count		CRC_Count,countudata				\n \
 udata		cycle								\n \
%pinfunc	tset1, PS_NONE						\n \
 chips		cs1pt								\n \
 datgen		sudata, dbase, udatadr				\n \
 udata		CRC									\n \
 mar		gosub, SUB_WaitFor_CRC				\n 
 
#define CRC_short_read(CRC)						\n \
%pinfunc	tset1, PS_GPIB5_D7,ADHIZ			\n \
 chips		cs1pt								\n \
 datgen		sudata, dbase, udatadr,basebase		\n \
 udata		CRC									\n \
 mar		gosub, SUB_read_CRC,read			\n  



//encapsulation layer
#define wirte_2CBit(ee,C1,C2,CRC,cycle)	\n \
	spi_send_A_Byte(ee)					\n \
	spi_send_A_Byte(C1)					\n \
	spi_send_A_Byte(C2)					\n \
	CRC_short_read(CRC)					\n 



#define Read_2DBit(ee,C1,C2,CRC1, en, D1, D2, CRC2)	   \n \
spi_send_A_Byte(ee)									   \n \
spi_send_A_Byte(C1)									   \n \
spi_send_A_Byte(C2)									   \n \
CRC_short_read(CRC1)								   \n \
													   \n \
spi_send_A_Byte(en)									   \n \
spi_read_A_Byte(D1)									   \n \
spi_read_A_Byte(D2)									   \n \
CRC_short_read(CRC2)								   \n 
