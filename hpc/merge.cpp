// Parallel Merge Sort using OpenMP
// Compile: g++ -fopenmp 1_dfs.cpp -o output
// Run:     ./output

#include <iostream>
#include <omp.h>
using namespace std;

/* Merge two sorted parts */
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

/* Parallel Merge Sort */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(arr, l, m);

            #pragma omp section
            mergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    int *arr = new int[n];

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    double start = omp_get_wtime();

    mergeSort(arr, 0, n - 1);

    double stop = omp_get_wtime();

    cout << "\nSorted array:\n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\nExecution time: " << stop - start << " seconds\n";

    delete[] arr;
    return 0;}
