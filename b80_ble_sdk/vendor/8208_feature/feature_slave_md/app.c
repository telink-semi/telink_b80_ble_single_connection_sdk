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
#include "app_buffer.h"
#include "app_att.h"



#if (FEATURE_TEST_MODE == TEST_SLAVE_MD)


#define MY_APP_ADV_CHANNEL			BLT_ENABLE_ADV_ALL
#define MY_ADV_INTERVAL_MIN			ADV_INTERVAL_30MS
#define MY_ADV_INTERVAL_MAX			ADV_INTERVAL_35MS

#define MY_RF_POWER_INDEX			RF_POWER_P2p87dBm

#define TEST_DATA_LEN		20



u32	advertise_begin_tick;

int write_data_test_tick = 0;

u8	app_test_data[TEST_DATA_LEN]={0x00,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
															  0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x11,0x11,0x11};


/**
 * @brief	BLE Advertising data
 */
const u8	tbl_advData[] = {
	 8,  DT_COMPLETE_LOCAL_NAME, 				'f','e','a','t','u','r','e',
	 2,	 DT_FLAGS, 								0x05, 					// BLE limited discoverable mode and BR/EDR not supported
	 3,  DT_APPEARANCE, 						0x80, 0x01, 			// 384, Generic Remote Control, Generic category
	 5,  DT_INCOMPLT_LIST_16BIT_SERVICE_UUID,	0x12, 0x18, 0x0F, 0x18,	// incomplete list of service class UUIDs (0x1812, 0x180F)
};

/**
 * @brief	BLE Scan Response Packet data
 */
const u8	tbl_scanRsp [] = {
	 8,  DT_COMPLETE_LOCAL_NAME, 				'f','e','a','t','u','r','e',
};









/**
 * @brief      callback function of LinkLayer Event "BLT_EV_FLAG_CONNECT"
 * @param[in]  e - LinkLayer Event type
 * @param[in]  p - data pointer of event
 * @param[in]  n - data length of event
 * @return     none
 */
void task_connect(u8 e, u8 *p, int n)
{

	bls_l2cap_requestConnParamUpdate (CONN_INTERVAL_10MS, CONN_INTERVAL_10MS, 99, CONN_TIMEOUT_4S);  // 1 S

	write_data_test_tick = clock_time();

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
	if(*p == HCI_ERR_CONN_TIMEOUT){

	}
	else if(*p == HCI_ERR_REMOTE_USER_TERM_CONN){  //0x13

	}
	else if(*p == HCI_ERR_CONN_TERM_MIC_FAILURE){

	}
	else{

	}


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
void task_suspend_exit (u8 e, u8 *p, int n)
{
	rf_set_power_level_index (MY_RF_POWER_INDEX);
}



/**
 * @brief      power management code for application
 * @param[in]  none
 * @return     none
 */
void blt_pm_proc(void)
{
	#if(BLE_APP_PM_ENABLE)
		#if (PM_DEEPSLEEP_RETENTION_ENABLE)
			bls_pm_setSuspendMask (SUSPEND_ADV | DEEPSLEEP_RETENTION_ADV | SUSPEND_CONN | DEEPSLEEP_RETENTION_CONN);
		#else
			bls_pm_setSuspendMask (SUSPEND_ADV | SUSPEND_CONN);
		#endif

		#if(UI_KEYBOARD_ENABLE)
			if(scan_pin_need || key_not_released )
			{
				bls_pm_setManualLatency(0);
			}
		#endif
	#endif//END of  BLE_APP_PM_ENABLE
}


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
						ADV_TYPE_CONNECTABLE_UNDIRECTED, OWN_ADDRESS_PUBLIC,
						0,  NULL,
						MY_APP_ADV_CHANNEL,
						ADV_FP_NONE);

	bls_ll_setAdvEnable(BLC_ADV_ENABLE);  //must: set adv enable
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

		blc_smp_peripheral_init();
		blc_smp_setSecurityLevel(Unauthenticated_Paring_with_Encryption);

	#else
		blc_smp_setSecurityLevel(No_Security);
	#endif

	//////////// Host Initialization  End /////////////////////////

//////////////////////////// BLE stack Initialization  End //////////////////////////////////





