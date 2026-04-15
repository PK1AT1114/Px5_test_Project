/*============================================================================*/
/* Copyright (C) PX5 - all rights reserved.                                    */
/*============================================================================*/

/*============================================================================*/
/*                              INCLUDE FILES                                  */
/*============================================================================*/
#include "pthread.h"
#include "sched.h"
#include <stdlib.h>                 /* Defines EXIT_FAILURE */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "definitions.h"            /* SYS function prototypes */
#include "configuration.h"

#include "pwm_driver/pwm_driver.h"
#include "spi_driver/spi_async_driver.h"
#include "can_driver/can_driver.h"

#include "click/Click.h"
#include "Cluster_Cfg.h"

#if AMBIENT
#include "click/Ambient/Ambient.h"
#endif

#if WEATHER
#include "click/Weather/WeatherClick.h"
#endif

#if PROXIMITY3
#include "click/Proximity3/Proximity3.h"
#endif

#if PROXIMITY_AMBIENT
#include "click/Proximity3/Proximity3.h"
#endif

#if SERVO
#include "click/Servo/RcServo.h"
#endif


/*============================================================================*/
/*                                  MACROS                                    */
/*============================================================================*/
#define MAX_NUMBER                     1000

#ifndef MEMORY_WORDS
#define MEMORY_WORDS                  4000
#endif

#define T1S_PLCA_ENABLE               (true)
#define T1S_PLCA_NODE_COUNT           (8U)
#define T1S_PLCA_BURST_COUNT          (0U)
#define T1S_PLCA_BURST_TIMER          (0x80U)

#define MAC_PROMISCUOUS_MODE          (false)
#define MAC_TX_CUT_THROUGH            (false)
#define MAC_RX_CUT_THROUGH            (false)

#define PRINT_RATE_TIMEOUT            (1000U)
#define PRINT(...)                    printf(__VA_ARGS__)

#define SW1_Get()                     ((PORT_REGS->GROUP[1].PORT_IN >> 11U) & 0x01U)
#define SW0_Get()                     ((PORT_REGS->GROUP[1].PORT_IN >> 7U) & 0x01U)

#define SWITCH_STATE_PRESSED          0U
#define SWITCH_STATE_RELEASED         1U
#define SWITCH_SW0_MASK               (0xAAAAU)
#define SWITCH_SW1_MASK               (0x5555U)

#define SERVO_MIN_ANGLE               (0U)
#define SERVO_MAX_ANGLE               (180U)

#define DELAY_LED                     (20U)

#ifdef DEBUG
#define ASSERT(x)                     __conditional_software_breakpoint(x)
#else
#define ASSERT(x)
#endif

#define ESC_RESETCOLOR                "\033[0m"
#define ESC_GREEN                     "\033[0;32m"
#define ESC_RED                       "\033[0;31m"
#define ESC_YELLOW                    "\033[1;33m"
#define ESC_BLUE                      "\033[0;36m"

/*============================================================================*/
/*                           RATE LIMITED PRINT MACRO                         */
/*============================================================================*/
#define PrintRateLimited(idx, timeout, name, value)                          \
do {                                                                         \
    static uint32_t cnt_ = 0;                                                \
    static uint32_t t0_;                                                     \
    uint32_t now = systick.tickCounter;                                      \
                                                                             \
    if (cnt_ > 0 && (uint32_t)(now - t0_) < (uint32_t)(timeout))             \
    {                                                                        \
        ++cnt_;                                                              \
    }                                                                        \
    else                                                                     \
    {                                                                        \
        t0_ = now;                                                           \
                                                                             \
        if (cnt_ <= 1)                                                       \
        {                                                                    \
            PRINT("%08lu: %s: 0x%08lX\r\n", t0_, (name),                     \
                  ((uint32_t)value));                                        \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            PRINT("%08lu: %s: 0x%08lX [skipped %lu]\r\n", t0_,               \
                  (name), ((uint32_t)value), cnt_ - 1);                      \
        }                                                                    \
        cnt_ = 1;                                                            \
    }                                                                        \
} while (0)


/*============================================================================*/
/*                      GLOBAL VARIABLES & THREAD HANDLES                      */
/*============================================================================*/
pthread_t Led_toggle_thread;
pthread_t Diagnostic_Test_thread;
pthread_t service_task_thread;
pthread_t Communication_task_thread;

/* Synchronization */
pthread_mutex_t evenOddLock;
pthread_cond_t  cond;

/* Shared variable */
int current_number = 0;

/* RTOS memory */
u_long memory_area[MEMORY_WORDS];


/*============================================================================*/
/*                          FEATURE-SPECIFIC VARIABLES                         */
/*============================================================================*/
#if AMBIENT
uint16_t Ambiant_data;
#endif

#if PROXIMITY3
uint16_t vcnl4200Proximity_data;
#endif

#if PROXIMITY_AMBIENT
uint16_t vcnl4200Ambiant_data;
#endif

#if SERVO
uint8_t servoBuffer[3] = {0, 0, 0};
#endif

