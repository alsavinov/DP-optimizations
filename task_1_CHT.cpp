#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#define int __int128
#define ll long long
using namespace std;
const int INF = 1e9 + 7;


int min(int a, int b) {
    return (a < b) ? a : b;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}
struct line {
    int k, b;
    line() {}
    line(int a, int _b) { k = a, b = _b; }
    int get(int x) { return k * x + b; }
};
int abs(int a, int b) {
    if (a > b) return a - b;
    return b - a;
}
int intersect(line a, line b) { // пересечения прямых
    if (a.k == b.k) return INF;
    int v = abs(b.b, a.b), ni = abs(a.k, b.k);
    int ans = (v + ni - 1) / ni;
    int fl = 1;
    if (b.b - a.b == 0) return 0;
    if (b.b - a.b < 0) fl *= -1;
    if (a.k - b.k < 0) fl *= -1;
    return fl * ans;
    return 1;
}
struct convex_hull_trick {
    vector<line> lines;
    vector<int> points;
    void add_line(line cur) { // добавление прямой
        while (lines.size() > 0 && lines.back().get(points.back()) > cur.get(points.back())) {
            lines.pop_back();
            points.pop_back();
        }
        if (lines.size() == 0) {
            points.push_back(-INF);
        } else {
            //if (lines.back().k == cur.k) return;
            points.push_back(intersect(lines.back(), cur));
        }
        lines.push_back(cur);
    }
    int get(int x) { // функция для вычисления оптимального значения в точке
        int l = 0, r = points.size();
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (points[m] < x) {
                l = m;
            } else {
                r = m;
            }
        }
        return lines[l].get(x);
    }
};


ll n;
vector<ll> a, b;
void get_cin() {
    cin >> n;
    a = vector<ll>(n);
    b = vector<ll>(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
}

void solve() {
    get_cin(); // ввод и подготовка данных
    vector<int> dp(n, INF);
    convex_hull_trick now;
    now.add_line(line(0, 0));
    dp[0] = 0;
    now.add_line(line(b[0], 0));
    for (ll i = 1; i < n; ++i) { // пересчет дп
        dp[i] = now.get(a[i]);
        now.add_line(line(b[i], dp[i]));
    }
    cout << (ll)(dp[n - 1]) << endl;
}


signed main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    solve();
}

