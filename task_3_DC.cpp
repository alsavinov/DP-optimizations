#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#define int long long
#define ll long long

using namespace std;
const int INF = 1e9 + 7;


int min(int a, int b) {
    return (a < b) ? a : b;
}


int max(int a, int b) {
    return (a > b) ? a : b;
}


vector<vector<int> > dp;
vector<int> a;
int n, k;


void make(int l, int r, int opl, int opr, int ck) {
    if (l > r) return;
    int m = (l + r) / 2, opt = -1;
    for (int i = opl; i <= min(m, opr); i++) {
        int may = dp[ck - 1][i - 1] + a[i - 1] * (m - i + 1);
        if (may > dp[ck][m]) {
            dp[ck][m] = may;
            opt = i;
        }
    }
    make(l, m - 1, opl, opt, ck);
    make(m + 1, r, opt, opr, ck);
}


void solve() {
    cin >> n >> k;
    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    dp = vector<vector<int> >(k + 1, vector<int>(n + 1, -1));
    for (int i = 0; i <= n; i++) dp[0][i] = 0;
    for (int i = 0; i <= k; i++) dp[i][0] = 0;
    sort(a.begin(), a.end());
    for (int i = 1; i <= k; i++) {
        make(1, n, 1, n, i);
    }
    cout << dp[k][n] << endl;
}


signed main() {
    solve();   
}

