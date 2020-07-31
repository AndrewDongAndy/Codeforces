// July 30, 2020
// https://codeforces.com/contest/1388/problem/E

/*

*/


#include <bits/stdc++.h>

using namespace std;


template <typename T>
class Fraction {
public:
  static constexpr bool AUTO_REDUCE = false;
  
  T num;
  T den;
  
  void normalize() {
    T g = __gcd(num, den);
    num /= g;
    den /= g;
    if (den < 0) {
      num = -num;
      den = -den;
    }
  }
  
  Fraction(const T& _num, const T& _den) : num(_num), den(_den) {
    assert(den != 0);
    if (AUTO_REDUCE) {
      normalize();
    }
  }
  
  Fraction(const T& n) : num(n), den(1) {
  }
  
  Fraction() : num(0), den(1) {
  }
  
  Fraction& operator+=(const Fraction& other) { num = num * other.den + den * other.num; den *= other.den; if (AUTO_REDUCE) normalize(); return *this; }
  Fraction& operator-=(const Fraction& other) { num = num * other.den - den * other.num; den *= other.den; if (AUTO_REDUCE) normalize(); return *this; }
  Fraction& operator*=(const Fraction& other) { num *= other.num; den *= other.den; if (AUTO_REDUCE) normalize(); return *this; }
  Fraction& operator/=(const Fraction& other) { assert(other != 0); num *= other.den; den *= other.num; if (AUTO_REDUCE) normalize(); return *this; }
  template <typename U> Fraction& operator+=(const U& other) { return *this += Fraction(other); }
  template <typename U> Fraction& operator-=(const U& other) { return *this -= Fraction(other); }
  template <typename U> Fraction& operator*=(const U& other) { return *this *= Fraction(other); }
  template <typename U> Fraction& operator/=(const U& other) { return *this /= Fraction(other); }
  Fraction operator-() const { return Fraction(-num, den); }
};

template <typename T> bool operator==(const Fraction<T>& lhs, const Fraction<T>& rhs) { return lhs.num == rhs.num && lhs.den == rhs.den; }
template <typename T, typename U> bool operator==(const Fraction<T>& lhs, U rhs) { return lhs == Fraction<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const Fraction<T>& rhs) { return Fraction<T>(lhs) == rhs; }

template <typename T> bool operator!=(const Fraction<T>& lhs, const Fraction<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const Fraction<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const Fraction<T>& rhs) { return !(lhs == rhs); }

template <typename T> bool operator<(const Fraction<T>& lhs, const Fraction<T>& rhs) { return lhs.num * rhs.den < rhs.num * lhs.den; }
template <typename T> bool operator<=(const Fraction<T>& lhs, const Fraction<T>& rhs) { return lhs.num * rhs.den <= rhs.num * lhs.den; }
template <typename T> bool operator>(const Fraction<T>& lhs, const Fraction<T>& rhs) { return lhs.num * rhs.den > rhs.num * lhs.den; }
template <typename T> bool operator>=(const Fraction<T>& lhs, const Fraction<T>& rhs) { return lhs.num * rhs.den >= rhs.num * lhs.den; }

template <typename T> Fraction<T> operator+(const Fraction<T>& lhs, const Fraction<T>& rhs) { return Fraction<T>(lhs) += rhs; }
template <typename T, typename U> Fraction<T> operator+(const Fraction<T>& lhs, U rhs) { return Fraction<T>(lhs) += rhs; }
template <typename T, typename U> Fraction<T> operator+(U lhs, const Fraction<T>& rhs) { return Fraction<T>(lhs) += rhs; }

template <typename T> Fraction<T> operator-(const Fraction<T>& lhs, const Fraction<T>& rhs) { return Fraction<T>(lhs) -= rhs; }
template <typename T, typename U> Fraction<T> operator-(const Fraction<T>& lhs, U rhs) { return Fraction<T>(lhs) -= rhs; }
template <typename T, typename U> Fraction<T> operator-(U lhs, const Fraction<T>& rhs) { return Fraction<T>(lhs) -= rhs; }

