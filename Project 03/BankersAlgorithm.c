// Programmer : Jsako

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int max_p = -1;
int max_r = 1;

struct vector_type {
    
    int resource;
    int available;
    
} *vector = NULL, * resource_vector = NULL, * available_vector = NULL;
typedef struct vector_type type_vector;

struct array_type {
    
    int value;
    
} *array = NULL, ** max_claim = NULL, ** allocation = NULL, ** need = NULL;
typedef struct array_type type_array;

void print_resource_vector() {
    
    printf("\n\tUNITS\tAVAILABLE\n");
    printf("------------------------\n");
    for(int i = 0; i <= max_r; i++) {
        printf("r%d", i);
        printf("\t%d\t%d", resource_vector[i].resource, available_vector[i].available);
        printf("\n");
    }
    return;
    
}

void print_matrix() {
    
    int x = max_r++;
    printf("\n\tMAX CLAIM");
    for(int i = 0; i <= x; i++) {
        printf("\t");
    }
    printf("CURRENT");
    for(int i = 0; i <= x; i++) {
        printf("\t");
    }
    printf("\tPOTENTIAL\n");
    for(int i = 0; i < 3; i++) {
        for(int resource_count = 0; resource_count < max_r; resource_count++) {
            printf("\tr%d", resource_count);
        }
        printf("\t");
    }
    printf("\n--------");
    for(int i = 0; i <= x; i++) {
        printf("------------------------------");
    }
    printf("\n");
    for(int i = 0; i < max_p; i++) {
        printf("p%d", i);
        for(int j = 0; j < max_r; j++) {
            printf("\t%d ", max_claim[i][j].value);
        }
        printf("\t");
        for(int k = 0; k < max_r; k++) {
            printf("\t%d ", allocation[i][k].value);
        }
        printf("\t");
        for(int m = 0; m < max_r; m++) {
            printf("\t%d ", need[i][m].value);
        }
        printf("\n");
    }
    printf("\n");
    return;
    
}

void first_option() {
    
    int r_temp = 0;
	int p_count = 0;
	int r_count = 0;
	printf("ENTER NUMBER OF PROCESSES : ");
	scanf("%d", &max_p);
	do {
	    printf("ENTER NUMBER OF RESOURCES : ");
	    scanf("%d", &max_r);
	} while(max_r <= 0);
	max_r--;
	int* y = (int*)malloc(max_r * sizeof(int));
	if(y == NULL) {
	    printf("\nNO MEMORY IS ALLOCATED FOR ARRAY...\n\n");
	    exit(0);
	}
	for(int i = 0; i <= max_r; i++) {
	    y[i] = 0;
	}
	vector = (type_vector*)malloc(max_r * sizeof(vector));
	array = (type_array*)malloc((max_p * max_r) * sizeof(array));
	resource_vector = (type_vector*)malloc(max_r * sizeof(vector));
	available_vector = (type_vector*)malloc(max_r * sizeof(vector));
	max_claim = (type_array**)malloc((max_p * max_r) * sizeof(array));
	allocation = (type_array**)malloc((max_p * max_r) * sizeof(array));
	need = (type_array**)malloc((max_p * max_r) * sizeof(array));
	resource_vector = (type_vector*)malloc((max_r) * sizeof(vector));
	available_vector = (type_vector*)malloc((max_r) * sizeof(vector));
	if(vector == NULL || resource_vector == NULL || available_vector == NULL) {
	    printf("\nNO MEMORY IS ALLOCATED FOR VECTOR...\n\n");
	    exit(0);
	}
	max_claim = (type_array**)malloc((max_p * max_r) * sizeof(array));
	allocation = (type_array**)malloc((max_p * max_r) * sizeof(array));
	need = (type_array**)malloc((max_p * max_r) * sizeof(array));
	for(int i = 0; i < max_p; i++) {
	    max_claim[i] = (type_array*)malloc(max_r * sizeof(array));
		allocation[i] = (type_array*)malloc(max_r * sizeof(array));
		need[i] = (type_array*)malloc(max_r * sizeof(array));
	}
	if(max_claim == NULL || allocation == NULL || need == NULL) {
	    printf("\nNO MEMORY IS ALLOCATED FOR ARRAY...\n\n");
		exit(0);
	}
	printf("ENTER NUMBER OF UNITS FOR RESOURCES (r0 TO r%d) : ", max_r);
	for(int i = 0; i <= max_r; i++) {
		scanf("%d", &r_temp);
		resource_vector[i].resource = r_temp;
	}
	for(p_count = 0; p_count < max_p; p_count++) {
	    printf("ENTER MAXIMUM NUMBER OF UNITS PROCESS p%d WILL REQUEST FROM EACH RESOURCE (r0 TO r%d) : ", p_count, max_r);
	    for(r_count = 0; r_count <= max_r; r_count++) {
			scanf("%d", &r_temp);
			max_claim[p_count][r_count].value = r_temp;
		}
	}
	for(p_count = 0; p_count < max_p; p_count++) {
		printf("ENTER NUMBER OF UNITS OF EACH RESOURCE (r0 TO r%d) ALLOCATED TO PROCESS p%d : ", max_r, p_count);
		for(r_count = 0; r_count <= max_r; r_count++) {
			scanf("%d", &r_temp);
			allocation[p_count][r_count].value = r_temp;
		}
	}
	for(r_count = 0; r_count <= max_r; r_count++) {
		for(int p_count = 0; p_count < max_p; p_count++) {
			y[r_count] += allocation[p_count][r_count].value;
		}
		if((resource_vector[r_count].resource - y[r_count]) >= 0) {
			available_vector[r_count].available = resource_vector[r_count].resource - y[r_count];
		} else {
			available_vector[r_count].available = 0;
		}
	}
	for(p_count = 0; p_count < max_p; p_count++) {
		for(r_count = 0; r_count <= max_r; r_count++) {
			need[p_count][r_count].value = max_claim[p_count][r_count].value - allocation[p_count][r_count].value;
		}
	}
	print_resource_vector();
	print_matrix();
	return;
    
}

