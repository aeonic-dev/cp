#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

const ld pi = acos(-1);
const ld sin75 = sin(75 * pi / 180);

void solve() {
    ld r;
    cin >> r;
    ld s = (sin75 * r * 2 + r) * 2;
    cout << setprecision(5) << fixed << s * s << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
