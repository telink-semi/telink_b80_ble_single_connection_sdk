/********************************************************************************************************
 * @file	blm_att.h
 *
 * @brief	This is the header file for BLE SDK
 *
 * @author	BLE GROUP
 * @date	06,2020
 *
 * @par     Copyright (c) 2020, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
 *
 *******************************************************************************************************/
#ifndef BLM_ATT_H_
#define BLM_ATT_H_

#if (FEATURE_TEST_MODE == TEST_MDATA_LENGTH_EXTENSION)

/**
 * @brief       this function serves to find handle of uuid16
 * @param[in]	p - pointer of data attribute
 * @param[in]	uuid
 * @param[in]	ref - HID Report
 * @return      0 - fail to find handle of uuid16
 *              1 - the handle of uuid16 that find
 */
u16 blm_att_findHandleOfUuid16 (att_db_uuid16_t *p, u16 uuid, u16 ref);

/**
 * @brief       this function serves to find handle of uuid128
 * @param[in]	p - pointer of data attribute
 * @param[in]	uuid - pointer of uuid
 * @return      0 - fail to find handle of uuid128
 *              1 - the handle of uuid128 that find
 */
u16 blm_att_findHandleOfUuid128 (att_db_uuid128_t *p, const u8 * uuid);
extern const u8 my_SppC2SUUID[16];

#endif  //end of (FEATURE_TEST_MODE == xxx)

#endif /* BLM_ATT_H_ */
