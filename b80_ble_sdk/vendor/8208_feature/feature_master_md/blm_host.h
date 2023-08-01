/********************************************************************************************************
 * @file	blm_host.h
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
#ifndef APP_HOST_H_
#define APP_HOST_H_

#if (FEATURE_TEST_MODE == TEST_MASTER_MD )

#define CHAR_HANDLE_MAX					10

// connection character device information
typedef struct
{
	u16 conn_handle;
	u8 conn_state;
	u8 mac_adrType;
	u8 mac_addr[6];
	u8 char_handle[CHAR_HANDLE_MAX];
}dev_char_info_t;

extern dev_char_info_t cur_conn_device;


typedef void (*main_service_t) (void);

extern main_service_t		main_service;
extern u16 	spp_char_handle;
/**
 * @brief		master dle test in mainloop
 * @param[in]	none
 * @return      none
 */
void feature_mdle_test_mainloop(void);

int controller_event_callback (u32 h, u8 *p, int n);
int app_l2cap_handler (u16 conn_handle, u8 *raw_pkt);
int app_host_smp_finish (void);

void host_update_conn_proc(void);

extern u32 host_update_conn_param_req;
extern int	app_host_smp_sdp_pending;

#endif  //end of (FEATURE_TEST_MODE == xxx)

#endif /* APP_HOST_H_ */
