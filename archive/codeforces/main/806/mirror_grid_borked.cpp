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

// Type aliases
typedef long int li;
typedef long long ll;
typedef long double ld;
typedef unsigned char byte;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
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
#define integral(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type
#define numeric(return_type) template<typename T> typename enable_if<is_arithmetic<T>::value, return_type>::type

// Misc templates
// @formatter:off
template<typename A, typename B> istream &operator>>(istream &stream, pair<A, B> &pair) { stream >> pair.first >> pair.second; return stream; }
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
template<typename T> istream &operator>>(istream &stream, vector<T> &vector) { for (auto &x: vector) cin >> x; return stream; }
template<typename T> istream &operator>>(istream &stream, T array[]) { for (auto &x: array) cin >> x; return stream; }
// @formatter:on

template<typename n_t = int, typename f_t = int, f_t infinity = INT_MAX>
struct ffa {
    n_t n;
    vector<vector<f_t>> residual;
    vector<bool> seen;

    ffa(n_t n) : n(n) {
        static_assert(is_integral<n_t>::value, "node index type must be integral");
        static_assert(is_integral<f_t>::value, "flow value type must be integral");

        residual = vector<vector<f_t>>(n, vector<f_t>(n));
    }

    // Adds an edge to the network
    void add_edge(n_t u, n_t v, f_t capacity, bool bidirectional = false) {
        residual[u][v] += capacity;
        if (bidirectional) residual[v][u] += capacity;
    }

    // Find augmenting paths in the network
    f_t dfs(n_t cur, n_t t, f_t flow) {
        if (cur == t) return flow;

        for (n_t next = 0; next < n; next++) {
            if (residual[cur][next] == 0 || seen[next]) continue;

            seen[next] = true;
            f_t f = dfs(next, t, min(flow, residual[cur][next]));
            if (f != 0) {
                residual[cur][next] -= f;
                residual[next][cur] += f;
                return f;
            }
        }

        return 0;
    }

    // Gets the max flow from s to t
    f_t max_flow(n_t s, n_t t) {
        f_t flow = 0;

        while (true) {
            seen = vector<bool>(n, false);
            seen[s] = true;

            f_t f = dfs(s, t, infinity);
            if (f == 0) break;

            flow += f;
        }

        return flow;
    }
};

int index(int r, int c) {
    return r * 100 + c;
}

int x(int index) {
    return index / 100;
}

int y(int index) {
    return index % 100;
}

pi pos(int index) {
    return {x(index), y(index)};
}

int left(int r, int c) {
    return 2 + index(r, c);
}

int right(int n, int r, int c) {
    return 2 + n * n + index(r, c);
}

void solve() {
    int n;
    cin >> n;

    vec<bitset<100>> grid(n);
    ffa<int, ll, LLONG_MAX> network(2 * n * n + 2); // 0=source, 1=sink, left=2+index(r,c), right=2+n*n+index(r,c)

    rep(i, 0, n) {
        char ch;
        cin >> ch;
        rep(j, 0, n) grid[i][j] = ch == '1';
        cin.ignore();
    }

    rep(i, 0, n) {
        rep(j, 0, n / 2) {

        }
    }
}

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    //cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}