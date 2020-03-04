#include <common.h>
#include <asm/global_data.h>
#include <asm/arch/clock.h>
#include <asm/arch/crm_regs.h>
#include <asm/arch/mx6-pins.h>
#include <asm/arch/sys_proto.h>
#include <asm/mach-imx/iomux-v3.h>
#include <asm/mach-imx/boot_mode.h>
#include <asm/mach-imx/video.h>
#include <asm/gpio.h>
#include <mmc.h>
#include <fsl_esdhc_imx.h>

DECLARE_GLOBAL_DATA_PTR;

#define UART_PAD_CTRL (PAD_CTL_PUS_100K_UP |                   \
					   PAD_CTL_SPEED_MED | PAD_CTL_DSE_40ohm | \
					   PAD_CTL_SRE_FAST | PAD_CTL_HYS)

#define ENET_PAD_CTRL (PAD_CTL_PUS_100K_UP | \
					   PAD_CTL_SPEED_MED | PAD_CTL_DSE_40ohm | PAD_CTL_HYS)

#define OTG_ID_PAD_CTRL (PAD_CTL_PKE | PAD_CTL_PUE |              \
						 PAD_CTL_PUS_47K_UP | PAD_CTL_SPEED_LOW | \
						 PAD_CTL_DSE_80ohm | PAD_CTL_SRE_FAST | PAD_CTL_HYS)

#define RGB_PAD_CTRL 0x10

#define LCD_RST IMX_GPIO_NR(2, 0)

static iomux_v3_cfg_t const uart4_pads[] = {
	MX6_PAD_KEY_COL0__UART4_TX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL),
	MX6_PAD_KEY_ROW0__UART4_RX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL),
};

static iomux_v3_cfg_t const rgb_pads[] = {
	MX6_PAD_DI0_DISP_CLK__IPU1_DI0_DISP_CLK | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DI0_PIN15__IPU1_DI0_PIN15 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DI0_PIN2__IPU1_DI0_PIN02 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DI0_PIN3__IPU1_DI0_PIN03 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT0__IPU1_DISP0_DATA00 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT1__IPU1_DISP0_DATA01 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT2__IPU1_DISP0_DATA02 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT3__IPU1_DISP0_DATA03 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT4__IPU1_DISP0_DATA04 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT5__IPU1_DISP0_DATA05 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT6__IPU1_DISP0_DATA06 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT7__IPU1_DISP0_DATA07 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT8__IPU1_DISP0_DATA08 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT9__IPU1_DISP0_DATA09 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT10__IPU1_DISP0_DATA10 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT11__IPU1_DISP0_DATA11 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT12__IPU1_DISP0_DATA12 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT13__IPU1_DISP0_DATA13 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT14__IPU1_DISP0_DATA14 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT15__IPU1_DISP0_DATA15 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT16__IPU1_DISP0_DATA16 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT17__IPU1_DISP0_DATA17 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT18__IPU1_DISP0_DATA18 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT19__IPU1_DISP0_DATA19 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT20__IPU1_DISP0_DATA20 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT21__IPU1_DISP0_DATA21 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT22__IPU1_DISP0_DATA22 | MUX_PAD_CTRL(RGB_PAD_CTRL),
	MX6_PAD_DISP0_DAT23__IPU1_DISP0_DATA23 | MUX_PAD_CTRL(RGB_PAD_CTRL),

	/* LCD_RST */
	MX6_PAD_NANDF_D0__GPIO2_IO00 | MUX_PAD_CTRL(NO_PAD_CTRL),
};

iomux_v3_cfg_t const backlight_pads[] = {
	MX6_PAD_SD1_CMD__GPIO1_IO18 | MUX_PAD_CTRL(ENET_PAD_CTRL),
#define RGB_BACKLIGHT_GP IMX_GPIO_NR(1, 18)
	MX6_PAD_KEY_COL2__GPIO4_IO10 | MUX_PAD_CTRL(NO_PAD_CTRL),
#define BL0EN_GPO IMX_GPIO_NR(4, 10)
};

static void enable_rgb(struct display_info_t const *dev)
{
	imx_iomux_v3_setup_multiple_pads(
		rgb_pads,
		ARRAY_SIZE(rgb_pads));

	gpio_direction_output(RGB_BACKLIGHT_GP, 1);
	gpio_direction_output(BL0EN_GPO, 1);

	gpio_direction_output(LCD_RST, 0);
	udelay(500);
	gpio_direction_output(LCD_RST, 1);
}

#define FB_SYNC_DATA_INVERT 0x20000000

