/*
 * BLE.c
 *
 *  Created on: Apr 13, 2024
 *      Author: Dhari
 */


#include "BLE.h"

uint8_t bufferBLE[BUFFER_SIZE_BLE];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  HAL_UART_Receive_IT(&huart2, bufferBLE, BUFFER_SIZE_BLE);

  HAL_UART_Transmit_IT(&huart2, bufferBLE, BUFFER_SIZE_BLE);
}

