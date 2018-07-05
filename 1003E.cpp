// July 5, 2018
// https://codeforces.com/contest/1003/problem/E

/*
Didn't solve during the contest. :(

The reason I was MLEing was probably because of my checks
in the dfs (which was previously called add_edges), which
were too precise and were off by one. This resulted in the
recursion going too deep and of course, adding too many
edges which made it MLE.

Obviously, it's nice to know I understand the problem
fully by using precise == checks, but maybe in practice
we should just be less precise and use >= or <=, depending
on the circumstances.
*/


#include <bits/stdc++.h>

using namespace std;


int N, D, K;
int total = 0;
vector< pair<int, int> > edges;


void dfs(int u, int deg, int depth) {
    if (depth == 0 || deg <= 0) return;
    for (int i = 0; i < deg; i++) {
        if (total == N) return;
        int v = ++total;
        edges.push_back({u, v});
        dfs(v, K - 1, depth - 1);
    }
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> N >> D >> K;


    if (N == 1 || D > N - 1) {
        cout << "NO\n";
        return 0;
    }

    if (K == 1) {
        if (N == 2) {
            cout << "YES" << '\n';
            cout << "1 2" << '\n';
        } else {
            cout << "NO" << '\n';
        }
        return 0;
    }


    for (int i = 1; i <= D; i++) {
        edges.push_back({i, i + 1});
    }
    total = D + 1;

    for (int i = 2; i <= D; i++) {
        int depth = min(i - 1, D + 1 - i);
        dfs(i, K - 2, depth);
    }


    if (total == N) {
        cout << "YES\n";
        for (auto e : edges) {
            cout << e.first << ' ' << e.second << '\n';
        }
    } else {
        cout << "NO\n";
    }

    return 0;
}
