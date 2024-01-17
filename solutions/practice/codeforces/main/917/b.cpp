#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n;
    string s;
    cin >> n >> s;
    unordered_set<char> uniq;

    ll num = 0;
    rep(i, 0, s.size()) {
        char ch = s[i];
        if (uniq.count(ch)) continue;
        uniq.insert(ch);

        int m = s.size() - i - 1;
        num += m + 1;
    }

    cout << num << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
