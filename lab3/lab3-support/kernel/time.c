#include <types.h>

extern unsigned long os_time;

size_t time()
{
	return os_time*10;
}
