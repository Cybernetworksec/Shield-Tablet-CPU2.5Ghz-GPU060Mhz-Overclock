/*
 * arch/arm/mach-tegra/board-ardbeg-powermon.c
 *
 * Copyright (c) 2013, NVIDIA CORPORATION. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <linux/i2c.h>
#include <linux/ina219.h>
#include <linux/platform_data/ina230.h>
#include <linux/i2c/pca954x.h>

#include "board.h"
#include "board-ardbeg.h"

#define PRECISION_MULTIPLIER_ARDBEG	1000

/* unused rail */
enum {
	UNUSED_RAIL,
};

/* following rails are present on Ardbeg */
/* rails on i2c2_1 */
enum {
	VDD_SYS_BAT,
	VDD_RTC_LDO5,
	VDD_3V3A_SMPS1_2,
	VDD_SOC_SMPS1_2,
	VDD_SYS_BUCKCPU,
	VDD_CPU_BUCKCPU,
	VDD_1V8A_SMPS3,
	VDD_1V8B_SMPS9,
	VDD_GPU_BUCKGPU,
	VDD_1V35_SMPS6,
	VDD_3V3A_SMPS1_2_2,
	VDD_3V3B_SMPS9,
	VDD_LCD_1V8B_DIS,
	VDD_1V05_SMPS8,
};

/* rails on i2c2_2 */
enum {
	VDD_SYS_BL,
	AVDD_1V05_LDO2,
};

static struct ina219_platform_data power_mon_info_0[] = {
	/* All unused INA219 devices use below data */
	[UNUSED_RAIL] = {
		.calibration_data = 0x369c,
		.power_lsb = 3.051979018 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "unused_rail",
		.divisor = 20,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},
};

/* following are power monitor parameters for Ardbeg */
static struct ina230_platform_data power_mon_info_1[] = {
	[VDD_SYS_BAT] = {
		.calibration_data  = 0x1366,
		.power_lsb = 2.577527185 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "VDD_SYS_BAT",
		.divisor = 25,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},

	[VDD_RTC_LDO5] = {
		.calibration_data  = 0x7FFF,
		.power_lsb = 0.078127384 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "VDD_RTC_LDO5",
		.divisor = 25,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},

	[VDD_3V3A_SMPS1_2] = {
		.calibration_data  = 0x4759,
		.power_lsb = 1.401587736 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "VDD_3V3A_SMPS1_2",
		.divisor = 25,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},

	[VDD_SOC_SMPS1_2] = {
		.calibration_data  = 0x7FFF,
		.power_lsb = 3.906369213 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "VDD_SOC_SMPS1_2",
		.divisor = 25,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},

	[VDD_SYS_BUCKCPU] = {
		.calibration_data  = 0x1AC5,
		.power_lsb = 1.867795126 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "VDD_SYS_BUCKCPU",
		.divisor = 25,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},

	[VDD_CPU_BUCKCPU] = {
		.calibration_data  = 0x2ECF,
		.power_lsb = 10.68179922 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "VDD_CPU_BUCKCPU",
		.divisor = 25,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},

	[VDD_1V8A_SMPS3] = {
		.calibration_data  = 0x5BA7,
		.power_lsb = 0.545539786 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "VDD_1V8A_SMPS3",
		.divisor = 25,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},

	[VDD_1V8B_SMPS9] = {
		.calibration_data  = 0x50B4,
		.power_lsb = 0.309777348 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "VDD_1V8B_SMPS9",
		.divisor = 25,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},

	[VDD_GPU_BUCKGPU] = {
		.calibration_data  = 0x369C,
		.power_lsb = 9.155937053 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "VDD_GPU_BUCKGPU",
		.divisor = 25,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},

	[VDD_1V35_SMPS6] = {
		.calibration_data  = 0x7FFF,
		.power_lsb = 3.906369213 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "VDD_1V35_SMPS6",
		.divisor = 25,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},

	/* following rail is duplicate of VDD_3V3A_SMPS1_2 hence mark unused */
	[VDD_3V3A_SMPS1_2_2] = {
		.calibration_data  = 0x4759,
		.power_lsb = 1.401587736 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "unused_rail",
		.divisor = 25,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},

	[VDD_3V3B_SMPS9] = {
		.calibration_data  = 0x3269,
		.power_lsb = 0.198372724 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "VDD_3V3B_SMPS9",
		.divisor = 25,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},

