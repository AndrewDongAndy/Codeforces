// July 16, 2018


#include <bits/stdc++.h>

using namespace std;


const int MAX = 20;


int N, M;
long long K;
long long grid[MAX][MAX];
map<long long, long long> dp[MAX][MAX];


long long solve(int y, int x, long long val) {
	if (y < 0 || x < 0) return 0;
	if (y == 0 && x == 0) return grid[y][x] == val;
	if (dp[y][x].count(val)) return dp[y][x][val];
	dp[y][x][val] += solve(y, x - 1, val ^ grid[y][x]);
	dp[y][x][val] += solve(y - 1, x, val ^ grid[y][x]);
	return dp[y][x][val];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif // _DEBUG)


	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> grid[i][j];
		}
	}

	cout << solve(N - 1, M - 1, K) << '\n';


	return 0;
}
