// July 26, 2018
// http://codeforces.com/contest/1011/problem/D

/*
I really don't know why I need to use asked % n during
the binary search; I shouldn't need more than 2 * log2(m)
total queries!

I'll solve this PROPERLY some other time.

TODO: solve this problem properly
*/


#include <bits/stdc++.h>

using namespace std;


int ask(int y) {
	cout << y << endl;
	int resp;
	cin >> resp;
	if (resp == 0) exit(0);
	return resp;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif // _DEBUG)


	int m, n;
	cin >> m >> n;
	vector<int> p(n);
	for (int i = 0; i < n; i++) {
		p[i] = ask(1);
	}

	int lo = 2, hi = m;
	int asked = 0;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		int resp = ask(mid) * p[asked % n];
		asked++;
		if (resp == 1) {
			lo = mid + 1;
		}
		else {
			hi = mid - 1;
		}
	}
	ask(lo);


	return 0;
}
