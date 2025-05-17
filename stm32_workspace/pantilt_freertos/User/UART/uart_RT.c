/*
 * @Author: ZYT
 * @Date: 2025-05-12 23:00:46
 * @LastEditors: ZYT
 * @LastEditTime: 2025-05-17 15:21:17
 * @FilePath: \pantilt_freertos\User\UART\uart_RT.c
 * @Brief: 
 * 
 * Copyright (c) 2025 by zyt, All Rights Reserved. 
 */
/*
 * @Author: ZYT
 * @Date: 2025-05-12 23:00:46
 * @LastEditors: ZYT
 * @LastEditTime: 2025-05-15 01:04:08
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
        Decode_Greenligit(ReceivebufferG);
        HAL_UART_Receive_IT(&huart2,ReceivebufferG,sizeof(ReceivebufferG));
        #endif
        #ifdef RED
        Decode_Redligit(ReceivebufferR);
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
    if(Receivebuffer[0]==0xAA&&Receivebuffer[1]==0xFF&&Receivebuffer[5]==0xFF&&Receivebuffer[6]==0xAA)
        {
            int16_t spe1_tmp=0;
            int16_t spe2_tmp=0;
            spe1_tmp = (Receivebuffer[2] << 8) | Receivebuffer[3];  // 16-bit 组合
            spe2_tmp        = Receivebuffer[4];

            // spe2_tmp = (Receivebuffer[4] << 8) | Receivebuffer[5];      //高位在前低位在后，大端模式
            // spe1_tmp = Receivebuffer[2];
            /*if(spe1_tmp>128)
            {
             spe1 =-(spe1_tmp-256)*10;
            }else{
             spe1=-spe1_tmp*10;
            }*/
            if(spe1_tmp>30000)
            {
             spe1 =-(spe1_tmp-65535)*10;
            }else{
             spe1=-spe1_tmp*10;
            }
            if (spe2_tmp > 128) {
                spe2 = (spe2_tmp - 256) * 6;
            } else {
                spe2 = spe2_tmp * 6;
            }

        }
        HAL_UART_Receive_IT(&huart2,Receivebuffer,sizeof(Receivebuffer));
}
#ifdef RED


void Decode_Redligit(uint8_t* Receivebuffer)
{
    if(Receivebuffer[0]==0xAA&&Receivebuffer[1]==0xFF&&Receivebuffer[17]==0xFF&&Receivebuffer[18]==0xAA)
        {
        dot1x = (Receivebuffer[2] << 8) | Receivebuffer[3];
        dot1y = Receivebuffer[4];
        dot2x = (Receivebuffer[5] << 8) | Receivebuffer[6];
        dot2y = Receivebuffer[7];
        dot3x = (Receivebuffer[8] << 8) | Receivebuffer[9];
        dot3y = Receivebuffer[10];
        dot4x = (Receivebuffer[11] << 8) | Receivebuffer[12];
        dot4y = Receivebuffer[13];
        red_x = (Receivebuffer[14] << 8) | Receivebuffer[15];
        red_y = Receivebuffer[16];
        }
        HAL_UART_Receive_IT(&huart2,Receivebuffer,sizeof(Receivebuffer));
}
#endif // RED