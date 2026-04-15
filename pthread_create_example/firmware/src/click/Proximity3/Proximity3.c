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
#include "Proximity3.h"
#include "../Click.h"
#include "definitions.h"  
//#include "udp_handler.h"

/******************************************************************************
 *  DEFINES & MACROS
 ******************************************************************************/
#define SERCOM_I2C_IsBusy()               SERCOM1_I2C_IsBusy()
#define SERCOM_I2C_WRITE(addr, ptr, size) SERCOM1_I2C_Write(addr, ptr, size)
#define SERCOM_I2C_WRITEREAD(addr, tx_ptr, tx_size, rx_ptr, rx_size) SERCOM1_I2C_WriteRead(addr, tx_ptr, tx_size, rx_ptr, rx_size)

#define VCNL4200_SLAVE_ADDRESS         0x51

/* Device ID Value. */
#define VCNL4200_DEVICE_ID_VALUE       0x1058

/* Table 1 command code and Register Description (Refer Table 1 Datasheet page 9). */
#define VCNL4200_ALS_CONF              0x00
#define VCNL4200_ALS_THDH              0x01
#define VCNL4200_ALS_THDL              0x02
#define VCNL4200_PS_CONF1              0x03
#define VCNL4200_PS_CONF2              0x03
#define VCNL4200_PS_CONF3              0x04
#define VCNL4200_PS_MS                 0x04
#define VCNL4200_PS_CANC               0x05
#define VCNL4200_PS_THDL               0x06
#define VCNL4200_PS_THDH               0x07
#define VCNL4200_PS_Data               0x08
#define VCNL4200_ALS_Data              0x09
#define VCNL4200_White_Data            0x0A
#define VCNL4200_INT_Flag              0x0D
#define VCNL4200_ID                    0x0E

/* Table 2 Register: ALS_Conf Description (Refer Table 2 Datasheet page 10). */
#define VCNL4200_ALS_SD_ON             0x00
#define VCNL4200_ALS_SD_OFF            0x01
#define VCNL4200_ALS_INT_EN            0x00
#define VCNL4200_ALS_INT_DIS           0x02
#define VCNL4200_ALS_PERS_1            0x00
#define VCNL4200_ALS_PERS_2            0x04
#define VCNL4200_ALS_PERS_3            0x08
#define VCNL4200_ALS_PERS_4            0x0C
#define VCNL4200_ALS_INT_SWITCH_0      0x00
#define VCNL4200_ALS_INT_SWITCH_1      0x20
#define VCNL4200_ALS_IT_50ms           0x00
#define VCNL4200_ALS_IT_100ms          0x40
#define VCNL4200_ALS_IT_200ms          0x80
#define VCNL4200_ALS_IT_400ms          0xC0

/* Table 6 Register: PS_CONF1 Description (Refer Table 6 Datasheet page 10). */
#define VCNL4200_PS_SD_ON              0x00
#define VCNL4200_PS_SD_OFF             0x01
#define VCNL4200_PS_IT_1T              0x00
#define VCNL4200_PS_IT_1_5T            0x02
#define VCNL4200_PS_IT_2T              0x04
#define VCNL4200_PS_IT_4T              0x06
#define VCNL4200_PS_IT_8T              0x08
#define VCNL4200_PS_IT_9T              0x0A
#define VCNL4200_PS_PERS_1             0x00
#define VCNL4200_PS_PERS_2             0x10
#define VCNL4200_PS_PERS_3             0x20
#define VCNL4200_PS_PERS_4             0x30
#define VCNL4200_PS_DUTY_1_160         0x00
#define VCNL4200_PS_DUTY_1_320         0x40
#define VCNL4200_PS_DUTY_1_640         0x80
#define VCNL4200_PS_DUtY_1_1280        0xC0

