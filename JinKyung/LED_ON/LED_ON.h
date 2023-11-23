/*
 * LED_ON.h
 *
 *  Created on: 2023. 11. 23.
 *      Author: 현대오토14
 */


#include "IfxPort.h"
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

void initLED(void);
void LED_On(void);
void LED_Off(void);
void LED_CONTROL(void);
void initGPIO (void);
