#include <iostream>
#include <stdio.h>
using namespace std;



int* merge(int* first, int* second, int Lsize, int Rsize){

    int mixSize = Lsize + Rsize;
    int* mixArray = new int[mixSize];

    int i = 0;
    int j = 0;
    int k = 0;  

    while(i < Lsize  && j < Rsize){

        if(first[i] < second[j]){
            mixArray[k] = first[i];
            i++;            
        }else{
            mixArray[k] = second[j];
            j++;
        }

        k++;
    }

    while(i < Lsize){
        mixArray[k] = first[i];
        k++;
        i++;
    }

    while(j < Rsize){
        mixArray[k] = second[j];
        k++;
        j++;

    }



    return mixArray;

    

}

int* mergeSort(int* arr, int size, int start, int end){

    int mid = (start+end)/2;

    if(start == end){
        int* SingleElement = new int[1];
        SingleElement[0] = arr[start];
        return SingleElement;
    }

    int* LeftPart = mergeSort(arr, size, start, mid );
    int* RightPart = mergeSort(arr, size, mid+1, end);

    int LeftPartSize = (mid - start) + 1;
    int RightPartSize = (end - (mid+1)) + 1;

    int* mergeLeftRight = merge(LeftPart, RightPart, LeftPartSize, RightPartSize);

    delete[] LeftPart;
    delete[] RightPart;

    return mergeLeftRight;

};

void printArray(int* arr, int size){
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    
    cout << endl;
}


int main(){

    int arr1[6] = {8,4,3, 9, 20, 19};
    int arr2[5] = {8,5,4,3,1};

    int arr1_size = sizeof(arr1)/sizeof(arr1[0]);
    int arr2_size = sizeof(arr2)/sizeof(arr2[0]);

    int* sorted_arr1 = mergeSort(arr1, arr1_size, 0, arr1_size - 1);
    int* sorted_arr2 = mergeSort(arr2, arr2_size, 0, arr2_size - 1);

    cout << "arr1: " << endl;
    printArray(sorted_arr1, arr1_size);

    cout << "arr2:" << endl;
    printArray(sorted_arr2, arr2_size);


    return 0;
}