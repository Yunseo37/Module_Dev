/*
 * GPIO_LED_Button.c
 *
 *  Created on: 2023. 11. 23.
 *      Author: 현대오토9
 */

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "IfxPort.h"

/*********************************************************************************************************************/
/*-----------------------------------------------------Macros--------------------------------------------------------*/
/*********************************************************************************************************************/

// #1. Change ports : LED P10,2 BUTTON 2.0
#define LED     &MODULE_P10,2   /* Port pin for the LED     */
#define BUTTON  &MODULE_P02,0   /* Port pin for the button  */

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
/* Function to configure the port pins for the push button and the LED */
void init_GPIOs(void)
{
    /* Setup the port pin connected to the LED to general output mode push-pull. This function can be used
     * to initialize any port pin by specifying the port number, pin number and port pin mode.
     */
    IfxPort_setPinMode(LED, IfxPort_Mode_outputPushPullGeneral);

    /* Setup the port pin connected to the push button to input mode. This function can be used to initialize any
     * port to input mode by just specifying the port number as illustrated.
     */
    IfxPort_setPinMode(BUTTON, IfxPort_Mode_inputPullUp);
}

/* Depending on the the state of the "BUTTON" port pin, the LED is turned on or off */
void control_LED(void)
{
    /* With the routine getPinState() the value of a particular pin can be retrieved. This
     * function can be used to retrieve any port state by just specifying the port number
     * as illustrated.
     */
    if(IfxPort_getPinState(BUTTON) == 0)
    {
        /* With the routine setPinState() the state of the port can be set to drive either
         * LOW or HIGH. This function can be used to retrieve any port state by just
         * specifying the port number as illustrated.
         */
        IfxPort_setPinState(LED, IfxPort_State_low);
    }
    else
    {
        IfxPort_setPinState(LED, IfxPort_State_high);
    }
}


