/*******************************************************************************
  SDL COMMON

  Company:
    Microchip Technology Inc.

  File Name:
    sdl_common.c

  Summary:
    Source file for common software SDLnostic routine.

  Description:
    This file provides general functions used by multiple peripheral SDLnostics.

 *******************************************************************************/

/*******************************************************************************
 * Copyright (C) 2027 Microchip Technology Inc. and its subsidiaries.
 *
 * Subject to your compliance with these terms, you may use Microchip software
 * and any derivatives exclusively with Microchip products. It is your
 * responsibility to comply with third party license terms applicable to your
 * use of third party software (including open source software) that may
 * accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
 * ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/

/*------------------------------------------------------------------------------------------------------------
* Include Files
*------------------------------------------------------------------------------------------------------------*/
#include "sdl_drv_common.h"

/*------------------------------------------------------------------------------------------------------------
* Constants
*------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------
* Data Types
*------------------------------------------------------------------------------------------------------------*/


static SDL_SYSTICK_TIMEOUT timeout;  
/*------------------------------------------------------------------------------------------------------------
* Function Declarations
*------------------------------------------------------------------------------------------------------------*/
static uint32_t sSDL_DRV_COMMON_SFR_Read(uint32_t address, uint8_t reg_size);
static void sSDL_DRV_COMMON_SFR_Write(volatile uint32_t address, uint32_t value, uint8_t reg_size);


/*------------------------------------------------------------------------------------------------------------
* Global Static Variables
*------------------------------------------------------------------------------------------------------------*/
 uint32_t sdlErrorStatus = 0;
 static uint32_t diagTimeoutUs = 4500U;

/*------------------------------------------------------------------------------------------------------------
* Global Extern Variables
*------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------
* Function Definitions
*------------------------------------------------------------------------------------------------------------*/
void SDL_DRV_COMMON_TimerStart_us(uint32_t delay_us)
{
    SDL_DRV_SYSTICK_StartTimeOut(&timeout,delay_us);
}

TIMEOUT_STATUS SDL_DRV_COMMON_IsTimeoutReached_us(void)
{
    TIMEOUT_STATUS isTimeout = TIMEOUT_NOT_OCCURRED;

    if (SDL_DRV_SYSTICK_IsTimeoutReached(&timeout) == true)
    {
        isTimeout = TIMEOUT_OCCURRED;
    }

    return isTimeout;
}

void SDL_DRV_COMMON_TimerDelay_us(uint32_t delay_us)
{
    SDL_DRV_SYSTICK_DelayUs(delay_us);
}

void SDL_DRV_COMMON_SetTimeout_us(uint32_t timeout_us)
{
    diagTimeoutUs = timeout_us;
}

uint32_t SDL_DRV_COMMON_GetTimeout_us(void)
{
    return diagTimeoutUs;
}

/* Function:
    void sSDL_DRV_COMMON_SFR_Write(uint32_t address, uint32_t value, uint8_t reg_size)

  Description:
    Write the given value in register based on size of register.

  Precondition:
    None

  Parameters:
    uint32_t address - Register address
    uint32_t value - Data to be written in register
    uint8_t reg_size Register size

  Returns:
    None

  Remarks:
    None

  Sample code:
    None
*/
static void sSDL_DRV_COMMON_SFR_Write(volatile uint32_t address, uint32_t value, uint8_t reg_size)
{
    if(reg_size == 1U)
    {
        *((volatile uint8_t *) (address)) = (uint8_t)value;
    }
    else if(reg_size == 2U)
    {
        *((volatile uint16_t *) (address)) = (uint16_t)value;
    }
    else if(reg_size == 4U)
    {
        *((volatile uint32_t *) (address)) = value;
    }
    else
    {
        /* Do Nothing */
    }
}

/* Function:
    uint32_t sSDL_DRV_COMMON_SFR_Read(uint32_t address, uint8_t reg_size)

  Description:
    Reads the data from register based on size of register.

  Precondition:
    None

  Parameters:
    uint32_t address - Register address
    uint8_t reg_size Register size

  Returns:
    uint32_t - Register value

  Remarks:
    None

  Sample code:
    None
*/
static uint32_t sSDL_DRV_COMMON_SFR_Read(uint32_t address, uint8_t reg_size)
{
    uint32_t value = 0U;

    if(reg_size == 1U)
    {
        value = *((volatile uint8_t *) (address));
    }
    else if(reg_size == 2U)
    {
        value = *((volatile uint16_t *) (address));
    }
    else if(reg_size == 4U)
    {
        value = *((volatile uint32_t *) (address));
    }
    else
    {
        /* Do Nothing */
    }

    return value;
}

