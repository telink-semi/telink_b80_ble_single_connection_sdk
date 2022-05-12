/********************************************************************************************************
 * @file     app_buffer.h
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

#ifndef VENDOR_B80_BLE_SAMPLE_APP_UART_H_
#define VENDOR_B80_BLE_SAMPLE_APP_UART_H_

#if (FEATURE_TEST_MODE == TEST_FEATURE_DEBUG&&BLE_DEBUG_MODE==BLE_DEBUG_UART)

#define   UART_TX_PIN    GPIO_PD5
#define   UART_RX_PIN    GPIO_PD6

#define UART_RXFIFO_SIZE		64
#define UART_RXFIFO_NUM		2

#define UART_TXFIFO_SIZE		64
#define UART_TXFIFO_NUM		8

#define UART_DATA_LEN    64      // data max 252
typedef struct{
    unsigned int len;        // data max 252
    unsigned char data[UART_DATA_LEN];
}uart_data_t;
extern u8 		 	uart_rx_fifo_b[UART_RXFIFO_SIZE * UART_RXFIFO_NUM];
extern my_fifo_t	 uart_rx_fifo;

extern  u8 		 	uart_tx_fifo_b[UART_TXFIFO_SIZE * UART_TXFIFO_NUM];
extern  my_fifo_t	 uart_tx_fifo;
extern  volatile unsigned char uart_dma_send_flag;
extern  uart_data_t txdata_buf;

/**
 * @brief     This function serves to initialize uart.
 * @param[in] none
 * @return    none
 */
void user_uart_init();

/**
 * @brief     This function serves to print data by uart.
 * @param[in] none
 * @return    0 is OK, -1 is err.
 */
s8 uart_tx_printf(const char *format, ...);

/**
 * @brief     This function serves to tx str by uart.
 * @param[in] none
 * @return    0 is OK, -1 is err.
 */
s8 uart_tx_str(char *txdata,unsigned int len);

/**
 * @brief		this function is used to process tx uart data.
 * @param[in]	none
 * @return      0 is ok
 */
int user_uart_loop(void);

/**
 * @brief     This function serves to handle uart irq.
 * @param[in] none
 * @return    none
 */
void uart_irq_handler(void);

#endif //end of (FEATURE_TEST_MODE == xxx)
#endif /* VENDOR_B80_BLE_SAMPLE_APP_UART_H_ */

