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
#include "app_att.h"
#include "app_ui.h"
#include "app_buffer.h"

#define 	ADV_IDLE_ENTER_DEEP_TIME			60  //60 s
#define 	CONN_IDLE_ENTER_DEEP_TIME			60  //60 s


#define MY_APP_ADV_CHANNEL			BLT_ENABLE_ADV_ALL
#define MY_ADV_INTERVAL_MIN			ADV_INTERVAL_30MS
#define MY_ADV_INTERVAL_MAX			ADV_INTERVAL_35MS

#define MY_RF_POWER_INDEX			RF_POWER_P2p87dBm

#define MY_DIRECT_ADV_TMIE			10000000

#define	BLE_DEVICE_ADDRESS_TYPE 	BLE_DEVICE_ADDRESS_PUBLIC



_attribute_data_retention_	int device_in_connection_state;
_attribute_data_retention_ u32	advertise_begin_tick;
#if (PM_DEEPSLEEP_ENABLE)
_attribute_data_retention_ u8  sendTerminate_before_enterDeep = 0;
#endif

_attribute_data_retention_ own_addr_type_t app_own_address_type = OWN_ADDRESS_PUBLIC;



/**
 * @brief	BLE Advertising data
 */
const u8	tbl_advData[] = {
	 8,  DT_COMPLETE_LOCAL_NAME, 				'e', 'S', 'a', 'm', 'p', 'l', 'e',
	 2,	 DT_FLAGS, 								0x05, 					// BLE limited discoverable mode and BR/EDR not supported
	 3,  DT_APPEARANCE, 						0x80, 0x01, 			// 384, Generic Remote Control, Generic category
	 5,  DT_INCOMPLT_LIST_16BIT_SERVICE_UUID,	0x12, 0x18, 0x0F, 0x18,	// incomplete list of service class UUIDs (0x1812, 0x180F)
};

/**
 * @brief	BLE Scan Response Packet data
 */
const u8	tbl_scanRsp [] = {
	 8,  DT_COMPLETE_LOCAL_NAME, 				'e', 'S', 'a', 'm', 'p', 'l', 'e',
};






/**
 * @brief      callback function of LinkLayer Event "BLT_EV_FLAG_ADV_DURATION_TIMEOUT"
 * @param[in]  e - LinkLayer Event type
 * @param[in]  p - data pointer of event
 * @param[in]  n - data length of event
 * @return     none
 */
void app_switch_to_indirect_adv(u8 e, u8 *p, int n)
{
	bls_ll_setAdvParam( MY_ADV_INTERVAL_MIN, MY_ADV_INTERVAL_MAX,
						ADV_TYPE_CONNECTABLE_UNDIRECTED, app_own_address_type,
						0,  NULL,
						MY_APP_ADV_CHANNEL,
						ADV_FP_NONE);

	bls_ll_setAdvEnable(BLC_ADV_ENABLE);  //must: set adv enable
}





/**
 * @brief      callback function of LinkLayer Event "BLT_EV_FLAG_CONNECT"
 * @param[in]  e - LinkLayer Event type
 * @param[in]  p - data pointer of event
 * @param[in]  n - data length of event
 * @return     none
 */
void task_connect(u8 e, u8 *p, int n)
{

	bls_l2cap_requestConnParamUpdate (CONN_INTERVAL_10MS, CONN_INTERVAL_10MS, 99, CONN_TIMEOUT_8S);  // 1 S

	latest_user_event_tick = clock_time();
	device_in_connection_state = 1;
	#if (UI_LED_ENABLE)
		gpio_write(GPIO_LED_RED, LED_ON_LEVAL);
	#endif
}



/**
 * @brief      callback function of LinkLayer Event "BLT_EV_FLAG_TERMINATE"
 * @param[in]  e - LinkLayer Event type
 * @param[in]  p - data pointer of event
 * @param[in]  n - data length of event
 * @return     none
 */
