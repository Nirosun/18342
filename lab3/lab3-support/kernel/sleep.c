/*
 * sleep.c
 */
 #include <exports.h>
 
extern unsigned int os_time;

 void sleep(unsigned int time)
 {
 	printf("sleeping...\n");
 	unsigned int finish_time = os_time + (time*1000/10);
 	while (finish_time > os_time)
 	{
 		//printf("time = %d\n", os_time);
 		// do nothing, wait
 	}
 	return;
} 

