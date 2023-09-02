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
#define integral(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type
#define numeric(return_type) template<typename T> typename enable_if<is_arithmetic<T>::value, return_type>::type

// Misc templates
// @formatter:off
template<typename A, typename B> istream &operator>>(istream &stream, pair<A, B> &pair) { stream >> pair.first >> pair.second; return stream; }
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
template<typename T> istream &operator>>(istream &stream, vector<T> &vector) { for (auto &x: vector) cin >> x; return stream; }
template<typename T> istream &operator>>(istream &stream, T array[]) { for (auto &x: array) cin >> x; return stream; }
// @formatter:on

void solve() {
    int f;
    cin >> f;

    // indexed by row * 81 + col
    vec<int> chars(f);
    vec<vec<pair<int, int>>> adj(f * 81);
    rep(row, 0, f) {
        cin >> chars[row];

        rep(i, 0, chars[row] + 1) {
            if (i > 0) adj[row * 81 + i].emplace_back(row * 81 + i - 1, 1);
            else if (row > 0) adj[row * 81 + i].emplace_back((row - 1) * 81 + chars[row - 1], 1);

            if (i < chars[row]) adj[row * 81 + i].emplace_back(row * 81 + i + 1, 1);
            else if (row < f - 1) adj[row * 81 + i].emplace_back((row + 1) * 81, 1);

            if (row > 0) {
                adj[row * 81 + i].emplace_back((row - 1) * 81 + min(i, chars[row - 1]), 1);
            }

            if (row < f - 1) {
                adj[row * 81 + i].emplace_back((row + 1) * 81 + min(i, chars[row + 1]), 1);
            }
        }
    }

    int fr, fc, tr, tc;
    cin >> fr >> fc >> tr >> tc;
    int from = --fr * 81 + fc, to = --tr * 81 + tc;

    vec<ll> d(f * 81, LLONG_MAX);
    priority_queue<pair<ll, int>, vec<pair<ll, int>>, greater<pair<ll, int>>> pq;
    d[from] = 0;
    pq.emplace(0, from);

    while (!pq.empty()) {
        auto p = pq.top();
        int node = p.second;
        ll dist = p.first;
        pq.pop();

        if (dist != d[node]) continue;
        travis(i, adj[node]) {
            if (dist + i.second < d[i.first]) {
                pq.emplace(d[i.first] = dist + i.second, i.first);
            }
        }
    }

    cout << d[to] << endl;
}

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    //cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)

    solve();
}