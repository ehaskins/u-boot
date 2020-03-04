#ifndef __GR60MXD_CONFIG_H__
#define __GR60MXD_CONFIG_H__

#include "mx6_common.h"


/* Framebuffer and LCD */
#define CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define CONFIG_IMX_VIDEO_SKIP
#define CONFIG_VIDEO_LOGO

/* MMC Configs */
#define CONFIG_SYS_FSL_ESDHC_ADDR      0

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

/* Environment organization */
#define CONFIG_ENV_SIZE (8 * 1024)

#define CONFIG_EXTRA_ENV_SETTINGS \
	"console=ttymxc3\0" \
	"fdt_high=0xffffffff\0" \
	"initrd_high=0xffffffff\0" \
	"fdt_addr=0x18000000\0" \
	"fdt_file=imx6q-gr60mxd.dtb\0" \
	"kernel_file=zImage\0" \
	"kernel_addr=" __stringify(CONFIG_LOADADDR) "\0"  \
    "mmcdev=2\0" \
    "mmcpart=2\0" \
	"mmcroot=/dev/mmcblk3p2 rootwait rw\0" \
	"splashfile=splash.bmp\0" \
    "splashimage=10000000\0" \
    "splashpos=m,m\0" \
	"loadsplash=fatload mmc ${mmcdev}:${mmcpart} ${splashimage} ${splashfile}\0" \
	"loadimage=fatload mmc ${mmcdev}:${mmcpart} ${kernel_addr} ${kernel_file}\0" \
	"loadfdt=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0" \
	"mmcargs=setenv bootargs console=${console},${baudrate} root=${mmcroot}\0" \
	"bootcmd=run mmcargs loadimage loadfdt; bootz ${kernel_addr} - ${fdt_addr}\0" \


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