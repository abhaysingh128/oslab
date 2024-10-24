#include <stdio.h>
#include <stdbool.h>

struct process_info {
    int max[10];
    int allocated[10];
    int need[10];
};

int no_of_process, no_of_resources;

// Function to take the input
void input(struct process_info process[no_of_process], int available[no_of_resources]) {
    printf("Enter maximum requirement:\n");
    for (int i = 0; i < no_of_process; i++) {
        for (int j = 0; j < no_of_resources; j++) {
            scanf("%d", &process[i].max[j]);
        }
    }

    printf("Enter allocated matrix:\n");
    for (int i = 0; i < no_of_process; i++) {
        for (int j = 0; j < no_of_resources; j++) {
            scanf("%d", &process[i].allocated[j]);
            process[i].need[j] = process[i].max[j] - process[i].allocated[j];
        }
    }

    printf("Resource Vector : ");
    for (int i = 0; i < no_of_resources; i++) {
        scanf("%d", &available[i]);
    }
}

// Apply the Banker's safety algorithm
bool applySafetyAlgo(struct process_info process[no_of_process], int available[no_of_resources], int safeSequence[no_of_process]) {
    bool finish[no_of_process];
    int work[no_of_resources];

    // Initialize work vector to available resources
    for (int i = 0; i < no_of_resources; i++) {
        work[i] = available[i];
    }

    // Initialize finish array to false for all processes
    for (int i = 0; i < no_of_process; i++) {
        finish[i] = false;
    }

    bool proceed = true;
    int k = 0;

    while (proceed) {
        proceed = false;
        for (int i = 0; i < no_of_process; i++) {
            if (finish[i] == false) {
                bool flag = true;
                // Check if process can be executed (need <= work)
                for (int j = 0; j < no_of_resources; j++) {
                    if (process[i].need[j] > work[j]) {
                        flag = false;
                        break;
                    }
                }
                // If process can be executed, update work and mark it finished
                if (flag) {
                    for (int j = 0; j < no_of_resources; j++) {
                        work[j] += process[i].allocated[j];
                    }
                    finish[i] = true;
                    safeSequence[k++] = i;
                    proceed = true;
                }
            }
        }
    }

    // Check if all processes are finished
    for (int i = 0; i < no_of_process; i++) {
        if (!finish[i]) {
            return false;
        }
    }
    return true;
}

// Check if the state is safe
bool isSafeState(struct process_info process[no_of_process], int available[no_of_resources], int safeSequence[no_of_process]) {
    return applySafetyAlgo(process, available, safeSequence);
}

int main() {
    // Input for number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &no_of_process);
    printf("Enter number of resources: ");
    scanf("%d", &no_of_resources);

    int available[no_of_resources];
    int safeSequence[no_of_process];

    // Create array of structure to store process information
    struct process_info process[no_of_process];

    // Take input
    input(process, available);

    // Apply Banker's algorithm and check for safe state
    if (isSafeState(process, available, safeSequence)) {
        printf("Request can be fulfilled\n");
        printf("Safe Sequence : ");
        for (int i = 0; i < no_of_process; i++) {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    } else {
        printf("System is not in a safe state.\n");
    }

    return 0;
}
