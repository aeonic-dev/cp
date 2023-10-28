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

map<string, int> modes{
        {"AIR", 0},
        {"SEA", 1},
        {"RAIL", 2},
        {"TRUCK", 3}
};

void solve() {
    int c, cost;
    cin >> c;

    // index for {city c, mode of transport t (0-3)} = c * 4 + t
    vec<vec<pair<int, ll>>> adj(c * 4);
    map<string, int> cities;
    rep(i, 0, c) {
        string s;
        cin >> s >> cost;

        cities[s] = i;
        rep(m1, 0, 4) {
            rep(m2, 0, 4) {
                if (m1 == m2) continue;
                adj[i * 4 + m1].emplace_back(i * 4 + m2, cost);
            }
        }
    }

    int r;
    cin >> r;
    rep(i, 0, r) {
        string ps, qs, ms;
        cin >> ps >> qs >> ms;
        int p = cities[ps], q = cities[qs], m = modes[ms], v;
        cin >> v;

        adj[p * 4 + m].emplace_back(q * 4 + m, v);
        adj[q * 4 + m].emplace_back(p * 4 + m, v);
    }

    string os, ds;
    cin >> os >> ds;
    int from = cities[os], to = cities[ds];

    vec<ll> d(c * 4, LLONG_MAX);
    priority_queue<pair<ll, int>, vec<pair<ll, int>>, greater<pair<ll, int>>> pq;
    rep(i, 0, 4) {
        d[from * 4 + i] = 0;
        rep(j, 0, 4) {
            if (i == j) continue;
            adj[from * 4 + i].emplace_back(from * 4 + j, 0);
        }
    }
    rep(i, 0, 4) pq.emplace(0, from * 4 + i);

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

    ll min = LLONG_MAX;
    rep(i, 0, 4) min = ::min(min, d[to * 4 + i]);
    cout << min << endl;
}

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    //cin.tie(nullptr); // Unties cin from cout (don't do this if you alternate input/output)

    solve();
//    int tests;
//    cin >> tests;
//    while (tests--) solve();
}