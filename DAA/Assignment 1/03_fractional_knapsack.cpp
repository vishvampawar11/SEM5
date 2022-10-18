#include <iostream>

using namespace std;

struct item
{
    double weight;
    double price;
    double ratio;
    double selectedFraction = 0;
};

void merge(item arr[], int l, int mid, int r)
{
    item *temp = new item[r - l + 1];
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r)
    {
        if (arr[i].ratio > arr[j].ratio)
            temp[k++] = arr[i++];
        else if (arr[i].ratio < arr[j].ratio)
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

void mergeSort(item arr[], int l, int r, int n)
{
    if (l < r)
    {
        int mid = l + (r - l) / 2;
        mergeSort(arr, l, mid, n);
        mergeSort(arr, mid + 1, r, n);
        merge(arr, l, mid, r);
    }
}

double solve(item arr[], int n, int W)
{
    double ans = 0;
    mergeSort(arr, 0, n - 1, n);
    int i = 0;
    while (W > 0 && i < n)
    {
        if (arr[i].weight <= W)
        {
            ans += arr[i].price;
            W -= arr[i].weight;
            arr[i].selectedFraction = 1;
        }
        else
        {
            double r = arr[i].price / arr[i].weight;
            ans += r * (double)W;
            arr[i].selectedFraction = (double)W / arr[i].weight;
            W = 0;
        }
        i++;
    }
    return ans;
}

int main()
{
    cout << "Enter weight of the bag: ";
    int W;
    cin >> W;
    cout << "Enter no of items: ";
    int n;
    cin >> n;
    item arr[n];
    cout << "Enter weight and profit for each item\n";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].weight;
        cin >> arr[i].price;
        arr[i].ratio = arr[i].price / arr[i].weight;
    }

    double ans = solve(arr, n, W);

    cout << "Items you entered\n";
    cout << "--------------------------------------------\n";
    cout << "Item\tWeight\tPrice\tSelected Fraction\n";
    cout << "--------------------------------------------\n";
    for (int i = 0; i < n; i++)
        cout << i + 1 << "\t" << arr[i].weight << "\t" << arr[i].price << "\t" << arr[i].selectedFraction << "\n";
    cout << "--------------------------------------------\n";

    cout << "Profit acheived: Rs." << ans << "\n";
    return 0;
}
