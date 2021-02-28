/*
 * author:  ADMathNoob
 * created: 02/28/21 08:33:49
 * problem: https://codeforces.com/contest/1491/problem/C
 */

/*
g++ -D _DEBUG -std=c++11 -Wl,--stack=268435456 -g -Wall -Wfatal-errors 1491C.cpp && a
g++ -D _DEBUG -std=c++11 -Wl,--stack=268435456 -g -Wall -Wfatal-errors 1491C.cpp -ggdb && gdb a
g++ -D _DEBUG -std=c++11 -Wl,--stack=268435456 -O3 -Wall -Wfatal-errors 1491C.cpp && a


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

  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    long long ans = 0;
    while (true) {
      set<int> not1;
      for (int i = 0; i < n; i++) {
        if (a[i] > 1) {
          not1.insert(i);
        }
      }
      if (not1.empty()) {
        break;
      }
      int x = *not1.begin();
      if (a[x] >= n - x) {
        ans += a[x] - (n - x);
        a[x] = n - x;
      }
      while (a[x] > 1) {
        int p = x;
        while (true) {
          auto it = not1.lower_bound(p + a[p]);
          if (a[p] > 1) {
            a[p] -= 1;
          }
          if (it == not1.end()) {
            break;
          }
          p = *it;
        }
        ans += 1;
      }
    }
    cout << ans << '\n';
  }

  return 0;
}
