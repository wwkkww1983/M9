/**
  ******************************************************************************
  * @file    AI Cleaning Robot
  * @author  Wfliu
  * @version V0.0
  * @date    11-July-2011
  * @brief   System Initialize
  * @define a lot of IO function for a easier look
  ******************************************************************************
  * Initialize the System Clock.ADC converter.EXTI.Timer and USART3
  * <h2><center>&copy; COPYRIGHT 2011 ILife CO.LTD</center></h2>
  ******************************************************************************
  */  

#ifndef __HomeStraight_H
#define __HomeStraight_H

#include "SysInitialize.h"

#define Homel_Wall_Distance  (int32_t)30000

void HomeStraight_Mode(void);
uint8_t Home_OutTrap_Right(void);
uint8_t Home_OutTrap_Left(void);



#endif /*----Behaviors------*/





