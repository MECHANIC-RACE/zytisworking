/*
 * @Author: ZYT
 * @Date: 2025-05-12 15:53:08
 * @LastEditors: ZYT
 * @LastEditTime: 2025-05-25 23:38:57
 * @FilePath: \pantilt_freertos__\User\Task\servo.c
 * @Brief: 
 * 
 * Copyright (c) 2025 by zyt, All Rights Reserved. 
 */
#include "head.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 {
 if(htim->Instance == TIM3)   //判断是哪个定时器触发的中断
{
    
//#ifdef 红绿都一样，伺服线程一样做，只是spe的来源不同
/**
if ((ERROR_FLAG == 1) || Q_NO == 1) {
    WritePosEx(1, 2350, 1000, 50);
    WritePosEx(2, 2200, 1000, 50);  //复位操作,红光no1
    
}

#ifdef RED  
   if((mode2==0||mode1==0)&&Q_NO==2)
   {
    WritePosEx(1, tar_pos1, 1000, 50);
    WritePosEx(2, tar_pos2, 1000, 50);
   }
   #endif // 只用于红光题号2时
   

    if(mode2==1){
      WriteSpe(2,spe2,50);  //向上为正
    }
     if(mode1==1){
      WriteSpe(1,spe1,50); //向右为正
    }
       // #endif 
      */
    
 }
  if(htim->Instance == TIM4)
  {
     // printf("%d,%d\n", Reset, Rxbuffer[1]);
  }
 }
