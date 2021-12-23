/********************************************************************************************************
 * @file     app.c
 *
 * @brief    for TLSR chips
 *
 * @author	 BLE Group
 * @date     May. 12, 2018
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
#include "tl_common.h"
#include "drivers.h"
#include "stack/ble/ble.h"

#include "app.h"
#include "../default_att.h"

#if(INTERNAL_TEST_MODE == TEST_SLAVE_MD)


#define ADV_IDLE_ENTER_DEEP_TIME	60  //60 s
#define CONN_IDLE_ENTER_DEEP_TIME	60  //60 s

#define MY_ADV_INTERVAL_MIN			ADV_INTERVAL_30MS
#define MY_ADV_INTERVAL_MAX			ADV_INTERVAL_35MS

#define	BLE_DEVICE_ADDRESS_TYPE 	BLE_DEVICE_ADDRESS_PUBLIC
own_addr_type_t app_own_address_type = OWN_ADDRESS_PUBLIC;

#define TEST_DATA_LEN		20

MYFIFO_INIT(blt_rxfifo, 64, 8);
MYFIFO_INIT(blt_txfifo, 40, 16);

/* ADV Packet, SCAN Response Packet define */
const u8 tbl_advData[] = {
	 0x05, 0x09, 'E', 'h', 'i', 'd',
	 0x02, 0x01, 0x05, 							// BLE limited discoverable mode and BR/EDR not supported
	 0x03, 0x19, 0x80, 0x01, 					// 384, Generic Remote Control, Generic category
	 0x05, 0x02, 0x12, 0x18, 0x0F, 0x18,		// incomplete list of service class UUIDs (0x1812, 0x180F)
};

const u8 tbl_scanRsp [] = {
	0x08, 0x09, 'E', 'R', 'e', 'm', 'o', 't', 'e',
};


u8 user_task_flg;
u8 sendTerminate_before_enterDeep = 0;
u32 interval_update_tick = 0;
int device_in_connection_state;
u32	advertise_begin_tick;
u32 lowBattDet_tick = 0;
int ui_mtu_size_exchange_req = 0;
u32 latest_user_event_tick;
int write_data_test_tick = 0;

_attribute_data_retention_	u8	app_test_data[TEST_DATA_LEN]={0x00,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
															  0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x11,0x11,0x11};

#if (STUCK_KEY_PROCESS_ENABLE)
	u32 stuckKey_keyPressTime;
#endif


/*----------------------------------------------------------------------------*/
/*------------- CallBack function of BLE                      ----------------*/
/*----------------------------------------------------------------------------*/
void app_switch_to_indirect_adv(u8 e, u8 *p, int n)
{
	bls_ll_setAdvParam( MY_ADV_INTERVAL_MIN, MY_ADV_INTERVAL_MAX,
						ADV_TYPE_CONNECTABLE_UNDIRECTED, app_own_address_type,
						0,  NULL,
						BLT_ENABLE_ADV_ALL,
						ADV_FP_NONE);

	bls_ll_setAdvEnable(1);  //must: set adv enable
}

void ble_remote_terminate(u8 e,u8 *p, int n) //*p is terminate reason
{
	device_in_connection_state = 0;

	gpio_write(LED_RED,0);

#if (WHILE_WHEN_TERMINATE)

	u32	tmp_tick = clock_time();
	while(1)
	{
		if(clock_time_exceed(tmp_tick,100000))
		{
			gpio_toggle(LED_GREEN);
			tmp_tick = clock_time();
		}
	}

#endif

	if(*p == HCI_ERR_CONN_TIMEOUT){

	}else if(*p == HCI_ERR_REMOTE_USER_TERM_CONN){  //0x13

	}else if(*p == HCI_ERR_CONN_TERM_MIC_FAILURE){

	}else{

	}

#if (BLE_REMOTE_PM_ENABLE)
	 //user has push terminate pkt to ble TX buffer before deepsleep
	if(sendTerminate_before_enterDeep == 1){
		sendTerminate_before_enterDeep = 2;
	}
#endif


	advertise_begin_tick = clock_time();
}

void task_connect(u8 e, u8 *p, int n)
{
	gpio_write(LED_RED,1);

	write_data_test_tick = clock_time();

	bls_l2cap_requestConnParamUpdate (8, 8, 99, 400);  //interval=10ms latency=99 timeout=4s

	latest_user_event_tick = clock_time();

	ui_mtu_size_exchange_req = 1;

	device_in_connection_state = 1;//

	interval_update_tick = clock_time() | 1; //none zero
}

volatile u8	AA_test_table[32];

void task_scan_rsp(u8 e, u8 *p, int n)
{
	memcpy(AA_test_table,p,n);
}

