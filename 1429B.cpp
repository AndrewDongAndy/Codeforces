// October 10, 2020
// https://codeforces.com/contest/1429/problem/B

/*
g++ -D _DEBUG -std=c++11 -Wl,--stack=268435456 -g -Wall -Wfatal-errors 1429B.cpp && a
g++ -D _DEBUG -std=c++11 -Wl,--stack=268435456 -g -Wall -Wfatal-errors 1429B.cpp -ggdb && gdb a

Helping test the servers!
*/


#include <bits/stdc++.h>

using namespace std;


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  freopen("debug_output.txt", "w", stderr);
#endif


  int n, m;
  cin >> n >> m;
  vector<vector<int>> a(n, vector<int>(m));
  vector<int> cntr(n, 0), cntc(m, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char c;
      cin >> c;
      a[i][j] = (c == '*');
      cntr[i] += a[i][j];
      cntc[j] += a[i][j];
    }
  }
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i][j]) {
        ans += (cntr[i] - 1) * (cntc[j] - 1);
      }
    }
  }
  cout << ans << '\n';


  return 0;
}
