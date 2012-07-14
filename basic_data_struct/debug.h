#ifndef DEBUG_H
#define DEBUG_H

#define _DEBUG_

#if defined(_DEBUG_)
	#define dbg(fmt, arg...) do {printf("(Func=%s Line=%d)",__func__,__LINE__); printf(fmt,##arg);} while(0)
#else
	#define dbg(fmt, arg...)
#endif

#define ret_val_if_fail(cond,val) do {if(!(cond)) {printf("(func=%s line=%d)",__func__,__LINE__);\
									printf("\""#cond"\" fail !\n"); return val;}} while(0)
#define goto_if_fail(cond,flag) do {if(!(cond)) {printf("(func=%s line=%d)",__func__,__LINE__);\
									printf("\""#cond"\" fail !\n"); goto flag;}} while(0)
#endif
