#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

void solve() {
    int n;
    cin >> n;

    rep(a, 0, 26) {
        rep(b, 0, 26) {
            rep(c, 0, 26) {
                if (a + b + c + 3 == n) {
                    cout << (char)(a + 'a') << (char)(b + 'a') << (char)(c + 'a') << '\n';
                    return;
                }
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