/* Function:
    void SDL_DRV_COMMON_UpdateErrorStatus(uint32_t errStatus)

  Description:
    Updates the global error status for SDLnostic routine. SDLnostic routines returns failure because of many reasons.
    Stores the specific error id for specific failure.

  Precondition:
    None

  Parameters:
    uint32_t errStatus - Error Id

  Returns:
    None

  Remarks:
    None

  Sample code:
    SDL_COMMON_UpdateErrorStatus(ERROR_ID)
*/
void SDL_DRV_COMMON_UpdateErrorStatus(uint32_t errStatus)
{
    sdlErrorStatus = errStatus;
}

/* Function:
    SDL_STATUS SDL_DRV_COMMON_SFRReset(uint32_t periphBase, const SDL_SFR_RESET_INFO *sfrInfo, uint16_t numReg, uint32_t *failRegOffset)

  Description:
    This interface verifies that the Read only and Write/Read registers' reset value are same as given in data sheet.
    If all the given registers value are same then return PASSED.
    If any one of the register value are different then return FAILED and pass the offset of that register to the user.

  Precondition:
    None

  Parameters:
    uint32_t periphBase                 - Peripheral base address
    const SDL_SFR_RESET_INFO *sfrInfo  - Structure for register offset, register reset value and register size
    uint16_t numReg                     - Number of registers
    uint32_t *failRegOffset             - In case of FAILURE, Store failed register offset.

  Returns:
    SDL_STATUS - Status of SDLnostic

  Remarks:
    None

  Sample code:
    None
*/
SDL_DRV_STATUS SDL_DRV_COMMON_SFRReset(uint32_t periphBase, const SDL_SFR_RESET_INFO *sfrInfo, uint16_t numReg, uint32_t *failRegOffset)
{
    uint8_t i;
    SDL_DRV_STATUS retVal = SDL_DRV_STATUS_NOT_EXECUTED;
    uint32_t regData;
    uint32_t address;

    if (( NULL != sfrInfo ) && ( NULL != failRegOffset ) && ( numReg > 0U ))
    {
        for (i = 0U; i < numReg; i++)
        {
            /* Get the register address from peripheral base address and register offset */
            address = (periphBase + sfrInfo[i].regOffset);

            /* Read the SFR value */
            regData = sSDL_DRV_COMMON_SFR_Read(address,sfrInfo[i].regSize);

            /* Compare SFR value with default value */
            if (regData != sfrInfo[i].regDefaultValue)
            {
                retVal = SDL_DRV_STATUS_FAILED;

                /* Store the failed register offset */
                *failRegOffset = sfrInfo[i].regOffset;
                break;
            }
        }

        /* Verify reset value check done for all the registers */
        if  (i == numReg)
        {
            retVal = SDL_DRV_STATUS_PASSED;
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }

    return retVal;
}

/* Function:
    SDL_STATUS SDL_DRV_COMMON_SFRWriteRead(uint32_t periphBase, const SDL_SFR_RW_INFO *sfrInfo, uint16_t numReg, uint32_t *failRegOffset)

  Description:
    This interface verifies that the Write/Read registers can be written and the same value can be read back.
    Write and read happens based on register write read property.
    If all the given registers are able to write and read correctly then return PASSED.
    If any one of the register are failed to write or read then return FAILED and pass the offset of that register to the user.

  Precondition:
    None

  Parameters:
    uint32_t periphBase                 - Peripheral base address
    const SDL_SFR_RW_INFO *sfrInfo     - Structure for read and write register offset, register property, register mask and register size
    uint16_t numReg                     - Number of registers
    uint32_t *failRegOffset             - In case of FAILURE, Store failed register offset.

  Returns:
    SDL_STATUS - Status of SDLnostic

  Remarks:
    None

  Sample code:
    None
*/
SDL_DRV_STATUS SDL_DRV_COMMON_SFRWriteRead(uint32_t periphBase, const SDL_SFR_RW_INFO *sfrInfo, uint16_t numReg, uint32_t *failRegOffset)
{
    SDL_DRV_STATUS retVal = SDL_DRV_STATUS_NOT_EXECUTED;
    uint32_t regData;
    uint32_t i;
    uint32_t writeAddress;
    uint32_t readAddress;

    if (( NULL != sfrInfo ) && ( NULL != failRegOffset ) && ( numReg > 0U ))
    {
        for(i = 0U; i < numReg; i++)
        {
            /* Get the write register address from peripheral base address and register offset */
            writeAddress = (periphBase + sfrInfo[i].writeReg);

            /* Get the read register address from peripheral base address and register offset */
            readAddress = (periphBase + sfrInfo[i].readReg);

            /* Write '1' to each bit of the register and read '1' from each bit of the register */
            if(sfrInfo[i].wrProperty == SDL_WRITE_1_READ_1)
            {
                /* Write the mask to the register */
                sSDL_DRV_COMMON_SFR_Write(writeAddress,sfrInfo[i].mask,sfrInfo[i].regSize);

                /* Read the register value */
                regData = sSDL_DRV_COMMON_SFR_Read(readAddress,sfrInfo[i].regSize);

                /* Verify register value is same as mask */
                if(regData != sfrInfo[i].mask )
                {
                    *failRegOffset = sfrInfo[i].writeReg;
                    retVal = SDL_DRV_STATUS_FAILED;
                    break;
                }
            }
            /* Write '1' to each bit of the register and read '0' from each bit of the register */
            else if(sfrInfo[i].wrProperty == SDL_WRITE_1_READ_0)
            {
                /* Write the mask to the register */
                sSDL_DRV_COMMON_SFR_Write(writeAddress,sfrInfo[i].mask,sfrInfo[i].regSize);

                 /* Read the register value */
                regData = sSDL_DRV_COMMON_SFR_Read(readAddress,sfrInfo[i].regSize);

                /* Verify register value is 0 */
                if(regData != 0U )
                {
                    *failRegOffset = sfrInfo[i].writeReg;
                    retVal = SDL_DRV_STATUS_FAILED;
                    break;
                }
            }
            /* Write '1' to each bit of the register and read '1' from each bit of the register and then
               Write '0' to each bit of the register and read '0' from each bit of the register */
            else if(sfrInfo[i].wrProperty == SDL_WRITE_1_0_READ_1_0)
            {
                /* Write the mask to the register */
                sSDL_DRV_COMMON_SFR_Write(writeAddress,sfrInfo[i].mask,sfrInfo[i].regSize);

                /* Read the register value */
                regData = sSDL_DRV_COMMON_SFR_Read(readAddress,sfrInfo[i].regSize);

                /* Verify register value is same as mask */
                if(regData != sfrInfo[i].mask )
                {
                    *failRegOffset = sfrInfo[i].writeReg;
                    retVal = SDL_DRV_STATUS_FAILED;
                    break;
                }

                /* Write the 0 to the register */
                sSDL_DRV_COMMON_SFR_Write(writeAddress, 0U, sfrInfo[i].regSize);

                /* Read the register value */
                regData = sSDL_DRV_COMMON_SFR_Read(readAddress,sfrInfo[i].regSize);

                /* Verify register value is 0 */
                if(regData != 0U )
                {
                    *failRegOffset = sfrInfo[i].writeReg;
                    retVal = SDL_DRV_STATUS_FAILED;
                    break;
                }
            }
            else
            {
                retVal = SDL_DRV_STATUS_FAILED;
                SDL_DRV_COMMON_UpdateErrorStatus(SDL_COMMON_ERROR_INVALID_WR_PROPERTY);
                break;
            }
        }

        /* Verify write/read check done for all the registers */
        if  (i == numReg)
        {
            retVal = SDL_DRV_STATUS_PASSED;
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }

    return retVal;
}

/* Function:
    int32_t SDL_COMMON_memcmp(const void *data1, const void *data2, size_t size)

  Description:
    Compares the 2 data for given size. Return 0 if both are same else return -1

  Precondition:
    None

  Parameters:
    const void *data1   - Data 1
    const void *data2   - Data 2
    size_t size         - size of data

  Returns:
    int32_t - Compare status

  Remarks:
    None

  Sample code:
    None
*/
int32_t SDL_DRV_COMMON_memcmp(const void *data1, const void *data2, size_t size)
{
    const int8_t *char_ptr1 = (const int8_t *)data1;
    const int8_t *char_ptr2 = (const int8_t *)data2;
    int32_t compareStatus = -1;
    size_t byteCount = 0;

    if((char_ptr1 != NULL) && (char_ptr2 != NULL) && (size > 0U))
    {
        while(byteCount < size)
        {
            /* Compare byte by byte from both the data for given size */
            if(char_ptr1[byteCount] != char_ptr2[byteCount])
            {
                break;
            }
            byteCount++;
        }

        /* Verify check done for all bytes */
        if(byteCount == size)
        {
            compareStatus = 0;
        }
    }
    else
    {
        /* Do Nothing */
    }

    return compareStatus;
}

/* Function:
    void SDL_DRV_COMMON_memset(void *data, char ch, size_t size)

  Description:
    Sets the given character value in buffer for given size.

  Precondition:
    None

  Parameters:
    void *data      - Buffer
    char ch         - Value to be written in buffer
    size_t size     - size of buffer

  Returns:
    None

  Remarks:
    None

  Sample code:
    None
*/
void SDL_DRV_COMMON_memset(void *data, char ch, size_t size)
{
    int8_t *char_ptr = (int8_t *)data;
    size_t byteCount = 0;

    if((char_ptr != NULL) && (size > 0U))
    {
        while(byteCount < size)
        {
            char_ptr[byteCount] = ( int8_t)ch;
            byteCount++;
        }
    }
    else
    {
        /* Do Nothing */
    }
}
