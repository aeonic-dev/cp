#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

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

void print(int mask, int n) {
    for (int i = n - 1; i >= 0; i--) cout << get_bit(mask, i);
    cout << endl;
}

void solve() {
    int n;
    cin >> n;
    int mask = 0;
    print(mask, n);
    rep(i, 1, 1 << n) {
        mask ^= (i & -i);
        print(mask, n);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