void second_option() {
    
    int n_count = 0;
	int p_count = 0;
	int r_count = 0;
	int max_t = max_p;
	bool u_process = false;
	bool* s_vector = (bool*)malloc(max_p * sizeof(bool));
	int* seq_vector = (int*)malloc(max_p * sizeof(int));
	if(s_vector == NULL || seq_vector == NULL) {
		printf("\nNO MEMORY IS ALLOCATED FOR VECTOR...\n\n");
		exit(0);
	}
	for(int i = 0; i < max_p; i++) {
		s_vector[i] = false;
		seq_vector[i] = -1;
	}
	while(n_count < max_p) {
		for(p_count = 0; p_count < max_p; p_count++) {
			if(!s_vector[p_count]) {
				printf("CHECKING :");
				printf(" <");
				for(r_count = 0; r_count < max_r; r_count++) {
					printf(" %d", need[p_count][r_count].value);
					if(need[p_count][r_count].value > available_vector[r_count].available) {
						u_process = true;
					}
				}
				printf(" > <= <");
				for(r_count = 0; r_count < max_r; r_count++) {
					printf(" %d", available_vector[r_count].available);
				}
				printf(" > :");
				if(u_process) {
					printf("p%d COULD NOT BE SEQUENCED\n", p_count);
					max_t--;
				} else {
					printf("p%d SAFELY SEQUENCED\n", p_count);
					s_vector[p_count] = true;
					seq_vector[n_count] = p_count;
					max_t = (max_p - 1);
					for(r_count = 0; r_count < max_r; r_count++) {
						available_vector[r_count].available += allocation[p_count][r_count].value;
					}
					n_count++;
				}
			}
			u_process = false;
			if(max_t == 0) {
				printf("\nDEADLOCK REACHED!\n");
				return;
			}
		}
	}
	printf("\nSAFE SEQUENCE : ");
	for(p_count = 0; p_count < max_p; p_count++) {
		if((p_count + 1) == max_p) {
		    printf("P%d\n\n", seq_vector[p_count]);
		} else {
		    printf("P%d, ", seq_vector[p_count]);
		}
	}
	return;
    
}

void third_option() {
    
    if(vector != NULL) {
		free(vector);
		vector = NULL;
	}
	if(array != NULL) {
		free(array);
		array = NULL;
	}
	if(resource_vector != NULL) {
		free(resource_vector);
		resource_vector = NULL;
	}
	if(available_vector != NULL) {
		free(available_vector);
		available_vector = NULL;
	}
	if(max_claim != NULL) {
		free(max_claim);
		max_claim = NULL;
	}
	if(allocation != NULL) {
		free(allocation);
		allocation = NULL;
	}
	if(need != NULL) {
		free(need);
		need = NULL;
	}
	return;
    
}

int main() {
    
    int i = 0;
	enum { ONE, TWO, THREE, INVALID } choice;
	while(i != 3) {
		printf("BANKER'S ALGORITHM\n");
		printf("------------------\n");
		printf("(1) ENTER PARAMETERS.\n");
        printf("(2) DETERMINE SAFE SEQUENCE.\n");
        printf("(3) QUIT PROGRAM.\n\n");
        printf("ENTER SELECTION : ");
		scanf("%d", &i);
		if(i == 1) {
		    choice = ONE;
		}
		else if(i == 2) {
		    choice = TWO;
		}
		else if(i == 3) {
		    choice = THREE;
		} else {
		    choice = INVALID;
		}
		switch(choice) {
		case ONE:
			first_option();
			break;
		case TWO:
			second_option();
			break;
		case THREE:
			third_option();
			break;
		case INVALID:
			printf("INVALID CHOICE, TRY AGAIN...\n\n");
		}
	};
	printf("QUITTING PROGRAM...");
	return 1;
    
}
