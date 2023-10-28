// Settings
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#include <bits/stdc++.h>

using namespace std;

// Few word type fast zoom
#define vec vector
#define pb push_back
#define eb emplace_back
#define uset unordered_set
#define umap unordered_map

// Type aliases
typedef long int li;
typedef long long ll;
typedef long double ld;
typedef unsigned char byte;
typedef pair<int, int> pi;
typedef pair<double, double> pd;
typedef pair<li, li> pli;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef vec<int> vi;
typedef vec<li> vli;
typedef vec<ll> vll;
typedef vec<pi> vpi;
typedef vec<string> vs;

// Other macros
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rev(i, a, b) for (int i = a; i > b; i--)
#define travis(x, s) for (auto &x: s)
#define gin(type) get_cin<type>()
#define gi() gin(int)

// Misc templates
// @formatter:off
template<typename A, typename B> istream &operator>>(istream &stream, pair<A, B> &pair) { stream >> pair.first >> pair.second; return stream; }
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << pair.first << " " << pair.second; }
template<typename T> istream &operator>>(istream &stream, vector<T> &vector) { for (auto &x: vector) cin >> x; return stream; }
template<typename T> istream &operator>>(istream &stream, T array[]) { for (auto &x: array) cin >> x; return stream; }
template<typename T> class ipq : public priority_queue<T, vector<T>, greater<T>> {};
template<typename T> T get_cin() { T t; cin >> t; return t; }
// @formatter:on

struct dsu {
    vector<int> par;

    dsu(int n) : par(n, -1) {}

    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;

        if (par[a] > par[b]) swap(a, b); // a is larger
        par[a] += par[b];
        par[b] = a;

        return true;
    }

    int find(int s) {
        return par[s] < 0 ? s : par[s] = find(par[s]);
    }

    int count() {
        int num = 0;
        for (auto &p: par) num += p < 0;
        return num;
    }
};

void stroke(vec<vec<int>> &board, int n, int m, int &num_str, pair<pi, pi> &ln, int delta) {
    auto x1 = ln.first.first, y1 = ln.first.second;
    auto x2 = ln.second.first, y2 = ln.second.second;

    rep(y, max(y1, 0), min(y2 + 1, m)) {
        rep(x, max(x1, 0), min(x2 + 1, n)) {
            auto &cur = board[y][x];

            if (cur > 0 && cur + delta <= 0) num_str--;
            if (cur <= 0 && delta > 0) num_str++;

            cur = max(0, cur + delta);
        }
    }
}

// join cell to any neighbors if no strokes on either the neighbor or this cell
void update_cell(vec<vec<int>> &board, int n, int m, dsu &ds, int &num_cmp, int x, int y) {
    if (board[y][x]) return;

    if (x - 1 >= 0 && !board[y][x - 1]) num_cmp -= ds.join(n * y + x, n * y + (x - 1));
    if (x <= n - 2 && !board[y][x + 1]) num_cmp -= ds.join(n * y + x, n * y + (x + 1));
    if (y - 1 >= 0 && !board[y - 1][x]) num_cmp -= ds.join(n * y + x, n * (y - 1) + x);
    if (y <= m - 2 && !board[y + 1][x]) num_cmp -= ds.join(n * y + x, n * (y + 1) + x);
}

void init_count(vec<vec<int>> &board, int n, int m, dsu &ds, int &num_cmp) {
    rep(y, 0, m) {
        rep(x, 0, n) {
            update_cell(board, n, m, ds, num_cmp, x, y);
        }
    }
}

void remove_stroke(vec<vec<int>> &board, int n, int m, dsu &ds, int &num_cmp, int &num_str, pair<pi, pi> &ln) {
    stroke(board, n, m, num_str, ln, -1);

    auto x1 = ln.first.first, y1 = ln.first.second;
    auto x2 = ln.second.first, y2 = ln.second.second;

    rep(y, max(y1, 0), min(y2 + 1, m)) {
        rep(x, max(x1, 0), min(x2 + 1, n)) {
            update_cell(board, n, m, ds, num_cmp, x, y);
        }
    }
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vec<vec<int>> board(m, vec<int>(n, 0));
    vec<pair<pi, pi>> strokes(q);
    int num_cmp = n * m, num_str = 0; // # components; # stroke cells (to subtract from component count)

    rep(i, 0, q) {
        strokes[i] = {
                {gi() - 1, gi() - 1},
                {gi() - 1, gi() - 1}
        };

        stroke(board, n, m, num_str, strokes[i], 1);
    }
    reverse(all(strokes));

    dsu ds(n * m);
    stack<int> res;

    init_count(board, n, m, ds, num_cmp);
    res.push(num_cmp - num_str);

    rep(i, 0, q - 1) {
        remove_stroke(board, n, m, ds, num_cmp, num_str, strokes[i]);
        res.push(num_cmp - num_str);
    }

    while (!res.empty()) {
        auto r = res.top();
        res.pop();

        cout << r << endl;
    }
//    cout << num_cmp << " " << num_str << endl << endl;
//    cout << num_cmp - num_str << endl;
}

#define MULTIPLE_CASES 0

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    //cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)
#if MULTIPLE_CASES
    int tests;
    cin >> tests;
    while (tests--) solve();
#else
    solve();
#endif
}