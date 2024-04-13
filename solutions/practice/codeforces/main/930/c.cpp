#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

bool cmp(int i, int j, char ch = 0) {
    cout << "? " << i << " " << i << " " << j << " " << j << endl;
    cin >> ch;
    return ch == '<';
}

void solve() {
    int n;
    cin >> n;
    vi ind(n), pos(n);
    iota(all(ind), 0);
    sort(all(ind), [&](int i, int j) -> bool { return cmp(i, j); });

    int l2 = (int) log2(n) + 1;
//    cout << l2 << " " << n - l2 << "\n";
    int i = l2 - n;
    if (!(n & (n - 1))) i = 0;

    cout << "! " << ind[i] << " " << ind[n - 1] << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
