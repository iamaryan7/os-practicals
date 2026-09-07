#include <stdio.h>

int main() {
    int frames, n, i, j;
    
    printf("===== FIFO Page Replacement Algorithm =====\n\n");

    // Input number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    // Input number of page references
    printf("Enter the number of page references: ");
    scanf("%d", &n);

    int ref_string[n];

    printf("Enter the reference string:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &ref_string[i]);
    }

    int memory[frames];
    int front = 0;
    int count = 0;

    int page_faults = 0;
    int page_hits = 0;

    // Initialize memory
    for(i = 0; i < frames; i++) {
        memory[i] = -1;
    }

    printf("\n----------------------------------------------------------------------\n");
    printf("Step   Page    Memory Frames                 Status      Faults\n");
    printf("----------------------------------------------------------------------\n");

    for(i = 0; i < n; i++) {
        int page = ref_string[i];
        int found = 0;

        // Check if page already exists
        for(j = 0; j < frames; j++) {
            if(memory[j] == page) {
                found = 1;
                break;
            }
        }

        if(found) {
            page_hits++;

            printf("%-6d%-8d", i + 1, page);

            for(j = 0; j < frames; j++) {
                if(memory[j] == -1)
                    printf("- ");
                else
                    printf("%d ", memory[j]);
            }

            printf("%15s%8d\n", "Hit", page_faults);
        }
        else {
            page_faults++;

            if(count < frames) {
                memory[count] = page;
                count++;
            }
            else {
                memory[front] = page;
                front = (front + 1) % frames;
            }

            printf("%-6d%-8d", i + 1, page);

            for(j = 0; j < frames; j++) {
                if(memory[j] == -1)
                    printf("- ");
                else
                    printf("%d ", memory[j]);
            }

            printf("%15s%8d\n", "Fault", page_faults);
        }
    }

    float hit_ratio = ((float)page_hits / n) * 100;
    float fault_ratio = ((float)page_faults / n) * 100;

    printf("----------------------------------------------------------------------\n");

    printf("\nTotal Page References : %d\n", n);
    printf("Total Page Faults     : %d\n", page_faults);
    printf("Total Page Hits       : %d\n", page_hits);
    printf("Hit Ratio             : %.2f%%\n", hit_ratio);
    printf("Fault Ratio           : %.2f%%\n", fault_ratio);

    printf("----------------------------------------------------------------------\n");

    return 0;
}