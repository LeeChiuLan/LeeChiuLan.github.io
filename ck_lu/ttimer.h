#ifndef __TTIMER_H__
#define __TTIMER_H__

#define MAX_TIMER_NUM 100

typedef void (* TTCallBackFunction)(int param1, int param2);

typedef struct WATCH_DOG_DATA
{
  int use;
  unsigned int time;
  int param1;
  int param2;
  TTCallBackFunction pCallBack;
}TTIMER;

void TTimerInit(void);
void TTimerExit(void);
int TTimerCreate(void);
void TTimerStart(int id, int msec, TTCallBackFunction callback, int param1, int param2);
void TTimerCancel(int id);
void TTimerDelete(int id);

#endif
