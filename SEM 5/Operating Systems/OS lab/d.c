//Priority Scheduling
#include <stdio.h>
// Creating a structure to represent a process
struct Process {
    int processID;       // Process ID
    int arrivalTime;     // Arrival time of the process
    int burstTime;       // Burst time of the process
    int priority;        // Priority of the process
};

// Creating a function to calculate average waiting time and average turnaround time
void calculateAverageTimes(struct Process processes[], int n) {
    int i, j, totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Calculating the waiting time and turnaround time for each process
    int waitingTime[n], turnaroundTime[n];
    waitingTime[0] = 0; // Waiting time for the first process is always 0

    for (i = 1; i < n; i++) 
    {
        waitingTime[i] = processes[i - 1].burstTime + waitingTime[i - 1];
        /*  
        Loop to calculates waiting time for each process starting from the second process (i = 1).
        It is calculated by adding the burst time of the previous process and the waiting time of 
        the previous process. And store the waiting time in its array
        */
    }
    for (i = 0; i < n; i++) 
    {
        /* 
        loop to calculates turnaround time for each process and updates the totalWaitingTime 
        and totalTurnaroundTime variables.It is calculated by adding the burst time and waiting 
        time of each process.
        */
        turnaroundTime[i] = processes[i].burstTime + waitingTime[i];
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    // Printing of the Gantt chart
    printf("\nGantt Chart:\n");
    printf(" ");
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < processes[i].burstTime; j++) 
        {
            printf("*");
        }
        printf(" ");
    }
    printf("\n|");
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < processes[i].burstTime - 1; j++) 
        {
            printf(" ");
        }
        printf("P%d", processes[i].processID);
        for (j = 0; j < processes[i].burstTime - 1; j++)
        {
            printf(" ");
        }
        printf("|");
    }
    printf("\n ");
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < processes[i].burstTime; j++) 
        {
            printf("*");
        }
        printf(" ");
    }
    printf("\n");
    printf("0");
    for (i = 0; i < n; i++) {
        for (j = 0; j < processes[i].burstTime; j++) {
            printf("  ");
        }
        printf("%d", turnaroundTime[i]);
    }
    printf("\n");


    // Printing the process details
    printf("\nProcess Details:\n");
    printf("Process\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) 
    {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].arrivalTime, processes[i].burstTime, processes[i].priority, waitingTime[i], turnaroundTime[i]);
    }
    // Calculate the average waiting time and average turnaround time by dividing it by n
    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}
int main() 
{
    int n, i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Create an array of processes
    struct Process processes[n];

    // Get the arrival time, burst time, and priority for each process from the user
    for (i = 0; i < n; i++) 
    {
        printf("Enter the arrival time for process P%d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter the burst time for process P%d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        printf("Enter the priority for process P%d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].processID = i + 1;
    }

    // Sort the processes based on priority in ascending order
    for (i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (processes[j].priority > processes[j + 1].priority) 
            {
                // Swap the processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate average waiting time and average turnaround time
    calculateAverageTimes(processes, n);
    printf("This code has been written by Shivam Dave 21BCB0107");
    return 0;
}