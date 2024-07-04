#include <stdio.h>
#include <stdlib.h>

// Function to compare intervals based on their finish times
int compareIntervals(const void *a, const void *b) {
    return ((int*)a)[1] - ((int*)b)[1];
}
int findmin(int intervals[][2],int n){
    int min=0;
    for (int i=0;i<n;i++){
        if (intervals[min][1]>intervals[i][1]){
            min=i;
        }
    }
    return min;
}

// Function to find the maximum subset of non-overlapping intervals
void printMaxNonOverlapIntervals(int intervals[][2], int n, FILE *output) {
    // Array to store selected intervals
    int selectedIntervals[n][2];
    int selectedCount = 0;
    int min;
    // Write the logic for the function here
    if (n>0){
        min=findmin(intervals,n);
        selectedIntervals[0][0]=intervals[min][0];
        selectedIntervals[0][1]=intervals[min][1];
        intervals[min][1]=1e8;
        selectedCount++;
    }
    for (int i=1;i<n;i++){
        min=findmin(intervals,n);
        if (intervals[min][0]>selectedIntervals[selectedCount-1][1]){
            selectedIntervals[selectedCount][0]=intervals[min][0];
            selectedIntervals[selectedCount][1]=intervals[min][1];
            selectedCount++;
        }
        intervals[min][1]=1e8;
    }
    // Print selected intervals to the output file
    for (int k = 0; k < selectedCount; k++) {
        fprintf(output, "(%d, %d) ", selectedIntervals[k][0], selectedIntervals[k][1]);
    }
}

// Function to read intervals from input file and call the function to find max non-overlapping intervals
void processIntervalsFromFile(const char *inputFileName, const char *outputFileName) {
    FILE *input = fopen(inputFileName, "r");
    FILE *output = fopen(outputFileName, "w");

    if (input == NULL || output == NULL) {
        fprintf(stderr, "Error: Unable to open files.\n");
        exit(1);
    }

    int n;
    fscanf(input, "%d", &n); // Read the number of intervals
    int intervals[n][2]; // Declare array to store intervals

    // Read intervals from input file
    for (int i = 0; i < n; i++) {
        fscanf(input, "%d %d", &intervals[i][0], &intervals[i][1]);
    }

    // Find and print maximum subset of non-overlapping intervals
    printMaxNonOverlapIntervals(intervals, n, output);

    fclose(input);
    fclose(output);
}

int main() {
    processIntervalsFromFile("MaxInterval_input.txt", "output.txt");
    printf("Output saved in 'output_1.txt'.\n");

    return 0;
}
