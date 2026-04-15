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
#include "WeatherClick.h"
#include "../Click.h"
#include "Bme280.h"
//#include "udp_handler.h"
#include "definitions.h"  

/******************************************************************************
 *  DEFINES & MACROS
 ******************************************************************************/
#define DEFAULT_STANDBY_TIME   BME280_STANDBY_HALFMS
#define DEFAULT_FILTER_COEFF   BME280_FILTER_COEFF_OFF
#define DEFAULT_TEMP_OSRS      BME280_OVERSAMP_X1
#define DEFAULT_PRESS_OSRS     BME280_OVERSAMP_X1
#define DEFAULT_HUM_OSRS       BME280_OVERSAMP_X1
#define DEFAULT_SENSOR_MODE    BME280_FORCED_MODE

/******************************************************************************
 *  ENUM
 ******************************************************************************/
typedef enum {
    /* Application's state machine's initial state. */
    WEATHER_START_FORCED_SENSING,
    WEATHER_IS_MEASURING,
    WEATHER_IS_MEASURING_RESULT,
    WEATHER_READ_MEASUREMENT,
    WEATHER_READ_MEASUREMENT_RESULT,
    WEATHER_IDLE,
    WEATHER_ERROR
} Weather_state_t;

typedef struct
{
    bool spiEnable; 
    uint8_t Initialized;
    bool data_ready;
    Weather_state_t state;
} WeatherData_t;

/******************************************************************************
 *  VARIABLES
 ******************************************************************************/
static WeatherData_t m_weatherData = { 0 };

static SensorTask_t task = { false, 100, 0, false };
/******************************************************************************
 *  FUNCTION DEFINITION
 ******************************************************************************/
/******************************************************************************
 ** Function Name        : weather_init
 ** Description          : Set the weather state to init.
 ******************************************************************************/
void weather_init(void)
{
    m_weatherData.spiEnable= BME280_init();
    
    if( m_weatherData.spiEnable)
    {   
        printf(">BME280: SPI initialization success.\r\n");
        BME280_reset();
        BME280_readFactoryCalibrationParams();

        BME280_setStandbyTime(DEFAULT_STANDBY_TIME);
        BME280_setFilterCoefficient(DEFAULT_FILTER_COEFF);
        BME280_setOversamplingTemperature(DEFAULT_TEMP_OSRS);
        BME280_setOversamplingPressure(DEFAULT_PRESS_OSRS);
        BME280_setOversamplingHumidity(DEFAULT_HUM_OSRS);
        BME280_setSensorMode(DEFAULT_SENSOR_MODE);
        BME280_initializeSensor();
        m_weatherData.state = WEATHER_START_FORCED_SENSING;
        m_weatherData.Initialized = true; 
        printf("Weather Init success!!\r\n");
    }
    else
    {
        printf(">BME280: SPI initialization failed.\r\n");
    }
   
    
}


/******************************************************************************
 ** Function Name        : weather_service
 ** Description          : Method is gateway between Weather click and Lan867x.
 ******************************************************************************/
void weather_service(void)
{    
    //static SensorTask_t task = { false, 20, 0, false };
    uint8_t txBuffer[14];

    float temperature = 0.0;
    float pressure = 0.0;
    float humidity = 0.0;

    if (task.enable == true && systick.tickCounter > task.next_interval) {

        /* Set the next Measure/send data time.*/
        task.next_interval = systick.tickCounter + task.interval;

        /* Read the sensor data. Check if Measurement is ready. */
        if(weather_task())
        {
            /* Read the compensated measurement readings for each parameter. */
            temperature = weather_get_temperatureDegC();
            pressure = weather_get_pressureKPa();
            humidity = weather_get_humidityRH();

//#ifdef DEBUG
    
            printf("Temperature=%d DegC, Pressure=%d kPA, Humidity=%d %%.  \r\n", (int)temperature, (int)pressure, (int)humidity);

//#endif

            /* Create the UDP payload. */
            *(uint16_t*)txBuffer = CLIMATE_VALUE;
            memcpy( txBuffer + 2, &temperature, 4);
            memcpy( txBuffer + 6, &pressure, 4);
            memcpy( txBuffer + 10, &humidity, 4);


            /* Send click information through UDP. */
//            if (UdpHandler_Send(txBuffer,14)==0)
//                task.data_ready = 0;

        }
    }
}

