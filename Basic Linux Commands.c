#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate the ls command
void listFiles() {
    printf("Listing files:\n");
    system("ls");
}

// Function to simulate the pwd command
void printWorkingDirectory() {
    printf("Current working directory:\n");
    system("pwd");
}

// Function to simulate the mkdir command
void makeDirectory() {
    char dirname[50];
    printf("Enter directory name to create: ");
    scanf("%s", dirname);
    char command[100];
    sprintf(command, "mkdir %s", dirname);
    system(command);
}

// Function to simulate the cat command
void displayFileContent() {
    char filename[50];
    printf("Enter filename to display: ");
    scanf("%s", filename);
    char command[100];
    sprintf(command, "cat %s", filename);
    system(command);
}

int main() {
    int choice;

    do {
        printf("\nBasic Linux Commands Simulation\n");
        printf("1. List files in current directory\n");
        printf("2. Print current working directory\n");
        printf("3. Create a directory\n");
        printf("4. Display contents of a file\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                listFiles();
                break;
            case 2:
                printWorkingDirectory();
                break;
            case 3:
                makeDirectory();
                break;
            case 4:
                displayFileContent();
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}
