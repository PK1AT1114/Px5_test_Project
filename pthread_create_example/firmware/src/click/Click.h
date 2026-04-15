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

#ifndef CLICK_H_INCLUDED
#define CLICK_H_INCLUDED
/******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "definitions.h"
#define SYSTICK_FREQ   72000000U

/******************************************************************************
 *  DEFINES & MACROS
 ******************************************************************************/
#define DELAY_MS(time) px5_timer_SYSTICK_DelayMs(time)

typedef void (*SYSTICK_CALLBACK)(uintptr_t context);

typedef struct
{
   SYSTICK_CALLBACK          callback;
   uintptr_t                 context;
   volatile uint32_t         tickCounter;
} SYSTICK_OBJECT ;

extern volatile SYSTICK_OBJECT systick;


/******************************************************************************
 *  ENUM
 ******************************************************************************/
enum Ethernet_payload_id {
    /* Nodes(Sensors) returning value. */
    /*test_COM*/
    UART_WAKE = 1300,
    
    PRESSURE_WAKE = 100,
    PRESSURE_VALUE = 101,

    PROXIMITY_WAKE = 200,
    PROXIMITY_VALUE = 201,

    GESTURE_WAKE = 300,
    GESTURE_VALUE = 301,

    CLIMATE_WAKE = 400,
    CLIMATE_VALUE = 401,

    AMBIENT_WAKE = 500,
    AMBIENT_VALUE = 501,

    JOYSTICK_WAKE = 600,
    JOYSTICK_VALUE = 601,

    SWITCH_VALUE = 701,

    /* Nodes where value can only be set. */
    ISELED_WAKE = 800,
    ISELED_SET = 801,

    MOTOR_WAKE = 900,
    MOTOR_SET = 901,

    MOTOR_COLOR_WAKE = 1000,
    MOTOR_COLOR_SET = 1001,

    SERVO_WAKE = 1100,
    SERVO_SET = 1101,

    OLED_SET = 1201,
};

typedef enum {
    CENTER = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    RCW,  /* Clock wise */
    RCCW, /* Counter clock wise */
    PRESS,
    RELEASE,
    ERROR
} Direction_t;

/******************************************************************************
 *  STRUCTURE
 ******************************************************************************/
/* SPI1 Channel structure. */
typedef struct {
    DRV_SPI_TRANSFER_HANDLE transferHandle;
    volatile DRV_SPI_TRANSFER_EVENT transferEvent;
} SPI_CLIENT_CHANNEL;


typedef void (*TIMER_CB)(void);

/* Structure for a task scheduling. */
typedef struct {
    bool enable;            /* enable/disable timer task */
    uint32_t interval;      /* time before calling the task in ms */
    uint32_t next_interval; /* next sys time in ms the task shall be called (now + interval). */
    TIMER_CB task_cb;       /* function pointer to the task */
} TimerTask_t;

typedef struct {
    bool enable;            /* enable/disable sensor measurement. */
    uint16_t interval;      /* time before calling the task in ms */
    uint32_t next_interval; /* next sys time in ms the task shall be called (now + interval) */
    bool data_ready;        /* whether sensor measurement is complete and data is ready or not.*/
} SensorTask_t;

void px5_timer_SYSTICK_DelayMs ( uint32_t delay_ms);
/******************************************************************************
 *  EXTERN
 ******************************************************************************/
//extern volatile SYSTICK_OBJECT systick;      /* Variable to get current timestamp. */

#endif /* CLICK_H_INCLUDED */

/*------------------------------ End of File ----------------------------------*/
