// July 20, 2019
// https://codeforces.com/contest/1178/problem/E

/*
Literally need to do more math.

THIS SHOULD HAVE BEEN SO EASY WGAT :(((((


Seriously though; tips:

1. Use all of the constraints in the problem! e.g. if we only need to find a
   working answer and they tell you it doesn't have to be optimal (as they do
   here), then use that fact. Don't try to construct the optimal solution,
   because if there were a way to do so, they probably would have asked for
   that as the solution.
2. If something is half of something else, try to find a way to use that fact
   in the solution.
3. If the general solution would be very hard, we probably have to use the
   fact that it's more specific here. For example, I would think that finding
   the longest palindromic subsequence in a general string would be pretty
   hard; so we need to do something with the fact that the alphabet size is 3.
4. Guess what information we can ignore. The fact that no two consecutive
   letters were equal didn't seem to help, so it could be just to throw you off!
   (This usually doesn't apply to math olympiad problems though.)
*/


#include <bits/stdc++.h>

using namespace std;


int n;
string s;
vector<int> v;

void solve(int l, int r) {
  if (l > r) {
    return;
  }
  if (r - l + 1 <= 3) {
    cout << s[l];
    return;
  }
  vector<int> cnt(3, 0);
  cnt[v[l]]++;
  cnt[v[l + 1]]++;
  cnt[v[r]]++;
  cnt[v[r - 1]]++;
  for (int i = 0; i < 3; i++) {
    if (cnt[i] >= 2) {
      cout << (char) ('a' + i);
      solve(l + 2, r - 2);
      cout << (char) ('a' + i);
      return;
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  freopen("debug_output.txt", "w", stderr);
#endif


  cin >> s;
  n = s.size();
  v.resize(n);
  for (int i = 0; i < n; i++) {
    v[i] = s[i] - 'a';
  }
  solve(0, n - 1);


  return 0;
}
