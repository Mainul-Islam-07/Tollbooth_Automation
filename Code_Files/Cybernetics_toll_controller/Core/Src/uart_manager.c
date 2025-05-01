#include "uart_manager.h"

// UART DMA Buffer
char uartRxBuffer[CMD_BUFFER_SIZE];


// Start UART DMA Reception
void startUartDMA(UART_HandleTypeDef *huart) {
	HAL_UARTEx_ReceiveToIdle_DMA(huart, (uint8_t*)uartRxBuffer, CMD_BUFFER_SIZE); //TO DO dynamic RX data


}

// UART RX Complete Callback
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    if (huart->Instance == USART2) {

//        processReceivedCommand(uartRxBuffer);
    	processReceivedCommand(uartRxBuffer, SOURCE_UART);


        memset(uartRxBuffer, 0, CMD_BUFFER_SIZE);  // Clear Buffer
        startUartDMA(global.comm_uart); // Restart DMA Reception
    }
}

void uartTransmitDMA(UART_HandleTypeDef *huart, const char* data){
	HAL_UART_Transmit_DMA(huart, (uint8_t*) data, strlen(data));
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart->ErrorCode & HAL_UART_ERROR_PE)
    {
        printf("UART Parity Error!\n");
        __HAL_UART_CLEAR_PEFLAG(huart);
    }
    if (huart->ErrorCode & HAL_UART_ERROR_NE)
    {
        printf("UART Noise Error!\n");
        __HAL_UART_CLEAR_NEFLAG(huart);
    }
    if (huart->ErrorCode & HAL_UART_ERROR_FE)
    {
        printf("UART Framing Error!\n");
        __HAL_UART_CLEAR_FEFLAG(huart);
    }
    if (huart->ErrorCode & HAL_UART_ERROR_ORE)
    {
        printf("UART Overrun Error!\n");
        __HAL_UART_CLEAR_OREFLAG(huart);
    }

    // Abort and restart DMA
    HAL_UART_Abort(huart);
    startUartDMA(huart); // Restart your UART DMA
}






