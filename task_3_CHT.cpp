#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#define int long long

using namespace std;
const int INF = 1e9 + 7;


int min(int a, int b) { 
    return (a < b) ? a : b;
}


int max(int a, int b) { 
    return (a > b) ? a : b;
}


struct line { // прямая
    int k, b;
    line() {}
    line(int a, int _b) { k = a, b = _b; }
    int get(int x) { return k * x + b; }
};


int intersect(line a, line b) { // пересечение прямых
    if (a.k == b.k) return INF;
    int v = abs(b.b - a.b), ni = abs(a.k - b.k);
    int ans = (v + ni - 1) / ni;
    int fl = 1;
    if (b.b - a.b == 0) return 0;
    if (b.b - a.b < 0) fl *= -1;
    if (a.k - b.k < 0) fl *= -1;
    return fl * ans;
}


struct convex_hull_trick { // convexHullTrick
    vector<line> lines;
    vector<int> points;
    void add_line(line cur) { 
        while (lines.size() > 0 && lines.back().get(points.back()) < cur.get(points.back())) { // удаление прямых
            lines.pop_back();
            points.pop_back();
        }
        if (lines.size() == 0) {
            points.push_back(-INF);
        } else {
            if (lines.back().k == cur.k) return; // проверка на равенство
            points.push_back(intersect(lines.back(), cur));
        }
        lines.push_back(cur);
    }
    int get(int x) { // удобный бинпоиск
        int l = -1, r = points.size();
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (points[m] > x) {
                r = m;
            } else {
                l = m;
            }
        }
        int pos = r - 1;
        return lines[pos].get(x);
    }
};


void solve() { // решение
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i]; 
    sort(a.begin(), a.end());
    vector<vector<int> > dp(k + 1, vector<int>(n + 1, 0));
    convex_hull_trick cht;
    for (int j = 1; j <= n; ++j) {
        cht.add_line(line(a[j - 1], -((j - 1) * a[j - 1])));
    }
    for (int i = 1; i <= k; ++i) {
        convex_hull_trick next;
        for (int j = 1; j <= n; ++j) { // здесь считаем dp для определенного слоя i
            dp[i][j] = cht.get(j);
        }
        for (int j = 1; j <= n; j++) { // здесь обновляем CHT для слоя i + 1 (следующего)
            next.add_line(line(a[j - 1], -((j - 1) * a[j - 1]) + dp[i][j - 1]));
        }
        cht = next; // просто присваиваем для следующего слоя
    }
    cout << dp[k][n] << endl;
}


signed main() {
    solve();
}