/* Table 7 Register: PS_CONF2 Description (Refer Table 7 Datasheet page 11). */
#define VCNL4200_PS_INT_DIS            0x00
#define VCNL4200_PS_INT_Trig_Clos      0x01
#define VCNL4200_PS_INT_Trig_away      0x02
#define VCNL4200_PS_INT_Trig_Clos_away 0x03
#define VCNL4200_PS_HD_12bits          0x00
#define VCNL4200_PS_HD_16bits          0x04

/* Table 8 Register: PS_CONF3 Description (Refer Table 8 Datasheet page 11). */
#define VCNL4200_PS_SC_EN_Enable       0x01
#define VCNL4200_PS_SC_EN_Disable      0x00
#define VCNL4200_PS_SC_ADV_Typ_sunx1   0x00
#define VCNL4200_PS_SC_ADV_Typ_Sunx2   0x02
#define VCNL4200_PS_TRIG               0x04
#define VCNL4200_PS_AF_Enable          0x08
#define VCNL4200_PS_AF_Disable         0x00
#define VCNL4200_PS_SMART_PERS_Disable 0x00
#define VCNL4200_PS_SMART_PERS_Enable  0x10
#define VcNL4200_PS_MPS_1              0x00
#define VCNL4200_PS_MPS_2              0x20
#define VCNL4200_PS_MPS_4              0x40
#define VCNL4200_PS_MPS_8              0x60

/* Table 9 Register: PS_MS Description (Refer Table 9 Datasheet page 11). */
#define VCNL4200_LED_I_50mA            0x00
#define VCNL4200_LED_I_75mA            0x01
#define VCNL4200_LED_I_100mA           0x02
#define VCNL4200_LED_I_120mA           0x03
#define VCNL4200_LED_I_140mA           0x04
#define VCNL4200_LED_I_160mA           0x05
#define VCNL4200_LED_I_180mA           0x06
#define VCNL4200_LED_I_200mA           0x07
#define VCNL4200_PS_SPO_00h            0x00
#define VCNL4200_PS_SPO_FFh            0x08
#define VCNL4200_PS_SP_1               0x00
#define VCNL4200_PS_SP_1_5             0x10
#define VCNL4200_Ps_MS_Normal          0x00
#define VCNL4200_PS_MS_Logic           0x20

#define VCNL4200_ALS_RESOLUTION        24

/******************************************************************************
 *  VARIABLES
 ******************************************************************************/
/* 2 buffer used one for proximity and ambience. */
static uint8_t m_buffer[2][2];
static SensorTask_t task = { false, 100, 0, false };
/******************************************************************************
 *  FUNCTION DECLARATIONS
 ******************************************************************************/
static uint16_t vcnl4200_get_id(void);
static void vcnl4200_ambient_init(void);
static void vcnl4200_proximity_init(void);
static bool vcnl4200_i2c_transfer(uint8_t address, uint8_t buffer_index);
/******************************************************************************
 *  FUNCTION DEFINITIONS
 *****************************************************************************/
/******************************************************************************
 ** Function Name	: vcnl4200_init
 ** Description		: Initialize the VCNL4200 sensor.
 ******************************************************************************/
void vcnl4200_proximityinit(void)
{
    /* Initialize the Ambient and proximity sensor. */
    vcnl4200_proximity_init();
//    vcnl4200_ambient_init();

    /* Check device ID. */
    if (vcnl4200_get_id() != VCNL4200_DEVICE_ID_VALUE)
        printf("> VCNL4200: Initialization failed. \r\n");
    else
        printf("> VCNL4200: Initialized. \r\n");

    DELAY_MS(10);
}
uint16_t vcnl4200_UpdateProximityValue(void)
{
    uint16_t proximity = 0;  
    
    if (task.data_ready)
    {

        /* Get the proximity value. */
        proximity = vcnl4200_get_proximity();    
        task.enable = false;            

    }   

    return proximity;
}
uint16_t vcnl4200_UpdateambientValue(void)
{    
    uint16_t ambient = 0;    
    if (task.data_ready)
    {        
        /* Get the proximity value. */
        ambient = vcnl4200_get_ambience();  
        ambient = ambient * VCNL4200_ALS_RESOLUTION/1000;
        // Step 2: Convert lux to irradiance
        ambient = ambient * 0.2f; // factor depends on spectrum
//        task.data_ready = 0;
        task.enable = false; 
    }   
    
    return ambient; // µW/cm²
}

