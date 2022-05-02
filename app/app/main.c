/**
 * SSAS - Simple Smart Automotive Software
 * Copyright (C) 2021 Parai Wang <parai@foxmail.com>
 */
/* ================================ [ INCLUDES  ] ============================================== */
#include "Std_Debug.h"
#include "Std_Timer.h"
#include <string.h>
#include <assert.h>
#if defined(_WIN32)
#include <unistd.h>
#endif


#include "TcpIp.h"
#include "SoAd.h"
#include "Sd.h"
#include "SomeIp.h"

#ifdef USE_FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#endif
/* ================================ [ MACROS    ] ============================================== */
/* ================================ [ TYPES     ] ============================================== */
/* ================================ [ DECLARES  ] ============================================== */
/* ================================ [ DATAS     ] ============================================== */
static Std_TimerType timer10ms;
/* ================================ [ LOCALS    ] ============================================== */
static void MainTask_10ms(void) {
  Sd_MainFunction();
  SomeIp_MainFunction();
}

static void Net_Init(void) {
  TcpIp_Init(NULL);
  SoAd_Init(NULL);
  Sd_Init(NULL);
  SomeIp_Init(NULL);
}

void Task_MainLoop(void) {
  Net_Init();
  Std_TimerStart(&timer10ms);
  for (;;) {
    if (Std_GetTimerElapsedTime(&timer10ms) >= 10000) {
      Std_TimerStart(&timer10ms);
      MainTask_10ms();
    }

    TcpIp_MainFunction();
    SoAd_MainFunction();
#ifdef USE_FREERTOS
    vTaskDelay(1);
#endif
  }
}
/* ================================ [ FUNCTIONS ] ============================================== */
int main(int argc, char *argv[]) {
  ASLOG(INFO, ("application build @ %s %s\n", __DATE__, __TIME__));

#ifdef USE_FREERTOS
  xTaskCreate((TaskFunction_t)Task_MainLoop, "MainLoop", configMINIMAL_STACK_SIZE, NULL,
              tskIDLE_PRIORITY + 1, NULL);
  vTaskStartScheduler();
#else
  Task_MainLoop();
#endif

  return 0;
}
