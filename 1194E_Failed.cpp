// July 14, 2019
// https://codeforces.com/contest/1194/problem/E

/*
SOLVE BEFORE CODING ANYTHING OMG
*/


#include <bits/stdc++.h>

using namespace std;


struct Event {
  char d; // direction: 'h' or 'v'
  int x;
  // for d == 'v'
  int y1, y2; // only for d == 'v'
  // for d == 'h'
  char t; // 'b' or 'e': begin or end
  int y;
  int id;
};

bool operator<(const Event &a, const Event &b) {
  if (a.x != b.x) {
    return a.x < b.x;
  }
  return (a.d == 'h' && a.t == 'b') || (b.d == 'h' && b.t == 'e');
}


const int SHIFT = 5000;
const int MAXN = 5000;

int N;
vector<Event> es;
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
  int h = 0, v = 0;
  for (int i = 0; i < N; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x1 += SHIFT;
    y1 += SHIFT;
    x2 += SHIFT;
    y2 += SHIFT;
    if (x1 == x2) {
      Event e;
      e.t = 'v';
      e.x = x1;
      e.y1 = y1;
      e.y2 = y2;
      e.id = v++;
      es.push_back(e);
    } else {
      es.push_back({'h', x1, -1, -1, 'b', y1, h});
      es.push_back({'h', x2, -1, -1, 'e', y1, h});
      h++;
    }
  }
  sort(es.begin(), es.end());
  long long ans = 0;
  vector<int> active(10001, -1);
  for (const Event &e : es) {
    if (e.d == 'h') {
      active[e.y] = (e.t == 'b' ? e.id : -1);
    } else {
      // vertical segment
      for (int i = e.y1; i <= e.y2; i++) {
        if (active[i] != -1) {
          intersects[e.id][active[i]] = 1;
        }
      }
      for (int i = 0; i < e.id; i++) {
        int cnt = (intersects[e.id] ^ intersects[i]).count();
        ans += 1LL * cnt * (cnt - 1) / 2;
      }
    }
  }
  cout << ans << '\n';


  return 0;
}
