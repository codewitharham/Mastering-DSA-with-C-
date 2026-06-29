#include <iostream>
using namespace std;

void QuickSort(int arr[], int low, int high) {
    int start = low;
    int end = high;
    

    int pivotValue = arr[(start + end) / 2]; 

    // Partitioning phase
    while (start <= end) {
        // Change '<' to '>' if you explicitly want descending order
        while (arr[start] < pivotValue) { 
            start++;
        }

        // Change '>' to '<' if you explicitly want descending order
        while (arr[end] > pivotValue) {
            end--;
        }

        if (start <= end) {
            int temp = arr[end];
            arr[end] = arr[start];
            arr[start] = temp;

            start++;
            end--;
        }
    } 

    // Recursive call for Left Part
    if (low < end) {
        QuickSort(arr, low, end);
    }

    // Recursive call for Right Part
    if (high > start) {
        QuickSort(arr, start, high);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr1[6] = {9, -3, 5, 2, 6, 1}; 

    cout << "Before QuickSort: ";
    printArray(arr1, 6);

    QuickSort(arr1, 0, 5);

    cout << "After QuickSort:  ";
    printArray(arr1, 6);

    return 0;
}