#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

int minRotation(string s) {
    int a=0, N=s.size(); s += s;
    rep(b,0,N) rep(k,0,N) {
            if (a+k == b || s[a+k] < s[b+k]) {b += max(0, k-1); break;}
            if (s[a+k] > s[b+k]) { a = b; break; }
        }
    return a;
}

void solve() {
    string s;
    cin >> s;

    int r = minRotation(s);
    rep(i, r, r + s.size()) {
        cout << s[i % s.size()];
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
