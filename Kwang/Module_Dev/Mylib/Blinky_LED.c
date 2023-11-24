/*
 * Blinky_LED.c
 *
 *  Created on: 2023. 11. 23.
 *      Author: 현대오토9
 */

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "IfxPort.h"
#include "Bsp.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
// #1 : To turn on LED of Easy module shield, MODULE_P00, 2 -> MODULE_P10, 2
#define LED         &MODULE_P10,2                                           /* LED: Port, Pin definition            */
#define WAIT_TIME   100                                                  /* Wait time constant in milliseconds   */

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/* This function initializes the port pin which drives the LED */
void initLED(void)
{
    /* Initialization of the LED used in this example */
    IfxPort_setPinModeOutput(LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

    /* Switch OFF the LED (low-level active) */
    IfxPort_setPinHigh(LED);
}

/* This function toggles the port pin and wait 500 milliseconds */
void blinkLED(void)
{
    IfxPort_togglePin(LED);                                                     /* Toggle the state of the LED      */
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME));    /* Wait 500 milliseconds            */
}


