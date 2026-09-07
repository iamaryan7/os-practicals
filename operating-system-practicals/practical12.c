#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 100
#define MAX_FILES 50

struct File {
    char name[20];
    int start;
    int length;
};

int main() {
    int total_blocks, choice;
    char disk[MAX_BLOCKS][20];
    struct File files[MAX_FILES];
    int file_count = 0;

    printf("===== Sequential (Contiguous) File Allocation Method =====\n\n");

    printf("Enter total number of disk blocks: ");
    scanf("%d", &total_blocks);

    // Initialize all blocks as Free
    for(int i = 0; i < total_blocks; i++) {
        strcpy(disk[i], "Free");
    }

    while(1) {
        printf("\n--------- Menu ---------\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Show Disk Status\n");
        printf("4. Show File Allocation Table\n");
        printf("5. Exit\n");
        printf("------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if(choice == 1) {
            char file_name[20];
            int start_block, length;
            int exists = 0;

            printf("Enter File Name: ");
            scanf("%s", file_name);

            // Check if file already exists
            for(int i = 0; i < file_count; i++) {
                if(strcmp(files[i].name, file_name) == 0) {
                    exists = 1;
                    break;
                }
            }

            if(exists) {
                printf("Error: File already exists!\n");
                continue;
            }

            printf("Enter Starting Block: ");
            scanf("%d", &start_block);

            printf("Enter Length (Number of Blocks): ");
            scanf("%d", &length);

            if(start_block < 0 || start_block >= total_blocks) {
                printf("Error: Invalid starting block!\n");
                continue;
            }

            if(start_block + length > total_blocks) {
                printf("Error: Not enough blocks available!\n");
                continue;
            }

            int is_free = 1;

            for(int i = start_block; i < start_block + length; i++) {
                if(strcmp(disk[i], "Free") != 0) {
                    is_free = 0;
                    break;
                }
            }

            if(is_free) {
                for(int i = start_block; i < start_block + length; i++) {
                    strcpy(disk[i], file_name);
                }

                strcpy(files[file_count].name, file_name);
                files[file_count].start = start_block;
                files[file_count].length = length;
                file_count++;

                printf("File '%s' allocated successfully from block %d to %d\n",
                       file_name, start_block, start_block + length - 1);
            }
            else {
                printf("Error: Contiguous free blocks not available!\n");
            }
        }

        else if(choice == 2) {
            char file_name[20];
            int found = -1;

            printf("Enter File Name to Delete: ");
            scanf("%s", file_name);

            for(int i = 0; i < file_count; i++) {
                if(strcmp(files[i].name, file_name) == 0) {
                    found = i;
                    break;
                }
            }

            if(found == -1) {
                printf("Error: File not found!\n");
                continue;
            }

            int start = files[found].start;
            int length = files[found].length;

            for(int i = start; i < start + length; i++) {
                strcpy(disk[i], "Free");
            }

            // Remove file from file table
            for(int i = found; i < file_count - 1; i++) {
                files[i] = files[i + 1];
            }

            file_count--;

            printf("File '%s' deleted successfully.\n", file_name);
        }

        else if(choice == 3) {
            printf("\nDisk Status (Block -> Content)\n");
            printf("----------------------------------\n");

            for(int i = 0; i < total_blocks; i++) {
                printf("Block %3d -> %s\n", i, disk[i]);
            }

            printf("----------------------------------\n");
        }

        else if(choice == 4) {
            if(file_count == 0) {
                printf("No files allocated yet.\n");
            }
            else {
                printf("\nFile Allocation Table\n");
                printf("------------------------------------------------\n");
                printf("%-15s %-15s %-10s\n",
                       "File Name", "Start Block", "Length");
                printf("------------------------------------------------\n");

                for(int i = 0; i < file_count; i++) {
                    printf("%-15s %-15d %-10d\n",
                           files[i].name,
                           files[i].start,
                           files[i].length);
                }

                printf("------------------------------------------------\n");
            }
        }

        else if(choice == 5) {
            printf("Exiting program...\n");
            break;
        }

        else {
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}