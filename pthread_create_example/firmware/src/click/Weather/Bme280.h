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

#ifndef _BM280_H
#define _BM280_H

/******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include <stdbool.h>
#include <stdint.h>

/******************************************************************************
 *  DEFINES & MACROS
 ******************************************************************************/
// Device Information
#define BME280_ADDR 0x76
#define BME280_CHIP_ID 0x60

#define BME280_SUCCESS         ((uint8_t)0)
#define BME280_ERROR           ((int8_t)-1)

// Sensor Modes
#define BME280_SLEEP_MODE 0x00
#define BME280_FORCED_MODE 0x01
#define BME280_NORMAL_MODE 0x03
#define BME280_SOFT_RESET 0xB6

// Oversampling Options
#define BME280_OVERSAMP_SKIPPED 0x00
#define BME280_OVERSAMP_X1 0x01
#define BME280_OVERSAMP_X2 0x02
#define BME280_OVERSAMP_X4 0x03
#define BME280_OVERSAMP_X8 0x04
#define BME280_OVERSAMP_X16 0x05

// Standby Time
#define BME280_STANDBY_HALFMS 0x00
#define BME280_STANDBY_63MS 0x01
#define BME280_STANDBY_125MS 0x02
#define BME280_STANDBY_250MS 0x03
#define BME280_STANDBY_500MS 0x04
#define BME280_STANDBY_1000MS 0x05
#define BME280_STANDBY_10MS 0x06
#define BME280_STANDBY_20MS 0x07

// Filter Coefficients
#define BME280_FILTER_COEFF_OFF 0x00
#define BME280_FILTER_COEFF_2 0x01
#define BME280_FILTER_COEFF_4 0x02
#define BME280_FILTER_COEFF_8 0x03
#define BME280_FILTER_COEFF_16 0x04


/* Register Addresses. */
#define BME280_ID_REG          0xD0
#define BME280_RESET_REG       0xE0
#define BME280_CTRL_HUM_REG    0xF2
#define BME280_STATUS_REG      0xF3
#define BME280_CTRL_MEAS_REG   0xF4
#define BME280_CONFIG_REG      0xF5
#define BME280_PRESS_MSB_REG   0xF7
#define BME280_PRESS_LSB_REG   0xF8
#define BME280_PRESS_XLSB_REG  0xF9
#define BME280_TEMP_MSB_REG    0xFA
#define BME280_TEMP_LSB_REG    0xFB
#define BME280_TEMP_XLSB_REG   0xFC
#define BME280_HUM_MSB_REG     0xFD
#define BME280_HUM_LSB_REG     0xFE

// Sensor Data Read Bytes
#define BME280_PRESS_MSB   0
#define BME280_PRESS_LSB   1
#define BME280_PRESS_XLSB  2
#define BME280_TEMP_MSB    3
#define BME280_TEMP_LSB    4
#define BME280_TEMP_XLSB   5
#define BME280_HUM_MSB     6
#define BME280_HUM_LSB     7
#define BME280_DATA_FRAME_SIZE 8

// Factory Calibration Parameters
#define BME280_CALIB_DT1_LSB_REG 0x88
#define BME280_CALIB_DT1_MSB_REG 0x89
#define BME280_CALIB_DT2_LSB_REG 0x8A
#define BME280_CALIB_DT2_MSB_REG 0x8B
#define BME280_CALIB_DT3_LSB_REG 0x8C
#define BME280_CALIB_DT3_MSB_REG 0x8D
#define BME280_CALIB_DP1_LSB_REG 0x8E
#define BME280_CALIB_DP1_MSB_REG 0x8F
#define BME280_CALIB_DP2_LSB_REG 0x90
#define BME280_CALIB_DP2_MSB_REG 0x91
#define BME280_CALIB_DP3_LSB_REG 0x92
#define BME280_CALIB_DP3_MSB_REG 0x93
#define BME280_CALIB_DP4_LSB_REG 0x94
#define BME280_CALIB_DP4_MSB_REG 0x95
#define BME280_CALIB_DP5_LSB_REG 0x96
#define BME280_CALIB_DP5_MSB_REG 0x97
#define BME280_CALIB_DP6_LSB_REG 0x98
#define BME280_CALIB_DP6_MSB_REG 0x99
#define BME280_CALIB_DP7_LSB_REG 0x9A
#define BME280_CALIB_DP7_MSB_REG 0x9B
#define BME280_CALIB_DP8_LSB_REG 0x9C
#define BME280_CALIB_DP8_MSB_REG 0x9D
#define BME280_CALIB_DP9_LSB_REG 0x9E
#define BME280_CALIB_DP9_MSB_REG 0x9F
#define BME280_CALIB_DH1_REG     0xA1
#define BME280_CALIB_DH2_LSB_REG 0xE1
#define BME280_CALIB_DH2_MSB_REG 0xE2
#define BME280_CALIB_DH3_REG     0xE3
#define BME280_CALIB_DH4_MSB_REG 0xE4
#define BME280_CALIB_DH4_LSB_REG 0xE5
#define BME280_CALIB_DH5_MSB_REG 0xE6
#define BME280_CALIB_DH6_REG     0xE7


/******************************************************************************
 *  UNION
 ******************************************************************************/
typedef union {

    struct {
        uint8_t im_update : 1;
        uint8_t : 2;
        uint8_t measuring : 1;
        uint8_t : 4;
    };
    uint8_t statusReg;
} bme280_status_t;

typedef union {

    struct {
        uint8_t mode : 2;
        uint8_t osrs_P : 3;
        uint8_t osrs_T : 3;
    };
    uint8_t ctrlMeasReg;
} bme280_ctrl_meas_t;

typedef union {

    struct {
        uint8_t spi3w_en : 1;
        uint8_t filter : 3;
        uint8_t t_sb : 3;
    };
    uint8_t configReg;
} bme280_config_t;

/******************************************************************************
 *  STRUCTURE
 ******************************************************************************/
typedef struct {
    uint16_t dig_T1;
    int dig_T2;
    int dig_T3;
    uint16_t dig_P1;
    int dig_P2;
    int dig_P3;
    int dig_P4;
    int dig_P5;
    int dig_P6;
    int dig_P7;
    int dig_P8;
    int dig_P9;
    uint8_t dig_H1;
    int dig_H2;
    uint8_t dig_H3;
    int dig_H4;
    int dig_H5;
    signed char dig_H6;
} bme280_calibration_param_t;
/******************************************************************************
*  FUNCTION PROTOTYPES
******************************************************************************/
bool BME280_init(void);
uint8_t BME280_getID(void);
void BME280_reset(void);
void BME280_sleep(void);
void BME280_readFactoryCalibrationParams(void);
void BME280_setStandbyTime(uint8_t Value);
void BME280_setFilterCoefficient(uint8_t Value);
void BME280_setOversamplingTemperature(uint8_t Value);
void BME280_setOversamplingPressure(uint8_t Value);
void BME280_setOversamplingHumidity(uint8_t Value);
void BME280_setSensorMode(uint8_t Value);
void BME280_initializeSensor(void);
bool BME280_startForcedSensing(void);
bool BME280_isMeasuring(void);
uint8_t BME280_isMeasuringResult(void);
bool BME280_readMeasurements(void);
void BME280_readMeasurementResult(void);
float BME280_getTemperature(void);
float BME280_getHumidity(void);
float BME280_getPressure(void);

#endif /* _BM280_H */

/* ********************************** End of File  ****************************/