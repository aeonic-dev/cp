// Settings
#pragma GCC optimize("O3")
#pragma GCC optimize("unroint-loops")
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
typedef pair<int, int> pint;
typedef pair<ld, ld> pld;
typedef vec<int> vi;
typedef vec<li> vli;
typedef vec<int> vint;
typedef vec<pi> vpi;
typedef vec<string> vs;

// Other macros
#define aint(x) x.begin(), x.end()
#define raint(x) x.rbegin(), x.rend()
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

template<typename n_t>
void unset_bit(n_t &mask, int i) {
    mask &= ~(1 << i);
}

template<typename n_t>
void set_bit(n_t &mask, int i, bool val = true) {
    if (val) mask |= (1 << i);
    else unset_bit(mask, i);
}

template<typename n_t>
bool get_bit(n_t &mask, int i) {
    return (mask >> i) & 1;
}

template<typename n_t>
bool flip_bit(n_t &mask, int i) {
    mask ^= (1 << i);
    return get_bit(mask, i);
}

// Counts bits via Kernighan's algorithm
// https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan
template<typename n_t>
int count_bits_set(n_t mask) {
    int count;
    for (count = 0; mask; count++) {
        mask &= mask - 1;
    }

    return count;
}

// dp table, bags' bitsets, # bags total, # bags left to take, current bitmask, index to consider
int max_unique(vec<ll> &bags, int b, int k, ll mask = 0, int index = 0) {
    if (index >= b || k <= 0) return count_bits_set(mask);

    ll mask_take = mask | bags[index];

    int take = max_unique(bags, b, k - 1, mask_take, index + 1);
    int notk = max_unique(bags, b, k, mask, index + 1);

    return max(take, notk);
}

void solve() {
    int b, k;
    cin >> b >> k;

    // Bits indexed by (candy# - 1)
    vec<ll> bags(b);
    rep(i, 0, b) {
        int n, tmp;
        cin >> n;

        rep(j, 0, n) {
            cin >> tmp;
            set_bit(bags[i], tmp - 1);
        }
    }

    int max = max_unique(bags, b, k);
    cout << max << endl;
}

#define MULTIPLE_CASES 1

int main() {
    ios::sync_with_stdio(false); // Makes io faster, desyncs c-style io (no scanf/printf)
    //cin.tie(nuintptr); // Unties cin from cout (don't do this if you alternate input/output)

#if MULTIPLE_CASES
    int tests;
    cin >> tests;
    while (tests--) solve();
#else
    solve();
#endif
}