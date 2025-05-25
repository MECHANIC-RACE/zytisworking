/*
 * @Author: ZYT
 * @Date: 2025-05-25 13:55:50
 * @LastEditors: ZYT
 * @LastEditTime: 2025-05-25 17:00:07
 * @FilePath: \pantilt_freertos__\User\Task\default.c
 * @Brief: 
 * 
 * Copyright (c) 2025 by zyt, All Rights Reserved. 
 */
//#include "head.h"
/**


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == RED_NO1_RESET_Pin) // 引脚判断
    //复位 以及红光no1
    {
        Reset = 1;
        Q_NO  = 1;
        mode1 = 0;
        mode2 = 0;
        WheelMode(1, mode1);
        WheelMode(2, mode2);
    }
    #ifdef RED

    if (GPIO_Pin == Q_NO2_Pin) // 引脚判断
    {
        Q_NO = 2;
        mode1 = 0;
        mode2 = 0;
        WheelMode(1, mode1);
        WheelMode(2, mode2);
    }
    if (GPIO_Pin == Q_NO3_Pin) // 引脚判断
    {
        Q_NO = 3;
        mode1 = 1;
        mode2 = 1;
        WheelMode(1, mode1);
        WheelMode(2, mode2);
        //U_Transmit(3);
    }
    #endif
    #ifdef GREEN
    if (GPIO_Pin == Q_NO4_Pin) // 引脚判断
    {
        Q_NO = 4;
        mode1 = 1;
        mode2 = 1;
        WheelMode(1, mode1);
        WheelMode(2, mode2);
        // U_Transmit(4);
    }
    #endif
    
}
    **/