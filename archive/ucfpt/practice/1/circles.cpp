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
#define gin(type) get_cin<type>()

// Misc templates
// @formatter:off
template<typename A, typename B> istream &operator>>(istream &stream, pair<A, B> &pair) { stream >> pair.first >> pair.second; return stream; }
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << pair.first << " " << pair.second; }
template<typename T> istream &operator>>(istream &stream, vector<T> &vector) { for (auto &x: vector) cin >> x; return stream; }
template<typename T> istream &operator>>(istream &stream, T array[]) { for (auto &x: array) cin >> x; return stream; }
template<typename T> class ipq : public priority_queue<T, vector<T>, greater<T>> {};
template<typename T> T get_cin() { T t; cin >> t; return t; }
// @formatter:on

void solve() {
    int c, r;
    cin >> c >> r;

    vec<int> radii(c);
    cin >> radii;

    vec<vec<int>> nodes(c); // all node angles on a given circle
    map<pair<int, int>, int> indices; // {circle, angle} -> node index
    vec<vec<pair<int, ld>>> edges(r * 2 + 2);

    int index = 0;

    rep(i, 0, r) {
        int d, a;
        cin >> d >> a;

        int i1 = indices[{d - 1, a}] = index++;
        nodes[d - 1].pb(a);

        int i2;
        // if the end of this road already exists as a node, use its index (not a new one)
        if (indices.count({d, a})) i2 = indices[{d, a}];
        else {
            i2 = indices[{d, a}] = index++;
            nodes[d].pb(a);
        }

        ld w = radii[d] - radii[d - 1];

        edges[i1].eb(i2, w);
        edges[i2].eb(i1, w);
    }

    int sc, sa, fc, fa;
    cin >> sc >> sa >> fc >> fa;

    int start, end;

    if (indices.count({sc - 1, sa})) {
        start = indices[{sc - 1, sa}];
    } else {
        start = indices[{sc - 1, sa}] = index++;
        nodes[sc - 1].pb(sa);
    }

    if (indices.count({fc - 1, fa})) {
        end = indices[{fc - 1, fa}];
    } else {
        end = indices[{fc - 1, fa}] = index++;
        nodes[fc - 1].pb(fa);
    }

    rep(i, 0, c) {
        rep(j, 0, nodes[i].size()) {
            rep(k, j + 1, nodes[i].size()) {
                int a1 = nodes[i][j];
                int a2 = nodes[i][k];
                if (a2 < a1) swap(a1, a2);

                int i1 = indices[{i, a1}];
                int i2 = indices[{i, a2}];

                ld w = 2 * M_PI * radii[i] * min(
                        a2 - a1,
                        a1 + (360 - a2)
                ) / 360;

                edges[i1].eb(i2, w);
                edges[i2].eb(i1, w);
            }
        }
    }

    vec<ld> dist(index, LDBL_MAX);
    ipq<pair<ld, int>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto cd = pq.top().first;
        auto cur = pq.top().second;
        pq.pop();

        if (cd != dist[cur]) continue;
        for (const pair<int, ld> &e: edges[cur]) {
            if (cd + e.second < dist[e.first]) {
                dist[e.first] = cd + e.second;
                pq.push({dist[e.first], e.first});
            }
        }
    }

    auto min_distance = dist[end];
    cout << setprecision(2) << fixed << round(min_distance * 100) / 100 << endl;
}

#define MULTIPLE_CASES 1

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