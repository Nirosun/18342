#include <types.h>
#include <exports.h>

extern volatile unsigned long os_time;

size_t time()
{
	/*
	 * return the volatile system time. unit:second
	 */
	return os_time * ((unsigned long)10);
}
