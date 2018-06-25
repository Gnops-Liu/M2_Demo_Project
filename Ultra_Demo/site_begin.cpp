#include "tester.h"

CONFIGURATION( tp_auto_flow )
{
	
}

SITE_BEGIN_BLOCK( sbb )
{
   	numy(10);
	numx(8);
	x_fast_axis(true);
	data_reg_width(36);
	cs_polarity_set(t_cs1, true);
	cs_polarity_set(t_cs2, true);
	cs_polarity_set(t_cs3, true);
	cs_polarity_set(t_cs4, true);
	cs_polarity_set(t_cs5, true);
	cs_polarity_set(t_cs6, true);
	cs_polarity_set(t_cs7, true);
	cs_polarity_set(t_cs8, true);
	dbm_config_set(numx(), numy(), 8);
	//ecr_config_set(numx(), numy(), pl_all_iopins);

	cs_active_high(t_cs1, t_cs2, t_cs5, t_cs6, t_cs7, t_cs8);

	
	//Do not touch following things
	CL_SiteBeginBlock();
	TB_Timer.Init();
	FlowTimer.Init();
}
