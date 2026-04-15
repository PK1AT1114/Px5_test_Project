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
#include "Bme280.h"
#include "../Click.h"
#include <stdio.h>
#include <string.h>
#include "../../spi_driver/spi_async_driver.h"
/******************************************************************************
 *  DEFINES & MACROS
 ******************************************************************************/
#define SPI_INSTANCE           (DRV_SPI_INDEX_0)
#define SPI_SPEED_HZ           (12000000)
#define CHIP_SELECT_PIN        (0)
#define MAX_PAYLOAD_LENGTH     (30)
typedef struct {
    uint8_t bme280_ctrl_hum;
    bme280_status_t bme280_status;
    bme280_config_t bme280_config;
    bme280_ctrl_meas_t bme280_ctrl_meas;
    bme280_calibration_param_t calibParam;
    long adc_T;
    long adc_H;
    long adc_P;
    long t_fine;
    
    uint8_t m_rxBuffer[MAX_PAYLOAD_LENGTH];
    uint8_t m_txBuffer[MAX_PAYLOAD_LENGTH];
} Bme280Data_t;

/******************************************************************************
 *  VARIABLES
 ******************************************************************************/

static Bme280Data_t m_clientData={0};

/******************************************************************************
 *  FUNCTION PROTOTYPES
 ******************************************************************************/
static long BME280_compensateTemperature(void);
static uint32_t BME280_compensatePressure(void);
static uint32_t BME280_compensateHumidity(void);

static bool BME280_readByte(uint8_t reg_addr);
static bool BME280_writeByte(uint8_t reg_addr, uint8_t data);
static bool BME280_readBlock(uint8_t reg_addr, uint8_t length);

//static void BME280_spi_event_handler( DRV_SPI_TRANSFER_EVENT event, DRV_SPI_TRANSFER_HANDLE transferHandle, uintptr_t context);

/******************************************************************************
 *  FUNCTION DEFINITIONS
 *****************************************************************************/
bool BME280_init(void)
{
    return(SpiDrvAsync_SetSpiConfig(SPI_INSTANCE, CHIP_SELECT_PIN, SPI_SPEED_HZ, true, true));  
}

uint8_t BME280_getID(void)
{
    while(!BME280_readByte(BME280_ID_REG))
    {
        SpiDrvAsync_Service();
    }
     
    return m_clientData.m_rxBuffer[1];
}

void BME280_reset(void)
{
     while(!BME280_writeByte(BME280_RESET_REG, BME280_SOFT_RESET))
    {
        SpiDrvAsync_Service();
    }
    DELAY_MS(200);
}

void BME280_sleep(void)
{
    m_clientData.bme280_ctrl_meas.mode = BME280_SLEEP_MODE;
    while(!BME280_writeByte(BME280_CTRL_MEAS_REG, m_clientData.bme280_ctrl_meas.ctrlMeasReg))
    {
        SpiDrvAsync_Service();
    }
}

