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

const ll mod = 1000000007;

void solve() {
    string s;
    cin >> s;
    sort(all(s));
    vec<string> res{s};
    while (next_permutation(all(s))) res.push_back(s);
    cout << res.size() << endl;
    for (auto str : res) cout << str << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
