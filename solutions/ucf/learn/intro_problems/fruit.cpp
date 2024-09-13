#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

void solve() {
    int days;
    cin >> days;
    vi sold(days);
    for (int &x: sold) cin >> x;
    
    rep(buy, 0, 1001) {
        int num = 0, max = 0;
        rep(day, 0, days) {
            num += buy;
            num -= sold[day];
            max = ::max(max, num);
            if (num < 0) goto next;
        }
        return void(cout << buy << " " << max << "\n");
        next:;
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
