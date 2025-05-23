/*
 * @Author: ZYT
 * @Date: 2025-05-12 23:00:46
 * @LastEditors: ZYT
 * @LastEditTime: 2025-05-24 00:31:21
 * @FilePath: \pantilt_freertos\User\UART\uart_RT.c
 * @Brief: 
 * 
 * Copyright (c) 2025 by zyt, All Rights Reserved. 
 */
#include "uart_RT.h"
#include "head.h"
void Decode_Greenligit(uint8_t* Receivebuffer);
void Decode_Redligit(uint8_t* Receivebuffer);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance==USART2)
    {
        #ifdef GREEN
        Decode_Greenligit(Rxbuffer);
        #HAL_UART_Receive_IT(&huart2, Rxbuffer, sizeof(Rxbuffer));
        #endif
        #ifdef RED
        Decode_Redligit(Rxbuffer);
        HAL_UART_Receive_IT(&huart2,Rxbuffer,sizeof(Rxbuffer));
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
            int16_t spe1_tmp=0;
            int16_t spe2_tmp=0;
            //spe1_tmp = (Receivebuffer[2] << 8) | Receivebuffer[3];  // 16-bit 组合
           // spe2_tmp = (Receivebuffer[4] << 8) | Receivebuffer[5];      //高位在前低位在后，大端模式
           spe1_tmp = Receivebuffer[12]-Receivebuffer[10];
           spe2_tmp = Receivebuffer[13]-Receivebuffer[11];//绿-红
           //    if(spe1_tmp>128)
           //    {
           //     spe1 =-(spe1_tmp-256)*10;
           //    }else{
           //     spe1=-spe1_tmp*10;
           //    }
           //    if(spe2_tmp>128){
           //    spe2 = (spe2_tmp-256)*6;
           //    }else{
           //     spe2=spe2_tmp*6;
           //    }
           spe1 = spe1_tmp;
           spe2 = -spe2_tmp;
    }
        HAL_UART_Receive_IT(&huart2,Receivebuffer,sizeof(Receivebuffer));
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
            red_x=Receivebuffer[10];
            red_y=Receivebuffer[11];
        }
        
}
#endif // DEBUG