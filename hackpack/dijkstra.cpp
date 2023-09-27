// vec<vec<pair<int, ll>>> edges(n);
vec<ll> dist(n, LLONG_MAX);
ipq<pair<int, ll>> pq;

int start = 0;
dist[start] = 0;
pq.push({0, start});

while (!pq.empty()) {
    auto cd = pq.top().first;
    auto cur = pq.top().second;
    pq.pop();

    if (cd != dist[cur]) continue;
    for (const pair<int, ll> &e: edges[cur]) {
        if (cd + e.second < dist[e.first]) {
            dist[e.first] = cd + e.second;
            pq.push({dist[e.first], e.first});
        }
    }
}