#if LED_PWM
uint16_t ledBrightnessCtrl = 0x00;
#endif

#if (SERVO || SWITCH)
uint16_t switchInfo = 0x0;
#endif

#if (AMBIENT || SWITCH || PROXIMITY3 || PROXIMITY_AMBIENT)
static uint8_t Can0MessageRAM[CAN0_MESSAGE_RAM_CONFIG_SIZE]__attribute__((aligned(32)));
#endif


/*============================================================================*/
/*                         FUNCTION PROTOTYPES                                 */
/*============================================================================*/
void platform_setup(void);

#if AMBIENT
extern void UdpHandler_Wake_Ambient(void);
#endif

#if PROXIMITY3
extern void UdpHandler_Wake_Proximity(void);
#endif

#if PROXIMITY_AMBIENT
extern void UdpHandler_Wake_Proximity(void);
#endif

#if WEATHER
extern void UdpHandler_Wake_CLIMATE(void);
#endif

#if SERVO
extern void UdpHandler_Set_Servo(uint8_t *buffer, uint16_t len);
#endif


/*============================================================================*/
/*                         UTILITY FUNCTIONS                                   */
/*============================================================================*/
uint32_t sys_now(void)
{
    return systick.tickCounter;
}


/*============================================================================*/
/*                         CAN CALLBACK HANDLERS                               */
/*============================================================================*/
static void OnCanMessageReceived(const APP_CAN_MSG *msg,
                                 APP_CAN_RX_SOURCE source)
{
    const char *sourceStr[] = {"FIFO0", "FIFO1", "Buffer"};

    printf(" RX [%s] ID:0x%X Len:%d Data:",
           sourceStr[source],
           (unsigned int)msg->id,
           msg->length);

    for (uint8_t i = 0; i < msg->length; i++)
    {
        printf(" %02X", msg->data[i]);
    }

    printf("\r\n");
}

static void OnCanTransmitComplete(bool success)
{
    printf(" TX %s\r\n", success ? "Success" : "Failed");
}

static void SendSensorPacket(uint8_t *sensorData, uint8_t dataLen, uint16_t sensorID)
{
    APP_CAN_MSG msg =
    {
        .id     = sensorID,
        .length = dataLen,
        .type   = APP_CAN_MSG_STANDARD_FD
    };

    for (uint8_t i = 0;
         i < dataLen && i < APP_CAN_MAX_DATA_LENGTH;
         i++)
    {
        msg.data[i] = sensorData[i];
    }

    APP_CAN_Transmit(&msg);
}


/*============================================================================*/
/*                         INITIALIZATION                                      */
/*============================================================================*/
void APP_Initialize(void)
{
    SpiDrvAsync_Init();
    PwmDrv_Init();

#if PROXIMITY3
    vcnl4200_proximityinit();
#endif
    

#if PROXIMITY_AMBIENT
    vcnl4200_ambientinit();
#endif

#if WEATHER
    weather_init();
#endif

#if SERVO
    servo_init();
#endif

#if LED_PWM
    PORT_REGS->GROUP[0].PORT_PINCFG[20] = 0x1;
    PORT_REGS->GROUP[0].PORT_PMUX[10] =
    (PORT_REGS->GROUP[0].PORT_PMUX[10] & 0xF0) | 5U;
#endif

#if SWITCH
    PORT_REGS->GROUP[1].PORT_DIR &= ~(1U << 11U);
    PORT_REGS->GROUP[1].PORT_DIR &= ~(1U << 7U);
#endif
    APP_CAN_Initialize(Can0MessageRAM);
    APP_CAN_RegisterRxCallback(OnCanMessageReceived);
    APP_CAN_RegisterTxCallback(OnCanTransmitComplete);
}


/*============================================================================*/
/*                         HARDWARE CONFIG                                     */
/*============================================================================*/
static void set_pin_mux(uint8_t port_id,
                        uint8_t pin_id,
                        uint8_t function)
{
    PORT_REGS->GROUP[port_id].PORT_PINCFG[pin_id] = 0x1;

    if (pin_id % 2 == 1)
    {
        PORT_REGS->GROUP[port_id].PORT_PMUX[pin_id / 2] =
            (PORT_REGS->GROUP[port_id].PORT_PMUX[pin_id / 2] & 0x0F) |
            (function << 4);
    }
    else
    {
        PORT_REGS->GROUP[port_id].PORT_PMUX[pin_id / 2] =
            (PORT_REGS->GROUP[port_id].PORT_PMUX[pin_id / 2] & 0xF0) |
            function;
    }
}


/*============================================================================*/
/*                         THREAD FUNCTIONS                                   */
/*============================================================================*/
void *Led_toggle(void *arguments)
{
    PORT_REGS->GROUP[0].PORT_DIR |= (1U << 18U);

    while (1)
    {
        PORT_REGS->GROUP[0].PORT_OUTTGL |= (1U << 18U);
        px5_pthread_tick_sleep(500);
    }

    return NULL;
}

