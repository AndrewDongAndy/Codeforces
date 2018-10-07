// October 7, 2018
// http://codeforces.com/problemset/problem/1059/D

/*
I HATE FLOATING-POINT ERRORS!!!

Will fix this later.
*/


#include <bits/stdc++.h>

using namespace std;


struct point {
	int x, y;
};

const long double INF = 1e14;
const int REPS = 200;
const long double EPS = 1e-12;

int N;
vector<point> pts;

bool works(long double r) {
	long double y = r, x = INF;
	for (point &p : pts) {
		if (abs(y - p.y) > r) return false;
		if (p.x > x) continue;

		long double s = sqrt(r - (y - p.y)) * sqrt(r + (y - p.y)) + p.x;
		x = min(x, s);
	}
	for (point &p : pts) {
		if (hypot(x - p.x, y - p.y) > r) return false;
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif // _DEBUG


	cin >> N;
	pts.resize(N);
	int positive = 0, negative = 0, zero = 0;
	for (int i = 0; i < N; i++) {
		point &p = pts[i];
		cin >> p.x >> p.y;
		if (p.y > 0) positive++;
		else if (p.y < 0) negative++;
		else zero++;
	}
	if (zero >= 2 || (positive > 0 && negative > 0)) {
		cout << "-1\n";
		return 0;
	}
	if (positive == 0) {
		for (point &p : pts) {
			p.y = -p.y;
		}
	}
	// binary search the answer
	long double a = 0, b = INF;
	for (int _ = 0; _ < REPS; _++) {
		long double k = (a + b) / 2;
		if (works(k)) {
			b = k;
		}
		else {
			a = k;
		}
	}

	cout.precision(9);
	cout << fixed;
	cout << (a + b) / 2 << '\n';


	return 0;
}
