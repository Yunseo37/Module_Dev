///*
// * ADC_LED.c
// *
// *  Created on: 2023. 11. 22.
// *      Author: 현대오토14
// */
//
//#include "ADC_LED.h"
//#include "IfxVadc.h"
//#include "IfxVadc_adc.h"
//
//typedef struct{
//        IfxVadc_Adc vadc;
//        IfxVadc_Adc_Group adcGroup;
//}App_VadcAutoScan;
//
//static void DrvAdc_Group0Init(void);
//static void DrvAdc_Group0ChannelInit(uint8 param_ChNum);
//
//App_VadcAutoScan g_VadcAutoScan;
//IfxVadc_Adc_Channel adc0Channel[ADC_GROUP_MAX];
//SensorAdcRaw stSensorAcdRaw;
//
//void AdcInit(void){
//    DrvAdc_Group0Init();
//}
//
//void Acd_GetAdcRawGroup0(void){
//    IfxVadc_Adc_Config adcConfig;
//    IfxVadc_Adc_initModuleConfig(&adcConfig, &MODULE_VADC);
//    IfxVadc_Adc_initModule(&g_VadcAutoScan.vadc, &adcConfig);
//
//    IfxVadc_Adc_GroupConfig adcGroupConfig;
//    IfxVadc_Adc_initGroupConfig(&adcGroupConfig, &g_VadcAutoScan.vadc);
//
//    adcGroupConfig.groupId = IfxVadc_GroupId_0;
//    adcGroupConfig.master = adcGroupConfig.groupId;
//
//    adcGroupConfig.arbiter.requestSlotScanEnabled = TRUE;
//
//
//}
