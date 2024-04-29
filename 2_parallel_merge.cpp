#include <iostream>
#include <omp.h>
using namespace std;

void merge(int arr[], int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int left[n1];
    int right[n2];

    for (int i = 0; i < n1; i++)
    {
        left[i] = arr[low + i];
    }

    for (int j = 0; j < n2; j++)
    {
        right[j] = arr[mid + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = low;
    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void parallelMergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, low, mid);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, high);
            }
        }
        merge(arr, low, mid, high);
    }
}


int main()
{
    const int size = 20000;
    int arr[size];

    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100;
    }
    
    double start_time;
    double end_time;

    start_time = omp_get_wtime(); 
    mergeSort(arr, 0, size - 1);
    end_time = omp_get_wtime(); 
    cout << "Time taken by sequential algorithm: " << end_time - start_time << " seconds\n";


    // start_time = omp_get_wtime(); 
    
    // end_time = omp_get_wtime(); 
    // cout << "Time taken by parallel algorithm: " << end_time - start_time << " seconds\n";


    start_time = omp_get_wtime(); 
    #pragma omp parallel
    {
        mergeSort(arr, 0, size - 1);
    }
    end_time = omp_get_wtime(); 

    cout << "Time taken by parallel algorithm: " << end_time - start_time << " seconds\n";
}