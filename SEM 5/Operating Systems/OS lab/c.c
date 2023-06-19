 //ROUND ROBIN JOB SCHEDULING METHOD 
#include <stdio.h>
int main()
{
   
    //Declaring the necessary variables and arrays
    int count, j, n, time, remain, flag = 0, time_quantum;
    int wait_time = 0, turnaround_time = 0, at[10], bt[10], rt[10];

    //Input the no. of processes from user
    printf("Enter Total Process:\t");
    scanf("%d", &n);
    //Initialize remain with n to track the remaining processes
    remain = n;
    /*Using a loop to read & store the arrival time and burst time for each process from the user. 
     Then initializing the remaining time for each process (rt) to be equal to the burst time.
    */
    for (count = 0; count < n; count++)
    {
        printf("Enter Arrival Time and Burst Time for Process Process Number %d: ", count + 1);
        scanf("%d", &at[count]);
        scanf("%d", &bt[count]);
        rt[count] = bt[count];
    }
    // Input the time quantum from user
    printf("Enter Time Quantum:\t");
    scanf("%d", &time_quantum);

    // Printing of Gantt chart
    printf("\nGantt Chart:\n");
    int time_slot = 1;
    //Enter a loop where the processes are executed until all processes are completed i.e. remain is 0
    for (time = 0, count = 0, remain = n; remain != 0;)
    {
    // Check if the remaining time of the current process is less than or equal to the time quantum and greater than 0.
    if (rt[count] <= time_quantum && rt[count] > 0)
    {
        printf("| P%d ", count + 1);
        time += rt[count];     // Increment the time by the remaining time of the current process
        rt[count] = 0;         // Set the remaining time of the current process to 0 as it is completed
        flag = 1;              // Set the flag to indicate that a process has completed
    }
    // Check if the remaining time of the current process is greater than 0
    else if (rt[count] > 0)
    {
        printf("| P%d ", count + 1);
        rt[count] -= time_quantum;   // Reduce the remaining time of the current process by the time quantum
        time += time_quantum;        // Increment the time by the time quantum
    }

    // Check if the remaining time of the current process is 0 and the flag is 1 (process completed)
    if (rt[count] == 0 && flag == 1)
    {
        remain--;          // Decrement the count of remaining processes
        printf("|");       // Print a vertical bar to indicate process completion
        flag = 0;          // Reset the flag
    }

    count++;               // Move to the next process
    if (count == n)
        count = 0;         // Wrap around to the first process if the last process is reached
    }
    printf("\n");

    //Printing the result
    printf("\nProcess\t|Turnaround Time|Waiting Time\n\n");
    for (count = 0; count < n; count++)
    {
        printf("P[%d]\t|\t%d\t|\t%d\n", count + 1, time - at[count], time - at[count] - bt[count]);
        wait_time += time - at[count] - bt[count];
        turnaround_time += time - at[count];
    }

    printf("\nAverage Waiting Time = %.2f\n", wait_time * 1.0 / n);
    printf("Average Turnaround Time = %.2f\n", turnaround_time * 1.0 / n);
    printf("This code has been written by Shivam Dave 21BCB0107");
    return 0;
}