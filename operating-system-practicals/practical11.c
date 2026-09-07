#include <stdio.h>

int main() {
    int frames, n, i, j;

    printf("===== Least Recently Used (LRU) Page Replacement Algorithm =====\n\n");

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
    int recent[frames];
    int size = 0;

    int page_faults = 0;
    int page_hits = 0;

    // Initialize memory
    for(i = 0; i < frames; i++) {
        memory[i] = -1;
        recent[i] = -1;
    }

    printf("\n---------------------------------------------------------------------------\n");
    printf("Step   Page    Memory Frames                 Status      Faults\n");
    printf("---------------------------------------------------------------------------\n");

    for(i = 0; i < n; i++) {
        int page = ref_string[i];
        int found = -1;

        // Check if page is already in memory
        for(j = 0; j < size; j++) {
            if(memory[j] == page) {
                found = j;
                break;
            }
        }

        if(found != -1) {
            // Page Hit
            page_hits++;

            // Update recent usage
            int k, pos;
            for(pos = 0; pos < size; pos++) {
                if(recent[pos] == page)
                    break;
            }

            for(k = pos; k < size - 1; k++) {
                recent[k] = recent[k + 1];
            }

            recent[size - 1] = page;

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
            // Page Fault
            page_faults++;

            if(size < frames) {
                memory[size] = page;
                recent[size] = page;
                size++;
            }
            else {
                // Replace Least Recently Used page
                int lru_page = recent[0];
                int index = 0;

                for(j = 0; j < frames; j++) {
                    if(memory[j] == lru_page) {
                        index = j;
                        break;
                    }
                }

                memory[index] = page;

                for(j = 0; j < frames - 1; j++) {
                    recent[j] = recent[j + 1];
                }

                recent[frames - 1] = page;
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

    printf("---------------------------------------------------------------------------\n");

    printf("\nTotal Page References : %d\n", n);
    printf("Total Page Faults     : %d\n", page_faults);
    printf("Total Page Hits       : %d\n", page_hits);
    printf("Hit Ratio             : %.2f%%\n", hit_ratio);
    printf("Fault Ratio           : %.2f%%\n", fault_ratio);

    printf("---------------------------------------------------------------------------\n");

    return 0;
}