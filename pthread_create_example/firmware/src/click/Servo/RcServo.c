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
#define MAX_SERVO_INSTANCES (4)
#define MAX_SERVO_ANGLE (180)
/******************************************************************************
 *  VARIABLES
 ******************************************************************************/
typedef struct
{
    uint16_t m_is[MAX_SERVO_INSTANCES];
    uint16_t m_shall[MAX_SERVO_INSTANCES];
    uint32_t m_period[MAX_SERVO_INSTANCES];
    uint32_t m_lower_offset[MAX_SERVO_INSTANCES];
    uint32_t m_lastRun;
} ServoData_t;

static ServoData_t m_servoData = { 0 };
/******************************************************************************
 *  FUNCTION PROTOTYPES
 ******************************************************************************/
static void set_pin_mux(uint8_t port, uint8_t pin, uint8_t function);
static void ChangeIs(uint8_t idx, int16_t change);
static bool SetServo(uint8_t idx, uint16_t angle);
/******************************************************************************
 *  FUNCTION DEFINITIONS
 *****************************************************************************/
/******************************************************************************
 ** Function Name        : servo_init
 ** Description          : Initialize the PWM peripheral.
 ******************************************************************************/
bool servo_init(void)
{
    uint8_t tmp;

    /* Using Slot 2 for servo and configure pins to PWM mode. */
    /* PC09*/
    set_pin_mux(2, 9, 5);
    /* PC10*/
    set_pin_mux(2, 10, 5);
    /* PB13*/
    set_pin_mux(1, 13, 5);
    /* PB14*/
    set_pin_mux(1, 14, 5);

    m_servoData.m_period[0] = m_servoData.m_period[1] = 5600U;
    m_servoData.m_period[2] = m_servoData.m_period[3] = 5600U;

    for (tmp = 0; tmp < MAX_SERVO_INSTANCES; tmp++) 
    {
        m_servoData.m_lower_offset[tmp] = m_servoData.m_period[tmp] * LOW_PWM_PERCENT / 100;
        m_servoData.m_period[tmp] = (m_servoData.m_period[tmp] * HIGH_PWM_PERCENT / 100) - m_servoData.m_lower_offset[tmp];
    }

    return true;
}

/******************************************************************************
 ** Function Name        : servo_service
 ** Description          : Method will run the Servo control service and interact with
                           Lan867x click.
 ******************************************************************************/
void servo_service(void)
{
     uint8_t i;
     uint32_t now = systick.tickCounter;
     if (now - m_servoData.m_lastRun > ANIMATION_DELAY) {
        m_servoData.m_lastRun = now;

        for (i = 0; i < MAX_SERVO_INSTANCES; i++) 
        {
            int16_t diff = m_servoData.m_shall[i] - m_servoData.m_is[i];
            if(diff >= ANIMATION_FAST_STEP) 
            {
                ChangeIs(i, ANIMATION_FAST_STEP);
            } else if(diff <= -ANIMATION_FAST_STEP) 
            {
                ChangeIs(i, -ANIMATION_FAST_STEP);
            } else if(diff >= ANIMATION_SLOW_STEP) 
            {
                ChangeIs(i, ANIMATION_SLOW_STEP);
            } else if(diff <= -ANIMATION_SLOW_STEP) 
            {
                ChangeIs(i, -ANIMATION_SLOW_STEP);
            }
            if (0 != diff) 
            {
                SetServo(i, m_servoData.m_is[i]);
            }
        }
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
static bool SetServo(uint8_t idx, uint16_t angle)
{
    uint32_t dutyCycle;
    bool status = false;

    if (idx >= MAX_SERVO_INSTANCES || angle >= MAX_SERVO_ANGLE)
        return false;

    angle = MAX_SERVO_ANGLE - angle;
    dutyCycle = (m_servoData.m_period[idx] * angle / MAX_SERVO_ANGLE) + m_servoData.m_lower_offset[idx];

    switch (idx) 
    {
    case 0:
        status = TCC1_PWM16bitDutySet(TCC1_CHANNEL0, dutyCycle);
        break;
    case 1:
        status = TCC1_PWM16bitDutySet(TCC1_CHANNEL1, dutyCycle);
        break;
    case 2:
        status = TCC3_PWM16bitDutySet(TCC3_CHANNEL0, dutyCycle);
        break;
    case 3:
        status = TCC3_PWM16bitDutySet(TCC3_CHANNEL1, dutyCycle);
        break;
    }
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
    if (pin_id % 2 == 1) 
    {
        /* PIN ID is Odd Number, update PUMXO register */
        PORT_REGS->GROUP[port_id].PORT_PMUX[pin_id / 2] = (PORT_REGS->GROUP[port_id].PORT_PMUX[pin_id / 2] & 0x0F) | function << 4;
    } 
    else 
    {
        /* PIN ID is Even Number, update PUMXE register */
        PORT_REGS->GROUP[port_id].PORT_PMUX[pin_id / 2] = (PORT_REGS->GROUP[port_id].PORT_PMUX[pin_id / 2] & 0xF0) | function;
    }
}
/******************************************************************************
 ** Function Name        : ChangeIs
 ** Description          : Chang the angle.
 ******************************************************************************/
static void ChangeIs(uint8_t idx, int16_t change)
{
    int16_t c = m_servoData.m_is[idx] + change;
    if (c < 0) {
        c = 0;
    } if (c > MAX_SERVO_ANGLE) {
        c = MAX_SERVO_ANGLE;
    }
    m_servoData.m_is[idx] = c;
}



/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*                   CALLBACK FUNCTION FROM UDP Handler                 */
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

void UdpHandler_Set_Servo(uint8_t *buffer, uint16_t len)
{
    uint8_t i = 0;
#ifdef DEBUG
    printf("payload: ");
    for(uint8_t i=0;i<len;++i)
    {
        printf("%d ",buffer[i]);
    }
    printf("\r\n");
#endif
    if(len==3)
    {
        i= buffer[i];
        m_servoData.m_shall[i]= (uint16_t)(buffer[1] | buffer[2] << 8);
#ifdef DEBUG
        printf("Servo Motor no:%d ,angel : %d. \r\n",i, m_servoData.m_shall[i]);
#endif
    }
    if(len==12)
    {
        for (i=0;i<MAX_SERVO_INSTANCES;i++)
        {
            m_servoData.m_shall[i]= (uint16_t)(buffer[i*3 + 1] | buffer[i*3+ 2] << 8);
#ifdef DEBUG
            printf("Servo Motor no:%d ,angel : %d. \r\n",i, m_servoData.m_shall[i]);
#endif
        }
    }

}
/*------------------------------ End of File ----------------------------------*/