void BME280_readFactoryCalibrationParams(void)
{
    uint8_t* paramBuff;

    while(!BME280_readBlock(BME280_CALIB_DT1_LSB_REG, 24))
    {
        SpiDrvAsync_Service();
    }
    paramBuff = &m_clientData.m_rxBuffer[1];

    m_clientData.calibParam.dig_T1 = (((uint16_t)paramBuff[1]) << 8) + paramBuff[0];
    m_clientData.calibParam.dig_T2 = (((int)paramBuff[3]) << 8) + paramBuff[2];
    m_clientData.calibParam.dig_T3 = (((int)paramBuff[5]) << 8) + paramBuff[4];
    m_clientData.calibParam.dig_P1 = (((uint16_t)paramBuff[7]) << 8) + paramBuff[6];
    m_clientData.calibParam.dig_P2 = (((int)paramBuff[9]) << 8) + paramBuff[8];
    m_clientData.calibParam.dig_P3 = (((int)paramBuff[11]) << 8) + paramBuff[10];
    m_clientData.calibParam.dig_P4 = (((int)paramBuff[13]) << 8) + paramBuff[12];
    m_clientData.calibParam.dig_P5 = (((int)paramBuff[15]) << 8) + paramBuff[14];
    m_clientData.calibParam.dig_P6 = (((int)paramBuff[17]) << 8) + paramBuff[16];
    m_clientData.calibParam.dig_P7 = (((int)paramBuff[19]) << 8) + paramBuff[18];
    m_clientData.calibParam.dig_P8 = (((int)paramBuff[21]) << 8) + paramBuff[20];
    m_clientData.calibParam.dig_P9 = (((int)paramBuff[23]) << 8) + paramBuff[22];

    while(!BME280_readByte(BME280_CALIB_DH1_REG))
    {
        SpiDrvAsync_Service();
    }
   
    m_clientData.calibParam.dig_H1 = m_clientData.m_rxBuffer[1];
   
    while(!BME280_readBlock(BME280_CALIB_DH2_LSB_REG, 7))
    {    
        SpiDrvAsync_Service();
    }
    m_clientData.calibParam.dig_H2 = (((int)paramBuff[1]) << 8) + paramBuff[0];
    m_clientData.calibParam.dig_H3 = (uint8_t)paramBuff[2];
    m_clientData.calibParam.dig_H4 = (((int)paramBuff[3]) << 4) | (paramBuff[4] & 0xF);
    m_clientData.calibParam.dig_H5 = (((int)paramBuff[5]) << 4) | (paramBuff[4] >> 4);
    m_clientData.calibParam.dig_H6 = (short)paramBuff[6]; 
}

void BME280_setStandbyTime(uint8_t sbtime)
{
    m_clientData.bme280_config.t_sb = sbtime;
}

void BME280_setFilterCoefficient(uint8_t coeff)
{
    m_clientData.bme280_config.filter = coeff;
}

void BME280_setOversamplingTemperature(uint8_t osrs_t)
{
    m_clientData.bme280_ctrl_meas.osrs_T = osrs_t;
}

void BME280_setOversamplingPressure(uint8_t osrs_p)
{
    m_clientData.bme280_ctrl_meas.osrs_P = osrs_p;
}

void BME280_setOversamplingHumidity(uint8_t osrs_h)
{
    m_clientData.bme280_ctrl_hum = osrs_h;
}

void BME280_setSensorMode(uint8_t mode)
{
    m_clientData.bme280_ctrl_meas.mode = mode;
}

void BME280_initializeSensor(void)
{
    while(!BME280_writeByte(BME280_CONFIG_REG, m_clientData.bme280_config.configReg))
    {
        SpiDrvAsync_Service();
    }
    while(!BME280_writeByte(BME280_CTRL_HUM_REG, m_clientData.bme280_ctrl_hum))
    {
        SpiDrvAsync_Service();
    }
    while(!BME280_writeByte(BME280_CTRL_MEAS_REG, m_clientData.bme280_ctrl_meas.ctrlMeasReg))
    {
        SpiDrvAsync_Service();
    }
}

bool BME280_startForcedSensing(void)
{
    m_clientData.bme280_ctrl_meas.mode = BME280_FORCED_MODE;
   return BME280_writeByte(BME280_CTRL_MEAS_REG, m_clientData.bme280_ctrl_meas.ctrlMeasReg);
}

bool BME280_isMeasuring(void)
{
    return ( BME280_readByte(BME280_STATUS_REG));
}

uint8_t BME280_isMeasuringResult(void)
{
    m_clientData.bme280_status.statusReg = m_clientData.m_rxBuffer[1];
    return (m_clientData.bme280_status.measuring);  
}

bool BME280_readMeasurements(void)
{
    return (BME280_readBlock(BME280_PRESS_MSB_REG, BME280_DATA_FRAME_SIZE));
}

