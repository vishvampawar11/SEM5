#include <iostream>
#include <vector>

using namespace std;

// RECURSIVE APPROACH
int solve(int n, int W, int profit[], int weight[])
{
    // if no items are left or bag is full, we can't make any profit
    if (n == 0 || W == 0)
        return 0;
    // if we can select this item, try both ways.
    if (weight[n - 1] <= W)
        return max(profit[n - 1] + solve(n - 1, W - weight[n - 1], profit, weight), solve(n - 1, W, profit, weight));
    // if we can't select this item solve for remaining input
    else
        return solve(n - 1, W, profit, weight);
}

int main()
{
    int W, n;
    cout << "Enter weight of the knapsack: ";
    cin >> W;
    cout << "Enter no of items: ";
    cin >> n;
    int profit[n], weight[n];
    cout << "Enter weight and profit of each item\n";
    for (int i = 0; i < n; i++)
        cin >> weight[i] >> profit[i];

    // cout << solve(n, W, profit, weight) << "\n";
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (weight[i - 1] <= j)
                dp[i][j] = max(profit[i - 1] + dp[i - 1][j - weight[i - 1]], dp[i - 1][j]);
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
            j -= weight[i - 1];
        }
        i--;
    }
    for (int i = selectedItems.size() - 1; i >= 0; i--)
        cout << selectedItems[i] << "\t"
             << profit[selectedItems[i] - 1] << "\t"
             << weight[selectedItems[i] - 1] << "\n";

    cout << "---------------------------\n\n";

    cout << "Profit acieved: Rs." << dp[n][W] << "\n ";
    return 0;
}
