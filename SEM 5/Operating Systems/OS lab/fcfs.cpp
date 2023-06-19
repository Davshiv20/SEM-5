#include<bits/stdc++.h>
using namespace std;

void CalculateWaitingTime(int process[], int burst[], int n)
{
    int wait[n];
    wait[0]=0;
    //print waiting time for process 1
    cout<<"Process ID"<<" "<<"Arrival Time"<<" "<<"Burst Time"<<"Waiting time"<<"Turnaround Time";
    cout<<"1"<<" "<<process[0]<<" "<<burst[0]<<" "<<wait[0]<<""
}




int main()
{
    int n;
    cout<<"Enter number of processes:";
    cin>>n;
    int process[n];
    cout<<"Enter arrival time:";
    for(int i=0;i<n;i++)
    {
        cin>>process[i];
    }
    int burst[n];
    cout<<"Enter burst time for each process:";
    for(int i=0;i<n;i++)
    {
        cin>>burst[i];
    }
}