void BME280_readMeasurementResult(void)
{
    uint8_t* sensorData = &m_clientData.m_rxBuffer[1];
    m_clientData.adc_H = ((uint32_t)sensorData[BME280_HUM_MSB] << 8) | sensorData[BME280_HUM_LSB];

    m_clientData.adc_T = ((uint32_t)sensorData[BME280_TEMP_MSB] << 12)
        | (((uint32_t)sensorData[BME280_TEMP_LSB] << 4) | ((uint32_t)sensorData[BME280_TEMP_XLSB] >> 4));

    m_clientData.adc_P = ((uint32_t)sensorData[BME280_PRESS_MSB] << 12)
        | (((uint32_t)sensorData[BME280_PRESS_LSB] << 4) | ((uint32_t)sensorData[BME280_PRESS_XLSB] >> 4));
}

float BME280_getTemperature(void)
{
    float temperature = (float)BME280_compensateTemperature() / 100;
    return temperature;
}

float BME280_getPressure(void)
{
    float pressure = (float)BME280_compensatePressure() / 1000;
    return pressure;
}

float BME280_getHumidity(void)
{
    float humidity = (float)BME280_compensateHumidity() / 1024;
    return humidity;
}

/*
 * Returns temperature in DegC, resolution is 0.01 DegC.
 * Output value of "5123" equals 51.23 DegC.
 */
static long BME280_compensateTemperature(void)
{
    long tempV1, tempV2, t;

    tempV1 = ((((m_clientData.adc_T >> 3) - ((long)m_clientData.calibParam.dig_T1 << 1))) * ((long)m_clientData.calibParam.dig_T2)) >> 11;
    tempV2 = (((((m_clientData.adc_T >> 4) - ((long)m_clientData.calibParam.dig_T1)) * ((m_clientData.adc_T >> 4) - ((long)m_clientData.calibParam.dig_T1))) >> 12)
                 * ((long)m_clientData.calibParam.dig_T3))
        >> 14;
    m_clientData.t_fine = tempV1 + tempV2;
    t = (m_clientData.t_fine * 5 + 128) >> 8;

    return t;
}

/*
 * Returns pressure in Pa as unsigned 32 bit integer.
 * Output value of "96386" equals 96386 Pa = 96.386 kPa
 */
static uint32_t BME280_compensatePressure(void)
{
    long pressV1, pressV2;
    uint32_t p;

    pressV1 = (((long)m_clientData.t_fine) >> 1) - (long)64000;
    pressV2 = (((pressV1 >> 2) * (pressV1 >> 2)) >> 11) * ((long)m_clientData.calibParam.dig_P6);
    pressV2 = pressV2 + ((pressV1 * ((long)m_clientData.calibParam.dig_P5)) << 1);
    pressV2 = (pressV2 >> 2) + (((long)m_clientData.calibParam.dig_P4) << 16);
    pressV1 = (((m_clientData.calibParam.dig_P3 * (((pressV1 >> 2) * (pressV1 >> 2)) >> 13)) >> 3)
                  + ((((long)m_clientData.calibParam.dig_P2) * pressV1) >> 1))
        >> 18;
    pressV1 = ((((32768 + pressV1)) * ((long)m_clientData.calibParam.dig_P1)) >> 15);

    if (pressV1 == 0) {
        // avoid exception caused by division by zero
        return 0;
    }

    p = (((uint32_t)(((long)1048576) - m_clientData.adc_P) - (pressV2 >> 12))) * 3125;
    if (p < 0x80000000) {
        p = (p << 1) / ((uint32_t)pressV1);
    } else {
        p = (p / (uint32_t)pressV1) * 2;
    }

    pressV1 = (((long)m_clientData.calibParam.dig_P9) * ((long)(((p >> 3) * (p >> 3)) >> 13))) >> 12;
    pressV2 = (((long)(p >> 2)) * ((long)m_clientData.calibParam.dig_P8)) >> 13;
    p = (uint32_t)((long)p + ((pressV1 + pressV2 + m_clientData.calibParam.dig_P7) >> 4));

    return p;
}

