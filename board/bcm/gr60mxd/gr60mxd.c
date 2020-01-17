#include <common.h>
#include <asm/global_data.h>
#include <asm/arch/mx6-pins.h>
#include <asm/arch/sys_proto.h>

DECLARE_GLOBAL_DATA_PTR;

int dram_init(void)
{
    gd->ram_size = imx_ddr_size();
    return 0;
}

int board_init(void)
{
    return 0;
}
