/** @file ub_test.c
 * 
 * @brief The UB Test for basic schedulability
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-20
 */

//#define DEBUG 0

#include <sched.h>
//#ifdef DEBUG
#include <exports.h>
///#endif

void sort(task_t* tasks, size_t num_tasks);

double U[62] = 
    {1.000000, 0.828427, 0.779763, 0.756828, 0.743492, 
     0.734772, 0.728627, 0.724062, 0.720538, 0.717735, 
     0.715452, 0.713557, 0.711959, 0.710593, 0.709412, 
     0.708381, 0.707472, 0.706666, 0.705946, 0.705298, 
     0.704713, 0.704182, 0.703698, 0.703254, 0.702846, 
     0.702469, 0.702121, 0.701798, 0.701497, 0.701217,
     0.700955, 0.700709, 0.700478, 0.700261, 0.700056, 
     0.699863, 0.699681, 0.699508, 0.699343, 0.699188, 
     0.699040, 0.698898, 0.698764, 0.698636, 0.698513, 
     0.698396, 0.698284, 0.698176, 0.698073, 0.697974, 
     0.697879, 0.697788, 0.697700, 0.697615, 0.697533, 
     0.697455, 0.697379, 0.697306, 0.697235, 0.697166,
     0.697100, 0.697036};


/**
 * @brief Perform UB Test and reorder the task list.
 *
 * The task list at the end of this method will be sorted in order is priority
 * -- from highest priority (lowest priority number) to lowest priority
 * (highest priority number).
 *
 * @param tasks  An array of task pointers containing the task set to schedule.
 * @param num_tasks  The number of tasks in the array.
 *
 * @return 0  The test failed.
 * @return 1  Test succeeded.  The tasks are now in order.
 */

void sort(task_t* tasks, size_t num_tasks)
{
    size_t i = 0;
    size_t j = 0;

    for (i = 0; i < num_tasks; i ++)
    {
        for (j = i + 1; j < num_tasks; j ++)
        {
            if (tasks[j].T < tasks[i].T)
            {
                task_t tmp = tasks[j];
                tasks[j] = tasks[i];
                tasks[i] = tmp;
            }
        }
    }
}

/*double ub_bound(size_t i)
{
	// no pow() from math.h... no choice but use this ugly alternative
	double cache[62] = 
	{1.000000, 0.828427, 0.779763, 0.756828, 0.743492, 
	 0.734772, 0.728627, 0.724062, 0.720538, 0.717735, 
	 0.715452, 0.713557, 0.711959, 0.710593, 0.709412, 
	 0.708381, 0.707472, 0.706666, 0.705946, 0.705298, 
	 0.704713, 0.704182, 0.703698, 0.703254, 0.702846, 
	 0.702469, 0.702121, 0.701798, 0.701497, 0.701217,
     0.700955, 0.700709, 0.700478, 0.700261, 0.700056, 
     0.699863, 0.699681, 0.699508, 0.699343, 0.699188, 
     0.699040, 0.698898, 0.698764, 0.698636, 0.698513, 
     0.698396, 0.698284, 0.698176, 0.698073, 0.697974, 
     0.697879, 0.697788, 0.697700, 0.697615, 0.697533, 
     0.697455, 0.697379, 0.697306, 0.697235, 0.697166,
     0.697100, 0.697036};	
     
	return cache[i-1];
}*/

/*int assign_schedule(task_t** tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
	//printf("begin assign_schedule...task num = %u\n", (unsigned)num_tasks);
	size_t i = 0;
	//printf("num_tasks = %u\n", (unsigned)i);
	
	double ub_test, max = ub_bound(num_tasks);
	printf("max = %d\n", (int)(max));

	unsigned long c, t;

	sort(*tasks, num_tasks);

	ub_test = 0;

    for(i = 0; i < num_tasks; i++)
    {
        c = (*tasks)[i].C;
        t = (*tasks)[i].T;

        if(ub_test + ( ((double)c/(double)t) > max) )
            return 0; // fail!
        else
        	ub_test += ((double)c/(double)t);
    }
    //printf("leaving ub test");
	return 1; // success	
}*/

int assign_schedule(task_t** tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
    size_t i;
    //size_t j;
    //task_t tmp;
    double ub_test = 0.0;

    sort(*tasks, num_tasks);

    // Use UB test to see if these tasks are schedulable.
    for(i = 0; i < num_tasks; i++)
    {
        if(ub_test + ((double)((*tasks)[i].C + (*tasks)[i].B) / (*tasks)[i].T) > U[i])
        {
            //printf("acc_start_time: %d, C: %lu, T, %lu\n", (int)(acc_start_time*100), (*tasks)[i].C, (*tasks)[i].T);
            //printf("left: %d\n", (int)(acc_start_time + ((double)((*tasks)[i].C / (*tasks)[i].T)));
            //printf("cache[%d]: %d\n", i, (int)(cache[i]*1000));
            return 0;
        }
        ub_test += ((double)(*tasks)[i].C / (*tasks)[i].T);
    }

    return 1;
}



