#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	
	FILE *fptr;
	const int numQueries = 129;
	long arr[numQueries];
	int i, tmp = 0;
	
	fptr = fopen("inputs/2.txt", "r");
	
	if (fptr == NULL){
		printf("Cannot open file \n");
        exit(0);
	}
	
	for (i; i<numQueries; i++){
		fscanf(fptr, "%li,", &arr[i]);
	}
	
	arr[1] = atoi(argv[1]);		// adding input
	arr[2] = atoi(argv[2]);
	
	for (i=0; i<numQueries; i++){
		switch (arr[i]){
			case 1:
				tmp = arr[ arr[i+1]] + arr[ arr[i+2]];
				arr[ arr[i+3]] = tmp;
				i +=3;
				break;
				
			case 2:
				tmp = arr[ arr[i+1]]*arr[ arr[i+2]];
				arr[ arr[i+3]] = tmp;
				i +=3;
				break;
				
			case 99:
				//if (arr[0] == 19690720)
					printf("%li : %li\n", arr[0],100*atoi(argv[1]) + atoi(argv[2]));
				return 0;
			default :
				printf("Smth went wrong.\n");

		}
		
	}
	fclose(fptr);

}