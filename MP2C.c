#include <stdio.h>
#include <stdlib.h>

extern void imgCvtGrayFloatToInt(int row, int col, float* imgArr, int* convertedArr);

int main() {
    int row, col;
    int i, j;

    printf("Input Row size: ");
    scanf("%d", &row);
    printf("Input Column size: ");
    scanf("%d", &col);


    float* imgArr = (float*)malloc(row * col * sizeof(float));
    int* convertedArr = (int*)malloc(row * col * sizeof(int));
    
    if (!imgArr || !convertedArr) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Input Array Values:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            scanf("%f", &imgArr[i * col + j]);  
        }
    }


    imgCvtGrayFloatToInt(row, col, imgArr, convertedArr);
    
    printf("The converted values:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", convertedArr[i * col + j]);  
        }
        printf("\n");
    }


    free(imgArr);
    free(convertedArr);

    return 0;
}

