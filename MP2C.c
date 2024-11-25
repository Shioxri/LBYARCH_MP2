#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void imgCvtGrayFloatToInt(int row, int col, float* imgArr, int* convertedArr);


void randomValueGenerator(int row, int col, float* imgArr, int sameValue) {
	int i;
    float value = (float)rand() / RAND_MAX;  
    for (i = 0; i < row * col; i++) {
        imgArr[i] = sameValue ? value : (float)rand() / RAND_MAX; 
    }
}


void timeAssemblyFunction(int row, int col, int sameValue) {
	int i;
    float* imgArr = (float*)malloc(row * col * sizeof(float));
    int* convertedArr = (int*)malloc(row * col * sizeof(int));
    if (!imgArr || !convertedArr) {
        printf("Memory allocation failed.\n");
        return;
    }

    
    randomValueGenerator(row, col, imgArr, sameValue);

    clock_t start, end;
    double time_used;



    start = clock();
    for (i = 0; i < 30; i++) {
        imgCvtGrayFloatToInt(row, col, imgArr, convertedArr);  
    }
    end = clock();


    time_used = ((double)(end - start)) / CLOCKS_PER_SEC / 30.0;
    printf("Average execution time for %dx%d: %f seconds\n", row, col, time_used);

    free(imgArr);
    free(convertedArr);
}


void manualInputMode() {
    int row, col;
	int i;
	int j;
    	
    printf("Input Row size: ");
    scanf("%d", &row);
    printf("Input Column size: ");
    scanf("%d", &col);

    float* imgArr = (float*)malloc(row * col * sizeof(float));
    int* convertedArr = (int*)malloc(row * col * sizeof(int));

    if (!imgArr || !convertedArr) {
        printf("Memory allocation failed.\n");
        return;
    }
    

    printf("Input Array Values:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            scanf("%f", &imgArr[i * col + j]);
        }
    }

    imgCvtGrayFloatToInt(row, col, imgArr, convertedArr);

    printf("The converted array is:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", convertedArr[i * col + j]);
        }
        printf("\n");
    }

    free(imgArr);
    free(convertedArr);
}


void timedTestingMode() {
    int sizes[3][2] = {{10, 10}, {100, 100}, {1000, 1000}};
    int sameValue;
	int i;
    printf("\nSelect pixel value mode:\n");
    printf("1. All pixels have the same value\n");
    printf("2. All pixels have different values\n");
    printf("Enter your choice: ");
    scanf("%d", &sameValue);

    sameValue = (sameValue == 1) ? 1 : 0;  
	printf("\nAverage time for 30 Runs:\n");
    for (i = 0; i < 3; i++) {
        int row = sizes[i][0];
        int col = sizes[i][1];
        timeAssemblyFunction(row, col, sameValue);
    }
}


int main() {
    int mode;
    char continueChoice;

    do {
        printf("Select mode:\n");
        printf("1. Manual Input Mode\n");
        printf("2. Timed Testing Mode\n");
        printf("Enter your choice: ");
        scanf("%d", &mode);

        if (mode == 1) {
            manualInputMode();
        } else if (mode == 2) {
            timedTestingMode();
        } else {
            printf("Invalid choice. Please try again.\n");
        }

        printf("Enter y/Y to continue, enter any other key to exit: ");
        scanf(" %c", &continueChoice);
    } while (continueChoice == 'y' || continueChoice == 'Y');

    printf("Exiting program. Goodbye!\n");
    return 0;
}

