/*
 * Blinky_LED.c
 *
 *  Created on: 2023. 11. 22.
 *      Author: 현대오토14
 */



#include "IfxPort.h"
#include "Bsp.h"

#define LED         &MODULE_P10, 2  // LED: Port, Pin definition
#define WAIT_TIME   500             // Wait time in millisec

// 초기화
void initLED(void){
    IfxPort_setPinModeOutput(LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(LED);
}

void blinkLED(void){
    IfxPort_togglePin(LED);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME));
}

void endLED(void){
    IfxPort_setPinLow(LED);
}
