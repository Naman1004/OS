#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, head, direction;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the request queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    sort(requests, n);

    int seek_count = 0, distance, cur_track;
    int left[n], right[n], l = 0, r = 0;

    if (direction == 0) {
        for (int i = 0; i < n; i++) {
            if (requests[i] < head)
                left[l++] = requests[i];
            else
                right[r++] = requests[i];
        }

        sort(left, l);
        sort(right, r);

        for (int i = l - 1; i >= 0; i--) {
            cur_track = left[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf("Served track: %d\n", cur_track);
        }

        if (r != 0) {
            distance = abs(head - 0);
            seek_count += distance;
            head = 0;
        }

        for (int i = 0; i < r; i++) {
            cur_track = right[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf("Served track: %d\n", cur_track);
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (requests[i] < head)
                left[l++] = requests[i];
            else
                right[r++] = requests[i];
        }

        sort(left, l);
        sort(right, r);

        for (int i = 0; i < r; i++) {
            cur_track = right[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf("Served track: %d\n", cur_track);
        }

        if (l != 0) {
            distance = abs(head - 199);
            seek_count += distance;
            head = 199;
        }

        for (int i = l - 1; i >= 0; i--) {
            cur_track = left[i];
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
            printf("Served track: %d\n", cur_track);
        }
    }

    printf("Total seek count: %d\n", seek_count);
    return 0;
}
