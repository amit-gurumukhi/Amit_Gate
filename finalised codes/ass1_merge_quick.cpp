#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
static int count=0;
static int count1=0;
// QuickSort implementation
int partition(int arr[], int start, int end){
    int pivot = arr[start];
    int i=start;
    int j=end+1;
    count+=3;
    do{
        do{
            i++;
            count+=2;
        }while(arr[i]<pivot);
        
        do{
            j--;
            count+=2;
        }while(arr[j]>pivot);
        count+=4;
        if(i<j){
        int temp=arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
        }
        count++;
    }while(i<j);
    count+=3;
    arr[start]=arr[j];
    arr[j]=pivot;
    return j;
}


void quickSort(int arr[], int start, int end){
    count++;
    if(start<end){
        int p= partition(arr,start,end);
        count++;
        quickSort(arr,start,p-1);
        quickSort(arr,p+1,end);
    }
    count++;
    return;
}

// MergeSort implementation
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];
    count1+=4;
    count1++; //for initialization.

    for (i = 0; i < n1; i++){
        L[i] = arr[l + i];
        count+=3;
    }
    for (j = 0; j < n2; j++){
        R[j] = arr[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    count1++;
    if (l < r) {
        int m = l + (r - l) / 2;
        count1++;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main() {
    int arr[1000];

    for (int i = 0; i < 1000; i++) {
        arr[i] = rand() % 1000;
    }

    auto start = chrono::high_resolution_clock::now();
    quickSort(arr, 0, 999);
    auto end = chrono::high_resolution_clock::now();

    cout << "QuickSort execution time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    cout << "QuickSort execution time: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " nanoseconds" << endl;



    for (int i = 0; i < 1000; i++) {
        arr[i] = rand() % 1000;
    }

    auto start_merge=chrono::high_resolution_clock::now();
    mergeSort(arr, 0, 999);
    auto merge_stop=chrono::high_resolution_clock::now();

    cout << "mergeSort execution time: " << chrono::duration_cast<chrono::microseconds>(merge_stop - start_merge).count() << " microseconds" << endl;

    cout << "mergeSort execution time: " << chrono::duration_cast<chrono::nanoseconds>(merge_stop - start_merge).count() << " nanoseconds" << endl;

    cout<<"count for quicksort is: "<<count << endl;
    cout<<"count for mergesort is: "<< count1;


    return 0;
}