struct display_info_t const displays[] = {
	{.bus = 0,
	 .addr = 0,
	 .di = 0,
	 .pixfmt = IPU_PIX_FMT_RGB24,
	 .detect = NULL,
	 .enable = enable_rgb,
	 .mode = {
		 .name = "tianma_tm070rvhg04",
		 .refresh = 60,
		 .xres = 800,
		 .yres = 480,
		 .pixclock = 30030,
		 .left_margin = 46,
		 .right_margin = 210,
		 .upper_margin = 23,
		 .lower_margin = 22,
		 .hsync_len = 5,
		 .vsync_len = 3,
		 .sync = FB_SYNC_EXT,
		 .vmode = FB_VMODE_NONINTERLACED}}};
size_t display_count = ARRAY_SIZE(displays);

static void setup_display(void)
{
	struct mxc_ccm_reg *mxc_ccm = (struct mxc_ccm_reg *)CCM_BASE_ADDR;
	struct iomuxc *iomux = (struct iomuxc *)IOMUXC_BASE_ADDR;
	int reg;

	enable_ipu_clock();
	/* Turn on LDB0,IPU,IPU DI0 clocks */
	reg = __raw_readl(&mxc_ccm->CCGR3);
	reg |= MXC_CCM_CCGR3_LDB_DI0_MASK;
	writel(reg, &mxc_ccm->CCGR3);

	/* set LDB0, LDB1 clk select to 011/011 */
	reg = readl(&mxc_ccm->cs2cdr);
	reg &= ~(MXC_CCM_CS2CDR_LDB_DI0_CLK_SEL_MASK | MXC_CCM_CS2CDR_LDB_DI1_CLK_SEL_MASK);
	reg |= (3 << MXC_CCM_CS2CDR_LDB_DI0_CLK_SEL_OFFSET) | (3 << MXC_CCM_CS2CDR_LDB_DI1_CLK_SEL_OFFSET);
	writel(reg, &mxc_ccm->cs2cdr);

	reg = readl(&mxc_ccm->cscmr2);
	reg |= MXC_CCM_CSCMR2_LDB_DI0_IPU_DIV;
	writel(reg, &mxc_ccm->cscmr2);

	reg = readl(&mxc_ccm->chsccdr);
	reg |= (CHSCCDR_CLK_SEL_LDB_DI0
			<< MXC_CCM_CHSCCDR_IPU1_DI0_CLK_SEL_OFFSET);
	writel(reg, &mxc_ccm->chsccdr);

	reg = IOMUXC_GPR2_BGREF_RRMODE_EXTERNAL_RES | IOMUXC_GPR2_DI1_VS_POLARITY_ACTIVE_HIGH | IOMUXC_GPR2_DI0_VS_POLARITY_ACTIVE_LOW | IOMUXC_GPR2_BIT_MAPPING_CH1_SPWG | IOMUXC_GPR2_DATA_WIDTH_CH1_18BIT | IOMUXC_GPR2_BIT_MAPPING_CH0_SPWG | IOMUXC_GPR2_DATA_WIDTH_CH0_18BIT | IOMUXC_GPR2_LVDS_CH1_MODE_DISABLED | IOMUXC_GPR2_LVDS_CH0_MODE_ENABLED_DI0;
	writel(reg, &iomux->gpr[2]);

	reg = readl(&iomux->gpr[3]);
	reg = (reg & ~(IOMUXC_GPR3_LVDS0_MUX_CTL_MASK | IOMUXC_GPR3_HDMI_MUX_CTL_MASK)) | (IOMUXC_GPR3_MUX_SRC_IPU1_DI0
																					   << IOMUXC_GPR3_LVDS0_MUX_CTL_OFFSET);
	writel(reg, &iomux->gpr[3]);

	/* backlights off until needed */
	imx_iomux_v3_setup_multiple_pads(backlight_pads,
									 ARRAY_SIZE(backlight_pads));

	gpio_direction_output(RGB_BACKLIGHT_GP, 0);
}

void splash_screen_prepare(void)
{
	printf("Loading splash\n");

	char *env_loadsplash;

	if (!env_get("splashimage") || !env_get("loadsplash"))
	{
		return;
	}

	env_loadsplash = env_get("loadsplash");
	if (env_loadsplash == NULL)
	{
		printf("Environment variable loadsplash not found!\n");
		return;
	}

	if (run_command_list(env_loadsplash, -1, 0))
	{
		printf("failed to run loadsplash %s\n\n", env_loadsplash);
	}

	return;
}

int dram_init(void)
{
	gd->ram_size = imx_ddr_size();
	return 0;
}

/*
 * Do not overwrite the console
 * Use always serial for U-Boot console
 */
int overwrite_console(void)
{
	return 1;
}

int board_init(void)
{
	gpio_request(RGB_BACKLIGHT_GP, "rgb backlight");
	gpio_request(LCD_RST, "LCD_RST");
	gpio_request(BL0EN_GPO, "BL0EN_GPO");

	setup_display();

	mdelay(100);

	splash_screen_prepare();

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

int misc_init_r(void)
{
	env_set_hex("reset_cause", get_imx_reset_cause());
	return 0;
}