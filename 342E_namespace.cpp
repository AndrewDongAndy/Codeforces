// May 7, 2020
// https://codeforces.com/problemset/problem/342/E

/*

*/


#include <bits/stdc++.h>

using namespace std;


namespace centroid {
  
const int N = 100005;
const int H = 20;

int n;
vector<int> g[N];

int pv[N];
vector<int> order;
int sz[N];
int depth[N];
int aux[N]; // aggregate value to calculate

// data for the centroid tree
int cpv[N];
int cdepth[N];
int dist[N][H]; // dist[v][i]: distance to v's ancestor who has depth i
int f[N][H]; // f[v][i]: the aggregate of v to the parent in centroid tree with depth i

void dfs(int v, int p) {
  pv[v] = p;
  order.push_back(v);
  sz[v] = 1;
  for (int u : g[v]) {
    if (u == p || cdepth[u] != -1) {
      continue;
    }
    depth[u] = depth[v] + 1;
    aux[u] = aux[v] + 1; // HERE: change to calculate what is needed
    dfs(u, v);
    sz[v] += sz[u];
  }
}

void do_dfs_from(int v) {
  depth[v] = 0;
  aux[v] = 0; // HERE: customize
  order.clear();
  dfs(v, -1);
}

int find_centroid(int v) {
  do_dfs_from(v);
  int h = sz[v] / 2;
  for (int u : order) {
    bool ok = (sz[v] - sz[u] <= h);
    for (int to : g[u]) {
      if (to == pv[u] || cdepth[to] != -1) {
        continue;
      }
      ok &= (sz[to] <= h);
    }
    if (ok) {
      return u;
    }
  }
  assert(0);
}

void calculate(int v) {
  do_dfs_from(v);
  int d = cdepth[v];
  for (int i : order) {
    dist[i][d] = depth[i];
    f[i][d] = aux[i];
  }
}

void dfs_cent(int v, int p) {
  // v: the centroid of its current component
  // p: parent in centroid tree
  cpv[v] = p;
  calculate(v);
  for (int u : g[v]) {
    if (cdepth[u] != -1) {
      continue;
    }
    int c = find_centroid(u);
    cdepth[c] = cdepth[v] + 1;
    dfs_cent(c, v);
  }
}

int build_centroid() { // returns the root of the subtree
  fill(cdepth, cdepth + N, -1);
  order.reserve(N);
  int c = find_centroid(0);
  cdepth[c] = 0;
  dfs_cent(c, -1);
}

} // namespace centroid

using namespace centroid;


int best[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  freopen("debug_output.txt", "w", stderr);
#endif


  int m;
  cin >> n >> m;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  build_centroid();
  vector<int> best(n, n);
  function<void(int)> paint = [&](int v) {
    for (int u = v; u != -1; u = cpv[u]) {
      best[u] = min(best[u], dist[v][cdepth[u]]);
    }
  };
  paint(0);
  while (m--) {
    int op, v;
    cin >> op >> v;
    v--;
    if (op == 1) {
      paint(v);
    } else {
      int ans = n;
      for (int u = v; u != -1; u = cpv[u]) {
        ans = min(ans, dist[v][cdepth[u]] + best[u]);
      }
      cout << ans << '\n';
    }
  }


  return 0;
}
