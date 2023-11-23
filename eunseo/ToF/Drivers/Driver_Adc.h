#ifndef DRIVER_ADC
#define DRIVER_ADC

/***********************************************************************/
/*Include*/ 
/***********************************************************************/
#include "Ifx_Types.h"
#include "IfxVadc.h"
#include "IfxVadc_Adc.h"

/***********************************************************************/
/*Typedef*/ 
/***********************************************************************/
typedef struct
{
    IfxVadc_Adc vadc; /* VADC handle */
    IfxVadc_Adc_Group adcGroup;
} App_VadcAutoScan;

typedef enum
{
    ADC_GROUP0_CH0 = 0u,
    ADC_GROUP0_CH1,
    ADC_GROUP0_CH2,
    ADC_GROUP0_CH3,
    ADC_GROUP0_CH4,
    ADC_GROUP0_CH5,
    ADC_GROUP0_CH6,
    ADC_GROUP0_CH7,
    ADC_GROUP0_MAX
}ADC_GROUP0;

typedef struct
{
    uint32 UlSSense1_Raw;
    uint32 UlSSense2_Raw;
    uint32 UlSSense3_Raw;
}SensorAdcRaw;


/***********************************************************************/
/*Define*/ 
/***********************************************************************/

/***********************************************************************/
/*External Variable*/ 
/***********************************************************************/
IFX_EXTERN App_VadcAutoScan g_VadcAutoScan;
extern SensorAdcRaw stSensorAdcRaw;


/***********************************************************************/
/*Global Function Prototype*/ 
/***********************************************************************/
extern void Driver_Adc_Init(void);
extern void Driver_Adc0_ConvStart(void);
extern uint32 Driver_Adc0_DataObtain(void);




#endif /* DRIVER_STM */
