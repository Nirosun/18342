/** @file splat.c
 *
 * @brief Displays a spinning cursor.
 *
 * Links to libc.
 */

int main(int argc, char** argv)
{
	while(1)
	{
		write(STDOUT_FILENO, "\r|",20); 
	}
	return 0;
}
