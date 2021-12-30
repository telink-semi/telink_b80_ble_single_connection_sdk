/********************************************************************************************************
 * @file     smp.h
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

#ifndef BLE_SMP_H_
#define BLE_SMP_H_





#define SMP_STANDARD_PAIR   	0
#define SMP_FAST_CONNECT   		1







typedef struct {  //82
	u8		flag;
	u8		peer_addr_type;  //address used in link layer connection
	u8		peer_addr[6];

	u8 		peer_key_size;
	u8		peer_id_adrType; //peer identity address information in key distribution, used to identify
	u8		peer_id_addr[6];

	u8 		own_ltk[16];      //own_ltk[16]
	u8		peer_irk[16];
	u8		peer_csrk[16];
}smp_param_save_t;











// IO Capability Values
typedef enum {
	IO_CAPABILITY_DISPLAY_ONLY = 0,
	IO_CAPABILITY_DISPLAY_YES_NO,
	IO_CAPABILITY_KEYBOARD_ONLY,
	IO_CAPABILITY_NO_INPUT_NO_OUTPUT,
	IO_CAPABILITY_KEYBOARD_DISPLAY, // not used by secure simple pairing
	IO_CAPABILITY_UNKNOWN = 0xff
} io_capability_t;








typedef enum{
	SMP_PAIRING_DISABLE_TRRIGER = 0,
	SMP_PAIRING_CONN_TRRIGER ,
	SMP_PAIRING_PEER_TRRIGER,
}smp_pairingTrriger_t;









/**************************************************
 * API used for slave enable the device pairing.
 * encrypt_en	SMP_PAIRING_DISABLE_TRRIGER   -  not allow encryption
 * 				SMP_PAIRING_CONN_TRRIGER      -  pairing process start once connect.
 * 				SMP_PAIRING_PEER_TRRIGER      -  pairing process start once peer device start.
 */
int 		bls_smp_enableParing (smp_pairingTrriger_t encrypt_en);



void 		blc_smp_configPairingSecurityInfoStorageAddress (int addr);




ble_sts_t  	blc_smp_param_setBondingDeviceMaxNumber ( int device_num);



u8			blc_smp_param_getCurrentBondingDeviceNumber(void);


u32 		blc_smp_param_loadByIndex(u8 index, smp_param_save_t* smp_param_load);




u32			blc_smp_param_loadByAddr(u8 addr_type, u8* addr, smp_param_save_t* smp_param_load);





void 		blc_smp_param_delete_all(void);






/*************************************************
 * 	@brief 		used for enable authentication MITM
 * 	@return  	0 - setting success
 * 				others - pin code not in ranged.(0 ~ 999,999)
 */
int blc_smp_enableAuthMITM (int en, u32 pinCodeInput);

/*************************************************
 * 	@brief 		used for set MITM protect input pinCode
 * 	@return  	0 - setting failure
 * 				others - pin code in ranged.(0 ~ 999,999)
 */
int blc_smp_set_pinCode(u32 pinCodeInput);

/*************************************************
 * 	@brief 		used for enable authentication bonding flag.
 */
int blc_smp_enableBonding (int en);

/*************************************************
 * 	used for set IO capability
 * */
void blc_smp_setIoCapability (u8 ioCapablility);



void HID_service_on_android7p0_init(void);








//some API name compatible with other versions of SDK

#define bls_smp_configParingSecurityInfoStorageAddr 		blc_smp_configPairingSecurityInfoStorageAddress

#endif /* BLE_SMP_H_ */
