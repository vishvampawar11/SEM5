#include <iostream>
#include <vector>

using namespace std;

struct item
{
    double weight;
    double price;
    double ratio;
    double selectedFraction = 0;
};

void merge(item arr[], int l, int mid, int r);
void mergeSort(item arr[], int l, int r, int n);
void fractionalKnapsack(item arr[], int n, int W);
void zeroOneKnpSack(item arr[], int n, int W);

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

    cout << "1. Fractional Knapsack\n";
    cout << "2. 0/1 Knapsack\n";
    cout << "Enter your choice: ";
    int ch;
    cin >> ch;

    switch (ch)
    {
        {
        case 1:
            fractionalKnapsack(arr, n, W);
            break;

        case 2:
            zeroOneKnpSack(arr, n, W);
            break;

        default:
            break;
        }
    }
}

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

void fractionalKnapsack(item arr[], int n, int W)
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
    cout << "--------------------------------------------\n";
    cout << "Item\tWeight\tPrice\tSelected Fraction\n";
    cout << "--------------------------------------------\n";
    for (int i = 0; i < n; i++)
        cout << i + 1 << "\t" << arr[i].weight << "\t" << arr[i].price << "\t" << arr[i].selectedFraction << "\n";
    cout << "--------------------------------------------\n";

    cout << "Profit acheived: Rs." << ans << "\n";
}

void zeroOneKnpSack(item arr[], int n, int W)
{
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (arr[i - 1].weight <= j)
                dp[i][j] = max((int)(arr[i - 1].price) + dp[i - 1][j - (int)arr[i - 1].weight], dp[i - 1][j]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    int ch;
    cout << "Print 1 to print selection matrix, 0 otherwise: ";
    cin >> ch;
    if (ch == 1)
    {
        cout << "#####Selection Martrix#####\n";
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= W; j++)
                cout << dp[i][j] << " ";
            cout << "\n";
        }
        cout << "\n\n";
    }

    int i = n, j = W;
    vector<int> selectedItems;
    cout << "#####Selected Items#####\n";
    cout << "---------------------------\n";
    cout << "No\tProfit\tWeight\n";
    cout << "---------------------------\n";
    while (i > 0)
    {
        if (dp[i - 1][j] != dp[i][j])
        {
            selectedItems.push_back(i);
            j -= arr[i - 1].weight;
        }
        i--;
    }
    for (int i = selectedItems.size() - 1; i >= 0; i--)
        cout << selectedItems[i] << "\t"
             << arr[selectedItems[i] - 1].price << "\t"
             << arr[selectedItems[i] - 1].weight << "\n";

    cout << "---------------------------\n\n";

    cout << "Profit acieved: Rs." << dp[n][W] << "\n ";
}
