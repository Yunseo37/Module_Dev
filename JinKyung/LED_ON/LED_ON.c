/*
 * LED_ON.c
 *
 *  Created on: 2023. 11. 23.
 *      Author: 현대오토14
 */

#include "LED_ON.h"
#include "Blinky_LED.h"
#include "Bsp.h"

#define LED         &MODULE_P10, 2  // LED: Port, Pin definition
#define WAIT_TIME   500             // Wait time in millisec

#define PCn_1_IDX 11
#define P1_IDX 1
#define PCn_2_IDX 19
#define P2_IDX 2

uint8 STATE = 0;

/*
// 초기화
void initLED(void){
    IfxPort_setPinModeOutput(LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(LED);
}
*/

void initGPIO (void)
{
    P02_IOCR0.U &= ~(0x1F << PCn_1_IDX);
    P02_IOCR0.U |= 0x02 << PCn_1_IDX;

    P10_IOCR0.U &= ~(0x1F << PCn_2_IDX);
    P10_IOCR0.U |= 0x10 << PCn_2_IDX;
}

void LED_On (void)
{
    IfxPort_togglePin(LED);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME));
}

void LED_Off (void)
{
    IfxPort_setPinLow(LED);
}


void LED_CONTROL (void)
{
    if ((P02_IN.U & (0x1 << P1_IDX)) == 0)
    {

        if(LED_STATE == 0) {
            IfxPort_setPinLow(LED);
            LED_STATE = 1;
        }
        else if (LED_STATE == 1){
            IfxPort_setPinHigh(LED);
            LED_STATE = 0;
        }
//        IfxPort_togglePin(LED);
    }
//    else
//    {
//        P10_OUT.U = 0x4;
//    }
}
