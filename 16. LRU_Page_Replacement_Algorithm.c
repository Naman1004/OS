#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Function to check if a page is in memory
int isPageInMemory(int pages[], int page, int n) {
    for (int i = 0; i < n; i++) {
        if (pages[i] == page) {
            return 1;
        }
    }
    return 0;
}

// Function to find the LRU page
int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void lruPageReplacement(int pages[], int n, int capacity) {
    int memory[capacity], time[capacity];
    int pageFaults = 0, counter = 0;

    for (int i = 0; i < capacity; i++) {
        memory[i] = -1;  // Initialize memory slots as empty
    }

    for (int i = 0; i < n; i++) {
        if (!isPageInMemory(memory, pages[i], capacity)) {
            int pos = findLRU(time, capacity);
            memory[pos] = pages[i];
            time[pos] = counter++;
            pageFaults++;
        } else {
            // Update the time for the page if it is already in memory
            for (int j = 0; j < capacity; j++) {
                if (memory[j] == pages[i]) {
                    time[j] = counter++;
                    break;
                }
            }
        }

        // Print current memory status
        printf("\nMemory: ");
        for (int j = 0; j < capacity; j++) {
            if (memory[j] != -1) {
                printf("%d ", memory[j]);
            } else {
                printf("- ");
            }
        }
    }

    printf("\n\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int n, capacity;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the memory capacity: ");
    scanf("%d", &capacity);

    lruPageReplacement(pages, n, capacity);

    return 0;
}
