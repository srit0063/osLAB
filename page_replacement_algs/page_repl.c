#include <stdio.h>
#include <stdbool.h>

#define MAX_PAGES 100

void printFrames(int frames[], int num_frames) {
    printf("[");
    int count = 0;
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] != -1) {
            printf("%d", frames[i]);
            count++;
        }
    }
    printf("]\n");
}


void fifoPageReplacement(int pages[], int num_pages, int num_frames) {
    printf("\n--- FIFO Page Replacement ---\n");

    int frames[num_frames];
    for (int i = 0; i < num_frames; i++) frames[i] = -1;

    int page_faults = 0;
    int next = 0;

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        bool is_present = false;


        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                is_present = true;
                break;
            }
        }

        printf("Page %d -> ", page);

        if (!is_present) {

            frames[next] = page;
            next = (next + 1) % num_frames;
            page_faults++;
        }

        printFrames(frames, num_frames);
    }
    printf("Total Page Faults (FIFO): %d\n", page_faults);
}


void lruPageReplacement(int pages[], int num_pages, int num_frames) {
    printf("\n--- LRU Page Replacement ---\n");

    int frames[num_frames];
    int last_used[num_frames];
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }

    int page_faults = 0;

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        bool is_present = false;
        int present_index = -1;


        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                is_present = true;
                present_index = j;
                break;
            }
        }

        printf("Page %d -> ", page);

        if (is_present) {

            last_used[present_index] = i;
        } else {

            page_faults++;


            int empty_index = -1;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    empty_index = j;
                    break;
                }
            }

            if (empty_index != -1) {

                frames[empty_index] = page;
                last_used[empty_index] = i;
            } else {

                int lru_index = 0;
                int min_time = last_used[0];
                for (int j = 1; j < num_frames; j++) {
                    if (last_used[j] < min_time) {
                        min_time = last_used[j];
                        lru_index = j;
                    }
                }
                frames[lru_index] = page;
                last_used[lru_index] = i;
            }
        }

        printFrames(frames, num_frames);
    }
    printf("Total Page Faults (LRU): %d\n", page_faults);
}


void optimalPageReplacement(int pages[], int num_pages, int num_frames) {
    printf("\n--- Optimal Page Replacement ---\n");

    int frames[num_frames];
    for (int i = 0; i < num_frames; i++) frames[i] = -1;

    int page_faults = 0;

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        bool is_present = false;

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                is_present = true;
                break;
            }
        }

        printf("Page %d -> ", page);

        if (!is_present) {
            page_faults++;

            int empty_index = -1;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    empty_index = j;
                    break;
                }
            }

            if (empty_index != -1) {
                frames[empty_index] = page;
            } else {

                int replace_index = -1;
                int farthest_use = -1;

                for (int j = 0; j < num_frames; j++) {
                    int next_use = -1;

                    for (int k = i + 1; k < num_pages; k++) {
                        if (pages[k] == frames[j]) {
                            next_use = k;
                            break;
                        }
                    }


                    if (next_use == -1) {
                        replace_index = j;
                        break;
                    }


                    if (next_use > farthest_use) {
                        farthest_use = next_use;
                        replace_index = j;
                    }
                }

                frames[replace_index] = page;
            }
        }

        printFrames(frames, num_frames);
    }
    printf("Total Page Faults (Optimal): %d\n", page_faults);
}

int main() {
    int num_pages, num_frames;
    int pages[MAX_PAGES];


    printf("Enter number of pages: ");
    if (scanf("%d", &num_pages) != 1 || num_pages <= 0 || num_pages > MAX_PAGES) {
        printf("Invalid number of pages.\n");
        return 1;
    }

    printf("Enter page reference string:\n");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    if (scanf("%d", &num_frames) != 1 || num_frames <= 0) {
        printf("Invalid number of frames.\n");
        return 1;
    }


    fifoPageReplacement(pages, num_pages, num_frames);
    lruPageReplacement(pages, num_pages, num_frames);
    optimalPageReplacement(pages, num_pages, num_frames);

    return 0;
}
