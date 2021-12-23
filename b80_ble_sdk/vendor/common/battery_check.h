/********************************************************************************************************
 * @file     battery_check.h
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
#ifndef BATTERY_CHECK_H_
#define BATTERY_CHECK_H_

#include "drivers.h"
#if (__PROJECT_5317_BLE_REMOTE__)

#define BATTERY_CHECK_PIN     GPIO_PB2
#define BATTERY_CHECK_ADC_CHN B2P

#define BATTERY_VOL_OK        0x00
#define BATTERY_VOL_LOW       0x01

#define BATTERY_VOL_MIN      ((u16)2000)//Unit: mV

#define ADC_SAMPLE_NUM       8


u8 TL_IsNeedInitAdcForBattCheck(void);
void TL_ClearBatteryCheckConfig(u8 clear);
void TL_BatteryCheckInit(void);
void TL_BattteryCheckProc(int minVol_mV);//

void battery_set_detect_enable (int en);
int  battery_get_detect_enable (void);

#endif ////ending of (__PROJECT_5317_BLE_REMOTE__)

#endif /* BATTERY_CHECK_H_ */
