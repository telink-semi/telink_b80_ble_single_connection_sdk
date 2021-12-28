/********************************************************************************************************
 * @file     blt_common.c
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
#include "blt_common.h"

#if 0//Flash size auto check.

u32 flash_sector_mac_address = CFG_ADR_MAC_128K_FLASH;			//default flash is 128k
u32 flash_sector_calibration = CFG_ADR_CALIBRATION_128K_FLASH;	//default flash is 128k

void blc_readFlashSize_autoConfigCustomFlashSector(void)
{
//	u8 temp_buf[4];
//	flash_read_mid(temp_buf);
//	u8	flash_cap = temp_buf[2];

	u32 flashMid;
	u8 flashUid[16];
	flash_read_mid_uid_with_check(&flashMid, &flashUid[0]);
	u8	flash_cap = (flashMid>>16);

	if(flash_cap == FLASH_SIZE_128K){
		flash_sector_mac_address = CFG_ADR_MAC_128K_FLASH;
		flash_sector_calibration = CFG_ADR_CALIBRATION_128K_FLASH;
	}
	else if(flash_cap == FLASH_SIZE_512K){
		flash_sector_mac_address = CFG_ADR_MAC_512K_FLASH;
		flash_sector_calibration = CFG_ADR_CALIBRATION_512K_FLASH;
	}
	else{
		//This SDK do not support flash size other than 512K/1M
		//If code stop here, please check your Flash
		while(1);
	}


//	flash_set_capacity(flash_cap);
}
#endif

/*
 * VVWWXX38C1A4YYZZ
 * public_mac: 		  VVWWXX 38C1A4
 * random_static_mac: VVWWXXYYZZ C0
 */

void blc_initMacAddress(int flash_addr, u8 *mac_public, u8 *mac_random_static)
{
//	u8  mac_public[6] 		 = {0x00, 0x00, 0x00, 0x38, 0xC1, 0xA4};  //company id: 0xA4C138
//	u8  mac_random_static[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0xC0};

	u8 mac_read[8];
	flash_read_page(flash_addr, 8, mac_read);

	u8 value_rand[5];
	generateRandomNum(5, value_rand);

	u8 ff_six_byte[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	if ( memcmp(mac_read, ff_six_byte, 6) ) {
		memcpy(mac_public, mac_read, 6);  //copy public address from flash
	}
	else{  //no public address on flash
		mac_public[0] = value_rand[0];
		mac_public[1] = value_rand[1];
		mac_public[2] = value_rand[2];
		mac_public[3] = 0x38;             //company id: 0xA4C138
		mac_public[4] = 0xC1;
		mac_public[5] = 0xA4;

		flash_write_page (flash_addr, 6, mac_public);
	}

	mac_random_static[0] = mac_public[0];
	mac_random_static[1] = mac_public[1];
	mac_random_static[2] = mac_public[2];
	mac_random_static[5] = 0xC0; 			//for random static

	u16 high_2_byte = (mac_read[6] | mac_read[7]<<8);
	if(high_2_byte != 0xFFFF){
		memcpy( (u8 *)(mac_random_static + 3), (u8 *)(mac_read + 6), 2);
	}
	else{
		mac_random_static[3] = value_rand[3];
		mac_random_static[4] = value_rand[4];

		flash_write_page (flash_addr + 6, 2, (u8 *)(mac_random_static + 3) );
	}
}

