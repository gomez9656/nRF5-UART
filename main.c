#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "app_uart.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf.h"
#include "bsp.h"
#include "nrf_uart.h"

#define UART_TX_BUFF_SIZE 128
#define UART_RX_BUFF_SIZE 128

#define UART_HWFC APP_UART_FLOW_CONTROL_DISABLED

void uart_err_handler(app_uart_evt_type_t * p){

}


int main(void)
{

  uint32_t err_code;

  bsp_board_init(BSP_INIT_LEDS);

  const app_uart_comm_params_t com_params = {
    
    RX_PIN_NUMBER,
    TX_PIN_NUMBER,
    RTS_PIN_NUMBER,
    CTS_PIN_NUMBER,
    UART_HWFC,
    false,
    NRF_UART_BAUDRATE_115200
  };


  APP_UART_FIFO_INIT(&com_params, UART_RX_BUFF_SIZE, UART_RX_BUFF_SIZE, uart_err_handler, APP_IRQ_PRIORITY_LOWEST, err_code);

  APP_ERROR_CHECK(err_code);

  printf("hello pc from nordic");

  while(true){
    
    uint8_t cr;

    while(app_uart_get(&cr) != NRF_SUCCESS){
      
      if(cr == 't'){
        
        bsp_board_leds_on();
        printf("leds on \r\n");
      }

      if(cr == 'k'){
        
        bsp_board_leds_off();
        printf("leds off \r\n");
      }
    }
  }
  
}


