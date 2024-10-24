#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int main() {
    int p, r;

    // Input: Number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &p);
    printf("Enter number of resources: ");
    scanf("%d", &r);

    int max[p][r], allocated[p][r], need[p][r], available[r], total[r];
    bool finish[p];

    // Input: Maximum Requirement matrix
    printf("Enter maximum requirement:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input: Allocated matrix
    printf("Enter allocated matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &allocated[i][j]);
        }
    }

    // Input: Resource Vector (Total instances of each resource)
    printf("Resource Vector: ");
    for (int i = 0; i < r; i++) {
        scanf("%d", &total[i]);
    }

    // Calculate Available resources
    for (int j = 0; j < r; j++) {
        int allocated_sum = 0;
        for (int i = 0; i < p; i++) {
            allocated_sum += allocated[i][j];
        }
        available[j] = total[j] - allocated_sum;
    }

    // Calculate Need matrix (max - allocated)
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }

    // Initialize finish array
    for (int i = 0; i < p; i++) {
        finish[i] = false;
    }

    // Deadlock detection using Banker's algorithm logic
    bool proceed = true;
    while (proceed) {
        proceed = false;
        for (int i = 0; i < p; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > available[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                // If resources can be allocated
                if (can_allocate) {
                    for (int j = 0; j < r; j++) {
                        available[j] += allocated[i][j];
                    }
                    finish[i] = true;
                    proceed = true;
                }
            }
        }
    }

    // Check if all processes finished
    bool deadlock = false;
    for (int i = 0; i < p; i++) {
        if (!finish[i]) {
            deadlock = true;
            break;
        }
    }

    if (deadlock) {
        printf("Deadlock detected\n");
    } else {
        printf("No deadlock detected\n");
    }

    return 0;
}
