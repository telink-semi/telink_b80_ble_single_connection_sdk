/********************************************************************************************************
 * @file     ble_config.h
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

#pragma once

//////////////////////////////////////////////////////////////////////////////
/**
 *  @brief  Definition for Device info
 */
#include "drivers.h"
#include "tl_common.h"

#define BLE_DEBUG     0 //!!! use for debug.  when release SDK, "BLE_DEBUG" must be set to 0.

#define  MAX_DEV_NAME_LEN 				18

#ifndef DEV_NAME
#define DEV_NAME                        "eModule"
#endif





#define KEYBOARD_MOUSE_APPLICATION                        0
#if KEYBOARD_MOUSE_APPLICATION
	#define SECURE_CONNECTION_ENABLE					    0
	//Link layer feature enable flag default setting
	//compatibility with wearable
	//#define BLE_CORE42_DATA_LENGTH_EXTENSION_ENABLE			0
	//#define BLE_BIG_MTU_ENABLE											0
	//#define ATT_RSP_BIG_MTU_PROCESS_EN      					BLE_BIG_MTU_ENABLE
	#define LL_FEATURE_SUPPORT_LE_2M_PHY					0
	#define BLE_STATE_MACHINE_EXTENSION_EN                  0
#endif

#define ELECTRONIC_SCALE_APPLICATION                        0
#if ELECTRONIC_SCALE_APPLICATION
	#define SECURE_CONNECTION_ENABLE					    0
	//Link layer feature enable flag default setting
	#define BLE_CORE42_DATA_LENGTH_EXTENSION_ENABLE			0
	#define LL_FEATURE_SUPPORT_LE_2M_PHY					0
	#define BLE_STATE_MACHINE_EXTENSION_EN                  0
#endif





static inline void blc_app_setExternalCrystalCapEnable(u8  en)
{
	blt_miscParam.ext_cap_en = en;
}




#define OPTIMIZE_CODE_SIZE       1






/////////////////// Feature ////////////////////////////
#ifndef SECURE_CONNECTION_ENABLE
#define SECURE_CONNECTION_ENABLE					   1
#endif

#ifndef BLE_BIG_MTU_ENABLE
#define BLE_BIG_MTU_ENABLE			1
#endif

#ifndef ATT_RSP_BIG_MTU_PROCESS_EN
#define ATT_RSP_BIG_MTU_PROCESS_EN			BLE_BIG_MTU_ENABLE
#endif
//Link layer feature enable flag default setting
#ifndef BLE_CORE42_DATA_LENGTH_EXTENSION_ENABLE
#define BLE_CORE42_DATA_LENGTH_EXTENSION_ENABLE			1
#endif

#ifndef LL_FEATURE_SUPPORT_LE_2M_PHY
#define LL_FEATURE_SUPPORT_LE_2M_PHY					1	//TODO yy
#endif


#ifndef		BLS_ADV_INTERVAL_CHECK_ENABLE
#define		BLS_ADV_INTERVAL_CHECK_ENABLE				0 ////1 according to sihui's advise, disable interval check.
#endif

#ifndef BLE_STATE_MACHINE_EXTENSION_EN
#define BLE_STATE_MACHINE_EXTENSION_EN              	1
#endif

#ifndef SOFT_UART_ENABLE
#define SOFT_UART_ENABLE                 				0
#endif


#if (MCU_CORE_TYPE == MCU_CORE_5317)
	#define	BLS_PROC_MASTER_UPDATE_REQ_IN_IRQ_ENABLE	0
#endif


//conn param update/map update
#ifndef	BLS_PROC_MASTER_UPDATE_REQ_IN_IRQ_ENABLE
#define BLS_PROC_MASTER_UPDATE_REQ_IN_IRQ_ENABLE		1
#endif


#ifndef BLS_PROC_LONG_SUSPEND_ENABLE
#define BLS_PROC_LONG_SUSPEND_ENABLE					0
#endif

#ifndef BLE_ADV_PEAK_CURRENT_OPT
#define BLE_ADV_PEAK_CURRENT_OPT						0
#endif




///////////////////////////////////////dbg channels///////////////////////////////////////////
#ifndef	DBG_CHN0_TOGGLE
#define DBG_CHN0_TOGGLE
#endif

#ifndef	DBG_CHN0_HIGH
#define DBG_CHN0_HIGH
#endif

#ifndef	DBG_CHN0_LOW
#define DBG_CHN0_LOW
#endif

#ifndef	DBG_CHN1_TOGGLE
#define DBG_CHN1_TOGGLE
#endif

#ifndef	DBG_CHN1_HIGH
#define DBG_CHN1_HIGH
#endif

#ifndef	DBG_CHN1_LOW
#define DBG_CHN1_LOW
#endif

#ifndef	DBG_CHN2_TOGGLE
#define DBG_CHN2_TOGGLE
#endif

#ifndef	DBG_CHN2_HIGH
#define DBG_CHN2_HIGH
#endif

#ifndef	DBG_CHN2_LOW
#define DBG_CHN2_LOW
#endif

#ifndef	DBG_CHN3_TOGGLE
#define DBG_CHN3_TOGGLE
#endif

#ifndef	DBG_CHN3_HIGH
#define DBG_CHN3_HIGH
#endif

#ifndef	DBG_CHN3_LOW
#define DBG_CHN3_LOW
#endif

#ifndef	DBG_CHN4_TOGGLE
#define DBG_CHN4_TOGGLE
#endif

#ifndef	DBG_CHN4_HIGH
#define DBG_CHN4_HIGH
#endif

#ifndef	DBG_CHN4_LOW
#define DBG_CHN4_LOW
#endif

#ifndef	DBG_CHN5_TOGGLE
#define DBG_CHN5_TOGGLE
#endif

#ifndef	DBG_CHN5_HIGH
#define DBG_CHN5_HIGH
#endif

#ifndef	DBG_CHN5_LOW
#define DBG_CHN5_LOW
#endif


