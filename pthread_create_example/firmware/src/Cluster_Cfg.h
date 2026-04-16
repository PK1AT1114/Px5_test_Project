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

#ifndef CLUSTER_CONFIGURATION_H
#define CLUSTER_CONFIGURATION_H

/******************************************************************************
 *  DEFINES & MACROS
 ******************************************************************************/
#define AMBIENT                 0
#define PROXIMITY3              0
#define PROXIMITY_AMBIENT       0
#define WEATHER                 0
#define SERVO                   1
#define LED_PWM                 0
#define SWITCH                  0

#define AMBIENT_ID              0x100
#define PROXIMITY3_ID           0x200
#define SERVO_ID                0x300
#define LED_PWM_ID              0x400
#define SWITCH_ID               0x500

#define DIAG_AMBIENT_ID         0x101
#define DIAG_PROXIMITY3_ID      0x201
#define DIAG_SERVO_ID           0x301
#define DIAG_LED_PWM_ID         0x401
#define DIAG_SWITCH_ID          0x501

#if defined AMBIENT
#define ADC 1
#else
#define ADC 0
#endif

/* Enable PWM based on click boards. */
#if defined SERVO || defined RGB_FAN_MOTOR
#define PWM 1
#else
#define PWM 1
#endif


#endif /* CLUSTER_CONFIGURATION_H */

/*------------------------------ End of File ----------------------------------*/