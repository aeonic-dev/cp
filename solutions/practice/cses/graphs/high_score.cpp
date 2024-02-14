#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

const ll inf = LLONG_MAX;

struct Ed { int a, b, w; int s() { return a < b ? a : -a; }};

struct Node { ll dist = inf; int prev = -1; };

void bellmanFord(vector<Node> &nodes, vector<Ed> &eds, int s) {
    nodes[s].dist = 0;
    sort(all(eds), [](Ed a, Ed b) { return a.s() < b.s(); });

    int lim = nodes.size() / 2 + 2; // /3+100 with shuffled vertices
    rep(i, 0, lim) for (Ed ed : eds) {
            Node cur = nodes[ed.a], &dest = nodes[ed.b];
            if (abs(cur.dist) == inf) continue;
            ll d = cur.dist + ed.w;
            if (d < dest.dist) {
                dest.prev = ed.a;
                dest.dist = (i < lim - 1 ? d : -inf);
            }
        }
    rep(i, 0, lim) for (Ed e : eds) {
            if (nodes[e.a].dist == -inf)
                nodes[e.b].dist = -inf;
        }
}

void solve() {
    int n, m;
    cin >> n >> m;

    vec<Node> s(n);
    vec<Ed> adj(m);
    rep(i, 0, m) {
        cin >> adj[i].a >> adj[i].b >> adj[i].w;
        adj[i].a--, adj[i].b--, adj[i].w = 0 - adj[i].w;
    }
    bellmanFord(s, adj, 0);

    if (s.back().dist == -inf) cout << "-1\n";
    else cout << -s.back().dist << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
