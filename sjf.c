#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

struct process {
  int pid;
  int at;
  int bt;
  int ct, wt, tat, rt, start_time;
};

int findmax(int a, int b) {
    return a > b ? a : b;
}

int findmin(int a, int b) {
    return a < b ? a : b;
}
  
void SJF(struct process ps[],int n)
{
    bool is_completed[100] = {false}, is_first_process = true;
    int current_time = 0;
    int completed = 0;
    int sum_tat = 0, sum_wt = 0, prev = 0;
    int gantt_chart[100], gc_index = 0;
    
    while(completed != n) {
        // Find process with min. burst time in ready queue at current time
        int min_index = -1;
        int minimum = INT_MAX;
        for(int i = 0; i < n; i++) {
            if(ps[i].at <= current_time && is_completed[i] == false) {
                if(ps[i].bt < minimum) {
                    minimum = ps[i].bt;
                    min_index = i;
                }
                if(ps[i].bt == minimum) {
                    if(ps[i].at < ps[min_index].at) {
                        minimum = ps[i].bt;
                        min_index = i;
                    }
                }
            }
        }

        if(min_index == -1) {
            current_time++;
        } else {
            ps[min_index].start_time = current_time;
            ps[min_index].ct = ps[min_index].start_time + ps[min_index].bt;
            ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
            ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;
                    
            sum_tat += ps[min_index].tat;
            sum_wt += ps[min_index].wt;
        
            completed++;
            is_completed[min_index] = true;
            current_time = ps[min_index].ct;
            prev = current_time;
            is_first_process = false;

            gantt_chart[gc_index++] = ps[min_index].pid;
        }
    }

    printf("\n\nGantt Chart:\n");
    for(int i = 0; i < gc_index; i++) {
        printf("| P%d ", gantt_chart[i]);
    }
    printf("|\n");

    printf("\nAverage Turn Around time= %f ", (float)sum_tat / n);
    printf("\nAverage Waiting Time= %f ", (float)sum_wt / n);
}

int main() {
    int n;
    printf("Enter total number of processes: ");
    scanf("%d", &n);    
    struct process ps[n];

    printf("Enter Process Arrival Time:");
    for(int i = 0; i < n; i++) {
        scanf("%d", &ps[i].at);
        ps[i].pid = i+1;
    }
    printf("Enter Process Burst Time:");
    for(int i = 0; i < n; i++) {
        scanf("%d", &ps[i].bt);
    }
    SJF(ps,n);
    return 0;
}
