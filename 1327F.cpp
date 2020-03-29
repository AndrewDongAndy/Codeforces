// March 23, 2020
// https://codeforces.com/contest/1327/problem/F

/*
Cool trick to avoid negative indices: just add another condition!

If my math were stronger, this would be an implementation problem.

Debugged version of my original code: you can see that it's messier without
using this trick: https://codeforces.com/contest/1327/submission/74508629
*/


#include <bits/stdc++.h>

using namespace std;


constexpr int MOD = 998244353;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  freopen("debug_output.txt", "w", stderr);
#endif


  int n, k, m;
  cin >> n >> k >> m;
  n++;
  vector<tuple<int, int, int>> conds;
  conds.emplace_back(0, 0, 0);
  for (int i = 0; i < m; i++) {
    int l, r, x;
    cin >> l >> r >> x;
    conds.emplace_back(l, r, x);
  }
  long long ans = 1;
  for (int b = 0; b < k; b++) {
    vector<int> one(n + 1, 0);
    vector<int> mx(n, 0);
    for (const auto &t : conds) {
      int l, r, x;
      tie(l, r, x) = t;
      if (x & (1 << b)) {
        one[l]++;
        one[r + 1]--;
      } else {
        mx[r] = max(mx[r], l);
      }
    }
    for (int i = 0; i < n; i++) {
      one[i + 1] += one[i];
    }
    vector<long long> psa(n + 1, 0);
    psa[1] = 1;
    int r = 0;
    for (int i = 1; i < n; i++) {
      psa[i + 1] = psa[i];
      if (one[i] == 0) {
        psa[i + 1] += psa[i] - psa[r];
        psa[i + 1] %= MOD;
      }
      r = max(r, mx[i]);
    }
    ans *= psa[n] - psa[r];
    ans %= MOD;
  }
  if (ans < 0) {
    ans += MOD;
  }
  cout << ans << '\n';


  return 0;
}
