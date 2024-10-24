#include <stdio.h>
#include <stdlib.h>

struct process{
    int pid;
    int bt;
    int at;
    int ct,wt,tat,start_time;
}ps[100];

int max(int a,int b)
{
    return a>b?a:b;
}

void bubbleSort(struct process arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j].at > arr[j+1].at) {
                struct process temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    printf("enter total number of processes:");
    scanf("%d",&n);
    float sum_tat=0,sum_wt=0;
    printf("Enter Process Arrival Time:");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&ps[i].at);
        ps[i].pid = i+1 ;
    }
    printf("Enter Process Burst Time:");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&ps[i].bt);
    }

    bubbleSort(ps, n);

    for(int i=0;i<n;i++)
    {
      ps[i].start_time = (i==0) ? ps[i].at : max(ps[i].at, ps[i-1].ct);  
      ps[i].ct =  ps[i].start_time + ps[i].bt;
      ps[i].tat = ps[i].ct-ps[i].at;       
      ps[i].wt = ps[i].tat-ps[i].bt;
      sum_tat += ps[i].tat;
      sum_wt += ps[i].wt;
    }

    printf("\n\nGantt Chart:\n");
    for(int i = 0; i < n; i++) {
        printf("| P%d ", ps[i].pid);
    }
    printf("\n");

    
    printf("\nAverage Turn Around time= %f ",sum_tat/n);
    printf("\nAverage Waiting Time= %f ",sum_wt/n);

    printf("\n");
    return 0;

}