/*
 * Returns humidity in %RH as unsigned 32 bit integer in Q22.10 format
 * (22 integer and 10 fractional bits).
 * Output value of "47445" represents 47445/1024 = 46.333 %RH
 */
static uint32_t BME280_compensateHumidity(void)
{
    long humV;
    uint32_t h;

    humV = (m_clientData.t_fine - ((long)76800));
    humV = (((((m_clientData.adc_H << 14) - (((long)m_clientData.calibParam.dig_H4) << 20) - (((long)m_clientData.calibParam.dig_H5) * humV)) + ((long)16384))
                >> 15)
        * (((((((humV * ((long)m_clientData.calibParam.dig_H6)) >> 10)
                  * (((humV * ((long)m_clientData.calibParam.dig_H3)) >> 11) + ((long)32768)))
                 >> 10)
                + ((long)2097152))
                   * ((long)m_clientData.calibParam.dig_H2)
               + 8192)
            >> 14));
    humV = (humV - (((((humV >> 15) * (humV >> 15)) >> 7) * ((long)m_clientData.calibParam.dig_H1)) >> 4));
    humV = (humV < 0 ? 0 : humV);
    humV = (humV > 419430400 ? 419430400 : humV);

    h = (uint32_t)(humV >> 12);
    return h;
}


bool BME280_writeByte(uint8_t reg_addr, uint8_t data)
{
    SpiDrvAsync_TransferParam_t param = { 0 };
    m_clientData.m_txBuffer[0] = reg_addr & 0x7F;
    m_clientData.m_txBuffer[1] = data;

    param.spiInstance = SPI_INSTANCE;
    param.csInstance = CHIP_SELECT_PIN;
    
    param.pTxBuf = m_clientData.m_txBuffer;
    param.pRxBuf = m_clientData.m_rxBuffer;
    param.bufSize = sizeof(m_clientData.m_txBuffer);
    
    param.zeroCopyTx = true;
    param.zeroCopyRx = true;

    if(!SpiDrvAsync_Transfer(&param)) {
        return false;
    }

    return true;
}

bool BME280_readByte(uint8_t reg_addr)
{
    SpiDrvAsync_TransferParam_t param = { 0 };
    /* Clear the buffer data. */
    memset(m_clientData.m_txBuffer, 255, 2);
    memset(m_clientData.m_rxBuffer, 0, 2);

    m_clientData.m_txBuffer[0] = reg_addr | 0x80;
    
    param.spiInstance = SPI_INSTANCE;
    param.csInstance = CHIP_SELECT_PIN;
    
    param.pTxBuf = m_clientData.m_txBuffer;
    param.pRxBuf = m_clientData.m_rxBuffer;
    param.bufSize = sizeof(m_clientData.m_txBuffer);
    
    param.zeroCopyTx = true;
    param.zeroCopyRx = true;
    if(!SpiDrvAsync_Transfer(&param)) {
        return false;
    }

    return true;
}

bool BME280_readBlock(uint8_t reg_addr, uint8_t length)
{
    SpiDrvAsync_TransferParam_t param = { 0 };
    /* Clear the buffer data. */
    memset(m_clientData.m_txBuffer, 255,  length + 1);
    memset(m_clientData.m_rxBuffer, 0, length + 1);

    m_clientData.m_txBuffer[0] = reg_addr | 0x80;
    
    param.spiInstance = SPI_INSTANCE;
    param.csInstance = CHIP_SELECT_PIN;
    
    param.pTxBuf = m_clientData.m_txBuffer;
    param.pRxBuf = m_clientData.m_rxBuffer;
    param.bufSize = sizeof(m_clientData.m_txBuffer);
    
    param.zeroCopyTx = true;
    param.zeroCopyRx = true;
    
    if(!SpiDrvAsync_Transfer(&param)) {
        return false;
    }

    return true;
}



/*---------------------- End of File ----------------------------------------*/