//_attribute_ram_code_
void blt_pm_proc(void)
{
	bls_pm_setSuspendMask(SUSPEND_DISABLE);

  #if(BLE_REMOTE_PM_ENABLE)
	{
		bls_pm_setSuspendMask (SUSPEND_ADV | SUSPEND_CONN);

//		user_task_flg = key_not_release;	TODO yy
		user_task_flg = 1;

		if(user_task_flg){
			bls_pm_setManualLatency(0);
		}


	#if(RC_DEEP_SLEEP_EN) //deepsleep
		if(sendTerminate_before_enterDeep == 1){ //sending Terminate and wait for ack before enter deepsleep
			if(user_task_flg){  //detect key Press again,  can not enter deep now
				sendTerminate_before_enterDeep = 0;
				bls_ll_setAdvEnable(1);   //enable adv again
			}
		}
		else if(sendTerminate_before_enterDeep == 2){  //Terminate OK
			analog_write(DEEP_ANA_REG0, CONN_DEEP_FLG);

			cpu_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_PAD, 0);  //deepsleep
		}

		//adv 60s, deepsleep
		if( blc_ll_getCurrentState() == BLS_LINK_STATE_ADV && !sendTerminate_before_enterDeep && \
			clock_time_exceed(advertise_begin_tick , ADV_IDLE_ENTER_DEEP_TIME * 1000000))
		{

			cpu_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_PAD, 0);  //deepsleep
		}
		//conn 60s no event(key/voice/led), enter deepsleep
		else if( device_in_connection_state && !user_task_flg && \
				clock_time_exceed(latest_user_event_tick, CONN_IDLE_ENTER_DEEP_TIME * 1000000) )
		{

			bls_ll_terminateConnection(HCI_ERR_REMOTE_USER_TERM_CONN); //push terminate cmd into ble TX buffer
			bls_ll_setAdvEnable(0);   //disable adv
			sendTerminate_before_enterDeep = 1;
		}
	#endif
	}
  #endif//END of  BLE_REMOTE_PM_ENABLE
}


void  ble_remote_set_sleep_wakeup(u8 e, u8 *p, int n)
{
	if( blc_ll_getCurrentState() == BLS_LINK_STATE_CONN
		&& ((u32)(bls_pm_getSystemWakeupTick() - clock_time())) > 80 *CLOCK_16M_SYS_TIMER_CLK_1MS ){  //suspend time > 30ms.add gpio wakeup
		bls_pm_setWakeupSource(PM_WAKEUP_PAD);  //gpio CORE wakeup suspend
	}
}


void user_init()
{
	/*
	 ***************************************************************************
	 * Keyboard matrix initialization. These section must be before battery_power_check.
	 * Because when low battery,chip will entry deep.if placed after battery_power_check,
	 * it is possible that can not wake up chip.
	 ***************************************************************************
	 */
  #if(RC_BTN_ENABLE)
	for(int i=0; i<(sizeof (ctrl_btn)/sizeof(*ctrl_btn)); i++){
//		gpio_set_wakeup(ctrl_btn[i],0,1);  	    //drive pin core(gpio) high wakeup suspend
		cpu_set_gpio_wakeup (ctrl_btn[i],0,1);  //drive pin pad high wakeup deepsleep
	}
  #endif

	/*-- BLE stack initialization --------------------------------------------*/
	u8 mac_public[6];
	u8 mac_random_static[6];
	blc_initMacAddress(CFG_ADR_MAC_512K_FLASH, mac_public, mac_random_static);

  #if(BLE_DEVICE_ADDRESS_TYPE == BLE_DEVICE_ADDRESS_PUBLIC)
	app_own_address_type = OWN_ADDRESS_PUBLIC;
  #elif(BLE_DEVICE_ADDRESS_TYPE == BLE_DEVICE_ADDRESS_RANDOM_STATIC)
	app_own_address_type = OWN_ADDRESS_RANDOM;
	blc_ll_setRandomAddr(mac_random_static);
  #endif

	/*-- BLE Controller initialization ---------------------------------------*/
	blc_ll_initBasicMCU(mac_public);//mandatory
	blc_ll_initAdvertising_module(mac_public);//adv module: mandatory for BLE slave,
	blc_ll_initSlaveRole_module();//slave module: mandatory for BLE slave,

	/*-- BLE Host initialization ---------------------------------------------*/
	extern void my_att_init(void);
	//GATT initialization
	my_att_init();
	//L2CAP initialization
	blc_l2cap_register_handler(blc_l2cap_packet_receive);

	/*-- BLE SMP initialization ----------------------------------------------*/
  #if (BLE_REMOTE_SECURITY_ENABLE)
	blc_smp_param_setBondingDeviceMaxNumber(4);  	//default is SMP_BONDING_DEVICE_MAX_NUM, can not bigger that this value
													//and this func must call before bls_smp_enableParing
	bls_smp_enableParing (SMP_PARING_CONN_TRRIGER );
  #else
	bls_smp_enableParing (SMP_PARING_DISABLE_TRRIGER );
  #endif

	//HID_service_on_android7p0_init();  //hid device on android 7.0/7.1

	/*-- USER application initialization -------------------------------------*/
	bls_ll_setAdvData( (u8 *)tbl_advData, sizeof(tbl_advData) );
	bls_ll_setScanRspData( (u8 *)tbl_scanRsp, sizeof(tbl_scanRsp));

	/* Configure ADV packet */
  #if(BLE_REMOTE_SECURITY_ENABLE)
	//get bonded device number
	u8 bond_number = blc_smp_param_getCurrentBondingDeviceNumber();
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
										BLT_ENABLE_ADV_ALL,
										ADV_FP_NONE);
		//debug: ADV setting err
		if(status != BLE_SUCCESS) { write_reg8(0x8000, 0x11); 	while(1); }

		//it is recommended that direct adv only last for several seconds, then switch to indirect adv
		bls_ll_setAdvDuration(2000000, 1);
		bls_app_registerEventCallback (BLT_EV_FLAG_ADV_DURATION_TIMEOUT, &app_switch_to_indirect_adv);
	}
	else//set indirect ADV
  #endif
	{
		u8 status = bls_ll_setAdvParam(  MY_ADV_INTERVAL_MIN, MY_ADV_INTERVAL_MAX,
										 ADV_TYPE_CONNECTABLE_UNDIRECTED, app_own_address_type,
										 0,  NULL,
										 BLT_ENABLE_ADV_ALL,
										 ADV_FP_NONE);
		//debug: ADV setting err
		if(status != BLE_SUCCESS) { write_reg8(0x8000, 0x11); 	while(1); }
	}

	bls_ll_setAdvEnable(1);  //adv enable
	rf_set_power_level_index (RF_POWER_P6p97dBm);//OK

	//ble event call back
	bls_app_registerEventCallback (BLT_EV_FLAG_CONNECT, &task_connect);
	bls_app_registerEventCallback (BLT_EV_FLAG_TERMINATE, &ble_remote_terminate);
