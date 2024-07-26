// Process the current index
void bfs(int i) {

}

void bfs(vector<vector<bool>> &adj, vector<bool> &visited, int n, int start) {
    queue<int> q;

    q.push(start);
    visited[start] = true;
    bfs(start);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int i = 0; i < n; i++) {
            if (!visited[i] && adj[cur][i]) {
                q.push(i);
                visited[i] = true;
                bfs(i);
            }
        }
    }
}