// Parallel Bubble Sort using OpenMP
// Compile: g++ -fopenmp 1_dfs.cpp -o output
// Run:     ./output

#include <iostream>
#include <omp.h>

using namespace std;

/* Swap function */
void swapValues(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

/* Parallel Bubble Sort (Odd-Even Transposition Sort) */
void bubble(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        /* Even phase */
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2)
        {
            if (a[j] > a[j + 1])
                swapValues(a[j], a[j + 1]);
        }

        /* Odd phase */
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2)
        {
            if (a[j] > a[j + 1])
                swapValues(a[j], a[j + 1]);
        }
    }
}

int main()
{
    int n;

    cout << "Enter total number of elements: ";
    cin >> n;

    int *a = new int[n];

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    bubble(a, n);

    cout << "\nSorted array:\n";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    cout << endl;

    delete[] a;
    return 0;
}