void *Diagnostic_Test(void *arguments)
{
    while (1)
    {
        /* Reserved */
    }
}


/*============================================================================*/
/*                         SERVICE TASK                                        */
/*============================================================================*/
void *service_task(void *arguments)
{

#if SERVO
    bool angleStatus = true;
#endif

    while (1)
    {
        /* Sensor Services */
#if AMBIENT
        UdpHandler_Wake_Ambient();
        ambient_service();
#endif

#if PROXIMITY3
        UdpHandler_Wake_Proximity();
        vcnl4200_proximity_service();
#endif

#if PROXIMITY_AMBIENT
        UdpHandler_Wake_Proximity();
        vcnl4200_ambient_service();
#endif

#if WEATHER
        UdpHandler_Wake_CLIMATE();
        weather_service();
#endif

        /* LED PWM */
#if LED_PWM
        
        PwmDrv_SetLevel(0, ledBrightnessCtrl);
        
#endif

        /* SERVO */
#if SERVO
        if ((angleStatus == true) && (switchInfo == SWITCH_SW0_MASK))
        {
            UdpHandler_Set_Servo(servoBuffer, 3U);

            if (servoBuffer[1] > SERVO_MIN_ANGLE)
            {
                servoBuffer[1]--;
            }

            if (servoBuffer[1] == SERVO_MIN_ANGLE)
            {
                angleStatus = false;
            }
        }
        else if (switchInfo == SWITCH_SW1_MASK)
        {
            UdpHandler_Set_Servo(servoBuffer, 3U);

            if (servoBuffer[1] < SERVO_MAX_ANGLE)
            {
                servoBuffer[1]++;
            }

            angleStatus = true;
        }

        servo_service();
#endif

        /* Shared Data Update */
        pthread_mutex_lock(&evenOddLock);

#if AMBIENT
        Ambiant_data = ambient_UpdateLightIntensity();
#endif

#if PROXIMITY3
        vcnl4200Proximity_data = vcnl4200_UpdateProximityValue();
#endif

#if PROXIMITY_AMBIENT
        vcnl4200Ambiant_data = vcnl4200_UpdateambientValue();
#endif

#if SWITCH
        switchInfo = 0U;

        if (SW0_Get() == SWITCH_STATE_PRESSED)
        {
            switchInfo |= SWITCH_SW0_MASK;
        }

        if (SW1_Get() == SWITCH_STATE_PRESSED)
        {
            switchInfo |= SWITCH_SW1_MASK;
        }
#endif

        pthread_mutex_unlock(&evenOddLock);

        /* Sleep */
#if (SERVO || SWITCH)
        px5_pthread_tick_sleep(20);
#elif LED_PWM
        px5_pthread_tick_sleep(DELAY_LED);
#else
        px5_pthread_tick_sleep(100);
#endif
    }

    return NULL;
}


/*============================================================================*/
/*                         COMMUNICATION TASK                                  */
/*============================================================================*/
void *Communication_task(void *arguments)
{
    while (1)
    {
        pthread_mutex_lock(&evenOddLock);

#if AMBIENT
        printf("\033[1m\033[33mAmbient Value: %d\r\n", Ambiant_data);
#endif

#if PROXIMITY3
        printf("\033[1m\033[33mvcnl4200Proximity Value: %d\r\n",
               vcnl4200Proximity_data);
#endif

#if PROXIMITY_AMBIENT
        printf("\033[1m\033[33mvcnl4200Ambiant Value: %d\r\n",
               vcnl4200Ambiant_data);
#endif

#if SWITCH
        printf("\033[1m\033[33mSwitch State: %d\r\n", switchInfo);
        SendSensorPacket((uint8_t *)&switchInfo, sizeof(switchInfo), 0x0100);
#endif

        pthread_mutex_unlock(&evenOddLock);

        px5_pthread_tick_sleep(100);
    }

    return NULL;
}


/*============================================================================*/
/*                         MAIN FUNCTION                                       */
/*============================================================================*/
int main(void)
{
    platform_setup();
    APP_Initialize();

    set_pin_mux(2, 9, 5);

    pthread_mutexattr_t mutexAttr;

    pthread_mutexattr_init(&mutexAttr);
    pthread_mutexattr_setprotocol(&mutexAttr, PTHREAD_PRIO_INHERIT);

    TCC1_PWMStart();

    px5_pthread_start(0xBD93A508, memory_area, sizeof(memory_area));

    pthread_mutex_init(&evenOddLock, &mutexAttr);
    pthread_mutexattr_destroy(&mutexAttr);
    pthread_cond_init(&cond, NULL);

    /* Create threads */
    pthread_create(&Led_toggle_thread, NULL, Led_toggle, NULL);
    pthread_create(&service_task_thread, NULL, service_task, NULL);
    pthread_create(&Communication_task_thread, NULL,
                   Communication_task, NULL);

    pthread_join(service_task_thread, NULL);
    pthread_join(Communication_task_thread, NULL);

    return 0;
}