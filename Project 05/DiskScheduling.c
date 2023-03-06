// Programmer : Jsako



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>



int s_size = 0;



struct arrayType {
    
    int val;
    bool v;
    
} **array_t = NULL, ** array_s = NULL, ** s_array = NULL, ** cs_array = NULL;



typedef struct arrayType t_array;



int countDistance(struct arrayType** c_array) {
    
    int t_distance = 0;
    int distance_t = 0;
    if(s_size == 1) {
        distance_t = 0;
    } else {
        for(int i = 0; i < s_size; i++) {
            if((i + 1) != s_size) {
                t_distance = abs(c_array[i]->val - c_array[i + 1]->val);
                distance_t += t_distance;
            }
        }
    }
    
    return distance_t;
    
}



struct arrayType** scanDirection(struct arrayType** s_array, bool direction) {
    
    int t_distance = 0;
    int t_value = 0;
    int sti = 0;
    int tti = 0;
    enum {decreasing, increasing} i_direction;
    i_direction = direction;
    s_array[0]->v = true;
    if(i_direction == decreasing) {
        printf("\nDECREASING ALGORITHM STARTING\n");
        for(int i = 0; i < s_size; i++) {
            for(int k = 0; k < s_size; k++) {
                if(k != (s_size - 1)) {
                    if(s_array[k]->val > s_array[k + 1]->val) {
                        if(s_array[k]->v) {
                            s_array[k + 1]->v = true;
                            s_array[k]->v = false;
                        }
                        t_value = s_array[k]->val;
                        s_array[k]->val = s_array[k + 1]->val;
                        s_array[k + 1]->val = t_value;
                    }
                }
            }
        }
    }
    else if(i_direction == increasing) {
        for(int i = 0; i < s_size; i++) {
            for(int k = 0; k < s_size; k++) {
                if(k != (s_size - 1)) {
                    if(s_array[k]->val < s_array[k + 1]->val) {
                        if(s_array[k]->v) {
                            s_array[k + 1]->v = true;
                            s_array[k]->v = false;
                        }
                        t_value = s_array[k]->val;
                        s_array[k]->val = s_array[k + 1]->val;
                        s_array[k + 1]->val = t_value;
                    }
                }
            }
        }
    }
    for(int n = 0; n < s_size; n++) {
        if(s_array[n]->v) {
            sti = n;
            tti = sti;
        }
    }
    t_value = s_array[sti]->val;
    s_array[sti]->val = s_array[0]->val;
    s_array[0]->val = t_value;
    tti = sti;
    return s_array;
    
}



struct arrayType** cScan(struct arrayType** cs_array) {
    
    int t_distance = 0;
    int t_value = 0;
    int sti = 0;
    int tti = 0;
    cs_array[0]->v = true;
    for(int i = 0; i < s_size; i++) {
        for(int k = 0; k < s_size; k++) {
            if(k != (s_size - 1)) {
                if(cs_array[k]->val < cs_array[k + 1]->val) {
                    if(cs_array[k]->v) {
                        cs_array[k + 1]->v = true;
                        cs_array[k]->v = false;
                    }
                    t_value = cs_array[k]->val;
                    cs_array[k]->val = cs_array[k + 1]->val;
                    cs_array[k + 1]->val = t_value;
                }
            }
        }
    }
    for(int n = 0; n < s_size; n++) {
        if(cs_array[n]->v) {
            sti = n;
            tti = sti;
        }
    }
    t_value = cs_array[sti]->val;
    cs_array[sti]->val = cs_array[0]->val;
    cs_array[0]->val = t_value;
    tti = sti;
    for(int m = sti; m < s_size; m++) {
        for(int k = (m + 1); k < s_size; k++) {
            if(k != (s_size - 1)) {
                if(cs_array[k]->val > cs_array[k + 1]->val) {
                    t_value = cs_array[k]->val;
                    cs_array[k]->val = cs_array[k + 1]->val;
                    cs_array[k + 1]->val = t_value;
                }
            }
        }
    }
    
    return cs_array;
    
}



