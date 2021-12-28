/********************************************************************************************************
 * @file     main.c
 *
 * @brief    This is the source file for BLE SDK
 *
 * @author	 BLE GROUP
 * @date         12,2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *******************************************************************************************************/

#include "tl_common.h"
#include "drivers.h"
#include "stack/ble/ble.h"

#include "app.h"
#include "app_att.h"
#include "app_buffer.h"



/**
 * @brief   IRQ handler
 * @param   none.
 * @return  none.
 */
_attribute_ram_code_ void irq_handler(void)
{
	blc_sdk_irq_handler();
}





/**
 * @brief		This is main function
 * @param[in]	none
 * @return      none
 */
int main(void)
{
	#if (BLE_APP_PM_ENABLE)
		blc_pm_select_internal_32k_crystal();
	#endif

	#if (FLASH_SIZE_OPTION == FLASH_SIZE_OPTION_128K)
		blc_ota_setFirmwareSizeAndBootAddress(48, MULTI_BOOT_ADDR_0x10000);
	#endif

	cpu_wakeup_init(EXTERNAL_XTAL_24M);

	clock_init(SYS_CLK_TYPE);

	gpio_init(1);

	#if 0 //TODO: check how many Flash & SRAM size used for this, decide if this function added (SiHui)
		/* Check MCU flash size */
		blc_readFlashSize_autoConfigCustomFlashSector();
	#endif

	/* load customized freq_offset CAP value and TP value. */
	blc_app_loadCustomizedParameters();

	rf_ble_1m_param_init();

	#if FIRMWARES_SIGNATURE_ENABLE
		blt_firmware_signature_check();
	#endif

	user_init_normal ();

    irq_enable();

	while (1) {
		#if (MODULE_WATCHDOG_ENABLE)
			wd_clear(); //clear watch dog
		#endif

		main_loop ();
	}
}

