#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

int tc = 1;
void solve() {
    string a, b;
    while (cin >> a >> b, a != "END") {
        sort(all(a)), sort(all(b));
        cout << "Case " << tc++
             << (a == b ? ": same\n" : ": different\n");
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