void vcnl4200_ambientinit(void)
{
    /* Initialize the Ambient and proximity sensor. */
    vcnl4200_ambient_init();

    /* Check device ID. */
    if (vcnl4200_get_id() != VCNL4200_DEVICE_ID_VALUE)
        printf("> VCNL4200: Initialization failed. \r\n");
    else
        printf("> VCNL4200: Initialized. \r\n");

    DELAY_MS(10);
}
/******************************************************************************
 ** Function Name   : vcnl4200_proximity_service
 ** Description     : Method is gateway between proximity sensor and Lan867x.
 ******************************************************************************/
void vcnl4200_proximity_service(void)
{
   // static SensorTask_t task = { false, 30, 0, false };

    if (task.enable == true && systick.tickCounter > task.next_interval) {

        /* Set the next Measure/send data time. */
        task.next_interval = systick.tickCounter + task.interval;

        /* Check if the proximity value is ready or not. */
        if (vcnl4200_proximity_task())
            task.data_ready = 1;
        
    }
}

/******************************************************************************
 ** Function Name   : vcnl4200_ambient_service
 ** Description     : Method is gateway between ambient sensor and Lan867x.
 ******************************************************************************/
void vcnl4200_ambient_service(void)
{
    /* Check if any wake packets arrived to sleep or wake the node. */
//    switch (ethernet_check_wake_message(AMBIENT_WAKE)) {
//    case 1: /* Wake the node. */
//        task.enable = true;
//        task.next_interval = systick.tickCounter;
//        break;
//    case 0: /* Sleep the node. */
//        task.enable = false;
//        break;
//    }

    if (task.enable == true && systick.tickCounter > task.next_interval) 
    {

        /* Set the next Measure/send data time. */
        task.next_interval = systick.tickCounter + task.interval;

        /* Check if the ambient value is ready. */
        if (vcnl4200_ambient_task()) 
            task.data_ready = 1;
    }
}

/******************************************************************************
 ** Function Name	: vcnl4200_proximity_task
 ** Description		: Run the proximity service.
 ** Return          : Returns the proximity service state.
 ******************************************************************************/
uint8_t vcnl4200_proximity_task(void)
{
    static uint8_t state = 0;

    switch (state) {
    case 0: /* Queue the I2C transfer to read the proximity value. */
        /* Check if I2C is busy. */
        if (SERCOM_I2C_IsBusy())
            return 0;

        if (!vcnl4200_i2c_transfer(VCNL4200_PS_Data, 0))
            return 0;

        state = 1;

        break;

    case 1: /* Check if I2C transmission is complete or not. */
        /* Check if I2C is busy. */
        if (SERCOM_I2C_IsBusy())
            return 0;

        state = 0;

        return 1;
    }
    return 0;
}

/******************************************************************************
 ** Function Name	: vcnl4200_ambient_task
 ** Description		: Read Ambient light sensor service.
 ** Return		    : Returns the ambient service state.
 ******************************************************************************/
uint8_t vcnl4200_ambient_task(void)
{
    static uint8_t state = 0;

    switch (state) {
    case 0: /* Queue the I2C transfer to read the ambient value. */
        /* Check if I2C is busy. */
        if (SERCOM_I2C_IsBusy())
            return 0;

        if (!vcnl4200_i2c_transfer(VCNL4200_ALS_Data, 1))
            return 0;

        state = 1;

        break;

    case 1: /* Check if I2C transmission is complete or not. */
        /* Check if I2C is busy. */
        if (SERCOM_I2C_IsBusy())
            return 0;

        state = 0;

        return 1;
    }
    return 0;
}

