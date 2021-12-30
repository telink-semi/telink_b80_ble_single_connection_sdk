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








/**
 * @brief		This function is used for slave enable the device pairing.
 * @param[in]	SMP_PAIRING_DISABLE_TRRIGER   -  not allow encryption
 * @param[in]	SMP_PAIRING_CONN_TRRIGER      -  pairing process start once connect.
 * @param[in]	SMP_PAIRING_PEER_TRRIGER      -  pairing process start once peer device start.
 * @param[in]	l2cap_rx_size   - the size of of rx buffer
 * @return		none.
 */
int 		bls_smp_enableParing (smp_pairingTrriger_t encrypt_en);


/**
 * @brief		This function is used to set Pairing message storage address.
 * @param[in]	addr - Pairing message storage address
 * @return		none.
 */
void 		blc_smp_configPairingSecurityInfoStorageAddress (int addr);


/**
 * @brief		This function is used to set maximum bonding device number.
 * @param[in]	device_num - maximum bonding device number.
 * @return		none.
 */
ble_sts_t  	blc_smp_param_setBondingDeviceMaxNumber ( int device_num);


/**
 * @brief		This function is used to get current bonding device number.
 * @return		bonding message number.
 */
u8			blc_smp_param_getCurrentBondingDeviceNumber(void);

/**
 * @brief		This function is used to load smp message.
 * @param[in]	index - load by index .
 * @param[in]	smp_param_load - load buffer.
 * @return		bonding message address.
 */
u32 		blc_smp_param_loadByIndex(u8 index, smp_param_save_t* smp_param_load);


/**
 * @brief		This function is used to load smp message.
 * @param[in]	addr_type - address type.
 * @param[in]	addr - address
 * @param[in]		smp_param_load - message load address.
 * @return		bonding message address.
 */
u32			blc_smp_param_loadByAddr(u8 addr_type, u8* addr, smp_param_save_t* smp_param_load);



/**
 * @brief		This function is used to delete all smp message.
 */

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
