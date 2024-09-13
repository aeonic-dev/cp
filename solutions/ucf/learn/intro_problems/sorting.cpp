#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

int k = 1;
void solve() {
    int n;
    cin >> n;
    vector<string> names(n);
    rep(i, 0, n) cin >> names[i];
    sort(all(names), [](const string &a, const string &b) {
        for (char ch = 'A'; ch <= 'Z'; ch++) {
            size_t p = count(all(a), ch), q = count(all(b), ch);
            if (p > q) return true;
            if (p < q) return false;
        }
        return true; // ?
    });
    cout << "Class #" << k++ << " ordering\n";
    rep(i, 0, n) cout << names[i] << "\n";
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
