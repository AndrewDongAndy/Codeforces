// July 14, 2019
//

/*

*/


#include <bits/stdc++.h>

using namespace std;


struct Segment {
  int t;
  int x1, y1, x2, y2;
};


const int SHIFT = 5000;
const int MAXC = 10001;
const int MAXN = 5000;


int N;
vector<Segment> hs, vs;
bitset<MAXN> intersects[MAXN];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  freopen("debug_output.txt", "w", stderr);
#endif


  cin >> N;
  for (int i = 0; i < N; i++) {
    Segment s;
    cin >> s.x1 >> s.y1 >> s.x2 >> s.y2;
    s.t = (s.x1 == s.x2 ? 'v' : 'h');
    s.x1 += SHIFT;
    s.y1 += SHIFT;
    s.x2 += SHIFT;
    s.y2 += SHIFT;
    if (s.x1 > s.x2) {
      swap(s.x1, s.x2);
    }
    if (s.y1 > s.y2) {
      swap(s.y1, s.y2);
    }
    if (s.t == 'h') {
      hs.push_back(s);
    } else {
      vs.push_back(s);
    }
  }
  for (int i = 0; i < hs.size(); i++) {
    for (int j = 0; j < vs.size(); j++) {
      Segment &h = hs[i], &v = vs[j];
      if (h.x1 <= v.x1 && v.x1 <= h.x2 && v.y1 <= h.y1 && h.y1 <= v.y2) {
        intersects[i][j] = 1;
      }
    }
  }
  long long ans = 0;
  for (int i = 0; i < hs.size(); i++) {
    for (int j = 0; j < i; j++) {
      int cnt = (intersects[i] & intersects[j]).count();
      ans += 1LL * cnt * (cnt - 1) / 2;
    }
  }
  cout << ans << '\n';


  return 0;
}
