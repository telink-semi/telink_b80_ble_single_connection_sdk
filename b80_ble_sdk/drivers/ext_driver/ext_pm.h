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


extern unsigned int ota_program_bootAddr;
extern unsigned int ota_program_offset;
extern unsigned int ota_firmware_size_k;



static inline void blc_app_setExternalCrystalCapEnable(unsigned char  en)
{
	blt_miscParam.ext_cap_en = en;
}


#endif

