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
#define travis(x, s) for (auto &x: s)
#define integral(return_type) template<typename T> typename enable_if<is_integral<T>::value, return_type>::type
#define numeric(return_type) template<typename T> typename enable_if<is_arithmetic<T>::value, return_type>::type

// templates
// @formatter:off
template<typename A, typename B> ostream &operator<<(ostream &stream, const pair<A, B> &pair) { return stream << "(" << pair.first << ", " << pair.second << ")"; }
// @formatter:on

ll min_cost(vec<ll> &min_costs, vec<ll> &buy_costs, vec<vec<ll>> &mixes, int i) {
    if (min_costs[i] != -1) return min_costs[i];

    min_costs[i] = buy_costs[i];
    if (min_costs[i] == 0) return 0;

    if (!mixes[i].empty()) {
        ll mix_cost = 0;
        rep(j, 0, mixes[i].size()) {
            mix_cost += min_cost(min_costs, buy_costs, mixes, mixes[i][j]);
        }
        min_costs[i] = min(min_costs[i], mix_cost);
    }

    return min_costs[i];
}

void solve() {
    ll n, k, tmp;
    cin >> n >> k;

    vec<ll> costs(n);
    vec<vec<ll>> mixes(n);

    rep(i, 0, n) cin >> costs[i];
    rep(i, 0, k) {
        cin >> tmp;
        costs[tmp - 1] = 0; // Input is 1-indexed
    }

    rep(i, 0, n) {
        cin >> tmp;
        mixes[i] = vec<ll>(tmp);

        rep(j, 0, tmp) {
            cin >> mixes[i][j];
            mixes[i][j]--; // Input is 1-indexed
        }
    }

    vec<ll> min_costs(n, -1);
    rep(i, 0, n) cout << min_cost(min_costs, costs, mixes, i) << " ";
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false); // makes io faster, desyncs c-style io (no scanf/printf)
//    cin.tie(nullptr); // unties cin from cout (don't do this if you alternate input/output)

    int tests;
    cin >> tests;
    while (tests--) solve();
}