	[VDD_LCD_1V8B_DIS] = {
		.calibration_data  = 0x7FFF,
		.power_lsb = 0.039063692 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "VDD_LCD_1V8B_DIS",
		.divisor = 25,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},

	[VDD_1V05_SMPS8] = {
		.calibration_data  = 0x7FFF,
		.power_lsb = 0.130212307 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "VDD_1V05_SMPS8",
		.divisor = 25,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},
};

static struct ina230_platform_data power_mon_info_2[] = {
	[VDD_SYS_BL] = {
		.calibration_data  = 0x1A29,
		.power_lsb = 0.63710119 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "VDD_SYS_BL",
		.divisor = 25,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},

	[AVDD_1V05_LDO2] = {
		.calibration_data  = 0x7FFF,
		.power_lsb = 0.390636921 * PRECISION_MULTIPLIER_ARDBEG,
		.rail_name = "AVDD_1V05_LDO2",
		.divisor = 25,
		.precision_multiplier = PRECISION_MULTIPLIER_ARDBEG,
	},
};

/* i2c addresses of rails present on Ardbeg */
/* addresses on i2c2_0 */
enum {
	INA_I2C_2_0_ADDR_40,
	INA_I2C_2_0_ADDR_41,
	INA_I2C_2_0_ADDR_42,
	INA_I2C_2_0_ADDR_43,
};

/* addresses on i2c2_1 */
enum {
	INA_I2C_2_1_ADDR_40,
	INA_I2C_2_1_ADDR_41,
	INA_I2C_2_1_ADDR_42,
	INA_I2C_2_1_ADDR_43,
	INA_I2C_2_1_ADDR_44,
	INA_I2C_2_1_ADDR_45,
	INA_I2C_2_1_ADDR_46,
	INA_I2C_2_1_ADDR_47,
	INA_I2C_2_1_ADDR_48,
	INA_I2C_2_1_ADDR_49,
	INA_I2C_2_1_ADDR_4B,
	INA_I2C_2_1_ADDR_4C,
	INA_I2C_2_1_ADDR_4E,
	INA_I2C_2_1_ADDR_4F,
};

/* addresses on i2c2_2 */
enum {
	INA_I2C_2_2_ADDR_49,
	INA_I2C_2_2_ADDR_4C,
};

static struct i2c_board_info ardbeg_i2c2_0_ina219_board_info[] = {
	[INA_I2C_2_0_ADDR_40] = {
		I2C_BOARD_INFO("ina219", 0x40),
		.platform_data = &power_mon_info_0[UNUSED_RAIL],
		.irq = -1,
	},

	[INA_I2C_2_0_ADDR_41] = {
		I2C_BOARD_INFO("ina219", 0x41),
		.platform_data = &power_mon_info_0[UNUSED_RAIL],
		.irq = -1,
	},

	[INA_I2C_2_0_ADDR_42] = {
		I2C_BOARD_INFO("ina219", 0x42),
		.platform_data = &power_mon_info_0[UNUSED_RAIL],
		.irq = -1,
	},

	[INA_I2C_2_0_ADDR_43] = {
		I2C_BOARD_INFO("ina219", 0x43),
		.platform_data = &power_mon_info_0[UNUSED_RAIL],
		.irq = -1,
	},
};

static struct i2c_board_info ardbeg_i2c2_1_ina230_board_info[] = {
	[INA_I2C_2_1_ADDR_40] = {
		I2C_BOARD_INFO("ina230", 0x40),
		.platform_data = &power_mon_info_1[VDD_SYS_BAT],
		.irq = -1,
	},

	[INA_I2C_2_1_ADDR_41] = {
		I2C_BOARD_INFO("ina230", 0x41),
		.platform_data = &power_mon_info_1[VDD_RTC_LDO5],
		.irq = -1,
	},

	[INA_I2C_2_1_ADDR_42] = {
		I2C_BOARD_INFO("ina230", 0x42),
		.platform_data = &power_mon_info_1[VDD_3V3A_SMPS1_2],
		.irq = -1,
	},

	[INA_I2C_2_1_ADDR_43] = {
		I2C_BOARD_INFO("ina230", 0x43),
		.platform_data = &power_mon_info_1[VDD_SOC_SMPS1_2],
		.irq = -1,
	},

	[INA_I2C_2_1_ADDR_44] = {
		I2C_BOARD_INFO("ina230", 0x44),
		.platform_data = &power_mon_info_1[VDD_SYS_BUCKCPU],
		.irq = -1,
	},