void task_terminate(u8 e,u8 *p, int n) //*p is terminate reason
{
	device_in_connection_state = 0;
	if(*p == HCI_ERR_CONN_TIMEOUT){

	}
	else if(*p == HCI_ERR_REMOTE_USER_TERM_CONN){  //0x13

	}
	else if(*p == HCI_ERR_CONN_TERM_MIC_FAILURE){

	}
	else{

	}

	#if (PM_DEEPSLEEP_ENABLE)
		 //user has push terminate pkt to ble TX buffer before deepsleep
		if(sendTerminate_before_enterDeep == 1){
			sendTerminate_before_enterDeep = 2;
		}
	#endif


	#if (UI_LED_ENABLE)
		gpio_write(GPIO_LED_RED, !LED_ON_LEVAL);  //light off
	#endif

	advertise_begin_tick = clock_time();
}



/**
 * @brief      callback function of LinkLayer Event "BLT_EV_FLAG_SUSPEND_EXIT"
 * @param[in]  e - LinkLayer Event type
 * @param[in]  p - data pointer of event
 * @param[in]  n - data length of event
 * @return     none
 */
_attribute_ram_code_ void user_set_rf_power (u8 e, u8 *p, int n)
{
	rf_set_power_level_index (MY_RF_POWER_INDEX);
}




/**
 * @brief      power management code for application
 * @param	   none
 * @return     none
 */
void blt_pm_proc(void)
{
#if(BLE_APP_PM_ENABLE)
		#if (UI_KEYBOARD_ENABLE)
			bls_pm_setSuspendMask (SUSPEND_ADV | SUSPEND_CONN);

		#if (BLE_OTA_SERVER_ENABLE)
			if(ota_is_working || scan_pin_need || key_not_released )
			{
				bls_pm_setSuspendMask(SUSPEND_DISABLE);
			}
		#else
			if(scan_pin_need || key_not_released )
			{
				bls_pm_setManualLatency(0);
			}
		#endif
		#endif

#if (PM_DEEPSLEEP_ENABLE)   //test connection power, should disable deepSleep
		if(sendTerminate_before_enterDeep == 2){  //Terminate OK
			cpu_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_PAD, 0);  //deepSleep
		}


		if(  !blc_ll_isControllerEventPending() ){  //no controller event pending
			//adv 60s, deepsleep
			if( blc_ll_getCurrentState() == BLS_LINK_STATE_ADV && !sendTerminate_before_enterDeep && \
				clock_time_exceed(advertise_begin_tick , ADV_IDLE_ENTER_DEEP_TIME * 1000000))
			{
				cpu_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_PAD, 0);  //deepsleep
			}
			//conn 60s no event(key/voice/led), enter deepsleep
			else if( device_in_connection_state && \
					clock_time_exceed(latest_user_event_tick, CONN_IDLE_ENTER_DEEP_TIME * 1000000) )
			{

				bls_ll_terminateConnection(HCI_ERR_REMOTE_USER_TERM_CONN); //push terminate cmd into ble TX buffer
				bls_ll_setAdvEnable(0);   //disable adv
				sendTerminate_before_enterDeep = 1;
			}
		}
#endif  //end of !TEST_CONN_CURRENT_ENABLE
#endif//END of  BLE_APP_PM_ENABLE
}





/**
 * @brief		user initialization when MCU power on or wake_up from deepSleep mode
 * @param[in]	none
 * @return      none
 */
