// Programmer : Jsako



#include "stdio.h"
#include "stdlib.h"
#include "limits.h"
#include "stdbool.h"



#define while_b \
    ttp = get_head(); \
    while (ttp != 0)



#define input(msg, var) \
    printf(msg); \
    scanf("%d", &(var))



int p_size, amt = 0;



bool f_bool;



struct block {

    int id, start, end, size;
    struct block *next;

} *mem = 0;



typedef struct block b;



b *ttp;



b *get_head() {

    b *q = (b *)malloc(sizeof(b));
    int a = INT_MAX;
    for (int i = 0; i < amt; i++) {
        if (mem[i].start < a) {
            a = mem[i].start;
            q = &mem[i];
        }
    }

    return q;

}



bool check_id(int i) {

    while_b {
        if (i == ttp->id) {
            return true;
            break;
        }
        ttp = ttp->next;
    }

    return false;

}



b *first_fit(b *btf, int size) {

    b *ret = ((b *)malloc(sizeof(b)));
    int ts = INT_MAX;
    bool q = false,  w = false;
    while_b {
        if (q || w) {
            return ret;
        }
        if (ttp->next == 0) {
            q = (p_size - ttp->end >= size && p_size - ttp->end <= ts);
            ts = (q) ? p_size - ttp->end : ts;
            ret = (q) ? ttp : ret;
            break;
        } else {
            w = (ttp->next->start - ttp->end >= size && ttp->next->start - ttp->end <= ts);
            ts = (w) ? ttp->next->start - ttp->end : ts;
            ret = (w) ? ttp : ret;
            ttp = ttp->next;
        }
    }

}



b *best_fit(b *btf, int size) {

    b *ret = ((b *)malloc(sizeof(b)));
    int ts = INT_MAX;
    while_b {
        if (ttp->next == 0) {
            bool e = (p_size - ttp->end >= size && p_size - ttp->end <= ts);
            ts = (e) ? p_size : ts;
            ret = (e) ? ttp : ret;
            ttp = ttp->next;
        } else {
            bool r = (ttp->next->start - ttp->end >= size && ttp->next->start - ttp->end <= ts);
            ts = (r) ? ttp->next->start - ttp->end : ts;
            ret = (r) ? ttp : ret;
            ttp = ttp->next;
        }
    }

    return ret;

}



void display() {

    printf("\nID\tSTART\tEND\n");
    printf("-------------------\n");
    while_b {
        printf("%d\t%d\t%d\n", ttp->id, ttp->start, ttp->end);
        ttp = ttp->next;
    }

}



void first_option() {

    mem = (b *)malloc(sizeof(b));
    b *ttp = ((b *)malloc(sizeof(b)));
    input("ENTER SIZE OF PHYSICAL MEMORY : ", p_size);
    input("ENTER HOLE-FITTING ALGORITHM (0 = FIRST FIT , 1 = BEST FIT) : ", f_bool);

}



void second_option() {

    amt++;
    mem = (b *)realloc(mem, amt * sizeof(b));
    input("ENTER BLOCK ID : ", (mem[amt - 1]).id);
    input("ENTER BLOCK SIZE : ", (mem[amt - 1]).size);
    if (amt == 1) {
        mem[amt - 1].start = 0;
        mem[amt - 1].end = mem[amt - 1].size + mem[amt - 1].start;
        mem[amt - 1].next = 0;
    } else {
        b *temp = (f_bool == 1) ? best_fit(&(mem[amt - 1]), (mem[amt - 1]).size) : first_fit(&(mem[amt - 1]), (mem[amt - 1]).size);
        if (check_id(temp->id)) {
            mem[amt - 1].next = temp->next;
            temp->next = &(mem[amt - 1]);
            mem[amt - 1].start = temp->end;
            mem[amt - 1].end = mem[amt - 1].start + (mem[amt - 1]).size;
        }
        else if (!(check_id(temp->id))) {
            printf("NO FIT...\n");
        }
    }

    display();

}



void third_option() {

    int i;
    b *d, *h;
    d = ((b *)malloc(sizeof(b)));
    h = ((b *)malloc(sizeof(b)));
    input("ENTER BLOCK ID : ", i);
    while_b {
        if (ttp->id == i) {
            d = ttp;
            break;
        }
        ttp = ttp->next;
    }
    while_b {
        if (ttp->next == d) {
            h = ttp;
            break;
        }
        ttp = ttp->next;
    }
    h->next = d->next;
    d->start = -1;
    d->end = -1;
    d->next = NULL;
    display();

}



void fourth_option() {

    while_b {
        if (ttp->next == NULL) {
            break;
        }
        int nextSize = ttp->next->size;
        if (ttp->next->start != ttp->end) {
            ttp->next->start = ttp->end;
            ttp->next->end = ttp->next->size + ttp->next->start;
        } else {
            ttp = ttp->next;
        }
    }

    display();

}



void fifth_option() {
    
    for (int i = 0; i < amt; i++) {
        mem[i].next = NULL;
        free(mem[i].next);
    }
    mem = NULL;
    free(mem);

}



int main() {
    
    int choice = -1;
    while(choice != 5) {
        printf("\nMEMORY ALLOCATION\n");
        printf("-----------------\n");
        printf("(1) ENTER PARAMETERS.\n");
        printf("(2) ALLOCATE MEMORY FOR BLOCK.\n");
        printf("(3) DEALLOCATE MEMORY FOR BLOCK.\n");
        printf("(4) DEFRAGMENT MEMORY.\n");
        printf("(5) QUIT PROGRAM.\n\n");
        input("ENTER SELECTION : ", choice);
        switch(choice) {
            case 1:
                first_option();
                break;
            case 2:
                second_option();
                break;
            case 3:
                third_option();
                break;
            case 4:
                fourth_option();
                break;
            case 5:
                fifth_option();
                printf("QUITTING PROGRAM...");
                break;
            default:
                printf("INVALID SELECTION, PLEASE TRY AGAIN...");
                break;
        }
    }
    
}
