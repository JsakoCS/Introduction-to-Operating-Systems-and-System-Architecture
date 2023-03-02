// Programmer : Jsako

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node {
    
    int id;
    int arrival;
    int total_cpu;
    int total_remaining;
    int done;
    int start_time;
    int already_started;
    int end_time;
    int turnaround_time;
    
} *table = NULL;

typedef struct node table_type;

int total_processes;

#define max(a,b) (a > b ? a : b)

void printing() {
    
    int process = total_processes;
    printf("ID\tARRIVAL\tTOTAL\tSTART\tEND\tTURNAROUND\n");
    printf("--------------------------------------------------\n");
    for(int i = 0; i < process; i++) {
        printf("%d\t%d\t%d\t", table[i].id, table[i].arrival, table[i].total_cpu);
        if(table[i].done == 1) {
            printf("%d\t%d\t%d", table[i].start_time, table[i].end_time, table[i].turnaround_time);
        }
        printf("\n");
    }
    return;
    
}

void first_option() {
    
    printf("ENTER TOTAL NUMBER OF PROCESSES : ");
    scanf("%d", &total_processes);
    table = (table_type *)malloc(total_processes * sizeof(table_type));
    for(int i = 0; i < total_processes; i++) {
        printf("ENTER PROCESS ID : ");
        scanf("%d", &table[i].id);
        printf("ENTER ARRIVAL CYCLE FOR PROCESS P[%d] : ", i + 1);
        scanf("%d", &table[i].arrival);
        printf("ENTER TOTAL CYCLES FOR PROCESS P[%d] : ", i + 1);
        scanf("%d", &table[i].total_cpu);
    }
    printf("\n");
    printing();
    printf("\n");
    return;
    
}

void second_option() {
    
    int local_num = total_processes;
    int early_arrival;
    int current_process;
    int current_cycle = 0;
    for(int i = 0; i < total_processes; i++) {
        table[i].done = 0;
    }
    while(local_num != 0) {
        early_arrival = INT_MAX;
        for(int i = 0; i < total_processes; i++) {
            if(table[i].done == 0) {
                if(early_arrival > table[i].arrival) {
                    early_arrival = table[i].arrival;
                    current_process = i;
                }
            }
        }
        table[current_process].start_time = max(current_cycle, early_arrival);
        table[current_process].end_time = table[current_process].start_time + table[current_process].total_cpu;
        table[current_process].turnaround_time = table[current_process].end_time - table[current_process].arrival;
        table[current_process].done = 1;
        current_cycle = table[current_process].end_time;
        local_num -= 1;
    }
    printf("\n");
    printing();
    printf("\n");
    return;
    
}

void third_option() {
    
    int local_num = total_processes;
    int lowest_cpu;
    int current_process;
    int current_cycle = 0;
    for(int i = 0; i < total_processes; i++) {
        table[i].done = 0;
    }
    while(local_num != 0) {
        lowest_cpu = INT_MAX;
        for(int i = 0; i < total_processes; i++) {
            if(table[i].done == 0) {
                if((lowest_cpu > table[i].total_cpu) && (table[i].arrival <= current_cycle)) {
                    lowest_cpu = table[i].total_cpu;
                    current_process = i;
                }
            }
        }
        table[current_process].start_time = current_cycle;
        table[current_process].end_time = table[current_process].start_time + table[current_process].total_cpu;
        table[current_process].turnaround_time = table[current_process].end_time - table[current_process].arrival;
        table[current_process].done = 1;
        current_cycle = table[current_process].end_time;
        local_num--;
    }
    printf("\n");
    printing();
    printf("\n");
    return;
    
}

void fourth_option() {
    
    int local_num = total_processes;
    int lowest_remaining;
    int current_process;
    int start_process;
    int current_cycle = 0;
    for(int i = 0; i < total_processes; i++) {
        table[i].done = 0;
        table[i].total_remaining = table[i].total_cpu;
        table[i].already_started = 0;
    }
    while(local_num != 0) {
        lowest_remaining = INT_MAX;
        for(int i = 0; i < total_processes; i++) {
            if(table[i].done == 0) {
                if((lowest_remaining > table[i].total_remaining) && (table[i].arrival <= current_cycle)) {
                    lowest_remaining = table[i].total_remaining;
                    current_process = i;
                }
            }
        }
        if(table[current_process].already_started == 0) {
            table[current_process].start_time = current_cycle;
            table[current_process].already_started = 1;
        }
        table[current_process].end_time = current_cycle + 1;
        table[current_process].turnaround_time = table[current_process].end_time - table[current_process].arrival;
        current_cycle++;
        table[current_process].total_remaining--;
        if(table[current_process].total_remaining == 0) {
            table[current_process].done = 1;
            local_num--;
        }
    }
    printf("\n");
    printing();
    printf("\n");
    return;
    
}

void fifth_option() {
    
    if(table != NULL) {
        free(table);
    }
    return;
    
}

int main() {
    
    int choice = 0;
    printf("BATCH SCHEDULING\n");
    printf("----------------\n");
    while(choice != 5) {
        printf("(1) ENTER PARAMETERS.\n");
        printf("(2) SCHEDULE PROCESSES WITH FIFO ALGORITHM.\n");
        printf("(3) SCHEDULE PROCESSES WITH SJF ALGORITHM.\n");
        printf("(4) SCHEDULE PROCESSES WITH SRT ALGORITHM.\n");
        printf("(5) QUIT AND FREE MEMORY.\n\n");
        printf("ENTER SELECTION : ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: first_option(); break;
            case 2: second_option(); break;
            case 3: third_option(); break;
            case 4: fourth_option(); break;
            case 5: fifth_option(); printf("QUITTING PROGRAM..."); break;
            default: printf("INVALID OPTION, TRY AGAIN...\n\n"); break;
        }
    }
    return 1;
    
}
