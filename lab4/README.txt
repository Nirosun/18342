Note:

1.
In the mutex_lock() function, we checked whether there is a deadlock. If there is, the function returns an EDEADLOCK error. 

Because the simple_mutex program includes a deadlock itself, and doesn't check the return value of mutex_lock(), we cannot run this particular test correctly. 


2.
Because we used replace_c.pl and replace_h.pl, the device frequencies are different with the original frequencies. Thus the result of running some of the tests may not be correct.


