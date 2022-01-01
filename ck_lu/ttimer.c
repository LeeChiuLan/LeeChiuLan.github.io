#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>



#include "ttimer.h"



void ttimermain(void);


static TTIMER TTimer[MAX_TIMER_NUM];
static pthread_t wdID;
static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
static int wdRun;

void TTimerInit(void)
{
  int i;
  
  for(i=0;i<MAX_TIMER_NUM;i++)
  {
    TTimer[i].use = -1;
    TTimer[i].time = 0;
    TTimer[i].param1 = 0;
    TTimer[i].param2 = 0;
    TTimer[i].pCallBack = NULL;
  }
  wdRun = 1;
  if(pthread_create(&wdID, NULL, (void *)ttimermain, NULL) != 0)
  {
    printf("Watch dog thread create failed\n");
  }
}
  
void TTimerExit(void)
{
  wdRun = 0;
  pthread_join(wdID, NULL);
}


void ttimermain(void)
{
  fd_set rfds;
  struct timeval tv;
  int i;

  while(wdRun)
  {
    FD_ZERO(&rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 10000;
    select (FD_SETSIZE, &rfds, NULL, NULL, &tv);
    for(i=0;i<MAX_TIMER_NUM;i++)
    {
      if(TTimer[i].use == 1)
      {
        TTimer[i].time--;
        if(TTimer[i].time == 0)
        {
          TTimer[i].use = 0;
          if(TTimer[i].pCallBack)
          {
            TTimer[i].pCallBack(TTimer[i].param1, TTimer[i].param2);
          }
        }
      }
    }
  }
}

int TTimerCreate(void)
{
  int i;
  int ret = -1;

  pthread_mutex_lock(&g_mutex);
  for(i=0;i<MAX_TIMER_NUM;i++)
  {
    if(TTimer[i].use == -1)
    {
      TTimer[i].use = 0;
      TTimer[i].time = 0;
      TTimer[i].param1 = 0;
      TTimer[i].param2 = 0;
      TTimer[i].pCallBack = NULL;
      ret = i;
      break;
    }
  }
  pthread_mutex_unlock(&g_mutex);
  return ret;
}

void TTimerDelete(int id)
{
  pthread_mutex_lock(&g_mutex);
  if((id >=0) && (id < MAX_TIMER_NUM))
  {
    TTimer[id].use = -1;
    TTimer[id].time = 0;
    TTimer[id].param1 = 0;
    TTimer[id].param2 = 0;
    TTimer[id].pCallBack = NULL;
  }
  pthread_mutex_unlock(&g_mutex);
}

void TTimerCancel(int id)
{
  pthread_mutex_lock(&g_mutex);
  if((id >=0) && (id < MAX_TIMER_NUM))
  {
    TTimer[id].use = 0;
    TTimer[id].time = 0;
    TTimer[id].param1 = 0;
    TTimer[id].param2 = 0;
    TTimer[id].pCallBack = NULL;
  }
  pthread_mutex_unlock(&g_mutex);
}

void TTimerStart(int id, int msec, TTCallBackFunction callback, int param1, int param2)
{
  pthread_mutex_lock(&g_mutex);
  if((id >=0) && (id < MAX_TIMER_NUM))
  {
    TTimer[id].use = 1;
    TTimer[id].time = msec;
    TTimer[id].param1 = param1;
    TTimer[id].param2 = param2;
    TTimer[id].pCallBack = callback;
  }
  pthread_mutex_unlock(&g_mutex);
}
