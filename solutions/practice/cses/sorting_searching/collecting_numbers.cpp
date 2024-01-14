#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n;
    cin >> n;
    bitset<200001> s;

    int res = 1;
    rep(i, 0, n) {
        int num;
        cin >> num;

        if (num < n && s[num + 1]) res++;
        s[num] = 1;
    }

    cout << res << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
