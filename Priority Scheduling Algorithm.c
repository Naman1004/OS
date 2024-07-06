#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;    // Process ID
    int burst_time; // Burst time of the process
    int priority;   // Priority of the process
};

// Function to sort the processes based on priority
void sortProcessesByPriority(struct Process proc[], int n) {
    int i, j;
    struct Process temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (proc[j].priority > proc[j+1].priority) {
                temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
}

// Function to find the waiting time for all processes
void findWaitingTime(struct Process proc[], int n, int wt[]) {
    wt[0] = 0;  // waiting time for first process is 0

    // calculating waiting time
    for (int i = 1; i < n; i++) {
        wt[i] = proc[i-1].burst_time + wt[i-1];
    }
}

// Function to calculate turn around time
void findTurnAroundTime(struct Process proc[], int n, int wt[], int tat[]) {
    // calculating turnaround time by adding burst_time[i] + wt[i]
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].burst_time + wt[i];
    }
}

// Function to calculate average time
void findAverageTime(struct Process proc[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Function to find waiting time of all processes
    findWaitingTime(proc, n, wt);

    // Function to find turn around time for all processes
    findTurnAroundTime(proc, n, wt, tat);

    // Display processes along with all details
    printf("Processes  Burst time  Waiting time  Turn around time\n");

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("   %d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / (float)n);
    printf("Average turn around time = %.2f\n", (float)total_tat / (float)n);
}

int main() {
    struct Process proc[] = { {1, 10, 3}, {2, 1, 1}, {3, 2, 4}, {4, 1, 5}, {5, 5, 2} };
    int n = sizeof(proc) / sizeof(proc[0]);

    sortProcessesByPriority(proc, n);
    findAverageTime(proc, n);
    return 0;
}
