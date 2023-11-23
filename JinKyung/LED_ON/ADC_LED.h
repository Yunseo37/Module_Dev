/*
 * ADC_LED.h
 *
 *  Created on: 2023. 11. 22.
 *      Author: 현대오토14
 */

#ifndef ADC_H
#define ADC_H

#include "Ifx_Types.h"

typedef enum{
ADC_GROUP_CH0 = 0u,
ADC_GROUP_CH1,
ADC_GROUP_CH2,
ADC_GROUP_CH3,
ADC_GROUP_CH4,
ADC_GROUP_CH5,
ADC_GROUP_CH6,
ADC_GROUP_CH7,
ADC_GROUP_MAX
}ADC_GROUP0;

typedef struct{
uint32 USense1_Raw;
uint32 USense2_Raw;
uint32 USense3_Raw;
}SensorAdcRaw;

extern SensorAdcRaw stSensorAcdRaw;

extern void AdcInit(void);
extern void Acd_GetAdcRawGroup0(void);

#endif