/******************************************************************************
 ** Function Name        : weather_task
 ** Description          : The method runs the service calculating temperature, pressure, and humidity. 
 ** Return               : Returns the status of service. 0: idle, 
                           1: in progress, 2: result is ready.
 ******************************************************************************/
uint8_t weather_task(void)
{
    static uint8_t resetCounter = 0;

    switch (m_weatherData.state) {
        
    case WEATHER_START_FORCED_SENSING:
         m_weatherData.data_ready=false;
        if (DEFAULT_SENSOR_MODE == BME280_FORCED_MODE)
          if(!BME280_startForcedSensing())
            {  
                m_weatherData.state = WEATHER_START_FORCED_SENSING;
                break;
            }
        m_weatherData.state = WEATHER_IS_MEASURING;
        break;

    case WEATHER_IS_MEASURING:
        resetCounter++;
        if (resetCounter > 5) {
            m_weatherData.state = WEATHER_START_FORCED_SENSING;
            break;
        }
        if (BME280_isMeasuring())
            m_weatherData.state = WEATHER_IS_MEASURING_RESULT;
        else
            m_weatherData.state = WEATHER_START_FORCED_SENSING;
        break;

    case WEATHER_IS_MEASURING_RESULT:
        if (BME280_isMeasuringResult())
            m_weatherData.state = WEATHER_IS_MEASURING;
        else
            m_weatherData.state = WEATHER_READ_MEASUREMENT;
        break;
        
    case WEATHER_READ_MEASUREMENT:
        resetCounter = 0;
        if(BME280_readMeasurements())
        {
            m_weatherData.state = WEATHER_READ_MEASUREMENT_RESULT;
        }
        break;
        
    case WEATHER_READ_MEASUREMENT_RESULT:
        BME280_readMeasurementResult();
        m_weatherData.state = WEATHER_START_FORCED_SENSING;
        m_weatherData.data_ready = true;
  
        break;
    case WEATHER_IDLE:
    case WEATHER_ERROR:
        break;
    }
    return m_weatherData.data_ready;
}


/******************************************************************************
 ** Function Name        : weather_get_temperatureDegC
 ** Description          : The method returns the temperature value.
 ** Return               : Returns the temperature value.
 ******************************************************************************/
float weather_get_temperatureDegC(void)
{
    return BME280_getTemperature();
}


/******************************************************************************
 ** Function Name        : weather_get_pressureKPa
 ** Description          : The method returns the pressure value.
 ** Return               : Returns the pressure value.
 ******************************************************************************/
float weather_get_pressureKPa(void)
{
    return BME280_getPressure();
}

/******************************************************************************
 ** Function Name        : weather_get_humidityRH
 ** Description          : The method returns the humidity value.
 ** Return               : Returns the humidity value.
 ******************************************************************************/
float weather_get_humidityRH(void)
{
    return BME280_getHumidity();
}

/******************************************************************************
 ** Function Name        : weather_goto_sleep
 ** Description          : The method will set the weather sensor to sleep.
 ******************************************************************************/
void weather_goto_sleep(void)
{
    BME280_sleep();
    m_weatherData.Initialized = 0;
    m_weatherData.state = WEATHER_START_FORCED_SENSING;
}

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*                   CALLBACK FUNCTION FROM UDP Handler                 */
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

void UdpHandler_Wake_CLIMATE(void)
{   
    if(m_weatherData.Initialized)// check if Module enable 
    {
        if(!task.enable){ //check if task enable 
            task.enable =true;
            if(task.next_interval ==0){
                task.next_interval = systick.tickCounter;  
            }
        }
    }
}
/*------------------------------ End of File ----------------------------------*/