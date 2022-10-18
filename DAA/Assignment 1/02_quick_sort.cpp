#include <iostream>

using namespace std;

int it = 1;

int partition(int arr[], int l, int h)
{
    int pivot = arr[h];
    int i = l - 1;
    for (int j = l; j <= h - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[h]);
    return i + 1;
}

void quickSort(int arr[], int l, int h, int n)
{
    if (l < h)
    {
        int pi = partition(arr, l, h);
        quickSort(arr, l, pi - 1, n);
        quickSort(arr, pi + 1, h, n);
        cout << "Iteration: " << it++ << ": ";
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << "\n";
    }
}

int main()
{
    cout << "Enter no of elements: ";
    int n;
    cin >> n;
    int arr[n];
    cout << "Array: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    quickSort(arr, 0, n - 1, n);
    cout << "Sorted Array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
    return 0;
}
