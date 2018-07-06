// July 5, 2018
// https://codeforces.com/contest/999/problem/E

/*
Apparently you need some topological sort-like method???
*/


#include <bits/stdc++.h>

using namespace std;


const int MAXN = 5000;

int N, M, S;
vector<int> adj[MAXN + 1];
bool visited[MAXN + 1];
bool from_cap[MAXN + 1];
set<int> reachable[MAXN + 1];

void dfs(int s) {
    if (visited[s]) continue;
    visited[s] = true;
    for (int u : adj[s]) {
        dfs(u);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);


    cin >> N >> M >> S;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }


    fill(visited + 1, visited + N + 1, false);
    dfs(S);
    for (int i = 1; i <= N; i++) {
        if (visited[i]) {
            reachable[S].insert(i);
        }
    }

    for (int i = 1; i <= N; i++) {
        if (i == S) continue;
        fill(visited + 1, visited + N + 1, false);
        dfs(i);
        for (int j = 1; j <= N; j++) {
            if (visited[j] && !reachable[S].count(j)) {
                reachable[i].insert(j);
            }
        }
    }

    int ans = 0;
    while ((int) reachable[S].size() < N) {
        int s = 0;
        for (int i = 1; i <= N; i++) {
            if (reachable[i].size() > reachable[s].size()) {
                s = i;
            }
        }

        for (int u : reachable[s]) {
            reachable[S].insert(u);
        }
        reachable[s].clear();

        ans++;
    }

    cout << ans << '\n';

    return 0;
}
