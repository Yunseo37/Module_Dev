/*
 * AppScheduler.c
 *
 *  Created on: 2023. 11. 23.
 *      Author: 현대오토9
 */
#include "AppScheduler.h"
#include "Driver_Stm.h"
#include "Mylib/ERU_Interrupt.h"
#include "Mylib/Blinky_LED.h"

typedef struct
{
    uint32_t u32nuCnt1ms;
    uint32_t u32nuCnt10ms;
    uint32_t u32nuCnt100ms;
}TestCnt;

// Static Function Prototype
static void AppTask1ms();
static void AppTask10ms();
static void AppTask100ms();

TestCnt stTestCnt;

void AppScheduling(int* status)
{
    if(stSchedulingInfo.u8nuScheduling1msFlag == 1u)
    {
        stSchedulingInfo.u8nuScheduling1msFlag = 0u;
        AppTask1ms(&status);

        if(stSchedulingInfo.u8nuScheduling10msFlag == 1u)
        {
            stSchedulingInfo.u8nuScheduling10msFlag = 0u;
            AppTask10ms(&status);
        }

        if(stSchedulingInfo.u8nuScheduling100msFlag == 1u)
        {
            stSchedulingInfo.u8nuScheduling100msFlag = 0u;
            AppTask100ms();
        }
    }
    return;
}


void AppTask1ms()
{

}

void AppTask10ms()
{

}

void AppTask100ms()
{
    blinkLED();
}