	[INA_I2C_2_1_ADDR_45] = {
		I2C_BOARD_INFO("ina230", 0x45),
		.platform_data = &power_mon_info_1[VDD_CPU_BUCKCPU],
		.irq = -1,
	},

	[INA_I2C_2_1_ADDR_46] = {
		I2C_BOARD_INFO("ina230", 0x46),
		.platform_data = &power_mon_info_1[VDD_1V8A_SMPS3],
		.irq = -1,
	},

	[INA_I2C_2_1_ADDR_47] = {
		I2C_BOARD_INFO("ina230", 0x47),
		.platform_data = &power_mon_info_1[VDD_1V8B_SMPS9],
		.irq = -1,
	},

	[INA_I2C_2_1_ADDR_48] = {
		I2C_BOARD_INFO("ina230", 0x48),
		.platform_data = &power_mon_info_1[VDD_GPU_BUCKGPU],
		.irq = -1,
	},

	[INA_I2C_2_1_ADDR_49] = {
		I2C_BOARD_INFO("ina230", 0x49),
		.platform_data = &power_mon_info_1[VDD_1V35_SMPS6],
		.irq = -1,
	},

	[INA_I2C_2_1_ADDR_4B] = {
		I2C_BOARD_INFO("ina230", 0x4B),
		.platform_data = &power_mon_info_1[VDD_3V3A_SMPS1_2_2],
		.irq = -1,
	},

	[INA_I2C_2_1_ADDR_4C] = {
		I2C_BOARD_INFO("ina230", 0x4C),
		.platform_data = &power_mon_info_1[VDD_3V3B_SMPS9],
		.irq = -1,
	},

	[INA_I2C_2_1_ADDR_4E] = {
		I2C_BOARD_INFO("ina230", 0x4E),
		.platform_data = &power_mon_info_1[VDD_LCD_1V8B_DIS],
		.irq = -1,
	},

	[INA_I2C_2_1_ADDR_4F] = {
		I2C_BOARD_INFO("ina230", 0x4F),
		.platform_data = &power_mon_info_1[VDD_1V05_SMPS8],
		.irq = -1,
	},
};

static struct i2c_board_info ardbeg_i2c2_2_ina230_board_info[] = {
	[INA_I2C_2_2_ADDR_49] = {
		I2C_BOARD_INFO("ina230", 0x49),
		.platform_data = &power_mon_info_2[VDD_SYS_BL],
		.irq = -1,
	},

	[INA_I2C_2_2_ADDR_4C] = {
		I2C_BOARD_INFO("ina230", 0x4C),
		.platform_data = &power_mon_info_2[AVDD_1V05_LDO2],
		.irq = -1,
	},

};

static struct pca954x_platform_mode ardbeg_pca954x_modes[] = {
	{ .adap_id = PCA954x_I2C_BUS0, .deselect_on_exit = true, },
	{ .adap_id = PCA954x_I2C_BUS1, .deselect_on_exit = true, },
	{ .adap_id = PCA954x_I2C_BUS2, .deselect_on_exit = true, },
	{ .adap_id = PCA954x_I2C_BUS3, .deselect_on_exit = true, },
};

static struct pca954x_platform_data ardbeg_pca954x_data = {
	.modes    = ardbeg_pca954x_modes,
	.num_modes      = ARRAY_SIZE(ardbeg_pca954x_modes),
};

static const struct i2c_board_info ardbeg_i2c2_board_info[] = {
	{
		I2C_BOARD_INFO("pca9546", 0x71),
		.platform_data = &ardbeg_pca954x_data,
	},
};

int __init ardbeg_pmon_init(void)
{
	i2c_register_board_info(1, ardbeg_i2c2_board_info,
		ARRAY_SIZE(ardbeg_i2c2_board_info));

	i2c_register_board_info(PCA954x_I2C_BUS0,
			ardbeg_i2c2_0_ina219_board_info,
			ARRAY_SIZE(ardbeg_i2c2_0_ina219_board_info));

	i2c_register_board_info(PCA954x_I2C_BUS1,
			ardbeg_i2c2_1_ina230_board_info,
			ARRAY_SIZE(ardbeg_i2c2_1_ina230_board_info));

	i2c_register_board_info(PCA954x_I2C_BUS2,
			ardbeg_i2c2_2_ina230_board_info,
			ARRAY_SIZE(ardbeg_i2c2_2_ina230_board_info));

	return 0;
}
