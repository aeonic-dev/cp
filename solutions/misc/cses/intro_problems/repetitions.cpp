#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define vec vector
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

void solve() {
    string s;
    cin >> s;
    if (s.size() == 1) {
        cout << 1 << endl;
        return;
    }
    
    int max = 1, num = 1;
    rep(i, 1, s.size()) {
        if (s[i] == s[i - 1]) num++;
        else num = 1;
        max = ::max(max, num);
    }
    cout << max << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
