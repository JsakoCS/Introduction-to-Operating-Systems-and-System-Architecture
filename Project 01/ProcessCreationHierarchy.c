// Programmer : Jsako

#include <stdio.h>
#include <stdlib.h>

int n;

struct node1 {
    
    int process;
    struct node1 *link;
    
};

typedef struct node1 linked_list_type;

struct node2 {
    
    int parent;
    linked_list_type *children;
    
} *pcb = NULL;

typedef struct node2 pcb_type;

void printing() {
    
    linked_list_type *next;
    for(int i = 0; i < n; i++) {
        if((pcb[i].parent != -1) && (pcb[i].children != NULL)) {
            printf("PCB[%d] is the parent of : ", i);
            next = pcb[i].children;
            while(next != NULL) {
                printf("PCB[%d] ", next->process);
                next = next->link;
            }
            printf("\n");
        }
    }
    
}

void option1() {
    
    printf("Enter maximum number of processes: ");
    scanf("%d", &n);
    pcb = malloc(n *sizeof(pcb_type));
    pcb[0].parent = 0;
    pcb[0].children = NULL;
    for(int i = 1; i < n; i++) {
        pcb[i].parent = -1;
    }
    return;
    
}

void option2() {
    
    linked_list_type *new_child, *next;
    int new_child_index = 1;
    int p;
    int q = 0;
    int num_children = 1;
    printf("Enter the parent process index: ");
    scanf("%d", &p);
    while(pcb[q].parent != -1) {
        q++;
    }
    new_child = (linked_list_type *) malloc(sizeof(linked_list_type));
    new_child->process = q;
    new_child->link = NULL;
    pcb[q].parent = p;
    pcb[q].children = NULL;
    if(pcb[p].children == NULL) {
        pcb[p].children = new_child;
    } else {
        next = pcb[p].children;
        num_children++;
        while(next->link != NULL) {
            next = next->link;
            num_children++;
        }
        next->link = new_child;
    }
    printing();
    return;

}

void destroying(linked_list_type *node) {
    
    if(node == NULL) {
        return;
    } else {
        destroying(node->link);
        int q = node->process;
        destroying(pcb[q].children);
        free(node);
        pcb[q].parent = -1;
        node = NULL;
    }
    
}

void option3() {
    
    int p;
    printf("Enter the index of the process whose descendants are to be destroyed: ");
    scanf("%d", &p);
    destroying(pcb[p].children);
    pcb[p].children = NULL;
    printing();
    
}

void option4() {
    
    if(pcb != NULL) {
        if(pcb[0].children != NULL) {
            destroying(pcb[0].children);
        }
        free(pcb);
    }
    printf("Quitting program...");
    
}

int main() {
    
    int choice = 0;
    while(choice != 4) {
        printf("\nPROCESS CREATION AND DESTRUCTION");
        printf("\n--------------------------------");
        printf("\n1) Enter parameters.");
        printf("\n2) Create a new child process.");
        printf("\n3) Destroy all descendants of a process.");
        printf("\n4) Quit program and free memory.");
        printf("\nEnter selection: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: option1(); break;
            case 2: option2(); break;
            case 3: option3(); break;
            case 4: option4(); break;
            default: printf("Invalid option selected..."); break;
        }
    }
    
}
