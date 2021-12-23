/********************************************************************************************************
 * @file     blt_common.h
 *
 * @brief    for TLSR chips
 *
 * @author	 BLE Group
 * @date     Sep. 18, 2018
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

#ifndef BLT_COMMON_H_
#define BLT_COMMON_H_

#include "common/types.h"
#include "drivers.h"
#include "stack/ble/ble_config.h"


#if 1//Flash size auto check.

/**************************** 128 K Flash *****************************/
#ifndef		CFG_ADR_MAC_128K_FLASH
#define		CFG_ADR_MAC_128K_FLASH								0x1F000
#endif

#ifndef		CFG_ADR_CALIBRATION_128K_FLASH
#define		CFG_ADR_CALIBRATION_128K_FLASH						0x1E000
#endif


/**************************** 512 K Flash *****************************/
///flash size is 512K flash use situation.
#ifndef		CFG_ADR_MAC_512K_FLASH
#define		CFG_ADR_MAC_512K_FLASH								0x76000
#endif

#ifndef		CFG_ADR_CALIBRATION_512K_FLASH
#define		CFG_ADR_CALIBRATION_512K_FLASH						0x77000
#endif


/**************************** 1 M Flash *******************************/
#ifndef		CFG_ADR_MAC_1M_FLASH
#define		CFG_ADR_MAC_1M_FLASH		   						0xFF000
#endif


#ifndef		CFG_ADR_CALIBRATION_1M_FLASH
#define		CFG_ADR_CALIBRATION_1M_FLASH						0xFE000
#endif


/** Calibration Information FLash Address Offset of  CFG_ADR_CALIBRATION_xx_FLASH ***/
#define		CALIB_OFFSET_CAP_INFO								0x00
#define		CALIB_OFFSET_TP_INFO								0x40
#define		CALIB_OFFSET_ADC_VREF								0xC0
#define		CALIB_OFFSET_FIRMWARE_SIGNKEY						0x0180


extern u32 flash_sector_mac_address;			//default flash is 512k
extern u32 flash_sector_calibration;


static inline void blc_app_loadCustomizedParameters(void)
{
//	 if(!blt_miscParam.ext_cap_en)
//	 {
//		 if(flash_sector_calibration)
//		 {
//			 u32 capInfoAddr = flash_sector_calibration + CALIB_OFFSET_CAP_INFO;
//
//			 //customize freq_offset adjust cap value, if not customized, default ana_81 is 0xd0
//			 if( (*(unsigned char*)capInfoAddr) != 0xff ){
//				 //ana_81<4:0> is cap value(0x00 - 0x1f)
//				 analog_write(0x81, (analog_read(0x81)&0xe0) | ((*(unsigned char*)capInfoAddr)&0x1f) );
//			 }
//		 }
//	 }
//	 else{//use external 24M cap
//		analog_write(0x80, analog_read(0x80)&0xbf);//an_80<6> = 0, disable internal cap
//		analog_write(0x81, analog_read(0x81)&0xe0);//an_81<4:0> = 0, clear internal cap value
//	 }

	 //TODO yy
//	 if(flash_sector_calibration)
//	 {
//		 u32 tpInfoAddr = flash_sector_calibration + CALIB_OFFSET_TP_INFO;
//
//		 // customize TP0/TP1 1M
//		 if( ((*(unsigned char*)(tpInfoAddr)) != 0xff) && ((*(unsigned char*) (tpInfoAddr+1)) != 0xff) ){
//			 rf_update_tp_value(*(unsigned char*) (tpInfoAddr), *(unsigned char*) (tpInfoAddr+1));
//		 }
//
//		 if ( ((*(unsigned char*) (tpInfoAddr+2)) != 0xff) && ((*(unsigned char*) (tpInfoAddr+3)) != 0xff) ){
//			 rf_load_2m_tp_value(*(unsigned char*) (tpInfoAddr+2), *(unsigned char*) (tpInfoAddr+3));
//		 }
//	 }
}


void blc_readFlashSize_autoConfigCustomFlashSector(void);
#endif

void blc_initMacAddress(int flash_addr, u8 *mac_public, u8 *mac_random_static);

#endif /* BLT_COMMON_H_ */
