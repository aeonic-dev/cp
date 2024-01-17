#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n;
    string a, b;
    cin >> n >> a >> b;

    int moves = 0;
    int na = 0, nb = 0;
    rep(i, 0, n) {
        bool va = a[i] == '1', vb = b[i] == '1';

        if (va) {
            if (!vb) {
                if (nb) {
                    nb--;
                    moves++;
                } else na++;
            }

            continue;
        }

        if (vb) {
            if (na) {
                na--;
                moves++;
            } else nb++;
        }
    }

    moves += na + nb; // remove leftover cats

    cout << moves << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
