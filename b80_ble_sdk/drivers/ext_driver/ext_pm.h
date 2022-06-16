/********************************************************************************************************
 * @file     ext_pm.h
 *
 * @brief    This is the header file for BLE SDK
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

#ifndef DRIVERS_8208_EXT_PM_H_
#define DRIVERS_8208_EXT_PM_H_

#ifndef PM_CUMULATIVE_ERROR_ELIMINATE_ENABLE
#define PM_CUMULATIVE_ERROR_ELIMINATE_ENABLE			    	0
#endif

#if (PM_CUMULATIVE_ERROR_ELIMINATE_ENABLE)

typedef struct{
	unsigned int   tick_sysClk;
	unsigned int   tick_32k;
	unsigned int   recover_flag;
}pm_tim_recover_t;

extern _attribute_aligned_(4) pm_tim_recover_t			pm_timCalib;
#endif

extern unsigned int ota_program_bootAddr;
extern unsigned int ota_program_offset;
extern unsigned int ota_firmware_size_k;

/**
 * @brief   This function serves to initialize MCU, run in ramcode.
 * @param   xtal - set crystal for different application.
 * 			In version A0, the chip cannot be lower than 2.2V when it is powered on for the first time,
 * 	 	    after calling this function, g_chip_version is the version number recorded.
 *
 * @return  none
 */
typedef void (*pm_wakeup_init_t)(XTAL_TypeDef);
extern pm_wakeup_init_t pm_wakeup_init;
/**
 * @brief		This function is used to enable the external crystal capacitor
 * @param[in]	en - enable the external crystal capacitor
 * @return      none
 */
static inline void blc_app_setExternalCrystalCapEnable(unsigned char  en)
{
	blt_miscParam.ext_cap_en = en;
}


#endif

