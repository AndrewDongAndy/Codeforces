/*
 * author:  ADMathNoob
 * created: 07/10/21 14:11:57
 * problem: https://codeforces.com/contest/100015/problem/F
 */

/*
g++ gym_100015F.cpp -std=c++17 -D_DEBUG -D_GLIBCXX_DEBUG -Wl,--stack=268435456 -Wall -Wextra -Wfatal-errors -Wshadow -ggdb && gdb a

g++ gym_100015F.cpp -std=c++17 -D_DEBUG -D_GLIBCXX_DEBUG -Wl,--stack=268435456 -Wall -Wextra -Wfatal-errors -Wshadow -O3



*/

#include <bits/stdc++.h>

using namespace std;

// can't have namespaces, else to_string(int) is hidden, for example

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) {
  return '"' + s + '"';
}

string to_string(const char* s) {
  return to_string((string) s);
}

string to_string(const char c) {
  string s = "'";
  s += c;
  s += "'";
  return s;
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
  bool first = true;
  string res = "{";
  for (int i = 0; i < (int) v.size(); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) {
    res += static_cast<char>('0' + v[i]);
  }
  return res;
}

template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto& x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_commas() {
}

template <typename Head, typename... Tail>
void debug_commas(Head H, Tail... T) {
  // comma before each element
  cerr << ", " << to_string(H);
  debug_commas(T...);
}

template <typename Head, typename... Tail>
void debug_better(Head H, Tail... T) {
  cerr << "[" << to_string(H);
  debug_commas(T...);
  cerr << "]" << endl;
}

// print an empty line
void debug_out() {
#ifdef _DEBUG
  cerr << endl;
#endif
}

// can't call debug with no arguments
#ifdef _DEBUG
#define debug(...)                    \
  cerr << "" << #__VA_ARGS__ << ": "; \
  debug_better(__VA_ARGS__)
#else
#define debug(...) 42
#endif

const int E = 18;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  vector<tuple<int, int, int>> T = {
    {3, 5, 7},
    {6, 11, 13},
    {9, 14, 16},
  };
  for (int i = 3; i <= 18; i += 3) {
    T.emplace_back(i - 2, i - 1, i);
  }
  for (auto& [a, b, c] : T) {
    --a; --b; --c;
  }
  debug(T);
  
  vector<int> dp(1 << E);
  for (int mm = (1 << E) - 1; mm >= 0; mm--) {
    if (mm == (1 << E) - 1) {
      dp[mm] = 0;
      continue;
    }
    dp[mm] = -E;
    for (int i = 0; i < E; i++) {
      if (!((mm >> i) & 1)) {
        int new_mm = (mm | (1 << i));
        int add = 0;
        for (const auto [a, b, c] : T) {
          if ((new_mm & (1 << a)) && (new_mm & (1 << b)) && (new_mm & (1 << c))) {
            if (a == i || b == i || c == i) {
              add += 1;
            }
          }
        }
        if (add == 0) {
          dp[mm] = max(dp[mm], add - dp[new_mm]);
        } else {
          dp[mm] = max(dp[mm], add + dp[new_mm]);
        }
      }
    }
  }
  
  while (true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }

    int mm = 0;
    for (int i = 0; i < n; i++) {
      int b;
      cin >> b;
      --b;
      mm |= (1 << b);
    }
    
    cout << (dp[mm] > 0 ? "Andy wins" : dp[mm] < 0 ? "Ralph wins" : "Draw") << '\n';
  }
  return 0;
}
