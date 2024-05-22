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


void solve() {
    cin >> n >> k;
    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    dp = vector<vector<int> >(k + 1, vector<int>(n + 1, -1));
    for (int i = 0; i <= n; i++) dp[0][i] = 0;
    for (int i = 0; i <= k; i++) dp[i][0] = 0;
    vector<vector<int> > opt(k + 1, vector<int>(n + 2, 1));
    for (int i = 0; i <= k; i++) opt[i][n + 1] = n;
    sort(a.begin(), a.end());
    for (int i = 1; i <= k; i++) {
        for (int j = n; j >= 1; j--) {
            int l = opt[i - 1][j], r = opt[i][j + 1];
            for (int x = l; x <= r; x++) {
                int may = dp[i - 1][x - 1] + (j - x + 1) * a[x - 1];
                if (may > dp[i][j]) {
                    dp[i][j] = may;
                    opt[i][j] = x;
                }
            }
        }
    }
    cout << dp[k][n];
}


signed main() {
    solve();
}

