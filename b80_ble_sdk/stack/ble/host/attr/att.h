/********************************************************************************************************
 * @file     att.h
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

#include "tl_common.h"


/** @defgroup ATT_PERMISSIONS_BITMAPS GAP ATT Attribute Access Permissions Bit Fields
 * @{
 * (See the Core_v5.0(Vol 3/Part C/10.3.1/Table 10.2) for more information)
 */
#define ATT_PERMISSIONS_READ                 0x01 //!< Attribute is Readable
#define ATT_PERMISSIONS_WRITE                0x02 //!< Attribute is Writable
#define ATT_PERMISSIONS_AUTHEN_READ          0x04 //!< Read requires Authentication
#define ATT_PERMISSIONS_AUTHEN_WRITE         0x08 //!< Write requires Authentication
#define ATT_PERMISSIONS_AUTHOR_READ          0x10 //!< Read requires Authorization
#define ATT_PERMISSIONS_AUTHOR_WRITE         0x20 //!< Write requires Authorization
#define ATT_PERMISSIONS_ENCRYPT_READ         0x40 //!< Read requires Encryption
#define ATT_PERMISSIONS_ENCRYPT_WRITE        0x80 //!< Write requires Encryption

#define ATT_PERMISSIONS_RDWR	             0x03  // ATT_PERMISSIONS_READ | ATT_PERMISSIONS_WRITE

/** @} End GAP_ATT_PERMISSIONS_BITMAPS */



/** @addtogroup GATT_Characteristic_Property GATT characteristic properties
 * @{
 */
#define CHAR_PROP_BROADCAST              0x01 //!< permit broadcasts of the Characteristic Value
#define CHAR_PROP_READ                   0x02 //!< permit reads of the Characteristic Value
#define CHAR_PROP_WRITE_WITHOUT_RSP      0x04 //!< Permit writes of the Characteristic Value without response
#define CHAR_PROP_WRITE                  0x08 //!< Permit writes of the Characteristic Value with response
#define CHAR_PROP_NOTIFY                 0x10 //!< Permit notifications of a Characteristic Value without acknowledgement
#define CHAR_PROP_INDICATE               0x20 //!< Permit indications of a Characteristic Value with acknowledgement
#define CHAR_PROP_AUTHEN                 0x40 //!< permit signed writes to the Characteristic Value
#define CHAR_PROP_EXTENDED               0x80 //!< additional characteristic properties are defined
/** @} end of group GATT_Characteristic_Property */









typedef int (*att_handleValueConfirm_callback_t)(void);
typedef int (*att_readwrite_callback_t)(void* p);
typedef void (*attRxMtuSizeExchangeCommpleteCb)(u16 connHandle, u16 remoteMtuSize, u16 effectMtuSize);

typedef struct attribute
{
  u16 attNum;
  u8  perm;
  u8  uuidLen;
  u32 attrLen;    //4 bytes aligned
  u8* uuid;
  u8* pAttrValue;
  att_readwrite_callback_t w;
  att_readwrite_callback_t r;
} attribute_t;







/******************************* User Interface  ************************************/
//GATT server table
/**
 * @brief	This function is used to set ATT table
 * @param	*p - the pointer of attribute table
 * @return	none.
 */
void bls_att_setAttributeTable(u8 *p);

void bls_att_registerHandleValueConfirmCb(att_handleValueConfirm_callback_t cb);

//MTU size
/**
 * @brief	This function is used to set RX MTU size
 * @param	mtu_size - ATT MTU size
 * @return	0: success
 * 			other: fail
 */
ble_sts_t blc_att_setRxMtuSize(u16 mtu_size);
/**
 * @brief	This function is used to request MTU size exchange
 * @param	connHandle - connect handle
 * @param	mtu_size - ATT MTU size
 * @return	0: success
 * 			other: fail
 */
//Attention: this API hide in stack, user no need use !!!
ble_sts_t blc_att_requestMtuSizeExchange(u16 connHandle, u16 mtu_size);
void blc_att_registerMtuSizeExchangeCb(attRxMtuSizeExchangeCommpleteCb cb);
void blt_att_resetMtuSizeToDefault(void);

/**
 * @brief   This function is used to get effective MTU size.
 * @param	connHandle - connect handle
 * @return  effective MTU value.
 */
u16  blc_att_getEffectiveMtuSize(void);


int l2cap_att_client_handler (u16 conn, u8 *p);