void firstOption() {
    
    int t;
    int st;
    printf("ENTER SIZE OF SEQUENCE : ");
    scanf("%d", &s_size);
    do {
        if(s_size <= 0) {
            printf("\nSEQUENCE SIZE MUST BE GREATER THAN ZERO...\n");
            printf("ENTER SIZE OF SEQUENCE : ");
            scanf("%d", &s_size);
        }
    } while(s_size < 0);
    array_t = (t_array**)malloc(s_size * sizeof(array_t));
    for(int i = 0; i < s_size; i++) {
        array_t[i] = (t_array*)malloc(s_size * sizeof(array_t));
        array_t[i]->v = false;
    }
    if(array_t == NULL) {
        printf("\nNOT ENOUGH MEMORY, EXITTING PROGRAM...\n\n");
        exit(0);
    }
    printf("ENTER STARTING TRACK : ");
    scanf("%d", &st);
    do {
        if(st <= 0) {
            printf("\nSEQUENCE SIZE MUST BE GREATER THAN ZERO...\n");
            printf("ENTER STARTING TRACK : ");
            scanf("%d", &st);
        }
    } while(st <= 0);
    array_t[0]->val = st;
    if(s_size >= 2) {
        printf("ENTER SEQUENCE OF TRACKS TO SEEK : ");
        for(int i = 1; i <= (s_size - 1); i++) {
            do {
                scanf("%d", &t);
                if(t < 0) {
                    printf("\nTRACK CANNOT BE A NEGATIVE NUMBER...\n");
                    printf("ENTER SEQUENCE OF TRACKS TO SEEK : ");
                    i = 1;
                    scanf("%d", &t);
                }
            } while(t < 0);
            array_t[i]->val = t;
        }
    }
    if(s_size == 1) {
        printf("\n");
    }
    printf("\n");
    return;
    
}



void secondOption() {
    
    int distance_t = 0;
    int t_distance = 0;
    if(s_size == 1) {
        distance_t = 0;
    } else {
        distance_t = countDistance(array_t);
    }
    printf("TRAVERSED SEQUENCE : ");
    for(int j = 0; j < s_size; j++) {
        printf("%d ", array_t[j]->val);
    }
    printf("\nTHE DISTANCE OF THE TRAVERSED TRACKS IS : %d\n\n", distance_t);
    return;
    
}



void thirdOption() {
    
    int t_distance = 0;
    int distance_t = 0;
    int s_distance = INT_MAX;
    int s_index = 0;
    array_s = (t_array**)malloc(s_size * sizeof(array_s));
    for(int i = 0; i < s_size; i++) {
        array_s[i] = (t_array*)malloc(s_size * sizeof(array_s));
    }
    if(array_s == NULL) {
        printf("\nNOT ENOUGH MEMORY, EXITTING PROGRAM...\n\n");
        exit(0);
    }
    array_s[0]->val = array_t[0]->val;
    array_t[0]->v = true;
    for(int i = 0; i < s_size; i++) {
        if(i != 0) {
            array_s[i]->val = array_t[s_index]->val;
            array_t[s_index]->v = true;
            s_distance = INT_MAX;
        }
        for(int j = 1; j < s_size; j++) {
            if(!array_t[j]->v) {
                t_distance = abs(array_s[i]->val - array_t[j]->val);
                if(s_distance > t_distance) {
                    s_distance = t_distance;
                    s_index = j;
                }
            }
        }
    }
    printf("TRAVERSED SEQUENCE : ");
    for(int j = 0; j < s_size; j++) {
        printf("%d ", array_s[j]->val);
    }
    distance_t = countDistance(array_s);
    printf("\nTHE DISTANCE OF THE TRAVERSED TRACKS IS : %d\n\n", distance_t);
    for(int k = 0; k < s_size; k++) {
        array_t[k]->v = false;
    }
    
    return;
    
}



