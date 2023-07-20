/********************************************************************************************************
 * @file     app.c
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
#include "stack/ble/ble.h"


#include "app.h"
#include "app_ui.h"
#include "app_buffer.h"

#include "blm_host.h"
#include "blm_pair.h"

#define MY_RF_POWER_INDEX			RF_POWER_P2p87dBm

#define	BLE_DEVICE_ADDRESS_TYPE 	BLE_DEVICE_ADDRESS_PUBLIC

#define 	SCAN_ENTER_DEEP_RETENTION_TIME			60  //10 s
#define 	CONN_ENTER_DEEP_RETENTION_TIME			120  //60 s

u32 latest_user_event_tick;
u8 sendTerminate_before_enterDeep = 0;
/**
 * @brief		user initialization when MCU power on or wake_up from deepSleep mode
 * @param[in]	none
 * @return      none
 */
void user_init_normal(void)
{
	/* random number generator must be initiated here( in the beginning of user_init_normal).
	 * When deepSleep retention wakeUp, no need initialize again */
	random_generator_init();  //this is must

	//////////////////////////// BLE stack Initialization  Begin //////////////////////////////////
	u8 mac_public[6];
	u8 mac_random_static[6];
	blc_initMacAddress(CFG_ADR_MAC, mac_public, mac_random_static);

	#if(BLE_DEVICE_ADDRESS_TYPE == BLE_DEVICE_ADDRESS_RANDOM_STATIC)
		blc_ll_setRandomAddr(mac_random_static);
	#endif

	//////////// LinkLayer Initialization  Begin /////////////////////////
	blc_ll_initBasicMCU();                      //mandatory
	blc_ll_initStandby_module(mac_public);				//mandatory
	blc_ll_initScanning_module(); 			//scan module: 		 mandatory for BLE master,
	blc_ll_initMasterRole_module();//master module: mandatory for BLE master,

	blc_ll_setAclConnMaxOctetsNumber(ACL_CONN_MAX_RX_OCTETS, ACL_CONN_MAX_TX_OCTETS);
	blc_ll_initAclConnTxFifo(app_acl_txfifo, ACL_TX_FIFO_SIZE, ACL_TX_FIFO_NUM);
	blc_ll_initAclConnRxFifo(app_acl_rxfifo, ACL_RX_FIFO_SIZE, ACL_RX_FIFO_NUM);

	u8 check_status = blc_controller_check_appBufferInitialization();
	if(check_status != BLE_SUCCESS){
		/* here user should set some log to know which application buffer incorrect */

		#if(UI_LED_ENABLE) //add some LED to show this error
			gpio_write(GPIO_LED_RED, LED_ON_LEVEL);
			gpio_write(GPIO_LED_WHITE, LED_ON_LEVEL);
		#endif

		while(1);
	}
	//////////// LinkLayer Initialization  End /////////////////////////



	//////////// HCI Initialization  Begin /////////////////////////
	//bluetooth event
	blc_hci_setEventMask_cmd (HCI_EVT_MASK_DISCONNECTION_COMPLETE | HCI_EVT_MASK_ENCRYPTION_CHANGE);

	//bluetooth low energy(LE) event
	blc_hci_le_setEventMask_cmd(		HCI_LE_EVT_MASK_CONNECTION_COMPLETE 		\
									|	HCI_LE_EVT_MASK_ADVERTISING_REPORT 			\
									|   HCI_LE_EVT_MASK_CONNECTION_UPDATE_COMPLETE  \
									|	HCI_LE_EVT_MASK_PHY_UPDATE_COMPLETE			\
									|   HCI_LE_EVT_MASK_CONNECTION_ESTABLISH );         //connection establish: telink private event

	blc_hci_registerControllerEventHandler(controller_event_callback);
	//////////// HCI Initialization  End /////////////////////////


	//////////// Controller Initialization  End /////////////////////////




	//////////// Host Initialization  Begin /////////////////////////
	/* GAP initialization must be done before any other host feature initialization !!! */
	blc_gap_central_init();    //gap initialization

	blc_att_setRxMtuSize(MTU_SIZE_SETTING);
	/* L2CAP Initialization */
	blc_l2cap_register_handler(app_l2cap_handler);
	blc_l2cap_initRxDataBuffer(app_l2cap_rx_fifo, L2CAP_RX_BUFF_SIZE);

	/* SMP Initialization */
	/* SMP Initialization may involve flash write/erase(when one sector stores too much information,
	 *   is about to exceed the sector threshold, this sector must be erased, and all useful information
	 *   should re_stored) , so it must be done after battery check */
	#if (BLE_HOST_SMP_ENABLE)
		bls_smp_configpairingSecurityInfoStorageAddr(FLASH_ADR_SMP_PAIRING);
		blm_smp_registerSmpFinishCb(app_host_smp_finish);

		blc_smp_central_init();

		//SMP trigger by master
		blm_host_smp_setSecurityTrigger(MASTER_TRIGGER_SMP_FIRST_PAIRING | MASTER_TRIGGER_SMP_AUTO_CONNECT);
	#else
		blc_smp_setSecurityLevel(No_Security);
	#endif

		extern int host_att_register_idle_func (void *p);
		host_att_register_idle_func (main_idle_loop);
	//////////// Host Initialization  End /////////////////////////

//////////////////////////// BLE stack Initialization  End //////////////////////////////////


//////////////////////////// User Configuration for BLE application ////////////////////////////
	/* set rf power index, user must set it after every suspend wakeup, cause relative setting will be reset in suspend */
	rf_set_power_level_index (MY_RF_POWER_INDEX);

	blc_ll_setCentralScanParameter(SCAN_TYPE_PASSIVE, SCAN_INTERVAL_100MS, SCAN_INTERVAL_100MS,	\
							OWN_ADDRESS_PUBLIC, SCAN_FP_ALLOW_ADV_ANY);
	blc_ll_setScanEnable (BLC_SCAN_ENABLE, DUP_FILTER_DISABLE);
	latest_user_event_tick = clock_time();
	///////////////////// Power Management initialization///////////////////
	#if(BLE_APP_PM_ENABLE)
		#if(!SAVE_RAM_CODE_ENABLE)
			blc_ll_initDeepsleepRetention_module();//Remove it if need save ramcode.
		#endif
		#if (UI_KEYBOARD_ENABLE)
			/////////// keyboard gpio wakeup init ////////
			cpu_set_gpio_wakeup (GPIO_PF1, Level_High,1);  //drive pin pad high wakeup deepsleep
		#endif
	#endif

}

