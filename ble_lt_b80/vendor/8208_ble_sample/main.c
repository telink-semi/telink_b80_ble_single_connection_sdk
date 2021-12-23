/********************************************************************************************************
 * @file	main.c
 *
 * @brief	This is the source file for BLE SDK
 *
 * @author	BLE GROUP
 * @date	2020.06
 *
 * @par     Copyright (c) 2020, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *
 *          Redistribution and use in source and binary forms, with or without
 *          modification, are permitted provided that the following conditions are met:
 *
 *              1. Redistributions of source code must retain the above copyright
 *              notice, this list of conditions and the following disclaimer.
 *
 *              2. Unless for usage inside a TELINK integrated circuit, redistributions
 *              in binary form must reproduce the above copyright notice, this list of
 *              conditions and the following disclaimer in the documentation and/or other
 *              materials provided with the distribution.
 *
 *              3. Neither the name of TELINK, nor the names of its contributors may be
 *              used to endorse or promote products derived from this software without
 *              specific prior written permission.
 *
 *              4. This software, with or without modification, must only be used with a
 *              TELINK integrated circuit. All other usages are subject to written permission
 *              from TELINK and different commercial license may apply.
 *
 *              5. Licensee shall be solely responsible for any claim to the extent arising out of or
 *              relating to such deletion(s), modification(s) or alteration(s).
 *
 *          THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *          ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *          WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *          DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE LIABLE FOR ANY
 *          DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *          (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *          LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *          ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *          (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *          SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
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

	/***********************************************
	 * if the bin size is less than 48K, we recommend using this setting.
	 */
	#if (FLASH_SIZE_OPTION == FLASH_SIZE_OPTION_128K) ///FLASH_SIZE_OPTION_128K
		bls_ota_setFirmwareSizeAndOffset(64, 0x10000);///default : ota_firmware_size_k=128;ota_program_bootAddr=0x20000; it is for hawk 128K flash
		bls_smp_configParingSecurityInfoStorageAddr(0x1C000);
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

