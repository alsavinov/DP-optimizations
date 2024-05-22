#include <iostream>
#include <vector>
#include <chrono>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#include <fstream>
#define int long long
#define ll long long

using namespace std;
const int INF = 1e18 + 7;


int min(int a, int b) {
    return (a < b) ? a : b;
}


int max(int a, int b) {
    return (a > b) ? a : b;
}


ifstream fin;
ofstream fout;
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


void solve_ras() { // решение для Разделяй и властвуй
    fin >> n >> k;
    a = vector<int>(n);
    for (int i = 0; i < n; i++) fin >> a[i];
    dp = vector<vector<int> >(k + 1, vector<int>(n + 1, -1));
    for (int i = 0; i <= n; i++) dp[0][i] = 0;
    for (int i = 0; i <= k; i++) dp[i][0] = 0;
    sort(a.begin(), a.end());
    for (int i = 1; i <= k; i++) {
        make(1, n, 1, n, i);
    }
}


void solve_knut() { // решение для оптимизации Кнута
    fin >> n >> k;
    a = vector<int>(n);
    for (int i = 0; i < n; i++) fin >> a[i];
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
}


struct line {
    int k, b;
    line() {}
    line(int a, int _b) { k = a, b = _b; }
    int get(int x) { return k * x + b; }
};


int intersect(line a, line b) {
    if (a.k == b.k) return INF;
    int v = abs(b.b - a.b), ni = abs(a.k - b.k);
    int ans = (v + ni - 1) / ni;
    int fl = 1;
    if (b.b - a.b == 0) return 0;
    if (b.b - a.b < 0) fl *= -1;
    if (a.k - b.k < 0) fl *= -1;
    return fl * ans;
}


struct convex_hull_trick {
    vector<line> lines;
    vector<int> points;
    void add_line(line cur) {
        while (lines.size() > 0 && lines.back().get(points.back()) < cur.get(points.back())) {
            lines.pop_back();
            points.pop_back();
        }
        if (lines.size() == 0) {
            points.emplace_back(-INF);
        } else {
            points.emplace_back(intersect(lines.back(), cur));
        }
        lines.push_back(cur);
    }
    int get(int x) {
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


void solve_cht() { // решение для Convex Hull Trick 
    int n, k;
    fin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) fin >> a[i];
    sort(a.begin(), a.end());
    vector<vector<int> > dp(k + 1, vector<int>(n + 1, 0));
    convex_hull_trick cht;
    for (int j = 1; j <= n; ++j) {
        cht.add_line(line(a[j - 1], -((j - 1) * a[j - 1])));
    }
    for (int i = 1; i <= k; ++i) {
        convex_hull_trick next;
        for (int j = 1; j <= n; ++j) {
            int news = cht.get(j);
            dp[i][j] = cht.get(j);
            next.add_line(line(a[j - 1], -((j - 1) * a[j - 1]) + dp[i][j - 1]));
        }
        cht = next;
    }
}


void stupid() { // базовое решение 
    int n, k;
    fin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) fin >> a[i];
    vector<vector<ll>> dp(k + 1, vector<ll>(n + 1, 0));
    for (ll i = 1; i <= k; ++i) {
        for (ll j = 1; j <= n; ++j) {
            for (ll y = 1; y <= j; ++y) {
                dp[i][j] = max(dp[i][j], j * a[y - 1] + dp[i - 1][y - 1] - (y - 1) * a[y - 1]);
            }
        }
    }
}


void generator_random_test_with_n_and_k(int must_k, int must_n) { // генератор тестов в зависимости от нужных значений
    int k = must_k, n = must_n;
    vector<int> mass;
    for (int i = 0; i < n; i++) { // генерируем массив 
        int x = rand() % 10000 + 1;
        mass.push_back(x);
    }
    // выводим всё в файл
    fout << n << " " << k << endl;
    for (auto c : mass) fout << c << " ";
}


// файлы для записи данных
string path_res_cht = "result_cht.txt";
string path_res_ras = "result_ras.txt";
string path_res_knut = "result_knut.txt";
string path_to_n = "result_n.txt";

// количество тестов, шаг графика, кол - во тестов на одни значения
const int NUM_TESTS = 40;
const int ADD = 25;
const int TO_ONE = 100;
signed main() {
    cout << fixed << setprecision(20);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // выводим в файл значения при определенном n и k 
    fout = ofstream(path_to_n);
    for (int i = 0; i < NUM_TESTS; i++) {
        fout << (i + 1) * ADD << endl;
    }
    fout.close();
    // очистим файл
    fout = ofstream(path_res_cht); 
    fout.close();
    int cur_k = ADD, cur_n = 10000;// начальное значение
    for (int it = 0; it < NUM_TESTS; it++) { // для тестов
        int time = 0;
        for (int i = 0; i < TO_ONE; i++) {
            string path = "test.txt"; 
            fout = ofstream(path);
            generator_random_test_with_n_and_k(cur_k, cur_n); // генерация теста
            fout.close();
            fin = ifstream(path);
            // время в начале
            auto begin = std::chrono::high_resolution_clock::now();
            solve_cht(); //// запуск нужного решения
            // время в конце
            auto end = std::chrono::high_resolution_clock::now();
            // время работы
            auto cur_time = end - begin;       
            auto elapsed_ms = cur_time / std::chrono::milliseconds(1);
            time += elapsed_ms;
        }
        time /= TO_ONE; // среднее значение
        // записываем в файл
        fout = ofstream(path_res_cht, std::fstream::app); 
        fout << time << endl;
        fout.close();
        // изменяем n или k 
        cur_k += ADD;
    }
}

