#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    int res = 0;
    rep(i, 0, n) {
        if (i > 1 && s[i - 2] == 'm' && s[i - 1] == 'a' && s[i] == 'p') {
            s[i] = '\0';
            res++;
        }
        if (i < n - 2 && s[i] == 'p' && s[i + 1] == 'i' && s[i + 2] == 'e') {
            s[i] = '\0';
            res++;
        }
    }
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
