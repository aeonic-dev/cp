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

void solve() {
    ll n, t, q;
    cin >> n;
    vec<ll> nums(30, 0);
    rep(query, 0, n) {
        cin >> t >> q;
        if (t == 1) {
            // ADD
            nums[q]++;
        } else {
            // GET
            vec<ll> n2(nums);
            for (int i = 30; i >= 0; i--) {
                if (get_bit(q, i)) {
                    ll need = 1ll << i;
                    int j = i;
                    while (j >= 0 && need > 0) {
                        ll num = pow(2, j) * n2[j];
                        if (need > num) {
                            n2[j] = 0;
                            need -= num;
                        } else {
                            n2[j] -= sqrt(need);
                            need = 0;
                        }

                        j--;
                    }
                    if (need > 0) {
                        cout << "NO\n";
                        goto next;
                    }
                    n2[j] -= need;
                }
            }
            cout << "YES\n";
            next:;
        }
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
