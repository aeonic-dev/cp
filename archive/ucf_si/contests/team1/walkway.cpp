// settings
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#include <bits/stdc++.h>

using namespace std;

// primitive types
typedef long long ll;
typedef long int li;

// aliases
#define vec vector
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
typedef vec<int> vi;
typedef vec<li> vli;
typedef vec<ll> vll;
typedef vec<pi> vpi;
typedef vec<string> vs;

// more aliases
#define pb push_back
#define eb emplace_back

// other macros
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rev(i, a, b) for (int i = a; i > b; i--)
#define integral(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type
#define numeric(return_type) template<typename T> typename enable_if<is_arithmetic<T>::value, return_type>::type

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

double cost(int a, int b, int h) {
    return .02 * h * (b + (a - b) / 2.0);
}

void solve() {
    while (true) {
        int n, a, b, h;
        cin >> n;

        if (n == 0) return;

        vec<vec<pair<int, double>>> edges(1001);

        // Build edges and compute weights
        rep(i, 0, n) {
            cin >> a >> b >> h;

            double cost = ::cost(a, b, h);

            edges[a].push_back({b, cost});
            edges[b].push_back({a, cost});
        }

        int s, v; // Start and end vertices
        cin >> s >> v;

        bool u[1001] = {false};
        vec<double> d(1001, DBL_MAX);
        d[s] = 0;

        priority_queue<pair<double, int>> pq;
        pq.push({0, s});

        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();

            if (cur.first != d[cur.second]) continue;

            for (auto &edge: edges[cur.second]) {
                double new_cost = d[cur.second] + edge.second;

                if (new_cost < d[edge.first])
                    pq.push({d[edge.first] = new_cost, edge.first});
            }
        }

        cout << d[v] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    cout << setprecision(2) << fixed;
    solve();
//    int tests;
//    cin >> tests;
//    while (tests--) solve();
}