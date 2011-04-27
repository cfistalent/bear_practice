#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *Function:	删除指定字符第一次出现之前字符串，返回余下字符串
 *In:		str		输入字符串
 *			c		用于匹配的字符
 *Out:		char*	余下字符串指针，若失败则返回NULL
 *Note:		-
 *LM:		2011-3-18
*/
char* strdel(char* str, char c)
{
	if(!(str != NULL))
	{
		printf("(Func=%s Line=%d)Input Error.\n",__func__,__LINE__);
		return NULL;
	}
	int cnt;
	char* ptr;

	cnt = 0;
	ptr = NULL;

	while((str[cnt] != '\0') && (str[cnt] != c))
	{
		cnt++;
	}

	if((str[cnt] == '\0') || (str[cnt+1] == '\0'))
	{
		ptr = NULL;
	}
	else
	{
		ptr = str + cnt + 1;
	}

	return ptr;	
}
