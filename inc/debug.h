#ifndef DEBUG_H
#define DEBUG_H
#include <stdio.h>

#define _DBG_

#ifdef _DBG_
	#define DBG(fmt,arg...) do {printf("(Func=%s Line=%d)",__func__,__LINE__); printf(fmt,##arg);} while(0)
#endif

#define ret_val_if_fail(cond,val) do {if(!(cond)) {printf("(Func=%s Line=%d)",__func__,__LINE__);\
									printf("\""#cond"\" fail !\n"); return val;}} while(0)
#define goto_if_fail(cond,flag) do {if(!(cond)) {printf("(Func=%s Line=%d)",__func__,__LINE__);\
									printf("\""#cond"\" fail !\n"); goto flag;}} while(0)
#endif
