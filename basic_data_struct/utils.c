#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

static long	start_sec;
static long start_usec;
static long end_sec;
static long end_usec;

int start_time_record(void)
{
	struct timeval	tv;
	int				ret;

	ret = 0;
	ret = gettimeofday(&tv, NULL);
	if (ret == 0)
	{
		start_sec	= tv.tv_sec;
		start_usec	= tv.tv_usec;
	}

	return ret;
}

int end_time_record(void)
{
	struct timeval	tv;
	int				ret;

	ret = 0;
	ret = gettimeofday(&tv, NULL);
	if (ret == 0)
	{
		end_sec		= tv.tv_sec;
		end_usec	= tv.tv_usec;
	}

	return ret;
}

void show_time(int format)
{
	long	time_spend;

	switch(format){
	case 0:
		time_spend = (end_sec - start_sec) * 1000000 + (end_usec - start_usec);
		printf("%ld usecond elapsed.\n",time_spend);
		break;
	case 1:
		time_spend = (end_sec - start_sec) * 1000 + (end_usec - start_usec) / 1000;
		printf("%ld msecond elapsed.\n",time_spend);
		break;
	case 2:
		time_spend = (end_sec - start_sec) + (end_usec - start_usec) / 1000000;
		printf("%ld second elapsed.\n",time_spend);
		break;
	default:
		time_spend = (end_sec - start_sec) * 1000000 + (end_usec - start_usec);
		printf("%ld usecond elapsed.\n",time_spend);
		break;
	}
}

