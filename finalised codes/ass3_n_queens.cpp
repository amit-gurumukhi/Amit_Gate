// #include <iostream>
// #include <cmath>
#include<bits/stdc++.h>
using namespace std;
int cnt=0;

bool canPlaceQueen(int k, int i, int x[]) {
    for (int j = 1; j < k; j++) {
        if (x[j] == i || abs(x[j] - i) == abs(j - k)) {
            return false;
        }
    }
    return true;
}

void NQueens(int k, int n, int x[]) {
    for (int i = 1; i <= n; i++) {
        if (canPlaceQueen(k, i, x)) {
            x[k] = i;
            if (k == n) {
                cnt++;
                cout << "Solution: ";
                for (int j = 1; j <= n; j++) {
                    cout << x[j] << " ";
                }
                cout << endl;
            } else {
                NQueens(k + 1, n, x);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    int x[n+1];
    
    NQueens(1, n, x);
    cout<<"no of solutions: "<<cnt;

    return 0;
}
