#include <stdio.h>

void fifoPageReplacement(int pages[], int n, int capacity) {
    int frame[capacity];
    int count = 0, pageFaults = 0, next = 0;

    for (int i = 0; i < capacity; i++) {
        frame[i] = -1; // Initializing frames to -1 to indicate they are empty
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if the page is already in any of the frames
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // If the page is not in any frame, we have a page fault
        if (!found) {
            frame[next] = pages[i]; // Replace the page at the 'next' index
            next = (next + 1) % capacity; // Move to the next frame in a circular manner
            pageFaults++;
        }

        // Print the current status of frames
        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == -1)
                printf("empty ");
            else
                printf("%d ", frame[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int n, capacity;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page numbers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    fifoPageReplacement(pages, n, capacity);

    return 0;
}
