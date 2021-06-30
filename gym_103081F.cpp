/*
 * author:  ADMathNoob
 * created: 06/27/21 14:20:50
 * problem: https://codeforces.com/gym/103081/problem/F
 */

/*
g++ F.cpp -std=c++11 -D_DEBUG -D_GLIBCXX_DEBUG -Wl,--stack=268435456 -Wall -Wextra -Wfatal-errors -Wshadow -ggdb && gdb a

g++ F.cpp -std=c++11 -D_DEBUG -D_GLIBCXX_DEBUG -Wl,--stack=268435456 -Wall -Wextra -Wfatal-errors -Wshadow -O3



*/

#include <bits/stdc++.h>

using namespace std;

int md;

void add(int& a, const int b) {
  a += b;
  if (a >= md) {
    a -= md;
  }
}

int mul(const int a, const int b) {
  return (int) ((long long) a * b % md);
}

const int N = 2026;

int C[N][N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int r, n;
  cin >> r >> n >> md;
  --r;
  
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
  dp[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int t = 0; t <= i; t++) {
      add(dp[i + 1][t + 1], dp[i][t]); // new leaf
      if (i != r) {
        if (t >= 2) {
          // join two
          add(dp[i + 1][t - 1], mul(dp[i][t], t * (t - 1) / 2));
        }
        if (t >= 1) {
          // add as parent of one
          add(dp[i + 1][t], mul(dp[i][t], t));
        }
      }
    }
  }
  // for (int i = 0; i <= n; i++) {
  //   for (int t = 0; t <= i; t++) {
  //     cerr << dp[i][t] << ' ';
  //   }
  //   cerr << '\n';
  // }
  cout << dp[n][1] << '\n';
  return 0;
}
