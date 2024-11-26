#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void imgCvtGrayFloatToInt(int row, int col, float* imgArr, int* convertedArr);


void timeAssemblyFunction(int row, int col, int sameValue, float value) {
    int i;
    float* imgArr = (float*)malloc(row * col * sizeof(float));
    int* convertedArr = (int*)malloc(row * col * sizeof(int));
    if (!imgArr || !convertedArr) {
        printf("Memory allocation failed.\n");
        return;
    }

    for (i = 0; i < row * col; i++) {
        imgArr[i] = (sameValue == 1) ? value : (float)rand() / RAND_MAX;
    }

    struct timespec start, end;
    long total_time_ns = 0;

    for (i = 0; i < 30; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        imgCvtGrayFloatToInt(row, col, imgArr, convertedArr);  
        clock_gettime(CLOCK_MONOTONIC, &end);

        
        long elapsed_ns = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
        total_time_ns += elapsed_ns;
    }

    double average_time_ns = (double)total_time_ns / 30.0;
    printf("Average execution time for %dx%d: %.4f nanoseconds\n", row, col, average_time_ns);

    free(imgArr);
    free(convertedArr);
}

void manualInputMode() {
    int row, col;
    int i, j;
    float value;
    char input[100];

    do {
        printf("Input Row size: ");
        fgets(input, sizeof(input), stdin); 

        if (sscanf(input, "%d", &row) != 1 || row <= 0) {
            printf("Invalid input! Please enter a positive integer for row size.\n");
        } else {
            break;
        }
    } while (1);  
    do {
        printf("Input Column size: ");
        fgets(input, sizeof(input), stdin); 
        if (sscanf(input, "%d", &col) != 1 || col <= 0) {
            printf("Invalid input! Please enter a positive integer for column size.\n");
        } else {
            break;
        }
    } while (1); 
	
    float* imgArr = (float*)malloc(row * col * sizeof(float));
    int* convertedArr = (int*)malloc(row * col * sizeof(int));

    if (!imgArr || !convertedArr) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Input Array Values (each value must be between 0 and 1):\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            do {
			    printf("Enter value for (R%d, C%d): ", i + 1, j + 1);
			
			    if (fgets(input, sizeof(input), stdin) == NULL) {
			        printf("Error reading input. Please try again.\n");
			        continue;
			    }

			    int result = sscanf(input, "%f", &value);
			
			    if (result != 1) {
			        printf("Invalid input! Please enter a valid number.\n");
			        continue;  
			    }
			
			    if (value < 0.0 || value > 1.0) {
			        printf("Invalid input! Value must be between 0 and 1.\n");
			    }

			} while (value < 0.0 || value > 1.0);  

            imgArr[i * col + j] = value;
        }
    }

    imgCvtGrayFloatToInt(row, col, imgArr, convertedArr);

    printf("\nThe converted array:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", convertedArr[i * col + j]);
        }
        printf("\n");
    }
    printf("\n");

    free(imgArr);
    free(convertedArr);
}


void timedTestingMode() {
    int sizes[3][2] = {{10, 10}, {100, 100}, {1000, 1000}};
    int sameValue;
	int i;
	char input[100];
	float value = (float)rand() / RAND_MAX;  

        printf("\nSelect pixel value mode:\n");
        printf("1. All pixels have the same value\n");
        printf("2. All pixels have different values\n");
    do {
        printf("Enter your choice: ");
        fgets(input, sizeof(input), stdin); 

        if (sscanf(input, "%d", &sameValue) != 1 || (sameValue != 1 && sameValue != 2)) {
            printf("Invalid choice! Please enter 1 or 2.\n");
        } else {
            break;
        }
    } while (1);  
	
    sameValue = (sameValue == 1) ? 1 : 0;  	
    
    if (sameValue == 1) {
    	printf("\nValue Used: %.4f", value);
	}

	printf("\nAverage time for 30 Runs:\n");
    for (i = 0; i < 3; i++) {
        int row = sizes[i][0];
        int col = sizes[i][1];
        timeAssemblyFunction(row, col, sameValue, value);
    }
    printf("\n");
}


int main() {
    int mode;
    char continueChoice;

    do {
        printf("\nSelect mode:\n");
        printf("1. Manual Input Mode\n");
        printf("2. Timed Testing Mode\n");
        printf("3. Exit Program\n");
        printf("Enter your choice: ");
        scanf("%d", &mode);
        while ((getchar()) != '\n');

        if (mode == 1) {
            manualInputMode();
        } else if (mode == 2) {
            timedTestingMode();
        } else if (mode == 3) {
            printf("Exiting program. Goodbye!\n");
            return 0;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
        	
	
        printf("Enter y/Y to continue, enter any other key to exit: ");
        scanf(" %c", &continueChoice); 
		while ((getchar()) != '\n'); 
    } while (continueChoice == 'y' || continueChoice == 'Y');

    printf("Exiting program. Goodbye!\n");
    return 0;
}


