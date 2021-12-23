/********************************************************************************************************
 * @file     ll_whitelist.h 
 *
 * @brief    for TLSR chips
 *
 * @author	 BLE Group
 * @date     Sep. 18, 2015
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

#ifndef LL_WHITELIST_H_
#define LL_WHITELIST_H_

#include "stack/ble/ble_common.h"



/**************************************** User Interface  **********************************************/


/*********************************************************************
 * @fn      ll_whiteList_reset
 *
 * @brief   API to reset the white list table.
 *
 * @param   None
 *
 * @return  LL Status
 */
ble_sts_t ll_whiteList_reset(void);

/*********************************************************************
 * @fn      ll_whiteList_add
 *
 * @brief   API to add new entry to white list
 *
 * @param   None
 *
 * @return  LL Status
 */
ble_sts_t ll_whiteList_add(u8 type, u8 *addr);

/*********************************************************************
 * @fn      ll_whiteList_delete
 *
 * @brief   API to delete entry from white list
 *
 * @param   type - The specified type
 *          addr - The specified address to be delete
 *
 * @return  LL Status
 */
ble_sts_t ll_whiteList_delete(u8 type, u8 *addr);

/*********************************************************************
 * @fn      ll_whiteList_getSize
 *
 * @brief   API to get total number of white list entry size
 *
 * @param   returnSize - The returned entry size
 *
 * @return  LL Status
 */
ble_sts_t ll_whiteList_getSize(u8 *returnPublicAddrListSize) ;






ble_sts_t  ll_resolvingList_add(u8 peerIdAddrType, u8 *peerIdAddr, u8 *peer_irk, u8 *local_irk);
ble_sts_t  ll_resolvingList_delete(u8 peerIdAddrType, u8 *peerIdAddr);

ble_sts_t  ll_resolvingList_reset(void);
ble_sts_t  ll_resolvingList_getSize(u8 *Size);

ble_sts_t  ll_resolvingList_getPeerResolvableAddr (u8 peerIdAddrType, u8* peerIdAddr, u8* peerResolvableAddr); //not available now
ble_sts_t  ll_resolvingList_getLocalResolvableAddr(u8 peerIdAddrType, u8* peerIdAddr, u8* LocalResolvableAddr); //not available now

ble_sts_t  ll_resolvingList_setAddrResolutionEnable (u8 resolutionEn);

ble_sts_t  ll_resolvingList_setResolvablePrivateAddrTimer (u16 timeout_s);   //not available now






#endif /* LL_WHITELIST_H_ */
