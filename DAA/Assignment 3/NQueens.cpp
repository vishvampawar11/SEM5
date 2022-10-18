#include <iostream>
#include <string>
#include <vector>

using namespace std;
/*
unsafe positions 
            X
              X   
            X X Q
              X
            X 
*/
bool safe(int row, int col, vector<string> &board, int n)
{
    int r = row, c = col;

    // check for unsafe pos in upper left diagonal
    while (r >= 0 && c >= 0)
    {
        if (board[r][c] == 'Q')
            return false;
        r--, c--;
    }

    r = row, c = col;
    // check for unsafe pos in current row
    while (c >= 0)
    {
        if (board[r][c] == 'Q')
            return false;
        c--;
    }

    r = row, c = col;
    // check for unsafe pos in lower left diagonal
    while (r < n && c >= 0)
    {
        if (board[r][c] == 'Q')
            return false;
        r++, c--;
    }
    // if all safe return true
    return true;
}

void solve(int col, vector<string> &board, vector<vector<string>> &ans, int n)
{
    // if we reach end of the board, we have found a possible solution. Add it to ans and return.
    if (col == n)
    {
        ans.push_back(board);
        return;
    }

    // Traversing this col.
    for (int row = 0; row < n; row++)
    {
        // check for safe place at every postion in this col.
        if (safe(row, col, board, n))
        {
            // place queen at this pos and solve problem for col+1.
            board[row][col] = 'Q';
            solve(col + 1, board, ans, n);
            // to backtrack the recursion empty this pos.
            // to find other possible solution.
            board[row][col] = '_';
        }
    }
}

int main()
{
    int n;
    cout << "Enter n: ";
    cin >> n;

    if (n < 4)
    {
        cout << "No ans possible!\n";
        return 0;
    }

    vector<vector<string>> ans; // stores all possible answers

    // filling the board.
    vector<string> board(n);
    for (int i = 0; i < n; i++)
    {
        string row;
        for (int j = 0; j < n; j++)
            row += '_';
        board[i] = row;
    }

    solve(0, board, ans, n);

    // printing all possible answers
    for (int i = 0; i < ans.size(); i++)
    {
        cout << "### Ans: " << i + 1 << " ###\n";
        for (int j = 0; j < ans[i].size(); j++)
        {
            for (int k = 0; k < ans[i][j].size(); k++)
                cout << ans[i][j][k] << " ";
            cout << "\n";
        }
        cout << "\n";
    }

    return 0;
}
