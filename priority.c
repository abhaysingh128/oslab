#include<stdio.h>
#include<stdbool.h>

struct process {
    int pid;
    int bt;
    int at;
    int priority;
    int ct, tat, wt;
};

void priority_scheduling(int n, struct process ps[]) {
    bool completed[100] = {false};
    int current_time = 0, completed_processes = 0;
    float total_wt = 0, total_tat = 0;
    
    printf("Gantt Chart: ");
    
    while (completed_processes != n) {
        int idx = -1;
        int highest_priority = 1000000; // High number to indicate lowest priority initially
        
        for (int i = 0; i < n; i++) {
            if (ps[i].at <= current_time && !completed[i] && ps[i].priority < highest_priority) {
                highest_priority = ps[i].priority;
                idx = i;
            }
        }
        
        if (idx != -1) {
            // Process idx is selected
            printf("P%d ", ps[idx].pid);
            current_time += ps[idx].bt;
            ps[idx].ct = current_time;
            ps[idx].tat = ps[idx].ct - ps[idx].at;
            ps[idx].wt = ps[idx].tat - ps[idx].bt;
            
            total_wt += ps[idx].wt;
            total_tat += ps[idx].tat;
            completed[idx] = true;
            completed_processes++;
        } else {
            current_time++;
        }
    }
    
    printf("\nAverage waiting time: %.2f\n", total_wt / n);
    printf("Average turnaround time: %.2f\n", total_tat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct process ps[n];
    
    printf("Enter burst times: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &ps[i].bt);
        ps[i].pid = i;
    }
    
    printf("Enter arrival times: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &ps[i].at);
    }
    
    printf("Enter priorities: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &ps[i].priority);
    }
    
    priority_scheduling(n, ps);
    
    return 0;
}
