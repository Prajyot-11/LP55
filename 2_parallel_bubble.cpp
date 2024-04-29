#include <iostream>
#include <omp.h>
using namespace std;

void bSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void bpSort(int arr[], int size)
{
    bool swapp = true;
#pragma opm parallel
    {
        while (swapp)
        {
            swapp = false;
            for (int i = 0; i < size - 1; i++)
            {
                if (arr[i] > arr[i + 1])
                {
                    swap(arr[i], arr[i + 1]);
                    swapp = true;
                }
            }
        }
    }
}

int main()
{
    const int size = 10000;
    int arr[size];
    for (int i = 0; i < size; ++i)
    {
        arr[i] = rand() % 100;
    }

    double start_time;
    double end_time;

    start_time = omp_get_wtime();
    bSort(arr, size);
    end_time = omp_get_wtime();

    cout << "The time for sequential bSort is :" << end_time - start_time << endl;

    for (int i = 0; i < size; ++i)
    {
        arr[i] = rand() % 100;
    }

    start_time = omp_get_wtime();
#pragma omp parallel
    {
        bpSort(arr, size);
    }
    end_time = omp_get_wtime();

    cout << "The time for parallel bubble Sort is :" << end_time - start_time << endl;
}