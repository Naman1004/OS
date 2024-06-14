#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for sleep function

// Function to simulate formatting the disk
void format_disk() {
    printf("Formatting disk...\n");
    // Simulate some delay
    for (int i = 0; i < 5; i++) {
        printf(".");
        fflush(stdout);
        sleep(1); // Sleep for 1 second
    }
    printf("\nDisk formatted successfully.\n");
}

// Function to simulate copying files
void copy_files() {
    printf("Copying files...\n");
    // Simulate some delay
    for (int i = 0; i < 5; i++) {
        printf(".");
        fflush(stdout);
        sleep(1); // Sleep for 1 second
    }
    printf("\nFiles copied successfully.\n");
}

// Function to simulate installing the bootloader
void install_bootloader() {
    printf("Installing bootloader...\n");
    // Simulate some delay
    for (int i = 0; i < 5; i++) {
        printf(".");
        fflush(stdout);
        sleep(1); // Sleep for 1 second
    }
    printf("\nBootloader installed successfully.\n");
}

// Main function to simulate the OS installation process
int main() {
    printf("Welcome to the OS Installer!\n");

    // Simulate user confirmation
    char input[4];
    printf("Do you want to install the OS? (yes/no): ");
    fgets(input, sizeof(input), stdin);
    if (strncmp(input, "yes", 3) != 0) {
        printf("Installation cancelled.\n");
        return 0;
    }

    // Simulate the installation steps
    format_disk();
    copy_files();
    install_bootloader();

    printf("OS installation completed successfully!\n");
    return 0;
}
