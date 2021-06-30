/*
 * author:  ADMathNoob
 * created: 06/27/21 15:25:37
 * problem: https://codeforces.com/gym/103081/problem/G
 */

/*
g++ G.cpp -std=c++11 -D_DEBUG -D_GLIBCXX_DEBUG -Wl,--stack=268435456 -Wall -Wextra -Wfatal-errors -Wshadow -ggdb && gdb a

g++ G.cpp -std=c++11 -D_DEBUG -D_GLIBCXX_DEBUG -Wl,--stack=268435456 -Wall -Wextra -Wfatal-errors -Wshadow -O3


Sneaky bug:
(moved + len[v] >= k)
doesn't do what is expected if len[v] == -1.
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000005;
const int LOG = 21;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  vector<int> tau(N, 1);
  for (int i = 1; i < N; i++) {
    for (int j = i + i; j < N; j += i) {
      tau[j] += 1;
    }
  }
  tau[0] = 0;
  
  int n, k;
  cin >> n >> k;
  vector<int> succ(n);
  for (int i = 0; i < n; i++) {
    succ[i] = (i + tau[i]) % n;
  }

  vector<vector<int>> jump(n, vector<int>(LOG));
  vector<vector<long long>> sum(n, vector<long long>(LOG));
  for (int i = 0; i < n; i++) {
    jump[i][0] = succ[i];
    sum[i][0] = i;
  }
  for (int j = 1; j < LOG; j++) {
    for (int i = 0; i < n; i++) {
      int nxt = jump[i][j - 1];
      jump[i][j] = jump[nxt][j - 1];
      sum[i][j] = sum[i][j - 1] + sum[nxt][j - 1];
    }
  }
  
  vector<int> pos(n, -1);
  vector<int> started(n, -1);
  vector<int> len(n, -1);
  for (int i = 0; i < n; i++) {
    if (started[i] != -1) {
      continue;
    }
    int v = i;
    vector<int> seq;
    while (true) {
      if (started[v] != -1) {
        if (started[v] == i) {
          int L = (int) seq.size() - pos[v];
          for (int z = pos[v]; z < (int) seq.size(); z++) {
            int u = seq[z];
            len[u] = L;
          }
        }
        break;
      }
      started[v] = i;
      pos[v] = (int) seq.size();
      seq.push_back(v);
      v = succ[v];
    }
  }
  
  long long ans = 1e18;
  int best = -1;
  for (int start = 0; start < n; start++) {
    int v = start;
    long long s = 0;
    int moved = 0;
    if (len[v] == -1) {
      for (int j = LOG - 1; j >= 0; j--) {
        if (moved + (1 << j) <= k - 1 && len[jump[v][j]] == -1) {
          s += sum[v][j];
          v = jump[v][j];
          moved += (1 << j);
        }
      }
      assert(len[v] == -1);
      s += v;
      v = jump[v][0];
      moved += 1;
    }
    if (moved == k || (len[v] > 0 && moved + len[v] >= k)) {
      for (int j = LOG - 1; j >= 0; j--) {
        if (moved + (1 << j) <= k) {
          s += sum[v][j];
          v = jump[v][j];
          moved += (1 << j);
        }
      }
      if (s < ans) {
        ans = s;
        best = start;
      }
    }
  }
  if (ans < 1e18) {
    int v = best;
    vector<int> res(k);
    for (int it = 0; it < k; it++) {
      res[it] = v;
      v = succ[v];
    }
    for (int i = 0; i < k; i++) {
      if (i > 0) {
        cout << ' ';
      }
      cout << res[i];
    }
    cout << '\n';
  } else {
    cout << -1 << '\n';
  }
  return 0;
}
