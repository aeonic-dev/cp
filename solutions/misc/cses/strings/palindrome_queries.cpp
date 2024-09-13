#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

const ll base = 30;
const ll mod = 1e9 + 7;

vec<ll> pwr;
string s;

struct node {
    int lo, hi, len;
    node *left, *right;
    ll ltor, rtol; // left-to-right & right-to-left hashes

    node(int lo, int hi) : lo(lo), hi(hi), len(hi - lo + 1) {
        if (lo == hi) {
            ltor = rtol = s[lo] - 'a' + 1;
            return;
        }

        left = new node(lo, (lo + hi) / 2);
        right = new node((lo + hi) / 2 + 1, hi);
        merge();
    }

    void merge() {
        ltor = (((left->ltor * pwr[right->len]) % mod) + right->ltor) % mod;
        rtol = (((right->rtol * pwr[left->len]) % mod) + left->rtol) % mod;
    }

    void set(int ind, char ch) {
        if (ind < lo || ind > hi) return;
        if (lo == hi) {
            s[ind] = ch; // ind = lo
            ltor = rtol = s[ind] - 'a' + 1;
            return;
        }

        left->set(ind, ch), right->set(ind, ch);
        merge();
    }

    pair<ll, ll> get_ltor(int l, int r) {
        if (l > hi || r < lo) return {0, 0};
        if (l <= lo && r >= hi) return {ltor, len};

        auto resl = left->get_ltor(l, r);
        auto resr = right->get_ltor(l, r);

        return {
                ((resl.first * pwr[resr.second]) % mod + resr.first) % mod,
                resl.second + resr.second
        };
    }

    pair<ll, ll> get_rtol(int l, int r) {
        if (l > hi || r < lo) return {0, 0};
        if (l <= lo && r >= hi) return {rtol, len};

        auto resl = left->get_rtol(l, r);
        auto resr = right->get_rtol(l, r);

        return {
                ((resr.first * pwr[resl.second]) % mod + resl.first) % mod,
                resl.second + resr.second
        };
    }

    bool is_palindrome(int l, int r) {
        auto resltor = get_ltor(l, r);
        auto resrtol = get_rtol(l, r);

        return resltor.first == resrtol.first;
    }
};

void solve() {
    int n, m;
    cin >> n >> m >> s;
    pwr = vec<ll>(n + 1, 1);
    rep(i, 0, n) pwr[i + 1] = (pwr[i] * base) % mod;

    node *st = new node(0, n - 1);
    rep(i, 0, m) {
        int q, l, r;
        string ch;

        cin >> q;
        if (q == 1) {
            cin >> l >> ch;
            st->set(l - 1, ch[0]);
            continue;
        }

        cin >> l >> r;
        if (st->is_palindrome(l - 1, r - 1)) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
