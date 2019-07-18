// July 17, 2019
//

/*
Nice Mo's algorithm problem, although I don't think it's that fair to require
this much knowledge of obscure stuff such as Minkowski polygon sum. (I had to
search it up here; my intuition was slightly off.)

The idea of Mo's algorithm is to move pointers in a smart way to calculate
all queries offline. We split the array into blocks of size O(sqrt(n)), where
n is the size of the array.

If the left endpoints are in the same block, we process them in order of the
right endpoints. Otherwise, we process them in the order of which block comes
earlier.

We always maintain an active range [l, r] in the array, such that we know the
answer to the query (l, r).

To move from one range to the next, move the right endpoint first, then the
left. This ensures there are no degenerate cases where l > r, because if
they are from the same block, then the right endpoint moves to the right.
Otherwise, if the right endpoint had to move left, then we must have just
crossed between two blocks, meaning the left endpoint had to move to the right.

Here, we need to make sure we don't order by the polygon index, since otherwise
moving an endpoint could take O(MAXV) time, where MAXV = 3e5 is the max number
of total vertices. Instead, we order by vertex index.

Implementation detail: having these functions makes it much shorter:
void add(int i)
void remove(int i)
corresponding to adding and removing the ith element of the array, respectively.

Another weird note: __gcd(x, y) = __gcd(abs(x), abs(y)) * (y / abs(y)),
i.e. __gcd(x, y) has the sign of y. (You can see my debug output tests. :P)

Again, submitting this the next day; hopefully passes lol
*/


#include <bits/stdc++.h>

using namespace std;


struct Point {
  int x, y;
};


struct Query {
  int id;
  int l, r;
  int ans = -1; // -1: unanswered (for debugging)
};


const long long INF = 1e18;
const int MAXN = 100000;
const int MAXQ = 100000;
const int MAXV = 300000;
const int BLOCK_SIZE = 500;


int N, Q;
map< pair<int, int>, int> m;
int e[MAXV];
int id_left[MAXN], id_right[MAXN]; // edge number of first and last edge of ith polygon
Query queries[MAXQ];

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
  int tot = 0;
  for (int i = 0; i < N; i++) {
    int k;
    cin >> k;
    id_left[i] = tot;
    id_right[i] = tot + k - 1;
    vector<Point> p(k);
    for (int j = 0; j < k; j++) {
      cin >> p[j].x >> p[j].y;
    }
    for (int j = 0; j < k; j++) {
      pair<int, int> v = {p[(j + 1) % k].y - p[j].y, p[(j + 1) % k].x - p[j].x};
      int g = __gcd(v.first, v.second);
      g = abs(g);
      v.first /= g;
      v.second /= g;
      if (!m.count(v)) {
        int s = (int) m.size();
        m[v] = s;
      }
      e[tot++] = m[v];
    }
  }
  cin >> Q;
  for (int i = 0; i < Q; i++) {
    Query &q = queries[i];
    q.id = i;
    int l, r;
    cin >> l >> r;
    l--;
    r--;
    q.l = id_left[l];
    q.r = id_right[r];
  }
  sort(queries, queries + Q, [](const Query &a, const Query &b) {
    int ba = a.l / BLOCK_SIZE;
    int bb = b.l / BLOCK_SIZE;
    if (ba != bb) {
      return ba < bb;
    }
    return a.r < b.r;
  });
  int l = 0, r = -1;
  int ans = 0; // distinct elements in range
  vector<int> cnt(m.size(), 0);
  function<void(int)> add = [&](int i) {
    if (cnt[e[i]] == 0) {
      ans++;
    }
    cnt[e[i]]++;
  };
  function<void(int)> remove = [&](int i) {
    cnt[e[i]]--;
    if (cnt[e[i]] == 0) {
      ans--;
    }
  };
  for (int i = 0; i < Q; i++) {
    Query &q = queries[i];
    while (r < q.r) {
      add(++r);
    }
    while (r > q.r) {
      remove(r--);
    }
    while (l > q.l) {
      add(--l);
    }
    while (l < q.l) {
      remove(l++);
    }
    q.ans = ans;
  }
  sort(queries, queries + Q, [](const Query &a, const Query &b) {
    return a.id < b.id;
  });
  for (int i = 0; i < Q; i++) {
    const auto &q = queries[i];
    cout << q.ans << '\n';
  }
  // cerr << "gcd(4, -6) = " << __gcd(4, -6) << '\n';
  // cerr << "gcd(-4, 6) = " << __gcd(-4, 6) << '\n';
  // cerr << "gcd(-4, -6) = " << __gcd(-4, -6) << '\n';


  return 0;
}
