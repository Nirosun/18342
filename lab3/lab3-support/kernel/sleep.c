/*
 * sleep.c: Sleep for a given time period.
 *
 * Author: Zhengyang Zuo <zzuo@andrew.cmu.edu>
           Yang Wu <yangwu@andrew.cmu.edu>
 * Date:   Fri, 7 Nov 2014 08:55 PM
 */

#include <exports.h>
#include "constant.h"
 
extern volatile unsigned int os_time;

void sleep(unsigned int time)
{

 	unsigned int finish_time = os_time + time / TIME_RESOLUTION;
 	while (os_time < finish_time);
 		// do nothing, wait
 	return;
} 