//////////////////////////// User Configuration for BLE application ////////////////////////////
	u8 status = bls_ll_setAdvParam(  MY_ADV_INTERVAL_MIN, MY_ADV_INTERVAL_MAX,
									 ADV_TYPE_CONNECTABLE_UNDIRECTED, OWN_ADDRESS_PUBLIC,
									 0,  NULL,
									 MY_APP_ADV_CHANNEL,
									 ADV_FP_NONE);
	if(status != BLE_SUCCESS) { 	while(1); }



	bls_ll_setAdvData( (u8 *)tbl_advData, sizeof(tbl_advData) );
	bls_ll_setScanRspData( (u8 *)tbl_scanRsp, sizeof(tbl_scanRsp));

	bls_ll_setAdvEnable(BLC_ADV_ENABLE);  //adv enable


	/* set rf power index, user must set it after every suspend wakeup, cause relative setting will be reset in suspend */
	rf_set_power_level_index (MY_RF_POWER_INDEX);


	bls_app_registerEventCallback (BLT_EV_FLAG_CONNECT, &task_connect);
	bls_app_registerEventCallback (BLT_EV_FLAG_TERMINATE, &task_terminate);
	bls_app_registerEventCallback (BLT_EV_FLAG_SUSPEND_EXIT, &task_suspend_exit);



	///////////////////// Power Management initialization///////////////////
	#if(BLE_APP_PM_ENABLE)
		blc_ll_initPowerManagement_module();        //pm module:      	 optional
		#if (PM_DEEPSLEEP_RETENTION_ENABLE)
			blc_ll_initDeepsleepRetention_module();//Remove it if need save ramcode, and add DeepsleepRetentionEarlyWakeupTiming to 1ms
			bls_pm_setSuspendMask (SUSPEND_ADV | DEEPSLEEP_RETENTION_ADV | SUSPEND_CONN | DEEPSLEEP_RETENTION_CONN);
			blc_pm_setDeepsleepRetentionThreshold(95, 95);
			blc_pm_setDeepsleepRetentionEarlyWakeupTiming(750);
		#else
			bls_pm_setSuspendMask (SUSPEND_ADV | SUSPEND_CONN);
		#endif
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

#if (PM_DEEPSLEEP_RETENTION_ENABLE)
/**
 * @brief		user initialization when MCU wake_up from deepSleep_retention mode
 * @param[in]	none
 * @return      none
 */
