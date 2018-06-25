#include "tester.h"
// ********************************************
// ****  Pin Lists                        *****
// ********************************************

PINLIST(pl_io) {
	PINS6(GPIO0, GPIO1, GPIO2, GPIO3, GPIO4, GPIO5)
	PINS1(VDDH_IO)
}
PINLIST(pl_dps) {
	PINS4(VDD,VDDH,VDD_2P4V,VPP)
}
PINLIST(pl_hv) {
	PINS1(_TEST_)
}
PINLIST(pl_GPIB) {
	PINS6(GPIO0, GPIO1, GPIO2, GPIO3, GPIO4, GPIO5)
}

PINLIST(pl_GPIO0)	{ PINS1(GPIO0) }
PINLIST(pl_GPIO1)	{ PINS1(GPIO1) }
PINLIST(pl_GPIO2)	{ PINS1(GPIO2) }
PINLIST(pl_GPIO3)	{ PINS1(GPIO3) }
PINLIST(pl_GPIO4)	{ PINS1(GPIO4) }
PINLIST(pl_GPIO5)	{ PINS1(GPIO5) }
PINLIST(pl_VDDH_IO)	{ PINS1(VDDH_IO) }
PINLIST(pl_VDD)		{ PINS1(VDD) }
PINLIST(pl_VDDH)	{ PINS1(VDDH) }
PINLIST(pl_VDD_2P4V){ PINS1(VDD_2P4V) }
PINLIST(pl_VPP)		{ PINS1(VPP) }
PINLIST(pl__TEST_)	{ PINS1(_TEST_) }
