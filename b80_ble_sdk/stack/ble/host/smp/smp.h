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





//See the Core_v5.0(Vol 3/Part C/10.2, Page 2067) for more information.
typedef enum {
	LE_Security_Mode_1_Level_1 = BIT(0),  No_Authentication_No_Encryption			= BIT(0), 	No_Security = BIT(0),
	LE_Security_Mode_1_Level_2 = BIT(1),  Unauthenticated_Paring_with_Encryption 	= BIT(1),
}le_security_mode_level_t;




/**
 * @brief      This function is used to initialize each parameter configuration of SMP, including the initialization of the binding area FLASH.
 * @param[in]  none
 * @return     0: Initialization failed;
 *             1: initialization succeeded.
 */
int 		blc_smp_peripheral_init(void);


/**
 * @brief      This function is used to set security level.
 * @param[in]  mode_level - The security level value can refer to the structure 'le_security_mode_level_t'.
 * @return     none.
 */
void 		blc_smp_setSecurityLevel(le_security_mode_level_t  mode_level);

/**
 * @brief      This function is used to configure the bonding storage address.
 * @param[in]  addr - SMP bonding storage start address.
 * @return     none.
 */
void 		blc_smp_configPairingSecurityInfoStorageAddress (int addr);



/**
 * @brief      This function is used to set the maximum number of devices that can be bound.
 * @param[in]  device_num - Set the maximum number of devices that can be bound.
 * @return     none.
 */
ble_sts_t  	blc_smp_param_setBondingDeviceMaxNumber ( int device_num);


/**
 * @brief      This function is used to get the number of currently bound devices.
 * @param[in]  none.
 * @return     The number of currently bound devices.
 */
u8			blc_smp_param_getCurrentBondingDeviceNumber(void);

/**
 * @brief      This function is used to obtain device binding information based on Index.
 * @param[in]  index - Device bonding index number.
 * @param[out] smp_param_load - The value can refer to the structure 'smp_param_save_t'.
 * @return     0: Failed to load binding information;
 *             others: FLASH address of the information area.
 */
u32 		blc_smp_param_loadByIndex(u8 index, smp_param_save_t* smp_param_load);



/**
 * @brief      This function is used to obtain binding information according to the master address and address type.
 * @param[in]  device_num - Set the maximum number of devices that can be bound.
 * @param[in]  adr_type - Address type.
 * @param[in]  addr - Address.
 * @param[out] smp_param_load - The value can refer to the structure 'smp_param_save_t'.
 * @return     0: Failed to load binding information;
 *             others: FLASH address of the information area.
 */
u32			blc_smp_param_loadByAddr(u8 addr_type, u8* addr, smp_param_save_t* smp_param_load);

/**
 * @brief      This function is used for the slave device to clear all binding information stored in the local FLASH.
 * @param[in]  none.
 * @return     none.
 */
void 		blc_smp_param_delete_all(void);







#endif /* BLE_SMP_H_ */
