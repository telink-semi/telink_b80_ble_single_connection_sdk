/********************************************************************************************************
 * @file	blm_pair.h
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
#ifndef BLM_PAIR_H_
#define BLM_PAIR_H_

#if (FEATURE_TEST_MODE == TEST_MDATA_LENGTH_EXTENSION)


#if (!BLE_HOST_SMP_ENABLE)

	typedef struct{
		u8 manual_pair;
		u8 mac_type;  //address type
		u8 mac[6];
		u32 pair_tick;
	}man_pair_t;

	extern man_pair_t blm_manPair;


	void user_master_host_pairing_management_init(void);
	void user_tbl_salve_mac_unpair_proc(void);
	int user_tbl_slave_mac_search(u8 adr_type, u8 * adr);
	int user_tbl_slave_mac_add(u8 adr_type, u8 *adr);
	int user_tbl_slave_mac_delete_by_adr(u8 adr_type, u8 *adr);

#endif


void app_setCurrentReadReq_attHandle(u16 handle);

/**
 * @brief		host pair or upair proc in main loop
 * @param[in]	none
 * @return      none
 */
void host_pair_unpair_proc(void);



extern int	app_pairing_enable;
extern int app_unpair_enable;

#endif  //end of (FEATURE_TEST_MODE == xxx)

#endif /* APP_PAIR_H_ */
