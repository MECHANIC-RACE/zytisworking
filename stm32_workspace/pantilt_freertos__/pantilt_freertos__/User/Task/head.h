/*
 * @Author: ZYT
 * @Date: 2025-05-12 15:18:52
 * @LastEditors: ZYT
 * @LastEditTime: 2025-05-25 22:34:15
 * @FilePath: \pantilt_freertos__\User\Task\head.h
 * @Brief: 
 * 
 * Copyright (c) 2025 by zyt, All Rights Reserved. 
 */
#ifndef HEAD
#define HEAD

#include "usart.h"
#include "gpio.h"
#include "User_SMS_STS.h"
#include "SCServo.h"
#include "io_retargetToUart.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "uart_RT.h"
#include "wtr_calculate.h"
#define RED  //红光模式还是绿光模式，主要是串口接受的不一样
#define N   100

extern __IO uint8_t Q_NO;
extern __IO uint8_t mode1;
extern __IO uint8_t mode2;
extern int16_t spe1;
extern int16_t spe2;
extern uint8_t ERROR_FLAG;
extern __IO uint8_t Reset;
#ifdef RED
extern uint8_t dot1x,dot1y,dot2x,dot2y,dot3x,dot3y,dot4x,dot4y;
extern int16_t tar_pos1,tar_pos2;
extern uint8_t dot_cal_x[4*N];
extern uint8_t dot_cal_y[4*N];
#endif // RED
extern uint8_t red_x,red_y;
extern int16_t fdb_pos1;
extern int16_t fdb_pos2;

#endif // !HEAD