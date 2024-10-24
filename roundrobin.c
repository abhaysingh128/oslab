#include<stdio.h>
#include<limits.h>
#include<stdbool.h>  //for bool datatype
#include <stdlib.h> //for qsort

struct process
{
  int pid;
  int at;
  int bt;
  int ct,wt,tat,start_time;
  int bt_remaining;
}ps[100];


int findmax(int a, int b)
{
    return a>b?a:b;
}

int main()
{
    int n, index;
    bool visited[100] = {false}, is_first_process = true;
    int current_time = 0;
    int completed = 0, tq;
    int gantt_chart[500], gc_index = 0;  // Array to store Gantt Chart sequence

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    int queue[100], front = -1, rear = -1;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;

    // Input arrival times
    printf("\nEnter Process Arrival Time: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &ps[i].at);
        ps[i].pid = i+1;
    }

    // Input burst times
    printf("\nEnter Process Burst Time: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &ps[i].bt);
        ps[i].bt_remaining = ps[i].bt;
    }

    // Input time quantum
    printf("\nEnter time quanta: ");
    scanf("%d", &tq);

    // Initialize queue with the first process
    front = rear = 0;
    queue[rear] = 0;
    visited[0] = true;

    // Start Round Robin Scheduling
    while (completed != n) {
        index = queue[front];      
        front++;

        // If the process is executed for the first time
        if (ps[index].bt_remaining == ps[index].bt) {
            ps[index].start_time = findmax(current_time, ps[index].at);
            current_time = ps[index].start_time;
        }

        // Store the process in the Gantt chart
        gantt_chart[gc_index++] = ps[index].pid;

        // If the process needs more time than the time quantum
        if (ps[index].bt_remaining - tq > 0) {
            ps[index].bt_remaining -= tq;
            current_time += tq;
        } else {
            // Process completes within the current time quantum
            current_time += ps[index].bt_remaining;
            ps[index].bt_remaining = 0;
            completed++;

            // Calculate completion, turnaround, and waiting times
            ps[index].ct = current_time;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].wt = ps[index].tat - ps[index].bt;

            // Accumulate the totals
            sum_tat += ps[index].tat;
            sum_wt += ps[index].wt;
        }

        // Add new processes to the queue if they have arrived
        for (int i = 1; i < n; i++) {
            if (ps[i].bt_remaining > 0 && ps[i].at <= current_time && visited[i] == false) {
                queue[++rear] = i;
                visited[i] = true;
            }
        }

        // Add the current process back to the queue if it's not completed
        if (ps[index].bt_remaining > 0) {
            queue[++rear] = index;
        }

        // If the queue is empty, add a new process from the list
        if (front > rear) {
            for (int i = 1; i < n; i++) {
                if (ps[i].bt_remaining > 0) {
                    queue[rear++] = i;
                    visited[i] = true;
                    break;
                }
            }
        }
    }

    // Display Gantt Chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < gc_index; i++) {
        if (i == 0 || gantt_chart[i] != gantt_chart[i-1]) {
            printf(" P%d ", gantt_chart[i]);
        }
    }
    printf("\n");

    // Display Average Turnaround Time and Waiting Time
    printf("\nAverage Turn Around Time = %.2f", (float)sum_tat / n);
    printf("\nAverage Waiting Time = %.2f", (float)sum_wt / n);
    printf("\n");
    return 0;
}