//	bls_app_registerEventCallback (BLT_EV_FLAG_SCAN_RSP, &task_scan_rsp);

	/* Power Management initialization */
#if(BLE_REMOTE_PM_ENABLE)
	blc_ll_initPowerManagement_module();        //pm module:      	 optional
	bls_pm_setSuspendMask (SUSPEND_ADV | SUSPEND_CONN);
	bls_app_registerEventCallback (BLT_EV_FLAG_SUSPEND_ENTER, &ble_remote_set_sleep_wakeup);
#else
	bls_pm_setSuspendMask (SUSPEND_DISABLE);
#endif

#if(LED_EN)

	reg_gpio_pa_gpio = 0xf1;	// A0, A4~A7
	reg_gpio_pa_oen = 0xe;
	reg_gpio_pb_gpio = 0x7;		// B0~B2
	reg_gpio_pb_oen = 0xf8;
	reg_gpio_pd_gpio = 0xff;	// D0~D7
	reg_gpio_pd_oen = 0;

	gpio_set_func(LED_BLUE,AS_GPIO);
	gpio_set_func(LED_GREEN,AS_GPIO);
	gpio_set_func(LED_WHITE,AS_GPIO);
	gpio_set_func(LED_RED,AS_GPIO);

	gpio_set_output_en(LED_BLUE,1);
	gpio_set_output_en(LED_GREEN,1);
	gpio_set_output_en(LED_WHITE,1);
	gpio_set_output_en(LED_RED,1);

#endif

	advertise_begin_tick = clock_time();

}



/*----------------------------------------------------------------------------*/
/*--------- Main Loop                                             ------------*/
/*----------------------------------------------------------------------------*/
u32	tick_toggle=0;
u32 tick_loop;
void main_loop (void)
{
	tick_loop ++;
	if(clock_time_exceed(tick_toggle,1000000))
	{
		gpio_toggle(LED_BLUE);
		tick_toggle = clock_time();
	}

	/* BLE entry -------------------------------------------------------------*/
	blt_sdk_main_loop();


	if(write_data_test_tick && clock_time_exceed(write_data_test_tick, 500)){ // >1s
		write_data_test_tick = clock_time() | 1;

		extern u8 blt_state;
		if(blt_state == BLS_LINK_STATE_CONN)
		{
			DBG_CHN10_TOGGLE;
			if( BLE_SUCCESS == blc_gatt_pushHandleValueNotify (SPP_SERVER_TO_CLIENT_DP_H, app_test_data, 20)){
				app_test_data[0] ++;
			}
		}
	}

	////////////////////////////////////// PM Process /////////////////////////////////
	//blt_pm_proc();
	bls_pm_setSuspendMask (SUSPEND_DISABLE);
}


_attribute_data_retention_  u8 seq_num_next = 0;

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

#endif  //end of __PROJECT_B80_BLE_SAMPLE__

