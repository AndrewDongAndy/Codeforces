/*
 * author:  ADMathNoob
 * created: 07/10/21 14:31:06
 * problem: https://codeforces.com/contest/100015/problem/D
 */

/*
g++ gym_100015D.cpp -std=c++17 -D_DEBUG -D_GLIBCXX_DEBUG -Wl,--stack=268435456 -Wall -Wextra -Wfatal-errors -Wshadow -ggdb && gdb a

g++ gym_100015D.cpp -std=c++17 -D_DEBUG -D_GLIBCXX_DEBUG -Wl,--stack=268435456 -Wall -Wextra -Wfatal-errors -Wshadow -O3



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

template <typename T>
class Graph {
 public:
  struct Edge {
    int from;
    int to;
    T cost;
  };

  vector<Edge> edges;
  vector<vector<int>> g;
  int n;

  function<bool(int)> ignore;

  Graph(int _n) : n(_n) {
    g.resize(n);
    ignore = nullptr;
  }

  virtual int add(int from, int to, T cost) = 0;

  virtual void set_ignore_edge_rule(const function<bool(int)>& f) {
    ignore = f;
  }

  virtual void reset_ignore_edge_rule() {
    ignore = nullptr;
  }
};

template <typename T>
class Digraph : public Graph<T> {
 public:
  using Graph<T>::edges;
  using Graph<T>::g;
  using Graph<T>::n;
  using Graph<T>::ignore;

  Digraph(int _n) : Graph<T>(_n) {
  }

  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = (int) edges.size();
    g[from].push_back(id);
    edges.push_back({from, to, cost});
    return id;
  }

  Digraph<T> reverse() const {
    Digraph<T> rev;
    for (const auto& e : edges) {
      rev.add(e.to, e.from, e.cost);
    }
    if (ignore != nullptr) {
      rev.set_ignore_edge_rule([&](int id) {
        return ignore(id);
      });
    }
    return rev;
  }
};

template <typename T>
vector<int> find_topsort(const Digraph<T>& g) {
  vector<int> deg(g.n, 0);
  for (int id = 0; id < (int) g.edges.size(); id++) {
    if (g.ignore != nullptr && g.ignore(id)) {
      continue;
    }
    deg[g.edges[id].to]++;
  }
  vector<int> x;
  for (int i = 0; i < g.n; i++) {
    if (deg[i] == 0) {
      x.push_back(i);
    }
  }
  for (int ptr = 0; ptr < (int) x.size(); ptr++) {
    int i = x[ptr];
    for (int id : g.g[i]) {
      if (g.ignore != nullptr && g.ignore(id)) {
        continue;
      }
      auto& e = g.edges[id];
      int to = e.to;
      if (--deg[to] == 0) {
        x.push_back(to);
      }
    }
  }
  if ((int) x.size() != g.n) {
    return vector<int>();
  }
  return x;
  // returns an empty vector if the digraph is not a DAG
}

const double EPS = 1e-9;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  while (true) {
    int n, m;
    cin >> n >> m;
    if (n == 0) {
      assert(m == 0);
      break;
    }
    vector<vector<pair<int, double>>> out(n);
    Digraph<double> g(n);
    for (int i = 0; i < m; i++) {
      int u, v, w;
      cin >> u >> v >> w;
      out[u].emplace_back(v, w);
      g.add(u, v);
    }
    vector<int> ts = find_topsort(g);
    for (int i = 0; i < n; i++) {
      int sum = 0;
      for (const auto [v, w] : out[i]) {
        sum += w;
      }
      for (auto& [v, w] : out[i]) {
        w /= sum;
      }
    }
    
    vector<double> dp(n);
    for (int z = n - 1; z >= 0; z--) {
      int v = ts[z];
      dp[v] = 0;
      for (const auto [u, p] : out[v]) {
        dp[v] += p * (1 + dp[u]);
      }
    }
    vector<double> p_visit(n);
    p_visit[0] = 1;
    for (int z = 0; z < n; z++) {
      int v = ts[z];
      for (const auto [u, p] : out[v]) {
        p_visit[u] += p * p_visit[v];
      }
    }
    
    double ans = dp[0];
    debug(ans);
    for (int i = 0; i < n; i++) {
      for (const auto [u, p] : out[i]) {
        if (1 - p < EPS) {
          continue;
        }
        double e = (dp[i] - p * (1 + dp[u])) / (1 - p);
        ans = max(ans, dp[0] + p_visit[i] * (e - dp[i]));
      }
    }
    cout.precision(10);
    cout << fixed;
    cout << ans << '\n';
  }
  return 0;
}