void user_init_normal(void)
{
	/* random number generator must be initiated here( in the beginning of user_init_nromal).
	 * When deepSleep retention wakeUp, no need initialize again */
	random_generator_init();  //this is must

	//////////////////////////// BLE stack Initialization  Begin //////////////////////////////////
	u8 mac_public[6];
	u8 mac_random_static[6];
	blc_initMacAddress(CFG_ADR_MAC, mac_public, mac_random_static);


	#if(BLE_DEVICE_ADDRESS_TYPE == BLE_DEVICE_ADDRESS_PUBLIC)
		app_own_address_type = OWN_ADDRESS_PUBLIC;
	#elif(BLE_DEVICE_ADDRESS_TYPE == BLE_DEVICE_ADDRESS_RANDOM_STATIC)
		app_own_address_type = OWN_ADDRESS_RANDOM;
		blc_ll_setRandomAddr(mac_random_static);
	#endif

	//////////// LinkLayer Initialization  Begin /////////////////////////



	blc_ll_initBasicMCU();                      //mandatory
	blc_ll_initStandby_module(mac_public);				//mandatory
	blc_ll_initAdvertising_module();//adv module: mandatory for BLE slave,
	blc_ll_initSlaveRole_module();//slave module: mandatory for BLE slave,

	blc_ll_setAclConnMaxOctetsNumber(ACL_CONN_MAX_RX_OCTETS, ACL_CONN_MAX_TX_OCTETS);
	blc_ll_initAclConnTxFifo(app_acl_txfifo, ACL_TX_FIFO_SIZE, ACL_TX_FIFO_NUM);
	blc_ll_initAclConnRxFifo(app_acl_rxfifo, ACL_RX_FIFO_SIZE, ACL_RX_FIFO_NUM);

	u8 check_status = blc_controller_check_appBufferInitialization();
	if(check_status != BLE_SUCCESS){
		/* here user should set some log to know which application buffer incorrect */
		while(1);
	}
	//////////// LinkLayer Initialization  End /////////////////////////



	//////////// HCI Initialization  Begin /////////////////////////

	//////////// HCI Initialization  End /////////////////////////


	//////////// Controller Initialization  End /////////////////////////



	//////////// Host Initialization  Begin /////////////////////////
	/* GAP initialization must be done before any other host feature initialization !!! */
	blc_gap_peripheral_init();    //gap initialization

	/* GATT Initialization */
	my_gatt_init();

	/* L2CAP Initialization */
	blc_l2cap_register_handler(blc_l2cap_packet_receive);
	blc_l2cap_initRxDataBuffer(app_l2cap_rx_fifo, L2CAP_RX_BUFF_SIZE);


	/* SMP Initialization */
	/* SMP Initialization may involve flash write/erase(when one sector stores too much information,
	 *   is about to exceed the sector threshold, this sector must be erased, and all useful information
	 *   should re_stored) , so it must be done after battery check */
	#if (APP_SECURITY_ENABLE)
		blc_smp_configPairingSecurityInfoStorageAddress(FLASH_ADR_SMP_PAIRING);
		blc_smp_param_setBondingDeviceMaxNumber(4);  	//default is 4, can not bigger than this value
													    //and this func must call before bls_smp_enableParing
		bls_smp_enableParing (SMP_PAIRING_CONN_TRRIGER );
	#else
		bls_smp_enableParing (SMP_PAIRING_DISABLE_TRRIGER );
	#endif

	//////////// Host Initialization  End /////////////////////////

//////////////////////////// BLE stack Initialization  End //////////////////////////////////





//////////////////////////// User Configuration for BLE application ////////////////////////////
	#if(APP_SECURITY_ENABLE)
		u8 bond_number = blc_smp_param_getCurrentBondingDeviceNumber(); 		//get bonded device number
		smp_param_save_t  bondInfo;
		if(bond_number)   //at least 1 bonding device exist
		{
			//get the latest bonding device (index: bond_number-1 )
			blc_smp_param_loadByIndex( bond_number - 1, &bondInfo);
		}

		if(bond_number)//set direct adv
		{
			//set direct adv
			u8 status = bls_ll_setAdvParam( MY_ADV_INTERVAL_MIN, MY_ADV_INTERVAL_MAX,
											ADV_TYPE_CONNECTABLE_DIRECTED_LOW_DUTY, app_own_address_type,
											bondInfo.peer_addr_type,  bondInfo.peer_addr,
											MY_APP_ADV_CHANNEL,
											ADV_FP_NONE);
			//debug: ADV setting err
			if(status != BLE_SUCCESS) { while(1); }

			//it is recommended that direct adv only last for several seconds, then switch to indirect adv
			bls_ll_setAdvDuration(MY_DIRECT_ADV_TMIE, 1);
			bls_app_registerEventCallback (BLT_EV_FLAG_ADV_DURATION_TIMEOUT, &app_switch_to_indirect_adv);
		}
		else//set indirect ADV
	#endif
		{
			u8 status = bls_ll_setAdvParam(  MY_ADV_INTERVAL_MIN, MY_ADV_INTERVAL_MAX,
											 ADV_TYPE_CONNECTABLE_UNDIRECTED, app_own_address_type,
											 0,  NULL,
											 MY_APP_ADV_CHANNEL,
											 ADV_FP_NONE);
			if(status != BLE_SUCCESS) { 	while(1); }
		}


	bls_ll_setAdvData( (u8 *)tbl_advData, sizeof(tbl_advData) );
	bls_ll_setScanRspData( (u8 *)tbl_scanRsp, sizeof(tbl_scanRsp));

	bls_ll_setAdvEnable(BLC_ADV_ENABLE);  //adv enable


	/* set rf power index, user must set it after every suspend wakeup, cause relative setting will be reset in suspend */
	user_set_rf_power(0, 0, 0);


	bls_app_registerEventCallback (BLT_EV_FLAG_CONNECT, &task_connect);
	bls_app_registerEventCallback (BLT_EV_FLAG_TERMINATE, &task_terminate);
	bls_app_registerEventCallback (BLT_EV_FLAG_SUSPEND_EXIT, &user_set_rf_power);



	#if(BLE_OTA_SERVER_ENABLE)
		/* OTA module initialization must be called after "blc_ota_setNewFirmwwareStorageAddress"(if used), and before any other OTA API.*/
		blc_ota_initOtaServer_module();

		blc_ota_registerOtaStartCmdCb(app_enter_ota_mode);
		blc_ota_registerOtaResultIndicationCb(app_ota_result);
	#endif



	///////////////////// Power Management initialization///////////////////
	#if(BLE_APP_PM_ENABLE)
		blc_ll_initPowerManagement_module();        //pm module:      	 optional
		bls_pm_setSuspendMask (SUSPEND_ADV | SUSPEND_CONN);
		bls_app_registerEventCallback (BLT_EV_FLAG_SUSPEND_ENTER, &app_set_kb_wakeup);
	#else
		bls_pm_setSuspendMask (SUSPEND_DISABLE);
	#endif

	#if (UI_KEYBOARD_ENABLE)
		/////////// keyboard gpio wakeup init ////////
		u32 pin[] = KB_DRIVE_PINS;
		for (int i=0; i<(sizeof (pin)/sizeof(*pin)); i++)
		{
			cpu_set_gpio_wakeup (pin[i], Level_High,1);  //drive pin pad high wakeup deepsleep
		}

		bls_app_registerEventCallback (BLT_EV_FLAG_GPIO_EARLY_WAKEUP, &proc_keyboard);
	#endif
////////////////////////////////////////////////////////////////////////////////////////////////



	advertise_begin_tick = clock_time();
}




/**
 * @brief     BLE main loop
 * @param[in]  none.
 * @return     none.
 */
void main_loop (void)
{

	////////////////////////////////////// BLE entry /////////////////////////////////
	blc_sdk_main_loop();
#if (UI_LED_ENABLE)
	gpio_write(GPIO_LED_GREEN,1);
#endif
	////////////////////////////////////// UI entry /////////////////////////////////
	#if (UI_KEYBOARD_ENABLE)
		proc_keyboard (0, 0, 0);
	#endif


	////////////////////////////////////// PM Process /////////////////////////////////
	blt_pm_proc();

}

