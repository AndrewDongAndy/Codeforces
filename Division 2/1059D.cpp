// October 7, 2018
// http://codeforces.com/problemset/problem/1059/D

/*

*/


#include <bits/stdc++.h>

using namespace std;


struct point {
	int x, y;
};

const int INF = (int) 1e9;
const int PRECISION = 100;

int N;
vector<point> pts;

bool works(double r) {
	double y = r, x = INF;
	for (int i = 0; i < N; i++) {
		point &p = pts[i];
		if (p.x > x) continue;
		if (abs(y - p.y) > r) return false;
		x = min(x, sqrt(pow(r, 2) - pow(y - p.y, 2)) + p.x);
	}
//	cout << "radius " << r << ": place circle at (" << x << ", " << y << ")\n";
	for (int i = 0; i < N; i++) {
		point &p = pts[i];
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
	int m = INF, M = -INF;
	for (int i = 0; i < N; i++) {
		point &p = pts[i];
		cin >> p.x >> p.y;
		if (p.y > 0) positive++;
		else if (p.y < 0) negative++;
		else zero++;
		m = min(m, p.y);
		M = max(M, p.y);
	}
	if (zero >= 2 || (positive > 0 && negative > 0)) {
		cout << "-1\n";
		return 0;
	}
	// binary search the answer
	double a = (positive > 0 ? M / 2 : m / 2), b = INF;
	if (positive == 0) {
		for (point &p : pts) {
			p.y = -p.y;
		}
	}
	for (int _ = 0; _ < PRECISION; _++) {
		double k = (a + b) / 2;
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
