
void power_down(void);
void vs_loose(void);
void vs_Hv(void);
void vs_Lv(void);

void ts_20_Mhz(void);

void analyze(void);

extern void ecr_addr_initialize();
extern void PointFailure_initialize(PointFailure *buffer, int length);

extern void EBM_setup_for_scan(long int* op_trim_reg, PinList* PL);
extern void EBM_setup_for_scan(long int* op_trim_reg, PinList* PL, DutNum dut);
extern void EBM_setup_for_save(long int* op_trim_reg, PinList* PL);
extern void EBM_save_address(long int EBM_register, PinList* PL);
extern void EBM_save_single_value(long int* reg_pointer, int length, PinList* PL);
extern void EBM_save_single_value(long int* reg_pointer, int length, PinList* PL, DutNum dut);
extern void ecr_set_for(PinList *pl);
extern void get_slaves_mask(SiteMask *mask);