template <typename T> Fraction<T> operator*(const Fraction<T>& lhs, const Fraction<T>& rhs) { return Fraction<T>(lhs) *= rhs; }
template <typename T, typename U> Fraction<T> operator*(const Fraction<T>& lhs, U rhs) { return Fraction<T>(lhs) *= rhs; }
template <typename T, typename U> Fraction<T> operator*(U lhs, const Fraction<T>& rhs) { return Fraction<T>(lhs) *= rhs; }

template <typename T> Fraction<T> operator/(const Fraction<T>& lhs, const Fraction<T>& rhs) { return Fraction<T>(lhs) /= rhs; }
template <typename T, typename U> Fraction<T> operator/(const Fraction<T>& lhs, U rhs) { return Fraction<T>(lhs) /= rhs; }
template <typename T, typename U> Fraction<T> operator/(U lhs, const Fraction<T>& rhs) { return Fraction<T>(lhs) /= rhs; }

template <typename T>
string to_string(const Fraction<T>& f) {
  return to_string(f.num) + " / " + to_string(f.den);
}

using F = Fraction<long long>;



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
  vector<int> xl(n), xr(n), y(n);
  for (int i = 0; i < n; i++) {
    cin >> xl[i] >> xr[i] >> y[i];
  }
  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {
    if (y[i] != y[j]) {
      return y[i] > y[j];
    }
    return xl[i] < xl[j];
  });
  vector<int> pos(n);
  for (int i = 0; i < n; i++) {
    pos[order[i]] = i;
  }
  vector<pair<F, pair<int, int>>> events;
  vector<pair<F, F>> bad;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      int b = order[i];
      int t = order[j];
      if (y[t] == y[b]) {
        continue;
      }
      int dy = y[t] - y[b];
      F m1(xl[b] - xr[t], dy);
      F m2(xr[b] - xl[t], dy);
      bad.emplace_back(m1, m2);
      events.emplace_back(m1, make_pair(-1, -1));
      events.emplace_back(m2, make_pair(b, t));
      // {
      //   F m1(xl[b] - xl[t], dy);
      //   F m2(xr[b] - xl[t], dy);
      //   bad.emplace_back(m1, m2);
      //   events.emplace_back(m2, make_pair(b, t));
      // }
      // {
      //   F m1(xl[b] - xr[t], dy);
      //   F m2(xr[b] - xr[t], dy);
      //   bad.emplace_back(m1, m2);
      //   events.emplace_back(m1, make_pair(-1, -1));
      // }
    }
  }
  events.emplace_back(0, make_pair(-1, -1));
  sort(bad.begin(), bad.end());
  sort(events.begin(), events.end());
  int r = -1;
  for (int i = 0; i < (int) bad.size(); i++) {
    if (r >= 0 && bad[i].first < bad[r].second) {
      bad[r].second = max(bad[r].second, bad[i].second);
    } else {
      bad[++r] = bad[i];
    }
  }
  int p = 0;
  F ans((int) 1e9);
  set<int> left, right;
  left.insert(order[0]);
  right.insert(order[n - 1]);
  for (int eid = 0; eid < (int) events.size(); eid++) {
    const auto& e = events[eid];
    F m = e.first;
    int i, j;
    tie(i, j) = e.second;
    if (i != -1) {
      if (pos[i] == n - 1) {
        right.erase(i);
      }
      if (--pos[i] == 0) {
        left.insert(i);
      }
      if (pos[j] == 0) {
        left.erase(j);
      }
      if (++pos[j] == n - 1) {
        right.insert(j);
      }
      for (int i = 0; i < n; i++) cerr << pos[i] << ' '; cerr << '\n';
    }
    if (eid + 1 < (int) events.size() && events[eid + 1].first == m) {
      continue;
    }
    while (p <= r && m >= bad[p].second) {
      p++;
    }
    if (p > r || m <= bad[p].first) {
      assert((int) left.size() == 1);
      assert((int) right.size() == 1);
      int a = *left.begin();
      int b = *right.begin();
      F x1 = xl[a] + m * y[a];
      F x2 = xr[b] + m * y[b];
      ans = min(ans, x2 - x1);
    }
  }
  cout.precision(10);
  cout << fixed;
  cout << (double) ans.num / ans.den << '\n';
  
  
  return 0;
}