void fourthOption() {
    
    int distance_t = 0;
    int i_direction = 0;
    s_array = (t_array**)malloc(s_size * sizeof(s_array));
    for(int i = 0; i < s_size; i++) {
        s_array[i] = (t_array*)malloc(s_size * sizeof(s_array));
        s_array[i]->val = array_t[i]->val;
        s_array[i]->v = false;
    }
    if(s_array == NULL) {
        printf("\nNOT ENOUGH MEMORY, EXITTING PROGRAM...\n\n");
        exit(0);
    }
    printf("ENTER INITIAL DIRECTION ( 0 = DECREASING , 1 = INCREASING ) : ");
    scanf("%d", &i_direction);
    do {
        if(i_direction > 1 || i_direction < 0) {
            printf("\nINITIAL DIRECTION MUST BE 0 FOR DECREASING OR 1 FOR INCREASING...\n");
            printf("\nENTER INITIAL DIRECTION ( 0 = DECREASING , 1 = INCREASING ) : ");
            scanf("%d", &i_direction);
        }
    } while(i_direction > 1 || i_direction < 0);
    s_array = scanDirection(s_array, i_direction);
    distance_t = countDistance(s_array);
    printf("TRAVERSED SEQUENCE : ");
    for(int j = 0; j < s_size; j++) {
        printf("%d ", s_array[j]->val);
    }
    printf("\nTHE DISTANCE OF THE TRAVERSED TRACKS IS : %d\n\n", distance_t);
    return;
    
}



void fifthOption() {
    
    int distance_t = 0;
    int i_direction = 0;
    cs_array = (t_array**)malloc(s_size * sizeof(cs_array));
    for(int i = 0; i < s_size; i++) {
        cs_array[i] = (t_array*)malloc(s_size * sizeof(cs_array));
        cs_array[i]->val = array_t[i]->val;
        cs_array[i]->v = false;
    }
    if(cs_array == NULL) {
        printf("\nNOT ENOUGH MEMORY, EXITTING PROGRAM...\n\n");
        exit(0);
    }
    cs_array = cScan(cs_array);
    distance_t = countDistance(cs_array);
    printf("TRAVERSED SEQUENCE : ");
    for(int j = 0; j < s_size; j++) {
        printf("%d ", cs_array[j]->val);
    }
    printf("\nTHE DISTANCE OF THE TRAVERSED TRACKS IS : %d\n\n", distance_t);
    return;
    
}



void sixthOption() {
    
    if(array_t == NULL) {
        return;
    } else {
        free(array_t);
        if(array_s != NULL) {
            free(array_s);
        }
        if(s_array != NULL) {
            free(s_array);
        }
        if(cs_array != NULL) {
            free(cs_array);
        }
    }
    
    return;
    
}



int main() {
    
    int c = 0;
    enum {first, second, third, fourth, fifth, sixth, invalid} menu_c;
    while(c != 6) {
        printf("DISK SCHEDULING\n");
        printf("---------------\n");
        printf("(1) ENTER PARAMETERS.\n");
        printf("(2) CALCULATE DISTANCE TO TRAVERSE TRACKS USING FIFO.\n");
        printf("(3) CALCULATE DISTANCE TO TRAVERSE TRACKS USING SSTF.\n");
        printf("(4) CALCULATE DISTANCE TO TRAVERSE TRACKS USING SCAN.\n");
        printf("(5) CALCULATE DISTANCE TO TRAVERSE TRACKS USING C-SCAN.\n");
        printf("(6) QUIT PROGRAM AND FREE MEMORY.\n\n");
        printf("ENTER SELECTION : ");
        scanf("%d", &c);
        if(c == 1) {
            menu_c = first;
        }
        else if(c == 2) {
            menu_c = second;
        }
        else if(c == 3) {
            menu_c = third;
        }
        else if(c == 4) {
            menu_c = fourth;
        }
        else if(c == 5) {
            menu_c = fifth;
        }
        else if(c == 6) {
            menu_c = sixth;
        } else {
            menu_c = invalid;
        }
        switch(menu_c) {
            case first:
                firstOption();
                break;
            case second:
                secondOption();
                break;
            case third:
                thirdOption();
                break;
            case fourth:
                fourthOption();
                break;
            case fifth:
                fifthOption();
                break;
            case sixth:
                sixthOption();
                printf("QUITTING PROGRAM...");
                break;
            case invalid:
                printf("INVALID CHOICE, PLEASE TRY AGAIN...\n\n");
        }
    };
    
    return 1;

}