/******************************************************************************
 ** Function Name   : vcnl4200_get_proximity
 ** Description     : The functions return the proximity value.
 ** Return          : Returns the value.
 ******************************************************************************/
uint16_t vcnl4200_get_proximity(void)
{
    return (uint16_t)(m_buffer[0][1] << 8) | m_buffer[0][0];
}

/******************************************************************************
 ** Function Name   : vcnl4200_get_ambience
 ** Description     : The functions return the ambient value.
 ** Return          : Returns the value.
 ******************************************************************************/
uint16_t vcnl4200_get_ambience(void)
{
    return (uint16_t)(m_buffer[1][1] << 8) | m_buffer[1][0];
}

/******************************************************************************
 *  STATIC FUNCTION DEFINITIONS
 ******************************************************************************/
/******************************************************************************
 ** Function Name	: vcnl4200_ambient_init
 ** Description		: Initialize the Ambient light measurement with the default values.
 ******************************************************************************/
static void vcnl4200_ambient_init(void)
{
    uint8_t writeBuffer[3];
    writeBuffer[0] = VCNL4200_ALS_CONF;
    writeBuffer[1] = 0;
    writeBuffer[2] = 0;

    SERCOM_I2C_WRITE(VCNL4200_SLAVE_ADDRESS, writeBuffer, 3);

    /* Wait till transmission is complete. */
    while (SERCOM_I2C_IsBusy());
}

/******************************************************************************
 ** Function Name	: vcnl4200_proximity_init
 ** Description		: Initialize the Proximity measurement with the default values.
 ******************************************************************************/
static void vcnl4200_proximity_init(void)
{
    uint8_t writeBuffer[3];
    writeBuffer[0] = VCNL4200_PS_CONF1;
    writeBuffer[1] = VCNL4200_PS_IT_9T | VCNL4200_PS_DUTY_1_320;
    writeBuffer[2] = VCNL4200_PS_AF_Enable;
    SERCOM_I2C_WRITE(VCNL4200_SLAVE_ADDRESS, writeBuffer, 3);
    DELAY_MS(10);

    /* Wait till transmission is complete. */
    while (SERCOM_I2C_IsBusy());

    writeBuffer[0] = VCNL4200_PS_CONF3;
    writeBuffer[1] = VCNL4200_PS_SC_EN_Enable;
    writeBuffer[2] = VCNL4200_LED_I_50mA;
    SERCOM_I2C_WRITE(VCNL4200_SLAVE_ADDRESS, writeBuffer, 3);
    DELAY_MS(10);

    /* Wait till transmission is complete. */
    while (SERCOM_I2C_IsBusy());
}

/******************************************************************************
 ** Function Name	: vcnl4200_get_id
 ** Description		: Read the sensor Id.
 ** Return		    : Returns the sensor Id.
 ******************************************************************************/
static uint16_t vcnl4200_get_id(void)
{
    vcnl4200_i2c_transfer(VCNL4200_ID, 0);
    while (SERCOM_I2C_IsBusy());
    return (uint16_t)(m_buffer[0][1] << 8) | m_buffer[0][0];
}

/******************************************************************************
 ** Function Name	: vcnl4200_i2c_transfer
 ** Description		: Read data from Proximity sensor ( using I2C restart).
 ** Return		    : Returns the transmission status.
 ******************************************************************************/
static bool vcnl4200_i2c_transfer(uint8_t address, uint8_t buffer_index)
{
    m_buffer[buffer_index][0] = address;

    return SERCOM_I2C_WRITEREAD(VCNL4200_SLAVE_ADDRESS, m_buffer[buffer_index], 1, m_buffer[buffer_index], 2);
}


/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/*                   CALLBACK FUNCTION FROM UDP Handler                 */
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

void UdpHandler_Wake_Proximity(void)
{   
    if(!task.enable) //check if task enable 
    {
        task.enable =true;
        if(task.next_interval ==0)
        {
            task.next_interval = systick.tickCounter;  
        }
          
    }
}
/*------------------------------ End of File ----------------------------------*/