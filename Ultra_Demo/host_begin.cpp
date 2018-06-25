#include "tester.h"

HOST_BEGIN_BLOCK( my_host_block_name )
{
	Get_LotNum();
	output("%s Rev 1",remote_get("ui_TestProgName",-1));
}
