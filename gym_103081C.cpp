/*
 * author:  ADMathNoob
 * created: 06/27/21 14:02:27
 * problem: https://codeforces.com/gym/103081/problem/C
 */

/*
g++ C.cpp -std=c++11 -D_DEBUG -D_GLIBCXX_DEBUG -Wl,--stack=268435456 -Wall -Wextra -Wfatal-errors -Wshadow -ggdb && gdb a

g++ C.cpp -std=c++11 -D_DEBUG -D_GLIBCXX_DEBUG -Wl,--stack=268435456 -Wall -Wextra -Wfatal-errors -Wshadow -O3



*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int X, Y;
int n;
double x[N], y[N];

vector<int> g[N];

void Add(int u, int v) {
  g[u].push_back(v);
  g[v].push_back(u);
}

bool Works(double d) {
  // cerr << "checking " << d << '\n';
  for (int i = 0; i < n + 2; i++) {
    g[i].clear();
  }
  for (int i = 0; i < n; i++) {
    if (x[i] <= d || Y - y[i] <= d) {
      Add(n, i);
    }
    if (y[i] <= d || X - x[i] <= d) {
      Add(n + 1, i);
    }
    for (int j = 0; j < i; j++) {
      double dx = x[i] - x[j];
      double dy = y[i] - y[j];
      if (dx * dx + dy * dy <= 4 * d * d) {
        Add(i, j);
      }
    }
  }
  vector<bool> was(n + 2, false);
  vector<int> que(1, n);
  was[n] = true;
  for (int b = 0; b < (int) que.size(); b++) {
    int v = que[b];
    for (int u : g[v]) {
      if (was[u]) {
        continue;
      }
      was[u] = true;
      que.push_back(u);
    }
  }
  return !was[n + 1];
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> X >> Y >> n;
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }
  double low = 0, high = 2e6;
  for (int it = 0; it < 100; it++) {
    double mid = (low + high) / 2;
    if (Works(mid)) {
      low = mid;
    } else {
      high = mid;
    }
  }
  cout << low << '\n';
  return 0;
}
