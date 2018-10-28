// October 16, 2018
// http://codeforces.com/contest/1019/problem/C

/*
Major fail.
*/


#include <bits/stdc++.h>

using namespace std;


const int MAXN = 1000000;

int N, M;
vector<int> adj[MAXN + 1];
bool accounted[MAXN + 1];
int dist[MAXN + 1];
bool visited[MAXN + 1];
vector<int> order;

void dfs(int s) {
	if (visited[s]) return;
	visited[s] = true;
	for (int u : adj[s]) {
		dfs(u);
	}
	order.push_back(s);
}

void bfs(int x) {
	fill(dist + 1, dist + N + 1, -1);
	queue<int> q;
	dist[x] = 0;
	q.push(x);
	while (!q.empty()) {
		int s = q.front(); q.pop();
		for (auto u : adj[s]) {
			if (accounted[u]) continue;
			accounted[u] = true;
			dist[u] = dist[s] + 1;
			if (dist[u] != 2) q.push(u);
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
#endif // _DEBUG


	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
	}
	for (int i = 1; i <= N; i++) {
		auto &r = adj[i];
		sort(r.begin(), r.end());
		r.erase(unique(r.begin(), r.end()), r.end());
	}
	fill(visited + 1, visited + N + 1, false);
	for (int i = 1; i <= N; i++) {
		dfs(i);
	}
	reverse(order.begin(), order.end());
	vector<int> ans;
	for (int i : order) {
		if (accounted[i]) continue;
		accounted[i] = true;
		ans.push_back(i);
		bfs(i);
	}
	cout << ans.size() << '\n';
	for (int s : ans) cout << s << ' ';
	cout << '\n';


	return 0;
}