/**
 * @brief		user initialization when wake_up from deepSleep retention mode
 * @param[in]	none
 * @return      none
 */
void user_init_deepRetn(void)
{
	//////////// LinkLayer Initialization  Begin /////////////////////////
	blc_ll_initBasicMCU();                      //mandatory
	blc_ll_initMasterRole_module();//master module: mandatory for BLE master,

	//////////// LinkLayer Initialization  End /////////////////////////

//////////////////////////// BLE stack Initialization  End //////////////////////////////////


//////////////////////////// User Configuration for BLE application ////////////////////////////
	/* set rf power index, user must set it after every suspend wakeup, cause relative setting will be reset in suspend */
	rf_set_power_level_index (MY_RF_POWER_INDEX);
	blm_ll_recoverDeepRetention();

	blc_ll_setCentralScanParameter(SCAN_TYPE_PASSIVE, SCAN_INTERVAL_100MS, SCAN_INTERVAL_100MS,	\
							OWN_ADDRESS_PUBLIC, SCAN_FP_ALLOW_ADV_ANY);
	blc_ll_setScanEnable (BLC_SCAN_ENABLE, DUP_FILTER_DISABLE);
	latest_user_event_tick = clock_time();
	///////////////////// Power Management initialization///////////////////
	#if(BLE_APP_PM_ENABLE)
		#if (UI_KEYBOARD_ENABLE)
			/////////// keyboard gpio wakeup init ////////
			cpu_set_gpio_wakeup (GPIO_PF1, Level_High,1);  //drive pin pad high wakeup deepsleep
		#endif
	#endif
}

