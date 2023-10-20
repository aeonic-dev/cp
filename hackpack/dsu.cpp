struct dsu {
    vector<int> par;

    dsu(int n): par(n, -1) {}

    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;

        if (par[a] > par[b]) swap(a, b); // a is larger
        par[a] += par[b];
        par[b] = a;

        return true;
    }

    int find(int s) {
        return par[s] < 0 ? s : par[s] = find(par[s]);
    }

    int count() {
        int num = 0;
        for (auto &p: par) num += p < 0;
        return num;
    }
};