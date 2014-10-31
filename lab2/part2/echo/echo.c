/** @file echo.c
 *
 * @author  Harry Q Bovik (Change this!)
 * @date    The current date
 */
#include <stdlib.h>
#include <unistd.h>
#include <exports.h>

#define MAX_SIZE 100

int main(int argc, char *argv[]) {

	/* Put your code here */
	int ret_read, ret_write, ret_val = 0;
	char buf[MAX_SIZE];
	
	printf("argc: %d, argv[1]: %s, argv[2]: %s\n", argc, argv[1], argv[2]);
	
	ret_read = read(0, buf, 10);

	ret_write = write(1, buf, 10);

	if (ret_read < 0 || ret_write < 0)
	{
		ret_val = -1;
	}

	//printf("leave echo with ret_val=%d\n", ret_val);

	return ret_val;
}
