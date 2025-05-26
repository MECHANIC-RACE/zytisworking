/*
 * @Author: ZYT
 * @Date: 2025-05-12 23:00:46
 * @LastEditors: ZYT
 * @LastEditTime: 2025-05-27 03:12:22
 * @FilePath: \pantilt_freertos__\User\UART\uart_RT.c
 * @Brief: 
 * 
 * Copyright (c) 2025 by zyt, All Rights Reserved. 
 */
#include "uart_RT.h"
#include "head.h"
uint8_t Rxbuffer[16];

void Decode_Greenligit(uint8_t* Receivebuffer);
void Decode_Redligit(uint8_t* Receivebuffer);
uint8_t dot_cal_x[4*N];
uint8_t dot_cal_y[4*N];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance==USART2)
    {
        #ifdef GREEN
        Decode_Greenligit(Rxbuffer);
        HAL_UART_Receive_IT(&huart2, Rxbuffer, 16);
        #endif
        #ifdef RED
        Decode_Redligit(Rxbuffer);
        
       // printf("%f,%f\n", spe1, spe2);
        //printf("1\n");
        HAL_UART_Receive_IT(&huart2, Rxbuffer, 16);
#endif
    }
}

        //Speed = -(Speed&~(1<<15));
void U_Transmit(uint8_t num)
{
    uint8_t Txbuffer[5];
    Txbuffer[0]=0xEE;
    Txbuffer[1]=0xEE;
    Txbuffer[2]=num;
    Txbuffer[0]=0xFF;
    Txbuffer[1]=0xFF;
    HAL_UART_Transmit(&huart2,Txbuffer,sizeof(Txbuffer),0xff);
}

void Decode_Greenligit(uint8_t* Receivebuffer)
{
    if(Receivebuffer[0]==0xAA&&Receivebuffer[1]==0xFF&&Receivebuffer[14]==0xFF&&Receivebuffer[15]==0xAA)
        {

        red_x = Receivebuffer[10];
        red_y = Receivebuffer[11];
        green_x = Receivebuffer[12];
        green_y = Receivebuffer[13];
    }
       // HAL_UART_Receive_IT(&huart2,Receivebuffer,sizeof(Receivebuffer));
}
#ifdef RED


void Decode_Redligit(uint8_t* Receivebuffer)
{
    if(Receivebuffer[0]==0xAA&&Receivebuffer[1]==0xFF&&Receivebuffer[14]==0xFF&&Receivebuffer[15]==0xAA)
        {
            dot1x=Receivebuffer[2];
            dot1y=Receivebuffer[3];
            dot2x=Receivebuffer[4];
            dot2y=Receivebuffer[5];
            dot3x=Receivebuffer[6];
            dot3y=Receivebuffer[7];
            dot4x=Receivebuffer[8];
            dot4y=Receivebuffer[9];
            red_x=Receivebuffer[12];
            red_y=Receivebuffer[13];
            
            
        }
        
}
#endif // DEBUG