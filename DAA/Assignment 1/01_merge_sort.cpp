#include <iostream>

using namespace std;

int it = 1;

void merge(int arr[], int l, int mid, int r)
{
    int *temp = new int[r - l + 1];
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r)
    {
        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else if (arr[i] > arr[j])
            temp[k++] = arr[j++];
        else
        {
            temp[k++] = arr[i++];
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= r)
        temp[k++] = arr[j++];
    k = 0;
    for (int i = l; i <= r; i++)
        arr[i] = temp[k++];
}

void mergeSort(int arr[], int l, int r, int n)
{
    if (l < r)
    {
        int mid = l + (r - l) / 2;
        mergeSort(arr, l, mid, n);
        mergeSort(arr, mid + 1, r, n);
        merge(arr, l, mid, r);
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
    mergeSort(arr, 0, n - 1, n);
    cout << "Sorted Array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
    return 0;
}
