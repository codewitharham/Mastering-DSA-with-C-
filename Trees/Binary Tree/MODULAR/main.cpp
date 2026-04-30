#include <iostream>
using namespace std;
#include <array>



int* Merge(int* left, int* right, int start, int mid, int end) {
    int* mergedArray = new int[end - start + 1]();
    
    int i = 0;
    int j = 0;
    int k = 0;

    int leftSize = mid - start + 1;
    int rightSize = end - mid;
    
    while ( i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            mergedArray[k] = left[i];
            i = i + 1;
            k = k + 1;
            
        } else {
            mergedArray[k] = right[j];
            j = j + 1;
            k = k + 1;
        };
    };

    while (i < leftSize) {
        mergedArray[k] = left[i];
        i = i + 1;
        k = k + 1;
    };

    while (j < rightSize) {
        mergedArray[k] = right[j];
        j = j + 1;
        k = k + 1;
    };
    return mergedArray;
};


int* MergeSort(int arr[], int start, int end) {
    // Base case: If the array has one or zero elements, it's already sorted
    if (start >= end) {
        int* singleElementArray = new int[1]();
        singleElementArray[0] = arr[start];
        return singleElementArray;
    };
    long int mid = start + end / 2;
    int* leftSorted = MergeSort(arr, start, mid);
    int* rightSorted = MergeSort(arr, mid + 1, end);
    int* mergedArray = Merge(leftSorted, rightSorted, start, mid, end);
    delete[] leftSorted; // Free the dynamically allocated memory for left sorted array
    delete[] rightSorted; // Free the dynamically allocated memory for right sorted array
    return mergedArray;

        
};

void PrintArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    };
    cout << endl;
};

int main(){

    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    cout << "Original array: ";
    PrintArray(arr, size);
    
    int* sortedArray = MergeSort(arr, 0, size - 1);
    
    cout << "Sorted array: ";
    PrintArray(sortedArray, size);
    
    delete[] sortedArray; // Free the dynamically allocated memory
    return 0;
   
    
};

