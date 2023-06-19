#include <stdio.h>
// SJF CPU algorithm
struct Process 
{
    int processID;       // Process ID
    int arrivalTime;     // Arrival time of the process
    int burstTime;       // Burst time of the process
};

// Creating a function to calculate waiting time & turnaround time for each process
void calculateTimes(struct Process processes[], int n, int waitingTime[], int turnaroundTime[]) 
// Here n is the total number of processes
{
    int i, j, minIndex, temp;//initializing

    // Sorting of the processes based on their burst time in ascending order using selection sort or any other sorting algo
    for (i = 0; i < n - 1; i++) 
    {
        minIndex = i;
        for (j = i + 1; j < n; j++) 
        {
            if (processes[j].burstTime < processes[minIndex].burstTime) 
            {
                minIndex = j;
            }
        }

        // Swapping of the processes
        temp = processes[minIndex].burstTime;
        processes[minIndex].burstTime = processes[i].burstTime;
        processes[i].burstTime = temp;

        temp = processes[minIndex].arrivalTime;
        processes[minIndex].arrivalTime = processes[i].arrivalTime;
        processes[i].arrivalTime = temp;

        temp = processes[minIndex].processID;
        processes[minIndex].processID = processes[i].processID;
        processes[i].processID = temp;
    }

    // We know that the waiting time for the first process is 0
    waitingTime[0] = 0;

    // To calculate waiting time for each process
    for (i = 1; i < n; i++) 
    {
        // We know that the Waiting-time = Burst-time of previous process + Waiting-time of previous process
        waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;
    }

    // To calculate turnaround time for each process
    for (i = 0; i < n; i++) {
        // As Turnaround time = Waiting time + Burst time
        turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
    }
}

// Creating a function to calculate average waiting time and average turnaround time
void calculateAverageTimes(struct Process processes[], int n) 
{
    //Initializing 
    int i, totalWaitingTime = 0, totalTurnaroundTime = 0;
    int waitingTime[n], turnaroundTime[n];

    // We have to now calculate waiting time and turnaround time for each process
    calculateTimes(processes, n, waitingTime, turnaroundTime);

     // To calculate total waiting time and total turnaround time
    for (i = 0; i < n; i++) 
    {
        totalWaitingTime += waitingTime[i];
        /* "+=" this means total waiting time = total waiting time + waiting time for the ith process*/
        totalTurnaroundTime += turnaroundTime[i];
    }

    // Now to calculate average waiting time and average turnaround time we divide by n(no. of processes)
    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    // Printing the results or the process details 
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) 
    {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].arrivalTime,
               processes[i].burstTime, waitingTime[i], turnaroundTime[i]);
    }
    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("\nAverage Turnaround Time: %.2f\n", avgTurnaroundTime);

    // Printing the Gantt chart
    printf("\nGantt Chart:\n");
    for (i = 0; i < n; i++) 
    {
        printf("*******");
    }
    printf("\n|");

    for (i = 0; i < n; i++) 
    {
        printf("  P%d  ", processes[i].processID);
        printf("|");
    }
    printf("\n");

    for (i = 0; i < n; i++)
    {
        printf("*******");
    }
    printf("\n");
}

int main() 
{
    //Initializing
    int n, i;

    printf("Enter the number of processes: ");// Inputing n
    scanf("%d", &n);

    // Create an array of processes
    struct Process processes[n];

    // Inputing the process details from the user step by step
    for (i = 0; i < n; i++) {
        printf("Process ID: ");
        scanf("%d", &processes[i].processID);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
    }

    // Calculating average waiting time and average turnaround time
    calculateAverageTimes(processes, n);
    printf("This code has been written by Shivam Dave 21BCB0107");
    return 0;
}