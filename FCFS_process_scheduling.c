#include<stdio.h> 

void findWaitingTime(int processes[], int n,  
                          int bt[], int wt[]) 
{ 
    // waiting time for first process is 0 
    wt[0] = 0; 
  
    // calculating waiting time 
    for (int  i = 1; i < n ; i++ ) 
        wt[i] =  bt[i-1] + wt[i-1] ; 
} 
  
void findTurnAroundTime( int processes[], int n,  
                  int bt[], int wt[], int tat[]) 
{ 
    // calculating turnaround time by adding 
    // bt[i] + wt[i] 
    for (int  i = 0; i < n ; i++) 
        tat[i] = bt[i] + wt[i]; 
} 
  
void findavgTime( int processes[], int n, int bt[]) 
{ 
    int wt[n], tat[n], total_wt = 0, total_tat = 0; 
  
    findWaitingTime(processes, n, bt, wt); 
  
    findTurnAroundTime(processes, n, bt, wt, tat); 
  
    printf("Processes   Burst time   Waiting time   Turn around time\n"); 
  
    for (int  i=0; i<n; i++) 
    { 
        total_wt = total_wt + wt[i]; 
        total_tat = total_tat + tat[i]; 
        printf("   %d ",(i+1));
        printf("       %d ", bt[i] );
        printf("       %d",wt[i] );
        printf("       %d\n",tat[i] ); 
    } 
    float s=(float)total_wt / (float)n;
    float t=(float)total_tat / (float)n;
    printf("Average waiting time = %f",s);
    printf("\n");
    printf("Average turn around time = %f ",t); 
}   
int main() 
{   
int n;
    printf("\n enter count of processes : ");
    scanf("%d",&n);   
    //process id's 
    int processes[n];    
    //Burst time of all processes 
    int  burst_time[n]; 
    printf("\n enter process id's ");
    for(int i=0;i<n;i++)
    {
    	scanf("%d",&processes[i]);
    }	
    printf("\n enter process's burst time");
    for(int i=0;i<n;i++)
    {
    	scanf("%d",&burst_time[i]);
    }   
    findavgTime(processes, n,  burst_time); 
    return 0; 
}
