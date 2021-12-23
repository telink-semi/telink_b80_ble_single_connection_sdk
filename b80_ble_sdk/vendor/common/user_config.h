/********************************************************************************************************
 * @file     user_config.h 
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

#pragma once


#if(__PROJECT_B80_BLE_SAMPLE__)
	#include "vendor/8208_ble_sample/app_config.h"
#elif(__PROJECT_B80_BLE_FEATURE__)
	#include "vendor/8208_feature/app_config.h"
#elif(__PROJECT_B80_BLE_INTERNAL_TEST__)
	#include "vendor/8208_ble_internal_test/app_config.h"
#else
	#include "../common/default_config.h"
#endif

