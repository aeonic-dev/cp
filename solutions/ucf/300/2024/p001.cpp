#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

vector<string> res;
bool go(string &str, int n, int k, int i = 0) {
    if (i == n) {
        for (char ch : str) if (ch < 'a' || ch > 'z') return false;
        return res.push_back(str), false;
    }
    if (sz(res) >= 10000) return true;
    
    if (i) {
        if ((int) str[i - 1] + k > (int) 'z') return false;
        for (str[i] = (char) (str[i - 1] + k); str[i] <= 'z'; str[i]++) {
            if (go(str, n, k, i + 1)) return true;
        }
        return false;
    }
    
    for (; str[0] <= 'z'; str[0]++) {
        if (go(str, n, k, 1)) return true;
    }
    return false; // shouldn't get here
}

void solve() {
    int k, n, r;
    cin >> k >> n >> r, k++, r--;
    string str;
    rep(i, 0, n) str += 'a';
    res.clear();
    go(str, n, k);
    sort(all(res)); // don't need this but it makes me feel better
    cout << res[r] << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
