#include <common.h>
#include <asm/global_data.h>
#include <asm/arch/clock.h>
#include <asm/arch/mx6-pins.h>
#include <asm/arch/sys_proto.h>
#include <asm/gpio.h>
#include <mmc.h>
#include <fsl_esdhc_imx.h>

DECLARE_GLOBAL_DATA_PTR;

#define UART_PAD_CTRL (PAD_CTL_PUS_100K_UP |                   \
					   PAD_CTL_SPEED_MED | PAD_CTL_DSE_40ohm | \
					   PAD_CTL_SRE_FAST | PAD_CTL_HYS)

#define USDHC_PAD_CTRL (PAD_CTL_PUS_47K_UP |                    \
						PAD_CTL_SPEED_LOW | PAD_CTL_DSE_80ohm | \
						PAD_CTL_SRE_FAST | PAD_CTL_HYS)

/*Need more drive strength for SD1 slot on base board*/
#define USDHC1_PAD_CTRL (PAD_CTL_PKE | PAD_CTL_PUE |              \
						 PAD_CTL_PUS_47K_UP | PAD_CTL_SPEED_LOW | \
						 PAD_CTL_DSE_40ohm | PAD_CTL_SRE_FAST | PAD_CTL_HYS)

#define ENET_PAD_CTRL (PAD_CTL_PUS_100K_UP | \
					   PAD_CTL_SPEED_MED | PAD_CTL_DSE_40ohm | PAD_CTL_HYS)

#define OTG_ID_PAD_CTRL (PAD_CTL_PKE | PAD_CTL_PUE |              \
						 PAD_CTL_PUS_47K_UP | PAD_CTL_SPEED_LOW | \
						 PAD_CTL_DSE_80ohm | PAD_CTL_SRE_FAST | PAD_CTL_HYS)

#define LCD_RST IMX_GPIO_NR(2, 0)

static iomux_v3_cfg_t const uart4_pads[] = {
	MX6_PAD_KEY_COL0__UART4_TX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL),
	MX6_PAD_KEY_ROW0__UART4_RX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL),
};

iomux_v3_cfg_t const usdhc3_pads[] = {
	MX6_PAD_SD3_CLK__SD3_CLK | MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD3_CMD__SD3_CMD | MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD3_DAT0__SD3_DATA0 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD3_DAT1__SD3_DATA1 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD3_DAT2__SD3_DATA2 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD3_DAT3__SD3_DATA3 | MUX_PAD_CTRL(USDHC_PAD_CTRL),

	/*CD pin*/
	MX6_PAD_SD3_DAT5__GPIO7_IO00 | MUX_PAD_CTRL(NO_PAD_CTRL),
};

iomux_v3_cfg_t const usdhc4_pads[] = {
	MX6_PAD_SD4_CLK__SD4_CLK | MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD4_CMD__SD4_CMD | MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD4_DAT0__SD4_DATA0 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD4_DAT1__SD4_DATA1 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD4_DAT2__SD4_DATA2 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD4_DAT3__SD4_DATA3 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD4_DAT4__SD4_DATA4 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD4_DAT5__SD4_DATA5 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD4_DAT6__SD4_DATA6 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD4_DAT7__SD4_DATA7 | MUX_PAD_CTRL(USDHC_PAD_CTRL),
};

#ifdef CONFIG_FSL_ESDHC_IMX
#define USDHC3_CD_GPIO IMX_GPIO_NR(7, 0)

static struct fsl_esdhc_cfg usdhc_cfg[2] = {
	{USDHC3_BASE_ADDR},
	{USDHC4_BASE_ADDR},
};

int board_mmc_getcd(struct mmc *mmc)
{
	struct fsl_esdhc_cfg *cfg = (struct fsl_esdhc_cfg *)mmc->priv;

	switch (cfg->esdhc_base)
	{
	case USDHC3_BASE_ADDR:
		gpio_direction_input(USDHC3_CD_GPIO);
		return !gpio_get_value(USDHC3_CD_GPIO);
	case USDHC4_BASE_ADDR:
		return 1; /* eMMC/uSDHC4 is always present */
	default: 
		return 0;
	}
}

int board_mmc_init(bd_t *bis)
{
	int ret;
	u32 index = 0;

	usdhc_cfg[0].sdhc_clk = mxc_get_clock(MXC_ESDHC3_CLK);
	usdhc_cfg[1].sdhc_clk = mxc_get_clock(MXC_ESDHC4_CLK);

	usdhc_cfg[0].max_bus_width = 4;
	usdhc_cfg[1].max_bus_width = 4;

	for (index = 0; index < CONFIG_SYS_FSL_USDHC_NUM; ++index)
	{
		switch (index)
		{
		case 0:
			imx_iomux_v3_setup_multiple_pads(
				usdhc3_pads, ARRAY_SIZE(usdhc3_pads));
			break;
		case 1:
			imx_iomux_v3_setup_multiple_pads(
				usdhc4_pads, ARRAY_SIZE(usdhc4_pads));
			break;
		default:
			printf("Warning: you configured more USDHC controllers"
				   "(%d) then supported by the board (%d)\n",
				   index + 1, CONFIG_SYS_FSL_USDHC_NUM);
			return -EINVAL;
		}

		ret = fsl_esdhc_initialize(bis, &usdhc_cfg[index]);
		if (ret)
			return ret;
	}

	return 0;
}
#endif

int dram_init(void)
{
	gd->ram_size = imx_ddr_size();
	return 0;
}

int board_init(void)
{
	return 0;
}

static void setup_iomux_uart(void)
{
	imx_iomux_v3_setup_multiple_pads(uart4_pads, ARRAY_SIZE(uart4_pads));
}

int board_early_init_f(void)
{
	setup_iomux_uart();

	return 0;
}
