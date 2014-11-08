/*
 * @ file sleep.c
 *
 * @ if the sys. time has not come to desired value, just wait
 */
 #include <exports.h>
 
extern volatile unsigned int os_time;

 void sleep(unsigned int time)
 {
 	
 #ifdef debug	
 	printf("sleeping...\n");
 #endif

 	unsigned int finish_time = os_time + time;
 	while (os_time < finish_time);
 		// do nothing, wait
 	return;
} 

