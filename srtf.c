#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct process {
    int pid;
    int at;    // Arrival Time
    int bt;    // Burst Time
    int ct, wt, tat, start_time;  // Completion, Waiting, Turnaround Times
};
void SRTF(struct process ps[],int n,int bt_remaining[])
{
    bool is_completed[100] = {false};  // Tracks completed processes
    int current_time = 0, completed = 0, last_pid = -1;
    float sum_tat = 0, sum_wt = 0;
    int gantt_chart[1000], gc_index = 0;  // Gantt chart large enough for preemptive entries

    while(completed != n) {
        // Find the process with the minimum remaining burst time in the ready queue
        int min_index = -1, minimum = INT_MAX;
        for(int i = 0; i < n; i++) {
            if(ps[i].at <= current_time && !is_completed[i] && bt_remaining[i] < minimum) {
                minimum = bt_remaining[i];
                min_index = i;
            }
        }

        // If no process is ready, increment time
        if(min_index == -1) {
            current_time++;
        } else {
            // Add process to Gantt chart only when it first enters the CPU or comes back after preemption
            if (last_pid != ps[min_index].pid) {
                gantt_chart[gc_index++] = ps[min_index].pid;
                last_pid = ps[min_index].pid;
            }

            // Mark the start time the first time the process starts execution
            if(bt_remaining[min_index] == ps[min_index].bt) {
                ps[min_index].start_time = current_time;
            }

            // Execute the process for 1 unit of time
            bt_remaining[min_index]--;
            current_time++;

            // If the process finishes, record its completion time and stats
            if(bt_remaining[min_index] == 0) {
                ps[min_index].ct = current_time;  // Completion time
                ps[min_index].tat = ps[min_index].ct - ps[min_index].at;  // Turnaround time
                ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;  // Waiting time
                
                sum_tat += ps[min_index].tat;
                sum_wt += ps[min_index].wt;
                completed++;
                is_completed[min_index] = true;
                last_pid = -1;  // Reset to log next process switch properly
            }
        }
    }

    // Output average times
    printf("\nAverage Turn Around Time = %.2f", sum_tat / n);
    printf("\nAverage Waiting Time = %.2f", sum_wt / n);

    // Output Gantt Chart
    printf("\n\nGantt Chart:\n|");
    for(int i = 0; i < gc_index; i++) {
        printf(" P%d |", gantt_chart[i]);
    }
    printf("\n");
}

int main() {
    int n;
    int bt_remaining[100];

    printf("Enter total number of processes: ");
    scanf("%d", &n);
    struct process ps[n];
    printf("Enter Process Arrival Time: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &ps[i].at);
        ps[i].pid = i + 1;
    }
    
    printf("Enter Process Burst Time: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &ps[i].bt);
        bt_remaining[i] = ps[i].bt;  // Remaining burst time initially equals burst time
    }
    SRTF(ps,n,bt_remaining);

    return 0;
}
