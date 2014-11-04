/*
 * sleep.c
 */
 #include <exports.h>
 
 void sleep(unsigned int time)
 {
 	unsigned int finish_time = os_time + (time*1000/10);
 	while (finish_time > os_time)
 	{
 		// do nothing, wait
 	}
 	return;
 } 