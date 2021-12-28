/********************************************************************************************************
 * @file     blt_common.h
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

#ifndef BLT_COMMON_H_
#define BLT_COMMON_H_


#include "drivers.h"
#include "vendor/common/user_config.h"


/**
 * @brief	128 K Flash MAC address and calibration data area
 */
#ifndef		CFG_ADR_MAC_128K_FLASH
#define		CFG_ADR_MAC_128K_FLASH								0x1F000
#endif

#ifndef		CFG_ADR_CALIBRATION_128K_FLASH
#define		CFG_ADR_CALIBRATION_128K_FLASH						0x1E000
#endif


/**
 * @brief	512 K Flash MAC address and calibration data area
 */
#ifndef		CFG_ADR_MAC_512K_FLASH
#define		CFG_ADR_MAC_512K_FLASH								0x7F000
#endif

#ifndef		CFG_ADR_CALIBRATION_512K_FLASH
#define		CFG_ADR_CALIBRATION_512K_FLASH						0x7E000
#endif






/**
 * @brief	Flash size option supported by this SDK
 */
#define		FLASH_SIZE_OPTION_128K			   					0x20000
#define		FLASH_SIZE_OPTION_512K			   					0x80000



#ifndef		FLASH_SIZE_OPTION
#define		FLASH_SIZE_OPTION		   							FLASH_SIZE_OPTION_128K
#endif





/**
 * @brief	Flash using area default Configuration, user can change some of them in app_config.h
 * 			CFG_ADR_MAC:  		  BLE MAC address stored in flash, can not change this value
 * 			CFG_ADR_CALIBRATION:  some calibration data stored in flash, can not change this value
 * 			FLASH_ADR_SMP_PAIRING:
 * 								  use 8K flash for SMP pairing information storage.
 * 									First 4K is for normal use, second 4K is a backup to guarantee SMP information never lose.
 * 									use API blc_smp_configPairingSecurityInfoStorageAddress(FLASH_ADR_SMP_PAIRING) to set the address.
 */
#if(FLASH_SIZE_OPTION == FLASH_SIZE_OPTION_128K)
	/* MAC and calibration data area */
	#define	CFG_ADR_MAC		   									CFG_ADR_MAC_128K_FLASH			//can not change this value
	#define	CFG_ADR_CALIBRATION		   							CFG_ADR_CALIBRATION_128K_FLASH	//can not change this value

/* SMP pairing and key information area */
	#ifndef FLASH_ADR_SMP_PAIRING
	#define FLASH_ADR_SMP_PAIRING         						0x1C000
	#endif
#elif (FLASH_SIZE_OPTION == FLASH_SIZE_OPTION_512K)
	/* MAC and calibration data area */
	#define	CFG_ADR_MAC		   									CFG_ADR_MAC_512K_FLASH			//can not change this value
	#define	CFG_ADR_CALIBRATION		   							CFG_ADR_CALIBRATION_512K_FLASH	//can not change this value

	/* SMP pairing and key information area */
	#ifndef FLASH_ADR_SMP_PAIRING
	#define FLASH_ADR_SMP_PAIRING         						0x7C000
	#endif
#else
	#error "unsupported flash size !!!"
#endif











/** Calibration Information FLash Address Offset of  CFG_ADR_CALIBRATION_xx_FLASH ***/
#define		CALIB_OFFSET_CAP_INFO								0x00
#define		CALIB_OFFSET_TP_INFO								0x40
#define		CALIB_OFFSET_ADC_VREF								0xC0
#define		CALIB_OFFSET_FIRMWARE_SIGNKEY						0x180








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





//void blc_readFlashSize_autoConfigCustomFlashSector(void);




void blc_initMacAddress(int flash_addr, u8 *mac_public, u8 *mac_random_static);






#endif /* BLT_COMMON_H_ */
