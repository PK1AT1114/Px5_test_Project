/*------------------------------------------------------------------------------*/
/* Copyright 2020, Microchip Technology Inc. and its subsidiaries.              */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following conditions are met:  */
/*                                                                              */
/* 1. Redistributions of source code must retain the above copyright notice,    */
/*    this list of conditions and the following disclaimer.                     */
/*                                                                              */
/* 2. Redistributions in binary form must reproduce the above copyright notice, */
/*    this list of conditions and the following disclaimer in the documentation */
/*    and/or other materials provided with the distribution.                    */
/*                                                                              */
/* 3. Neither the name of the copyright holder nor the names of its             */
/*    contributors may be used to endorse or promote products derived from      */
/*    this software without specific prior written permission.                  */
/*                                                                              */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  */
/* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    */
/* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   */
/* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE    */
/* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,             */
/* OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF      */
/* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;                 */
/* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,     */
/* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR      */
/* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,               */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/*------------------------------------------------------------------------------*/

/******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "Ambient.h"
#include "../Click.h"
#include "definitions.h"  
//#include "udp_handler.h"

#define POLY1_TERM1             147.2
#define POLY1_TERM0             -9.5
#define ADCC_RESOLUTION         4096
#define ADCC_REFERENCE          3300
/******************************************************************************
 *  VARIABLES
 ******************************************************************************/
static uint16_t m_result = 0;
static SensorTask_t task = { false, 50, 0, false };

/******************************************************************************
 *  FUNCTION DEFINITIONS
 *****************************************************************************/
/******************************************************************************
 ** Function Name        : ambient_service
 ** Description          : Method is gateway between ambient sensor and Lan867x.
 ******************************************************************************/
uint16_t ambient_UpdateLightIntensity(void)
{
    uint16_t adcData = 0x00;   
    
    if (task.data_ready) 
    {
        adcData = ambient_get_result();        
        task.enable = false;
    }      

    return adcData;
}

void ambient_service(void)
{
//     
//    task.data_ready = 0;

    if (task.enable == true && systick.tickCounter > task.next_interval) {

        /* Set the next Measure/send data time. */
        task.next_interval = systick.tickCounter + task.interval;

        /* Check if the ambient value is ready. */
        if (ambient_task()) 
            task.data_ready = 1;
    }
}

/******************************************************************************
 ** Function Name        : ambient_task
 ** Description          : The functions runs the ADC conversion of ambient data.
 ** Return               : Returns the status of ADC conversion. 1 means result ready.
 ******************************************************************************/
uint8_t ambient_task(void)
{
    static uint8_t currentState = 0;

    switch (currentState) {
    case 0: /* Start ADC conversion. */
    
        ADC_GlobalEdgeConversionStart();

        /* Set state to read the conversion result. */
        currentState = 1;

        break;

    case 1: /* Check if ADC Conversion is complete. */

        if (!ADC_ChannelResultIsReady(ADC_CH4))
            return 0;

        /* Read the ADC result. */
        m_result = ADC_ResultGet(ADC_CH4);

        /* Set state to start ADC conversion. */
        currentState = 0;

        return 1;
    }

    return 0;
}

/******************************************************************************
 ** Function Name        : ambient_get_result
 ** Description          : The functions returns the ambient value.
 ** Return               : Returns the value.
 ******************************************************************************/
uint16_t ambient_get_result(void)
{
    return m_result;
}


/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*                   CALLBACK FUNCTION FROM UDP Handler                 */
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

void UdpHandler_Wake_Ambient(void)
{   
    if(!task.enable) //check if task enable 
    {
        task.enable =true;
        if(task.next_interval ==0){
            task.next_interval = systick.tickCounter;  
        }
    }
}
/*------------------------------ End of File ----------------------------------*/