/**
 * @brief      power management code for application
 * @param[in]  none
 * @return     none
 */
void blt_pm_proc(void)
{
	#if(BLE_APP_PM_ENABLE)
		if(  !blc_ll_isControllerEventPending() ){  //no controller event pending
			//adv 60s, deepsleep
			if( blc_ll_getCurrentState() == BLS_LINK_STATE_IDLE)
			{
				sendTerminate_before_enterDeep = 0;
				cpu_sleep_wakeup(DEEPSLEEP_MODE_RET_SRAM_LOW16K, PM_WAKEUP_PAD, 0);  //deepsleep
			}
			//conn 60s no event(key/voice/led), enter deepsleep
			else if( blc_ll_getCurrentState() == BLS_LINK_STATE_CONN &&  \
					clock_time_exceed(latest_user_event_tick, CONN_ENTER_DEEP_RETENTION_TIME * 1000000) )
			{
				if(!sendTerminate_before_enterDeep)
				{
					if(BLE_SUCCESS==blm_ll_disconnect(cur_conn_device.conn_handle, HCI_ERR_REMOTE_USER_TERM_CONN))
					{
						sendTerminate_before_enterDeep = 1;
					}
				}
			}
			else if(blc_ll_getCurrentState() == BLS_LINK_STATE_SCAN && \
					clock_time_exceed(latest_user_event_tick, SCAN_ENTER_DEEP_RETENTION_TIME * 1000000))
			{
				sendTerminate_before_enterDeep = 0;
				blc_ll_setScanEnable(0, 0);
			}
		}
	#endif//END of  BLE_APP_PM_ENABLE
}

#if TEST_MASTER_MD
	u32 write_data_test_tick = 0;
	#define TEST_DATA_LEN		20
	u8	app_test_data[TEST_DATA_LEN]={0x00,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
																  0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x11,0x11,0x11};
	void feature_md_test_mainloop(void)
	{
		if(write_data_test_tick && clock_time_exceed(write_data_test_tick, 500)){ // >1s
			write_data_test_tick = clock_time() | 1;

			if(blc_ll_getCurrentState() == BLS_LINK_STATE_CONN)
			{
				if( BLE_SUCCESS == blc_gatt_pushWriteCommand (cur_conn_device.conn_handle, spp_char_handle, app_test_data, 20)){
					app_test_data[0] ++;
				}
			}
		}
	}
#endif


/**
 * @brief     BLE main idle loop
 * @param[in]  none.
 * @return     none.
 */
int main_idle_loop (void)
{
	////////////////////////////////////// BLE entry /////////////////////////////////
	blm_sdk_main_loop();

	host_pair_unpair_proc();
	#if TEST_MASTER_MD
		feature_md_test_mainloop();
	#endif
	#if TEST_MASTER_DLE
		feature_mdle_test_mainloop();
	#endif
	////////////////////////////////////// UI entry /////////////////////////////////
	#if (UI_LED_ENABLE)
		gpio_write(GPIO_LED_GREEN,1);
	#endif

	#if (UI_KEYBOARD_ENABLE)
		proc_keyboard (0, 0, 0);
	#endif
	//proc conn param update
	if(host_update_conn_param_req){
		host_update_conn_proc();
	}
	blt_pm_proc();

	return 0;
}

/**
 * @brief     BLE main loop
 * @param[in]  none.
 * @return     none.
 */
void main_loop (void)
{
	main_idle_loop ();

	if (main_service)
	{
		main_service ();
		main_service = 0;
	}
}

