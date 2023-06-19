#include <stdio.h>

//structure to represent the process
struct Process 
{
    int processID;       // Process ID
    int arrivalTime;     // Arrival time of the process
    int burstTime;       // Burst time of the process
};

// Creating a function to calculate waiting time & turnaround time for each process
void calculateTimes(struct Process processes[], int n, int waitingTime[], int turnaroundTime[]) 
{
    int i;
    // We know that the waiting time for the first process is 0
    waitingTime[0] = 0;

    // To calculate waiting time for each process
    for (i = 1; i < n; i++) 
    {
        // We know that the Waiting-time = Burst-time of previous process + Waiting-time of previous process
        waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;
    }

    // To calculate turnaround time for each process
    for (i = 0; i < n; i++) 
    {
        // As Turnaround time = Waiting time + Burst time
        turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
    }
}

// Creating a function to calculate average waiting time and average turnaround time
void calculateAverageTimes(struct Process processes[], int n) // Where n is the number of processes
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

    // Printing the results
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) 
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].arrivalTime,
               processes[i].burstTime, waitingTime[i], turnaroundTime[i]);
    }
    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);

        // Print the Gantt chart
    printf("\nGantt Chart:\n");
    for (i = 0; i < n; i++) {
        printf("******");
    }
    printf("\n|");

    for (i = 0; i < n; i++) {
        printf("  P%d  ", processes[i].processID);
        printf("|");
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("*******");
    }
    printf("\n");
}

int main() 
{
    int n, i;
    printf("Enter the number of processes: ");// taking in no. of processes
    scanf("%d", &n);

    // Create an array of processes
    struct Process processes[n];

    // Inputing the process details from the user step by step
    printf("Enter process details:\n");
    for (i = 0; i < n; i++) 
    {
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        //Inputing the arrival time 
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        //Inputing the burst time
        scanf("%d", &processes[i].burstTime);
        processes[i].processID = i + 1;//incrementing proccessID
    }

    // Calculating average waiting time and average turnaround time
    calculateAverageTimes(processes, n);
    printf("This code has been run and compiled by Shivam Dave 21BCB0107");
    return 0;
}