_attribute_ram_code_
void user_init_deepRetn(void)
{


	//////////// LinkLayer Initialization  Begin /////////////////////////
	blc_ll_initBasicMCU();                      //mandatory

//////////////////////////// User Configuration for BLE application ////////////////////////////

	/* set rf power index, user must set it after every suspend wakeup, cause relative setting will be reset in suspend */
	rf_set_power_level_index (MY_RF_POWER_INDEX);
	blc_ll_recoverDeepRetention();
	irq_enable();
	#if (UI_KEYBOARD_ENABLE)
		/////////// keyboard gpio wakeup init ////////
		u32 pin[] = KB_DRIVE_PINS;
		for (int i=0; i<(sizeof (pin)/sizeof(*pin)); i++)
		{
			cpu_set_gpio_wakeup (pin[i], Level_High,1);  //drive pin pad high wakeup deepsleep
		}
	#endif
////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif






#if (UI_KEYBOARD_ENABLE)

int 	key_not_released;
u8 		key_type;
static u32 keyScanTick = 0;

extern u32	scan_pin_need;

#define CONSUMER_KEY   	   		1
#define KEYBOARD_KEY   	   		2

/**
 * @brief		this function is used to process keyboard matrix status change.
 * @param[in]	none
 * @return      none
 */
void key_change_proc(void)
{

	u8 key0 = kb_event.keycode[0];
	u8 key_buf[8] = {0,0,0,0,0,0,0,0};

	key_not_released = 1;
	if (kb_event.cnt == 2)   //two key press, do  not process
	{
	}
	else if(kb_event.cnt == 1)
	{
		if(key0 >= CR_VOL_UP )  //volume up/down
		{
			key_type = CONSUMER_KEY;
			u16 consumer_key;
			if(key0 == CR_VOL_UP){  	//volume up
				consumer_key = MKEY_VOL_UP;
			}
			else if(key0 == CR_VOL_DN){ //volume down
				consumer_key = MKEY_VOL_DN;
			}
			blc_gatt_pushHandleValueNotify (BLS_CONN_HANDLE,HID_CONSUME_REPORT_INPUT_DP_H, (u8 *)&consumer_key, 2);
		}
		else
		{
			key_type = KEYBOARD_KEY;
			key_buf[2] = key0;
			blc_gatt_pushHandleValueNotify (BLS_CONN_HANDLE,HID_NORMAL_KB_REPORT_INPUT_DP_H, key_buf, 8);
		}
	}
	else   //kb_event.cnt == 0,  key release
	{
		key_not_released = 0;
		if(key_type == CONSUMER_KEY)
		{
			u16 consumer_key = 0;
			blc_gatt_pushHandleValueNotify ( BLS_CONN_HANDLE,HID_CONSUME_REPORT_INPUT_DP_H, (u8 *)&consumer_key, 2);
		}
		else if(key_type == KEYBOARD_KEY)
		{
			key_buf[2] = 0;
			blc_gatt_pushHandleValueNotify (BLS_CONN_HANDLE,HID_NORMAL_KB_REPORT_INPUT_DP_H, key_buf, 8); //release
		}
	}
}



/**
 * @brief      this function is used to detect if key pressed or released.
 * @param[in]  e - LinkLayer Event type
 * @param[in]  p - data pointer of event
 * @param[in]  n - data length of event
 * @return     none
 */

void proc_keyboard (u8 e, u8 *p, int n)
{
	if(clock_time_exceed(keyScanTick, 8000)){
		keyScanTick = clock_time();
	}
	else{
		return;
	}

	kb_event.keycode[0] = 0;
	int det_key = kb_scan_key (0, 1);

	if (det_key){
		key_change_proc();
	}
}


#endif  //end of UI_KEYBOARD_ENABLE







/**
 * @brief      callback function of LinkLayer Event "BLT_EV_FLAG_SUSPEND_ENTER"
 * @param[in]  e - LinkLayer Event type
 * @param[in]  p - data pointer of event
 * @param[in]  n - data length of event
 * @return     none
 */
void app_set_kb_wakeup(u8 e, u8 *p, int n)
{
#if (BLE_APP_PM_ENABLE)
	if( blc_ll_getCurrentState() == BLS_LINK_STATE_CONN
		&& ((u32)(bls_pm_getSystemWakeupTick() - clock_time())) > 80 *CLOCK_16M_SYS_TIMER_CLK_1MS ){  //suspend time > 30ms.add gpio wakeup
		bls_pm_setWakeupSource(PM_WAKEUP_PAD);  //gpio CORE wakeup suspend
	}
#endif
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

	////////////////////////////////////// UI entry /////////////////////////////////
	#if (UI_KEYBOARD_ENABLE)
		proc_keyboard (0, 0, 0);
	#endif
	
	if(write_data_test_tick && clock_time_exceed(write_data_test_tick, 500)){ // >1s
		write_data_test_tick = clock_time() | 1;

		if(blc_ll_getCurrentState() == BLS_LINK_STATE_CONN)
		{
			if( BLE_SUCCESS == blc_gatt_pushHandleValueNotify (BLS_CONN_HANDLE,SPP_SERVER_TO_CLIENT_DP_H, app_test_data, 20)){
				app_test_data[0] ++;
			}
		}
	}


	////////////////////////////////////// PM Process /////////////////////////////////
	blt_pm_proc();

}

 u8 seq_num_next = 0;

int myC2SWrite(void * p)
{
	rf_packet_att_data_t *req = (rf_packet_att_data_t*)p;

	u8 seq_num = req->dat[0];

	if(seq_num == seq_num_next){

	}
	else{
		write_reg8(0x40000, 0x77);
		irq_disable();

		#if (UI_LED_ENABLE)
			gpio_write(GPIO_LED_WHITE, LED_ON_LEVAL);
		#endif

		while(1);
		write_reg8(0x40000, 0x22);
	}

	seq_num_next = seq_num + 1;

	return 1;
}

#endif //end of (FEATURE_TEST_MODE == xxx)

