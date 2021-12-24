/********************************************************************************************************
 * @file	blt_common.h
 *
 * @brief	This is the header file for BLE SDK
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

/* SMP paring and key information area */
	#ifndef FLASH_ADR_SMP_PAIRING
	#define FLASH_ADR_SMP_PAIRING         						0x1C000
	#endif
#elif (FLASH_SIZE_OPTION == FLASH_SIZE_OPTION_512K)
	/* MAC and calibration data area */
	#define	CFG_ADR_MAC		   									CFG_ADR_MAC_512K_FLASH			//can not change this value
	#define	CFG_ADR_CALIBRATION		   							CFG_ADR_CALIBRATION_512K_FLASH	//can not change this value

	/* SMP paring and key information area */
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
