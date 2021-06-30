/*
 * author:  ADMathNoob
 * created: 06/27/21 15:30:35
 * problem: https://codeforces.com/gym/103081/problem/I
 */

/*
g++ I.cpp -std=c++11 -D_DEBUG -D_GLIBCXX_DEBUG -Wl,--stack=268435456 -Wall -Wextra -Wfatal-errors -Wshadow -ggdb && gdb a

g++ I.cpp -std=c++11 -D_DEBUG -D_GLIBCXX_DEBUG -Wl,--stack=268435456 -Wall -Wextra -Wfatal-errors -Wshadow -O3


Read the problem carefully.

Also, a cool property is that, in any connected graph, the radius is at least half of
the diameter. Thus, we can just find the node farthest from some node and output
ceil(log2(d)) + 1 (or something like that).
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100005;
const int M = 100005;

int n, m;
vector<int> g[N];
int from[M], to[M];

bool done[N];
int dist[N];
int que[N];
int beg, endd;

void Bfs(int start) {
  beg = 0;
  endd = 0;
  dist[start] = 0;
  que[beg] = start;
  while (beg <= endd) {
    int v = que[beg++];
    for (int id : g[v]) {
      int u = from[id] ^ to[id] ^ v;
      if (done[u] || dist[u] != -1) {
        continue;
      }
      dist[u] = dist[v] + 1;
      que[++endd] = u;
    }
  }
}

void ResetDist() {
  for (int i = 0; i <= endd; i++) {
    dist[que[i]] = -1;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> from[i] >> to[i];
    --from[i]; --to[i];
    g[from[i]].push_back(i);
    g[to[i]].push_back(i);
  }
  fill(dist, dist + n, -1);
  Bfs(0);
  for (int i = 0; i < n; i++) {
    if (dist[i] == -1) {
      cout << -1 << '\n';
      return 0;
    }
  }
  ResetDist();
  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  random_shuffle(order.begin(), order.end());
  int diam = -1;
  int tries = 0;
  while (tries < n) {
    if (clock() > 5.75 * CLOCKS_PER_SEC) {
      break;
    }
    int start = order[tries];
    Bfs(start);
    diam = max(diam, *max_element(dist, dist + n));
    int far = max_element(dist, dist + n) - dist;
    ResetDist();
    Bfs(far);
    diam = max(diam, *max_element(dist, dist + n));
    ResetDist();
    done[start] = true;
    ++tries;
  }
  if (diam == 1) {
    cout << 1 << '\n';
    return 0;
  }
  cout << (int) floor(log2(diam - 1)) + 1 << '\n';
  // cerr << tries << '\n';
  // cerr << ans << '\n';
  return 0;
}
