/********************************************************************************************************
 * @file     main.c
 *
 * @brief    for TLSR chips
 *
 * @author	 BLE Group
 * @date     May. 12, 2018
 *
 * @par      Copyright (c) Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *           
 *			 The information contained herein is confidential and proprietary property of Telink 
 * 		     Semiconductor (Shanghai) Co., Ltd. and is available under the terms 
 *			 of Commercial License Agreement between Telink Semiconductor (Shanghai) 
 *			 Co., Ltd. and the licensee in separate contract or the terms described here-in. 
 *           This heading MUST NOT be removed from this file.
 *
 * 			 Licensees are granted free, non-transferable use of the information in this 
 *			 file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided. 
 *           
 *******************************************************************************************************/
#include "tl_common.h"
#include "drivers.h"
#include "stack/ble/ble.h"
#include "app.h"

#if(INTERNAL_TEST_MODE == TEST_SLAVE_MD)

_attribute_ram_code_ void irq_handler(void)
{
	irq_blt_sdk_handler();
}

int main(void)
{
	blc_pm_select_internal_32k_crystal();

	/***********************************************
	 * if the bin size is less than 48K, we recommend using this setting.
	 */

	cpu_wakeup_init(EXTERNAL_XTAL_24M);

	#if (CLOCK_SYS_CLOCK_HZ == 16000000)
		clock_init(SYS_CLK_16M_Crystal);
	#elif (CLOCK_SYS_CLOCK_HZ == 32000000)
		clock_init(SYS_CLK_32M_Crystal);
	#elif (CLOCK_SYS_CLOCK_HZ == 48000000)
		clock_init(SYS_CLK_48M_Crystal);
	#endif

	gpio_init(1);

	#if 0
	/* Check MCU flash size */
	blc_readFlashSize_autoConfigCustomFlashSector();
	#endif

	/* load customized freq_offset CAP value and TP value. */
	blc_app_loadCustomizedParameters();

	rf_mode_init();
	rf_set_ble_1M_mode();

	#if FIRMWARES_SIGNATURE_ENABLE
		blt_firmware_signature_check();
	#endif

	user_init ();

    irq_enable();
	while (1) {
	#if (MODULE_WATCHDOG_ENABLE)
		wd_clear(); //clear watch dog
	#endif

		main_loop ();
	}
}

#endif

