// July 14, 2019
//

/*
lol should have just done math only
*/


#include <bits/stdc++.h>

using namespace std;


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  freopen("debug_output.txt", "w", stderr);
#endif


  int k = 9;
  vector<int> v = {1, 2, k};
  const int MAX = 20;
  vector<bool> dp(MAX + 1, false);
  dp[0] = false;
  for (int i = 1; i <= MAX; i++) {
    bool res = false;
    for (int m : v) {
      if (i - m < 0) {
        continue;
      }
      res |= !dp[i - m];
    }
    dp[i] = res;
  }
  for (int i = 0; i <= MAX; i++) {
    cerr << i << " stones is " << (dp[i] ? "winning" : "losing") << '\n';
  }


  return 0;
}
