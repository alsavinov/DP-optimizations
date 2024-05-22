#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#define int __int128 // возможно переполнение long long
#define ll long long
using namespace std;
const int INF = 1e18 + 7;


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
        while (lines.size() > 0 && lines.back().get(points.back()) < cur.get(points.back())) {
            lines.pop_back();
            points.pop_back();
        }
        if (lines.size() == 0) {
            points.push_back(INF);
        } else {
            points.push_back(intersect(lines.back(), cur));
        }
        lines.push_back(cur);
    }

    
    int get(int x) { // функция для поиска оптимального значения в точке
        int l = 0, r = points.size();
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (points[m] > x) {
                l = m;
            } else {
                r = m;
            }
        }
        int pos = r;
        return lines[l].get(x);
    }
};


struct figure {
    ll x = 0, y = 0, a = 0;
    figure(ll _x, ll _y, ll _a) : x(_x), y(_y), a(_a) {}
    figure() {}
};


ll n;
vector<figure> fs;


void get_cin() {
    cin >> n;
    fs.resize(n + 1);
    fs[0] = figure(-INF, 0, 0);
    for (int i = 1; i <= n; ++i) cin >> fs[i].x >> fs[i].y >> fs[i].a;
    sort(fs.begin(), fs.end(), [](const figure& a, const figure& b) { // сортируем массив по x
        return a.x < b.x;
        });

}


void solve() {
    get_cin(); // ввод и подготовка данных
    int dp = 0, answer = 0;
    convex_hull_trick now;
    now.add_line(line(0, 0));
    now.points.reserve(n + 1);
    now.lines.reserve(n + 1);
    for (ll i = 1; i <= n; ++i) {
        dp = now.get(fs[i].y) + fs[i].x * fs[i].y - fs[i].a; // пересчет дп
        answer = max(answer, dp);
        now.add_line(line(-fs[i].x, dp));  // добавление новой прямой
    }
    cout << (ll)(answer) << endl;
}


signed main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    solve();
}


