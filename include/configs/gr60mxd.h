#ifndef __GR60MXD_CONFIG_H__
#define __GR60MXD_CONFIG_H__

#include "mx6_common.h"


/* Framebuffer and LCD */
#define CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define CONFIG_IMX_VIDEO_SKIP
#define CONFIG_VIDEO_LOGO

/* Ethernet Config */
#define CONFIG_FEC_MXC
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_XCV_TYPE		RGMII
#define CONFIG_ETHPRIME			"FEC"
#define CONFIG_FEC_MXC_PHYADDR		-1

/* MMC Configs */
#define CONFIG_SYS_FSL_ESDHC_ADDR      0

/* USB Configs */
#define CONFIG_USBD_HS
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET	/* For OTG port */
#define CONFIG_MXC_USB_PORTSC	(PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS	0

// #define CONFIG_MMCROOT "/dev/mmcblk3p2"

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN (10 * SZ_1M)

/* Physical Memory Map */
#define PHYS_SDRAM MMDC0_ARB_BASE_ADDR
#define PHYS_SDRAM_SIZE (2u * 1024 * 1024 * 1024)

#define CONFIG_SYS_SDRAM_BASE PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE IRAM_SIZE
#define CONFIG_SYS_INIT_SP_OFFSET \
    (CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
    (CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

#define CONFIG_EXTRA_ENV_SETTINGS \
	"kboot=bootz\0" \
	"console=ttymxc3\0" \
	"fdt_high=0xffffffff\0" \
	"initrd_high=0xffffffff\0" \
	"fdt_addr=0x18000000\0" \
	"fdt_file=mackerel/imx6q-gr60mxd.dtb\0" \
	"kernel_file=mackerel/zImage\0" \
	"loadaddr=" __stringify(CONFIG_LOADADDR) "\0"  \
	"splashfile=mackerel/splash.bmp\0" \
    "splashimage=10000000\0" \
    "splashpos=m,m\0" \
	"loadsplash=fatload mmc 3:1 ${splashimage} ${splashfile}\0" \
	"loadimage=fatload ${boot_type} ${boot_dev}:${boot_part} ${loadaddr} ${kernel_file}\0" \
	"loadfdt=fatload ${boot_type} ${boot_dev}:${boot_part} ${fdt_addr} ${fdt_file}\0" \
	"boot_type=mmc\0" \
	"boot_dev=2\0" \
	"boot_part=1\0" \
	"mmcvars=" \
	"	setenv bootargs console=${console},${baudrate} boot_dev=mmcblk2 vt.global_cursor_default=0 ;" \
	"	setenv boot_type mmc;" \
	"	setenv boot_dev 3;" \
	"	setenv boot_part 1;" \
	"\0" \
	"sdvars=" \
	"	setenv bootargs console=${console},${baudrate} boot_dev=mmcblk2 vt.global_cursor_default=0 ;" \
	"	setenv boot_type mmc;" \
	"	setenv boot_dev 2;" \
	"	setenv boot_part 1;" \
	"\0" \
	"usbvars=" \
	"	setenv bootargs console=${console},${baudrate} boot_dev=mmcblk2 vt.global_cursor_default=0 ;" \
	"	setenv boot_type usb;" \
	"	setenv boot_dev 0;" \
	"	setenv boot_part 1;" \
	"\0" \
	"bootcmd=run boot_mmc\0" \
	"boot_loaded=bootz ${loadaddr} - ${fdt_addr}\0" \
	"boot_mmc=run mmcvars loadimage loadfdt boot_loaded\0" \
	"boot_sd=run sdvars loadimage loadfdt boot_loaded\0" \
	"boot_usb=run usbvars loadimage loadfdt boot_loaded\0" \

/* Miscellaneous configurable options */
#define CONFIG_SYS_MEMTEST_START       0x10000000
#define CONFIG_SYS_MEMTEST_END	       0x10010000
#define CONFIG_SYS_MEMTEST_SCRATCH     0x10800000
/*
#define CONFIG_DEFAULT_FDT_FILE "imx6q-gr60mxd.dtb"
#include "mx6sabre_common.h"
*/

/* Overrides setting */
/*
#undef CONFIG_PHY_ATHEROS
#define CONFIG_PHY_MICREL
#undef CONFIG_ANDROID_RECOVERY
#define CONFIG_CMD_FUSE
#ifdef CONFIG_CMD_FUSE
#define CONFIG_MXC_OCOTP
#endif
*/
/* USB Configs */
/*
#define CONFIG_CMD_USB
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_MX6
#define CONFIG_USB_STORAGE
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET 
#define CONFIG_MXC_USB_PORTSC (PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS 0
#define CONFIG_MFG_NAND_PARTITION ""
#define CONFIG_SYS_FSL_USDHC_NUM 2
#define CONFIG_SYS_MMC_ENV_DEV 1  
#define CONFIG_SYS_MMC_ENV_PART 0 
*/
#endif 