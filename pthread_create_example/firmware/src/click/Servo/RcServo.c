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
#include "RcServo.h"
#include "../Click.h"
//#include "udp_handler.h"

/******************************************************************************
 *  DEFINES & MACROS
 ******************************************************************************/
#define LOW_PWM_PERCENT (88)
#define HIGH_PWM_PERCENT (98)
#define USABLE_PWM (HIGH_PWM_PERCENT - LOW_PWM_PERCENT)
#define MAX_PAYLOAD_LENGTH (20)
#define ANIMATION_DELAY (5)
#define ANIMATION_FAST_STEP    (20)
#define ANIMATION_SLOW_STEP    (1)

/******************************************************************************
 *  VARIABLES
 ******************************************************************************/
typedef struct
{
    uint16_t m_is;
    uint16_t m_shall;
    uint32_t m_period;
    uint32_t m_lower_offset;
//    uint32_t m_lastRun;
} ServoData_t;

static ServoData_t m_servoData = { 0 };
/******************************************************************************
 *  FUNCTION PROTOTYPES
 ******************************************************************************/
static void set_pin_mux(uint8_t port, uint8_t pin, uint8_t function);
static void ChangeIs(int16_t change);
static bool SetServo(uint16_t angle);
/******************************************************************************
 *  FUNCTION DEFINITIONS
 *****************************************************************************/
/******************************************************************************
 ** Function Name        : servo_init
 ** Description          : Initialize the PWM peripheral.
 ******************************************************************************/
bool servo_init(void)
{    
    set_pin_mux(2, 9, 5); //PC09 
    
    m_servoData.m_period = 5600U;   
    
    m_servoData.m_lower_offset = m_servoData.m_period * LOW_PWM_PERCENT / 100;
    
    m_servoData.m_period = (m_servoData.m_period * HIGH_PWM_PERCENT / 100) - m_servoData.m_lower_offset;
    
    return true;
}

/******************************************************************************
 ** Function Name        : servo_service
 ** Description          : Method will run the Servo control service and interact with
                           Lan867x click.
 ******************************************************************************/
void servo_service(void)
{    
    int16_t diff = m_servoData.m_shall - m_servoData.m_is;
    if(diff >= ANIMATION_FAST_STEP) 
    {
        ChangeIs(ANIMATION_FAST_STEP);
    } 
    else if(diff <= -ANIMATION_FAST_STEP) 
    {
        ChangeIs(-ANIMATION_FAST_STEP);
    } 
    else if(diff >= ANIMATION_SLOW_STEP) 
    {
        ChangeIs(ANIMATION_SLOW_STEP);
    } 
    else if(diff <= -ANIMATION_SLOW_STEP) 
    {
        ChangeIs( -ANIMATION_SLOW_STEP);
    }
    if (0 != diff)
    {
        SetServo(m_servoData.m_is);
    }
}


/******************************************************************************
 ** Function Name        : SetServo
 ** Description          : The method will set the angle of servo motor.
 ** Parameter            :
                     idx : motor instance number.
                   angle : the angle of the motor.
 ** Return               : status of execution.
 ******************************************************************************/
static bool SetServo(uint16_t angle)
{
    uint32_t dutyCycle;
    bool status = false;
    angle = angle;
    
    dutyCycle = (m_servoData.m_period * angle / MAX_SERVO_ANGLE) + m_servoData.m_lower_offset;
    
    status = TCC1_PWM16bitDutySet(TCC1_CHANNEL0, dutyCycle);
       
    return status;
}



/******************************************************************************
 ** Function Name        : set_pin_mux
 ** Description          : Sets pin to a multiplex mode specified.
 ******************************************************************************/
static void set_pin_mux(uint8_t port_id, uint8_t pin_id, uint8_t function)
{
    PORT_REGS->GROUP[port_id].PORT_PINCFG[pin_id] = 0x1;

    /* Set Multiplex Setting of the PIN */
    if (pin_id % 2 == 1) {
        /* PIN ID is Odd Number, update PUMXO register */
        PORT_REGS->GROUP[port_id].PORT_PMUX[pin_id / 2] = (PORT_REGS->GROUP[port_id].PORT_PMUX[pin_id / 2] & 0x0F) | function << 4;
    } else {
        /* PIN ID is Even Number, update PUMXE register */
        PORT_REGS->GROUP[port_id].PORT_PMUX[pin_id / 2] = (PORT_REGS->GROUP[port_id].PORT_PMUX[pin_id / 2] & 0xF0) | function;
    }
}
/******************************************************************************
 ** Function Name        : ChangeIs
 ** Description          : Chang the angle.
 ******************************************************************************/
static void ChangeIs(int16_t change)
{
    int16_t c = m_servoData.m_is + change;
    if (c < 0) {
        c = 0;
    } if (c > MAX_SERVO_ANGLE) {
        c = MAX_SERVO_ANGLE;
    }
    m_servoData.m_is = c;
}



/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*                   CALLBACK FUNCTION FROM UDP Handler                 */
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

void UdpHandler_Set_Servo(uint8_t *buffer, uint16_t len)
{
    uint8_t i = 0;
//    printf("payload: ");
//    for(uint8_t i=0;i<len;++i)
//    {
//        printf("%d ",buffer[i]);
//    }
//    printf("\r\n");
    
    i= buffer[i];
    m_servoData.m_shall= (uint16_t)(buffer[1] | buffer[2] << 8);
#ifdef DEBUG
        printf("Servo Motor no:%d ,angel : %d. \r\n",i, m_servoData.m_shall[i]);
#endif


}
/*------------------------------ End of File ----------------------------------*/