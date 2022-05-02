/**
 * SSAS - Simple Smart Automotive Software
 * Copyright (C) 2021 Parai Wang <parai@foxmail.com>
 */
/* ================================ [ INCLUDES  ] ============================================== */
#include "Std_Timer.h"
#include "assert.h"
/* ================================ [ MACROS    ] ============================================== */
#define STD_TIMER_STARTED 1
#define STD_TIMER_SET_NO_OVERFLOW 2
#define STD_TIMER_SET_OVERFLOW 3

#define STD_TIMER_SET_MAX (STD_TIME_MAX / 2)
/* ================================ [ TYPES     ] ============================================== */
/* ================================ [ DECLARES  ] ============================================== */
/* ================================ [ DATAS     ] ============================================== */
/* ================================ [ LOCALS    ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */
void Std_TimerStart(Std_TimerType *timer) {
  timer->status = STD_TIMER_STARTED;
  timer->time = Std_GetTime();
}

void Std_TimerStop(Std_TimerType *timer) {
  timer->status = 0;
  timer->time = 0;
}

bool Std_IsTimerStarted(Std_TimerType *timer) {
  return (timer->status != 0);
}

std_time_t Std_GetTimerElapsedTime(Std_TimerType *timer) {
  std_time_t curTime;
  std_time_t elapsed = 0;

  if (timer->status) {
    curTime = Std_GetTime();
    if (curTime > timer->time) {
      elapsed = curTime - timer->time;
    } else {
      elapsed = (STD_TIME_MAX - curTime) + 1 + timer->time;
    }
  }

  return elapsed;
}

void Std_TimerSet(Std_TimerType *timer, std_time_t timeout) {
  std_time_t curTime = Std_GetTime();

  assert(timeout <= STD_TIMER_SET_MAX);

  if (timeout <= (STD_TIME_MAX - curTime)) {
    timer->time = curTime + timeout;
    timer->status = STD_TIMER_SET_NO_OVERFLOW;
  } else {
    timer->time = timeout - 1 - (STD_TIME_MAX - curTime);
    timer->status = STD_TIMER_SET_OVERFLOW;
  }
}

bool Std_IsTimerTimeout(Std_TimerType *timer) {
  bool r = false;
  std_time_t curTime = Std_GetTime();
  /* 0 -------- 1/4 -------- 1/2 -------- 3/4 -------- MAX */
  switch (timer->status) {
  case STD_TIMER_SET_NO_OVERFLOW:
    if (curTime >= timer->time) {
      r = true;
    } else if ((timer->time > STD_TIMER_SET_MAX) && (curTime < STD_TIMER_SET_MAX)) {
      r = true;
    }
    break;
  case STD_TIMER_SET_OVERFLOW:
    if ((curTime <= STD_TIMER_SET_MAX) && (curTime >= timer->time)) {
      r = true;
    } else if ((timer->time > (STD_TIME_MAX / 4)) && (curTime > STD_TIMER_SET_MAX) &&
               (curTime < ((STD_TIME_MAX / 4 * 3)))) {
      r = true;
    }
    break;
  }

  return r;
}
