// August 18, 2020
// https://codeforces.com/contest/1392/problem/F

/*
s = sum of a[i]
find the integer x such that s >= x + (x + 1) + ... + (x + n - 1)
but s < (x + 1) + (x + 2) + ... + (x + n)

i.e. find the greatest x such that
n / 2 * (2x + n - 1) <= s
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
  
  
  int n;
  cin >> n;
  vector<long long> a(n);
  long long s = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    s += a[i];
  }

  // long long low = 0, high = s;
  // while (low < high) {
  //   long long mid = (low + high + 1) >> 1;
  //   if (mid * 2 + n - 1 <= s * 2 / n) {
  //     low = mid;
  //   } else {
  //     high = mid - 1;
  //   }
  // }
  // s -= (low * 2 + n - 1) * n / 2;
  // for (int i = 0; i < n; i++) {
  //   a[i] = low + i;
  // }
  // for (int i = 0; i < s; i++) {
  //   a[i]++;
  // }

  long long x = (s * 2 - (long long) n * n + n) / (2 * n);
  s -= (x * 2 + n - 1) * n / 2;
  for (int i = 0; i < n; i++) {
    a[i] = x + i + (i < s);
  }

  for (int i = 0; i < n; i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
  
  
  return 0;
}
